CREATE TABLE Belediye (
    isim varchar(255) PRIMARY KEY,
    kentsel_donusum int
);

CREATE TABLE Firma (
    firma_ID int PRIMARY KEY,
    firma_adi varchar(255)
);

CREATE TABLE Bina (
    bina_ID int PRIMARY KEY,
    mahalle varchar(255),
    sokak varchar(255),
    temel_tarihi date,
    daire_sayisi int,
    bld_ismi varchar(255),
    donusum_yapilabilir int DEFAULT 0,
    CONSTRAINT fk_bina_bld FOREIGN KEY (bld_ismi) REFERENCES Belediye(isim) ON DELETE NO ACTION ON UPDATE CASCADE
);

CREATE TABLE Ev_Sahipleri (
    daire_no int,
    bina_ID int,
    isim varchar(255),
    kimlik_no int unique not null,
    CONSTRAINT pk_evshp PRIMARY KEY (daire_no, bina_ID),
    CONSTRAINT fk_evshp_bina FOREIGN KEY (bina_ID) REFERENCES Bina(bina_ID) ON DELETE CASCADE ON UPDATE CASCADE
);

CREATE TABLE Odeme (
    daire_no int,
    bina_ID int,
    bld_ismi varchar(255),
    odenen_miktar int,
    odenmesi_gereken_miktar int,
    CONSTRAINT pk_odeme PRIMARY KEY (daire_no, bina_ID, bld_ismi),
    CONSTRAINT fk_odeme FOREIGN KEY (daire_no, bina_ID) REFERENCES Ev_Sahipleri(daire_no, bina_ID) ON DELETE CASCADE
);

CREATE TABLE Yapim (
    bina_ID int,
    firma_ID int,
    yapim_maliyeti int not null,
    yapim_tarihi date,
    CONSTRAINT pk_yapim PRIMARY KEY (bina_ID, firma_ID),
    CONSTRAINT fk_yapim_bina FOREIGN KEY (bina_ID) REFERENCES Bina(bina_ID) ON DELETE CASCADE,
    CONSTRAINT fk_yapim_firma FOREIGN KEY (firma_ID) REFERENCES Firma(firma_ID) ON DELETE CASCADE
 );

CREATE TABLE Yikim (
    bina_ID int,
    firma_ID int,
    yikim_maliyeti int not null, 
    yikim_tarihi date,
    CONSTRAINT pk_yikim PRIMARY KEY (bina_ID, firma_ID),
    CONSTRAINT fk_yikim_bina FOREIGN KEY (bina_ID) REFERENCES Bina(bina_ID) ON DELETE CASCADE,
    CONSTRAINT fk_yikim_firma FOREIGN KEY (firma_ID) REFERENCES Firma(firma_ID) ON DELETE CASCADE
);

CREATE FUNCTION donusum_yapilabilir_check() RETURNS TRIGGER AS $$
DECLARE
	kentsel_donusum NUMERIC;
	ad varchar(255);
BEGIN
SELECT NEW.bld_ismi INTO ad;
SELECT Belediye.kentsel_donusum INTO kentsel_donusum FROM Belediye WHERE ad = Belediye.isim;
IF (NEW.temel_tarihi) < '1980-01-01' AND kentsel_donusum = 1 THEN
	NEW.donusum_yapilabilir = 1;
ELSE
	NEW.donusum_yapilabilir = 0;
END IF;
RETURN NEW;
END;
$$ LANGUAGE plpgsql;

CREATE TRIGGER donusum_yapilabilir_check
BEFORE INSERT OR UPDATE ON Bina
FOR EACH ROW
EXECUTE FUNCTION donusum_yapilabilir_check();

CREATE FUNCTION yapim_yikim_check() RETURNS TRIGGER AS $$
BEGIN
IF (SELECT donusum_yapilabilir FROM Bina WHERE bina_ID = NEW.bina_ID) = 0 THEN
    RAISE EXCEPTION 'Donusum yapilamaz';
	RETURN 0;
