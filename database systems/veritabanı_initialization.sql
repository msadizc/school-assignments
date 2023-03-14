INSERT INTO Belediye VALUES 
  ('Mesudiye Belediyesi',1);

INSERT INTO Belediye VALUES 
  ('Akçadağ Belediyesi',1);

INSERT INTO Belediye VALUES 
  ('Şişli Belediyesi',0);

CREATE SEQUENCE firma_seq
MINVALUE 1
MAXVALUE 99
INCREMENT BY 1

INSERT INTO Firma VALUES 
  (nextval('firma_seq'),'Kalyon Grup');

INSERT INTO Firma VALUES 
  (nextval('firma_seq'),'Limak Holding');

INSERT INTO Firma VALUES 
  (nextval('firma_seq'),'Cengiz Holding');

CREATE SEQUENCE bina_seq
MINVALUE 1
MAXVALUE 99
INCREMENT BY 1

INSERT INTO Bina VALUES 
    (nextval('bina_seq'),'Cumhuriyet','Hürriyet','1985-04-17',5,'Şişli Belediyesi');
INSERT INTO Bina VALUES 
    (nextval('bina_seq'),'Cumhuriyet','Yenice','1990-05-20',4,'Şişli Belediyesi');
INSERT INTO Bina VALUES 
    (nextval('bina_seq'),'Yeniağaç','Cumhuriyet','1932-06-25',3,'Şişli Belediyesi');
INSERT INTO Bina VALUES 
    (nextval('bina_seq'),'Yeniağaç','Gazi Mustafa Kemal','2000-07-30',2,'Şişli Belediyesi');
INSERT INTO Bina VALUES 
    (nextval('bina_seq'),'Karaaslan','Cumhuriyet','2005-08-15',3,'Şişli Belediyesi');
INSERT INTO Bina VALUES 
    (nextval('bina_seq'),'Vefa','Cumhuriyet','1967-10-15',5,'Şişli Belediyesi');
INSERT INTO Bina VALUES 
    (nextval('bina_seq'),'Dedeoğlu','Kaldırım','1985-04-17',2,'Mesudiye Belediyesi');
INSERT INTO Bina VALUES 
    (nextval('bina_seq'),'Dedeoğlu','Tütün','1969-05-20',3,'Mesudiye Belediyesi');
INSERT INTO Bina VALUES 
    (nextval('bina_seq'),'Hamidiye','Çamlık','1995-06-25',4,'Mesudiye Belediyesi');
INSERT INTO Bina VALUES 
    (nextval('bina_seq'),'Hamidiye','Çamlık','1977-07-30',5,'Mesudiye Belediyesi');
INSERT INTO Bina VALUES 
    (nextval('bina_seq'),'Sırma','Sütun','1943-08-15',2,'Mesudiye Belediyesi');
INSERT INTO Bina VALUES 
    (nextval('bina_seq'),'Sırma','Paşa','1956-09-20',3,'Mesudiye Belediyesi');
INSERT INTO Bina VALUES 
    (nextval('bina_seq'),'Bentbaşı','Özal','1965-07-13', 3, 'Akçadağ Belediyesi');
INSERT INTO Bina VALUES 
    (nextval('bina_seq'),'Taştepe','İnönü','1987-04-13', 4, 'Akçadağ Belediyesi');
INSERT INTO Bina VALUES 
    (nextval('bina_seq'),'Kiltepe','Ronaldo','1977-05-22', 5, 'Akçadağ Belediyesi');
INSERT INTO Bina VALUES 
    (nextval('bina_seq'),'Bentbaşı','Paşa','1976-07-08', 2, 'Akçadağ Belediyesi');
INSERT INTO Bina VALUES 
    (nextval('bina_seq'),'Taştepe','Fıstık','2005-10-04', 3, 'Akçadağ Belediyesi');
INSERT INTO Bina VALUES 
    (nextval('bina_seq'),'Kiltepe','Kayısı','1978-02-25', 4, 'Akçadağ Belediyesi');
INSERT INTO Bina VALUES 
    (nextval('bina_seq'),'Bentbaşı','Paşa','1976-04-12', 2, 'Akçadağ Belediyesi');