END IF;
RETURN NEW;
END;
$$ LANGUAGE plpgsql;

CREATE TRIGGER yapim_check
BEFORE INSERT OR UPDATE ON Yapim
FOR EACH ROW
EXECUTE FUNCTION yapim_yikim_check();

CREATE TRIGGER yikim_check
BEFORE INSERT OR UPDATE ON Yikim
FOR EACH ROW
EXECUTE FUNCTION yapim_yikim_check();

CREATE OR REPLACE FUNCTION binadaki_ev_sahipleri(binaid INT)
RETURNS SETOF VARCHAR
AS $$
DECLARE
    sahipler_cursor CURSOR FOR
    SELECT e.isim FROM Ev_Sahipleri e WHERE e.bina_ID = binaid;
    evsahibi_ismi VARCHAR;
BEGIN
    OPEN sahipler_cursor;
    FETCH NEXT FROM sahipler_cursor INTO evsahibi_ismi;
    WHILE FOUND LOOP
        RETURN NEXT evsahibi_ismi;
        FETCH NEXT FROM sahipler_cursor INTO evsahibi_ismi;
    END LOOP;
    CLOSE sahipler_cursor;
END;
$$ LANGUAGE plpgsql;

CREATE OR REPLACE FUNCTION en_yasli_binayi_sec(belediye_ismi VARCHAR)
RETURNS TABLE (bina_id INTEGER, mahalle VARCHAR, sokak VARCHAR, temel_tarihi DATE, daire_sayisi INTEGER, bld_ismi VARCHAR, donusum_yapilabilir INTEGER)
AS $$
BEGIN
    RETURN QUERY
    SELECT b.bina_ID, b.mahalle, b.sokak, b.temel_tarihi, b.daire_sayisi, b.bld_ismi, b.donusum_yapilabilir
    FROM Bina b
    WHERE b.bld_ismi = belediye_ismi
    ORDER BY b.temel_tarihi
    LIMIT 1;
END;
$$ LANGUAGE plpgsql;


CREATE OR REPLACE FUNCTION yapim_yikim_maliyeti_bul(binaid INT)
RETURNS INTEGER
AS $$
DECLARE
    yapim_ml INTEGER;
    yikim_ml INTEGER;
BEGIN
    SELECT SUM(yapim_maliyeti) INTO yapim_ml
    FROM Yapim
    WHERE bina_ID = binaid;

    SELECT SUM(yikim_maliyeti) INTO yikim_ml
    FROM Yikim
    WHERE bina_ID = binaid;

    RETURN yapim_ml + yikim_ml;
END;
$$ LANGUAGE plpgsql;

CREATE OR REPLACE FUNCTION check_yikim_tarihi()
RETURNS TRIGGER AS $$
BEGIN
    IF (NEW.yikim_tarihi >= (SELECT yapim_tarihi FROM Yapim WHERE NEW.bina_ID = Yapim.bina_ID)) THEN
        RAISE EXCEPTION 'Yikim tarihi yapim tarihinden once olmalidir.';
    END IF;
    RETURN NEW;
END;
$$ LANGUAGE plpgsql;

CREATE TRIGGER tr_yikim_tarihi
BEFORE INSERT OR UPDATE ON Yikim
FOR EACH ROW
EXECUTE FUNCTION check_yikim_tarihi();

CREATE OR REPLACE FUNCTION check_odenen()
RETURNS TRIGGER AS $$
BEGIN
    IF (NEW.odenen_miktar > NEW.odenmesi_gereken_miktar) THEN
        RAISE EXCEPTION 'Ödenen miktar ödenmesi gereken miktardan fazla olamaz.';
    END IF;
    RETURN NEW;
END;
$$ LANGUAGE plpgsql;

CREATE TRIGGER tr_odenen
BEFORE INSERT OR UPDATE ON Odeme
FOR EACH ROW
EXECUTE FUNCTION check_odenen();