INSERT INTO Bina VALUES 
    (nextval('bina_seq'),'Ekşere','Gölbaşı','1962-12-03', 1, 'Mesudiye Belediyesi');

INSERT INTO Ev_Sahipleri (daire_no, bina_ID, isim, kimlik_no) VALUES
    (1, 1, 'Ahmet Demir', 78901),
    (2, 1, 'Mehmet Ali', 27812),
    (3, 1, 'Selin Kaya', 31563),
    (4, 1, 'Ege Tan', 45214),
    (5, 1, 'Emre Can', 56715),
    (1, 2, 'Gizem Yılmaz', 67156),
    (2, 2, 'Mert Güler', 78967),
    (3, 2, 'Alper Çakır', 85078),
    (4, 2, 'Caner Yılmaz', 12080),
    (1, 3, 'Ayşegül Yıldırım', 22011),
    (2, 3, 'Aslıhan Kaya', 34129),
    (3, 3, 'Gökhan Yıldırım', 62357),
    (1, 4, 'Aysun Kılıç', 78965),
    (2, 4, 'Gökhan Öztürk', 89004),
    (1, 5, 'Sevilay Kılınç', 90183),
    (2, 5, 'Emre Kılıç', 12342),
    (3, 5, 'Can Kılıç', 12302),
    (1, 6, 'Sevil Çelik', 90783),
    (2, 6, 'Doğukan Kahya', 90483),
    (3, 6, 'Kemal Kulak', 90083),
    (4, 6, 'Suzan Kestane', 90683),
    (5, 6, 'Tarık Şeker', 95683),
    (1, 7, 'Mehmet Ali Engin', 23012),
    (2, 7, 'Batıkan Mahya', 34684),
    (1, 8, 'Egehan Tan', 45036),
    (2, 8, 'Fatma Canoğlu', 16145),
    (3, 8, 'Erdeniz Yılmaz', 61556),
    (1, 9, 'Mert Güler', 48617),
    (2, 9, 'Alperen Çakar', 19078),
    (3, 9, 'Mahmut Şamil Özgen', 96789),
    (4, 9, 'Baran Yılkan', 1174),
    (1, 10, 'Tayfun Kahveci', 18412),
    (2, 10, 'Ayhan Manço', 34123),
    (3, 10, 'Kerim Aslan', 45234),
    (4, 10, 'Türkan Aykan', 52345),
    (5, 10, 'Gökmen Yılmaz', 61756),
    (1, 11, 'Aykan Yıldıran', 76567),
    (2, 11, 'Ayten Gören', 18357),
    (1, 12, 'Ayan Bilge', 16867),
    (2, 12, 'Torun Kalay', 15207),
    (3, 12, 'Muharrem Keleş', 18967),
    (1, 13, 'Samuel Demir', 11523),
    (2, 13, 'Micheak Ali', 45048),
    (3, 13, 'Tom Kaya', 56745),
    (1, 14, 'Emily Tan', 67893),
    (2, 14, 'Paris Can', 78767),
    (3, 14, 'Elizabeth Yılmaz', 17578),
    (4, 14, 'Elizabeth Güler', 90689),
    (1, 15, 'Tom Sawyer', 12306),
    (2, 15, 'Enner Özkan', 23912),
    (3, 15, 'Hagi Yılmaz', 34523),
    (4, 15, 'Perez Yıldırım', 45414),
    (5, 15, 'Sinan Kaya', 56735),
    (1, 16, 'Ercan Arslan', 62356),
    (2, 16, 'Muharrem Ay', 78117),
    (1, 17, 'Osman Yıldırım', 89078),
    (2, 17, 'Şadi Ay', 78907),
    (3, 17, 'Fatih Yıldırım', 89188),
    (1, 18, 'Fazliç Ay', 78947),
    (2, 18, 'Yıldım Yıldırım', 89478),
    (3, 18, 'Güneş Ay', 18367),
    (4, 18, 'Zeus Yıldırım', 89648),
    (1, 19, 'Kemalettin Kırdagezen', 69176),
    (2, 19, 'Cemal Çarmık', 16923),
    (1, 20, 'Hüseyin Zurnaçalan', 28792);

INSERT INTO Yapim (bina_ID, firma_ID, yapim_maliyeti, yapim_tarihi) VALUES
    (8, 3, 212000, '2028-01-02'),
    (10, 1, 265500, '2022-07-05'),
    (11, 3, 225000, '2025-06-02'),
    (12, 3, 455000, '2023-12-21'),
    (13, 1, 300000, '2024-07-06'),
    (15, 2, 156000, '2023-09-03'),
    (16, 1, 852000, '2025-12-13'),
    (18, 3, 312000, '2023-07-12'),
    (19, 1, 152000, '2028-03-16'),
    (20, 2, 612000, '2040-12-02');


INSERT INTO Yikim (bina_ID, firma_ID, yikim_maliyeti, yikim_tarihi) VALUES
    (8, 3, 212000, '2020-02-03'),
    (10, 1, 265500, '2021-02-12'),
    (11, 3, 225000, '2021-03-14'),
    (12, 3, 455000, '2021-11-17'),
    (13, 1, 300000, '2021-02-04'),
    (15, 2, 156000, '2020-06-27'),
    (16, 1, 852000, '2019-11-13'),
    (18, 3, 312000, '2017-04-12'),
    (19, 1, 100000, '2026-03-16'),
    (20, 2, 110000, '2039-12-02');

INSERT INTO Odeme (daire_no, bina_ID, bld_ismi, odenen_miktar, odenmesi_gereken_miktar) VALUES
    (1, 3, 'Şişli Belediyesi', 32000,50000),
    (2, 3, 'Şişli Belediyesi', 15000,38000),
    (3, 3, 'Şişli Belediyesi', 31000,50000),
    (1, 6, 'Şişli Belediyesi', 8000,38000),
    (2, 6, 'Şişli Belediyesi', 4000,28000),
    (3, 6, 'Şişli Belediyesi', 21000,50000),
    (4, 6, 'Şişli Belediyesi', 16000,43000),
    (5, 6, 'Şişli Belediyesi', 2000,35500),
    (1, 8, 'Şişli Belediyesi', 8500,32000),
    (2, 8, 'Şişli Belediyesi', 40000,45000),
    (3, 8, 'Şişli Belediyesi', 1000,43550),
    (1, 10, 'Mesudiye Belediyesi', 5500,42500),
    (2, 10, 'Mesudiye Belediyesi', 2870,50000),
    (3, 10, 'Mesudiye Belediyesi', 32000,34000),
    (4, 10, 'Mesudiye Belediyesi', 7000,42500),
    (5, 10, 'Mesudiye Belediyesi', 1000,41000),
    (1, 11, 'Mesudiye Belediyesi', 21000, 50000),
    (2, 11, 'Mesudiye Belediyesi', 18000, 30000),
    (1, 12, 'Mesudiye Belediyesi', 12000, 23000),
    (2, 12, 'Mesudiye Belediyesi', 20000, 40000),
    (3, 12, 'Mesudiye Belediyesi', 3000, 10000),
    (1, 13, 'Akçadağ Belediyesi', 16500, 33000),
    (2, 13, 'Akçadağ Belediyesi', 14200, 25000),
    (3, 13, 'Akçadağ Belediyesi', 17300, 27000),
    (1, 15, 'Akçadağ Belediyesi', 4500, 13000),
    (2, 15, 'Akçadağ Belediyesi', 500, 20000),
    (3, 15, 'Akçadağ Belediyesi', 1000, 10000),
    (4, 15, 'Akçadağ Belediyesi', 12000, 35000),
    (5, 15, 'Akçadağ Belediyesi', 34000, 34000),
    (1, 16, 'Akçadağ Belediyesi', 35000, 50000),
    (2, 16, 'Akçadağ Belediyesi', 18000, 45000),
    (1, 18, 'Akçadağ Belediyesi', 2000, 20000),
    (2, 18, 'Akçadağ Belediyesi', 9000, 15000),
    (3, 18, 'Akçadağ Belediyesi', 13200, 15000),
    (4, 18, 'Akçadağ Belediyesi', 14500, 20000),
    (1, 19, 'Akçadağ Belediyesi', 5500, 11000),
    (2, 19, 'Akçadağ Belediyesi', 9500, 13000),
    (1, 20, 'Mesudiye Belediyesi', 10200, 18000);