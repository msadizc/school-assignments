#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//Mehmet �adi �zcan
//20011037

//Tahtay� olu�turmak i�in yazd���m fonksiyon. Boyut de�i�keni girdi olarak al�n�r ve buna g�re
//tahtan�n ilk halinin memory allocation'� dinamik �ekilde yap�l�r.
char** tahtaOlustur(int boyut) {
    int i, j;
    char** tahta = (char**)malloc(boyut * sizeof(char*));
    if (tahta == NULL) {
        printf("Tahta icin bellek ayrilamadi.");
        exit(1);
    }

    for (i = 0; i < boyut; i++) {
        tahta[i] = (char*)malloc(boyut * sizeof(char));
        if (tahta[i] == NULL) {
            printf("Tahta icin bellek ayrilamadi.");
            exit(1);
        }
    }

    for (i = 0; i < boyut; i++) {
        for (j = 0; j < boyut; j++) {
            tahta[i][j] = 'O';
        }
    }
    return tahta;
}

//Tahta i�in ayr�lan belle�i temizler.
void freeTahta(char** tahta, int boyut) {
    int i;
    for (i = 0; i < boyut; i++) {
        free(tahta[i]);
    }
    free(tahta);
}

//Mevcut bir tahtay� ekrana yazd�rmak i�in yazd���m fonksiyon. 
//hangi eleman�n hangi indiste oldu�unun belli olmas� i�in
//indis numaralar� sa� ve �st kenarda yaz�lm��t�r.
void tahtayiYazdir(char** tahta, int boyut) {
    int i, j;
    printf("    ");
    for (i = 0; i < boyut; i++) {
        printf("%d   ", i);
    }
    printf("\n");
    for (i = 0; i < boyut; i++) {
        printf("----");
    }
    printf("\n");
    for (i = 0; i < boyut; i++) {
        printf("%d | ", i);
        for (j = 0; j < boyut; j++) {
            printf("%c   ", tahta[i][j]);
        }
        printf("\n");
    }
}

//Bo� olarak �retilen tahtaya A,B,C,D,E ve . de�erlerini rastgele �ekilde
//yazan ve oyun ba��nda rastgele �ekilde tahtay� olu�turan fonksiyon.
void tahtayiRenklendir(char** tahta, int boyut) {
    srand(time(0));
    int harf_sayisi = (boyut * boyut + 4) / 5;
    char harfler[5] = {'A', 'B', 'C', 'D', 'E'};
    int tekrar_sayisi[5] = {0, 0, 0, 0, 0};
    int i, j, tmp;

    for (i = 0; i < boyut; i++) {
        for (j = 0; j < boyut; j++) {
            do {
                tmp = rand() % 5;
            } while (tekrar_sayisi[tmp] >= harf_sayisi);

            tahta[i][j] = harfler[tmp];
            tekrar_sayisi[tmp]++;
        }
    }

	// k x k'l�k tahtada k �ift say�ysa ortadaki 4 yeri; k tek say�ysa sadece en ortadaki yeri bo� b�rak�yorum.
    if (boyut % 2 == 0) {
        tahta[(boyut / 2) - 1][(boyut / 2) - 1] = '.';
        tahta[(boyut / 2) - 1][(boyut / 2)] = '.';
        tahta[(boyut / 2)][(boyut / 2) - 1] = '.';
        tahta[(boyut / 2)][(boyut / 2)] = '.';
    } else {
        tahta[(boyut - 1) / 2][(boyut - 1) / 2] = '.';
    }
}

//Oyuncunun yapmak istedi�i bir hamlenin kurallara uygun olup olmad���n� kontrol eden fonksiyon.
//Girdi parametreleri:
//tahta: mevcut oyun tahtas� --- boyut: tahtan�n boyutu
//x, y: hamle yap�lmak istenen ta��n ba�lang�� koordinatlar�
//jump_x, jump_y: z�planarak �zerinden ge�ilecek ta��n koordinatlar�
//empty_x, empty_y: z�plama sonras�nda ta��n yerle�ece�i yeni h�crenin koordinatlar�n� tutacak pointerlar
int hamleGecerliMi(char** tahta, int boyut, int x, int y, int jump_x, int jump_y, int *empty_x, int *empty_y) {
    //Hamle yap�lmak istenen ta��n ve z�planarak �st�nden ge�ilecek ta��n koordinatlar�n�n tahtan�n s�n�rlar� i�inde olup olmad���n� kontrol eder.
    if (x >= 0 && x < boyut && y >= 0 && y < boyut && jump_x >= 0 && jump_x < boyut && jump_y >= 0 && jump_y < boyut) {
        //Hamle yap�lmak istenen h�crelerin bo� olmad���n� kontrol eder.
        if (tahta[x][y] != '.' && tahta[jump_x][jump_y] != '.') {
            //Hamlenin yatay bir hamle olup olmad���n� kontrol eder. (Sa� sol)
            if (x == jump_x && abs(y - jump_y) == 1) {
                //�st�nden z�planacak h�crenin sa��nda veya solunda bo� bir h�cre olup olmad���n� kontrol eder.
                if ((jump_y > y && jump_y + 1 < boyut && tahta[x][jump_y + 1] == '.') || (jump_y < y && jump_y - 1 >= 0 && tahta[x][jump_y - 1] == '.')) {
                    //Z�plama sonras� yerle�ilecek h�crenin koordinatlar�n� belirler.
                    *empty_x = x;
                    *empty_y = (jump_y > y) ? jump_y + 1 : jump_y - 1;
                    return 1; //Hamle ge�erlidir.
                }
            //Hamlenin dikey bir hamle olup olmad���n� kontrol eder (Yukar� a�a��).
            } else if (y == jump_y && abs(x - jump_x) == 1) {
                //�st�nden z�planacak h�crenin yukar�s�nda veya a�a��s�nda bo� bir h�cre olup olmad���n� kontrol eder.
                if ((jump_x > x && jump_x + 1 < boyut && tahta[jump_x + 1][y] == '.') || (jump_x < x && jump_x - 1 >= 0 && tahta[jump_x - 1][y] == '.')) {
                    *empty_x = (jump_x > x) ? jump_x + 1 : jump_x - 1;
                    *empty_y = y;
                    return 1;
                }
            }
        }
    }
    return 0; //Hamle ge�ersizdir.
}

//Tahtada yap�labilecek ge�erli hamle kal�p kalmad���n� kontrol eden fonksiyon.
int gecerliHamleKaldiMi(char** tahta, int boyut) {
    int x, y, empty_x, empty_y;

    for (x = 0; x < boyut; x++) {
        for (y = 0; y < boyut; y++) {
            if (tahta[x][y] != '.') {
                //Yatay hareketleri kontrol eder.
                //x+1 koordinat�n�n tahtan�n s�n�rlar� i�inde olup olmad���, x+1 koordinat�ndaki h�crenin bo� olmad���
                //x+2 koordinat�n�n tahtan�n s�n�rlar� i�inde olup olmad���, x+2 koordinat�ndaki h�crenin bo� oldu�u kontrol edilir.
                //e�er 1 d�nd�r�l�rse yatayda sa�a do�ru yap�labilecek hamle var demektir.
                if (x + 1 < boyut && tahta[x + 1][y] != '.' && x + 2 < boyut && tahta[x + 2][y] == '.') {
                    return 1;
                }
                //x-1 koordinat�n�n tahtan�n s�n�rlar� i�inde olup olmad���, x-1 koordinat�ndaki h�crenin bo� olmad���
                //x-2 koordinat�n�n tahtan�n s�n�rlar� i�inde olup olmad���, x-2 koordinat�ndaki h�crenin bo� oldu�u kontrol edilir.
                //e�er 1 d�nd�r�l�rse yatayda sola do�ru yap�labilecek hamle var demektir.
                if (x - 1 >= 0 && tahta[x - 1][y] != '.' && x - 2 >= 0 && tahta[x - 2][y] == '.') {
                    return 1;
                }
                //A�a��da ayn� i�lemler dikey hareketler i�in kontrol edilir.
				if (y + 1 < boyut && tahta[x][y + 1] != '.' && y + 2 < boyut && tahta[x][y + 2] == '.') {
                    return 1;
                }
                if (y - 1 >= 0 && tahta[x][y - 1] != '.' && y - 2 >= 0 && tahta[x][y - 2] == '.') {
                    return 1;
                }
            }
        }
    }
    return 0; //0 d�nd�r�l�rse tahtada ge�erli hareket kalmam�� ve oyun bitmi� demektir.
}

//Bir ta��n atlama yapt�ktan sonra �oklu atlama yap�p yapamayaca��n� kontrol eder.
int cokluAtlamaKontrol(char** tahta, int boyut, int x, int y) {
    int dx, dy, empty_x, empty_y;
    //dx ve dy ile ta��n kom�ular� kontrol edilir.
    for (dx = -1; dx <= 1; dx++) {
        for (dy = -1; dy <= 1; dy++) {
        	//dx ve dy 0 ise ta��n kendi konumu temsil edildi�i i�in burada kontrol yap�lmayacakt�r.
            if (dx == 0 && dy == 0) continue;
            //belirtilen y�nde ba�ka bir hamle yap�l�p yap�lmayaca�� hamleGecerliMi fonksiyonu �a�r�larak kontrol edilir.
            if (hamleGecerliMi(tahta, boyut, x, y, x + dx, y + dy, &empty_x, &empty_y)) {
                return 1;
            }
        }
    }
    return 0;
}

//Hamle yap�ld���nda tahtadaki de�i�iklikleri yapan fonksiyon.
//de�i�kenler hamleGecerliMi fonksiyonunda a��klanm��t�r.
//ekstra olarak captured_pieces de�i�keni kullan�lm��t�r. Bu de�i�ken oyuncu taraf�ndan yenilen ta�lar� tutan bir karakter dizisini temsil eder.
void makeMove(char** tahta, int x, int y, int jump_x, int jump_y, int empty_x, int empty_y, char* captured_pieces) {
    tahta[empty_x][empty_y] = tahta[x][y];
    captured_pieces[strlen(captured_pieces)] = tahta[jump_x][jump_y];
    tahta[jump_x][jump_y] = '.';
    tahta[x][y] = '.';
}

//Yenilen ta�lardan ka� tam set ve ekstra ta� oldu�unu bularak puan hesaplayan fonksiyon.
//Girdi parametreleri:
//captured: yakalanan ta�lar� tutan karakter dizisi
//set: tam set say�s�n� tutacak pointer
//ekstra: ekstra ta� say�s�n� tutacak pointer
void puanHesapla(char* captured, int* set, int* ekstra) {
    char colors[] = {'A', 'B', 'C', 'D', 'E'};
    int color_count[5] = {0, 0, 0, 0, 0};
    int i, j;

    //Yakalanan ta�lar dizisinde her rengin ka� kez ge�ti�ini sayar.
    for (i = 0; captured[i] != '\0'; i++) {
        for (j = 0; j < 5; j++) {
            if (captured[i] == colors[j]) {
                color_count[j]++;
                break;
            }
        }
    }

    //Tam setleri sayar.
    *set = color_count[0];
    for (i = 1; i < 5; i++) {
        if (color_count[i] < *set) {
            *set = color_count[i];
        }
    }

    //Tam setleri ��kard�ktan sonra kalan ekstra ta� say�s�n� hesaplar.
    *ekstra = 0;
    for (i = 0; i < 5; i++) {
        *ekstra += (color_count[i] - *set);
    }
}

//Oyundaki mevcut puanlar� yazd�r�r.
void mevcutPuaniYazdir(char* player1_captured, char* player2_captured) {
    int player1_sets, player1_extra, player2_sets, player2_extra;

    puanHesapla(player1_captured, &player1_sets, &player1_extra);
    puanHesapla(player2_captured, &player2_sets, &player2_extra);

    printf("Oyuncu 1: %d set, %d ekstra tas (Yenilen taslar: %s)\n", player1_sets, player1_extra, player1_captured);
    printf("Oyuncu 2: %d set, %d ekstra tas (Yenilen taslar: %s)\n", player2_sets, player2_extra, player2_captured);
}

//Oyun sonundaki puanlar� yazd�r�r.
void sonPuaniYazdir(char* player1_captured, char* player2_captured) {
    int player1_sets, player1_extra, player2_sets, player2_extra;

    puanHesapla(player1_captured, &player1_sets, &player1_extra);
    puanHesapla(player2_captured, &player2_sets, &player2_extra);

    printf("Oyuncu 1: %d set, %d ekstra tas (Yenilen taslar: %s)\n", player1_sets, player1_extra, player1_captured);
    printf("Oyuncu 2: %d set, %d ekstra tas (Yenilen taslar: %s)\n", player2_sets, player2_extra, player2_captured);

    if (player1_sets > player2_sets || (player1_sets == player2_sets && player1_extra > player2_extra)) {
        printf("Oyuncu 1 kazandi!\n");
    } else if (player2_sets > player1_sets || (player1_sets == player2_sets && player2_extra > player1_extra)) {
        printf("Oyuncu 2 kazandi!\n");
    } else {
        printf("Oyun berabere!\n");
    }
}

//Tahtay� kopyalamak i�in kullan�l�r.
void tahtayiKopyala(char** src, char** dest, int boyut) {
    int i, j;
    for (i = 0; i < boyut; i++) {
        for (j = 0; j < boyut; j++) {
            dest[i][j] = src[i][j];
        }
    }
}

//Bilgisayar hamlesini hesaplayan fonksiyon.
//Girdi olarak tahta, boyut ve bilgisayar�n yemi� oldu�u ta�lar verilmektedir.
void computerMove(char** tahta, int boyut, char* captured_pieces) {
    int x, y, jump_x, jump_y, empty_x, empty_y;
    //Bilgisayar yapaca�� hamleyi; yapabilece�i rastgele hamleler aras�ndan set tamamlamas� 
    //i�in en �ok ihtiyac� olan hamleyi se�erek yapacakt�r.
	srand(time(0));

    char required_piece = '\0';
    int color_count[5] = {0};
    char colors[5] = {'A', 'B', 'C', 'D', 'E'};
    int i, j;

    //Yenilen ta�lar�n renk say�lar� hesaplan�r
    for (i = 0; captured_pieces[i] != '\0'; i++) {
        for (j = 0; j < 5; j++) {
            if (captured_pieces[i] == colors[j]) {
                color_count[j]++;
                break;
            }
        }
    }

    //Sahip oldu�u ta�lar aras�nda en az sahip oldu�u ta�� bulur ve required_piece de�i�kenine bu rengi atar.
    int min_count = color_count[0];
    required_piece = colors[0];
    for (i = 1; i < 5; i++) {
        if (color_count[i] < min_count) {
            min_count = color_count[i];
            required_piece = colors[i];
        }
    }

    //Buldu�u rastgele hamleler aras�ndan en �ok i�ine yarayacak hamleyi bulmak i�in �e�itli kontroller yapar.
    while (1) {
        x = rand() % boyut;
        y = rand() % boyut;
        if (tahta[x][y] == '.') continue; //Se�ilen rastgele koordinattaki h�cre bo�sa d�ng�n�n ba��na d�n�l�r ve farkl� bir hamle se�ilir.
		int dx, dy;
        for (dx = -1; dx <= 1; dx++) {
            for (dy = -1; dy <= 1; dy++) {
                if (dx == 0 && dy == 0) continue;
                jump_x = x + dx;
                jump_y = y + dy;
                if (hamleGecerliMi(tahta, boyut, x, y, jump_x, jump_y, &empty_x, &empty_y)) {
                    if (tahta[jump_x][jump_y] == required_piece) {
                    	//Buldu�u rastgele hamlelerden birisi ihtiyac� olan ta� ise, bu hamleyi yapar ve fonksiyondan ��k�l�r.
                        makeMove(tahta, x, y, jump_x, jump_y, empty_x, empty_y, captured_pieces);
                        return;
                    }
                }
            }
        }
    }

    //E�er required_piece'i bulmas�na yard�m edecek bir hamle bulamazsa rastgele bir hamle yapar.
    while (1) {
        x = rand() % boyut;
        y = rand() % boyut;
        if (tahta[x][y] == '.') continue;
		int dx, dy;
        for (dx = -1; dx <= 1; dx++) {
            for (dy = -1; dy <= 1; dy++) {
                if (dx == 0 && dy == 0) continue;
                jump_x = x + dx;
                jump_y = y + dy;
                if (hamleGecerliMi(tahta, boyut, x, y, jump_x, jump_y, &empty_x, &empty_y)) {
                    makeMove(tahta, x, y, jump_x, jump_y, empty_x, empty_y, captured_pieces);
                    return;
                }
            }
        }
    }
}

//Oyunu saved_game.txt dosyas�na kaydeder. Kaydedilen bilgiler s�ras�yla: tahta boyutu, bilgisayara kar�� olma durumu, oyuncu s�ras�, tahta durumu ve iki oyuncunun sahip oldu�u ta�lard�r.
void oyunuKaydet(char** tahta, int boyut, int bilgisayaraKarsi, int oyuncuSirasi, char* player1_captured, char* player2_captured) {
    FILE *fp = fopen("saved_game.txt", "w");
    if (fp == NULL) {
        printf("Oyunu kaydederken hata olustu.\n");
        return;
    }
    fprintf(fp, "%d %d %d\n", boyut, bilgisayaraKarsi, oyuncuSirasi);
    int i, j;
    for (i = 0; i < boyut; i++) {
        for (j = 0; j < boyut; j++) {
            fprintf(fp, "%c", tahta[i][j]);
        }
        fprintf(fp, "\n");
    }
    fprintf(fp, "%s\n", player1_captured);
    fprintf(fp, "%s\n", player2_captured);
    fclose(fp);
    printf("Oyun kaydedildi.\n");
}

//saved_game.txt dosyas�ndaki verileri okuyarak oyun olu�turur.
int kayittanYukle(char*** tahta, int* boyut, int* bilgisayaraKarsi, int* oyuncuSirasi, char* player1_captured, char* player2_captured) {
    FILE *fp = fopen("saved_game.txt", "r");
    if (fp == NULL) {
        printf("Kayitli oyun bulunamadi.\n");
        return 0;
    }
    fscanf(fp, "%d %d %d", boyut, bilgisayaraKarsi, oyuncuSirasi);
    *tahta = tahtaOlustur(*boyut);
    int i, j;
    for (i = 0; i < *boyut; i++) {
        for (j = 0; j < *boyut; j++) {
            fscanf(fp, " %c", &(*tahta)[i][j]);
        }
    }
    fscanf(fp, "%s", player1_captured);
    fscanf(fp, "%s", player2_captured);
    fclose(fp);
    printf("Oyun kayittan yuklenmistir.\n");
    return 1;
}

//Oyun i�ini y�neten fonksiyon:
//Girdi olarak tahta, boyut, bilgisayar kar�� olma durumu, oyuncu s�ras� ve elde edilen ta�lar al�n�r.
void Oyun(char** tahta, int boyut, int bilgisayaraKarsi, int oyuncuSirasi, char* player1_captured, char* player2_captured) {
    int oyunSonu = 0;								//Oyunun devam edip etmedi�ini temsil eden de�i�ken
    char previous_player1_captured[50] = "";		//1.ve 2.oyuncular�n yedi�i ta�lar� g�steren diziler.
    char previous_player2_captured[50] = "";
    char** eski_tahta = tahtaOlustur(boyut);		//Hamle yap�lmadan �nceki tahtay� tutar.
    int current_x, current_y;						//Mevcut hamle koordinatlar�
    int ilk_hamle = 1;								//Ayn� ta�la �oklu hamle yap�labilece�i durumlarda hamlenin yap�lan ilk hamle mi yoksa sonraki hamlelerden mi oldu�unu belirtir.

    printf("Skippity oyunu basliyor.\n");

    while (!oyunSonu) {
        if (!bilgisayaraKarsi) {
            system("cls"); //Bilgisayara kar�� oynanmayan durumda ekran� temizler. Bilgisayara kar�� oyun modunda bilgisayar hamle yapt�ktan hemen sonra tahta yenilendi�i ve bilgisayar�n yapt���
        }					//hamle tam olarak anla��lmad��� i�in ekran� temizlememeyi tercih ettim.

        printf("Mevcut Tahta:\n");
        tahtayiYazdir(tahta, boyut);

        if (!gecerliHamleKaldiMi(tahta, boyut)) {
            printf("Yapilacak baska hamle kalmadi!\n");
            break;
        }

        int x, y, jump_x, jump_y, empty_x, empty_y;

        if (bilgisayaraKarsi && oyuncuSirasi == 2) {
            computerMove(tahta, boyut, player2_captured);
            printf("Bilgisayar bir hamle yapti.\n");
            oyuncuSirasi = 1;
            ilk_hamle = 1;
        } else {
            //Oyuncunun s�ras�
            if (ilk_hamle) {
                printf("Sira Oyuncu %d'de:\n", oyuncuSirasi);
                printf("Hangi tasi hareket ettirmek istiyorsunuz (satir sutun): ");
                scanf("%d %d", &x, &y);
            } else {
                x = current_x;
                y = current_y;
            }

            printf("Hangi tasi yemek istiyorsunuz (satir sutun): ");
            scanf("%d %d", &jump_x, &jump_y);

            if (hamleGecerliMi(tahta, boyut, x, y, jump_x, jump_y, &empty_x, &empty_y)) {
                //Undo yap�labilece�i i�in mevcut durum kaydedilir
                tahtayiKopyala(tahta, eski_tahta, boyut);
                strcpy(previous_player1_captured, player1_captured);
                strcpy(previous_player2_captured, player2_captured);
				//Hamle ger�ekle�tirilir.
                if (oyuncuSirasi == 1) {
                    makeMove(tahta, x, y, jump_x, jump_y, empty_x, empty_y, player1_captured);
                } else {
                    makeMove(tahta, x, y, jump_x, jump_y, empty_x, empty_y, player2_captured);
                }
                current_x = empty_x;
                current_y = empty_y;
                printf("Gecerli hamle.\n");

                //Sonu�lar� yazd�r�r.
                mevcutPuaniYazdir(player1_captured, player2_captured);

                //Undo yap�lmak istenip istenmedi�i kullan�c�ya sorulur
                char undo;
                printf("Hamleyi geri almak istiyor musunuz? (e/h): ");
                scanf(" %c", &undo);
                if (undo == 'e' || undo == 'E') {
                    //Bir �nceki duruma d�n�l�r.
                    tahtayiKopyala(eski_tahta, tahta, boyut);
                    strcpy(player1_captured, previous_player1_captured);
                    strcpy(player2_captured, previous_player2_captured);
                    printf("Hamle geri alindi.\n");
                    printf("Yeni bir hamle yapmalisiniz.\n");
                    continue;
                }

                //Kullan�c�n�n oyunu kaydetmek isteyip istemedi�i sorulur.
                char save;
                printf("Oyunu kaydetmek istiyor musunuz? (e/h): ");
                scanf(" %c", &save);
                if (save == 'e' || save == 'E') {
                    oyunuKaydet(tahta, boyut, bilgisayaraKarsi, oyuncuSirasi, player1_captured, player2_captured);
                    continue;
                }
				//�oklu atlama kontrol� yap�l�r ve b�yle bir durum mevcutsa kullan�c�ya ayn� ta�la ba�ka bir hamle yapt�r�l�r.
                if (!cokluAtlamaKontrol(tahta, boyut, current_x, current_y)) {
                    oyuncuSirasi = (oyuncuSirasi == 1) ? 2 : 1;
                    ilk_hamle = 1;
                } else {
                    ilk_hamle = 0;
                    printf("Ayni tasla baska bir hamle yapabilirsiniz.\n");
                    tahtayiYazdir(tahta, boyut);
                }
            } else {
                printf("Gecersiz hamle. Tekrar deneyin.\n");
            }
        }
    }

    system("cls");
    printf("Oyun Sonunda Tahta:\n");
    tahtayiYazdir(tahta, boyut);
    sonPuaniYazdir(player1_captured, player2_captured);
    freeTahta(eski_tahta, boyut);
}

int main() {
    int boyut, oyun_modu, kayittan_devam;
    char player1_captured[50] = "";
    char player2_captured[50] = "";
    int bilgisayaraKarsi = 0;
    int oyuncuSirasi = 1;
    char** tahta;

    printf("Oyun modunu seciniz:\n1. Yeni Oyun\n2. Kaydedilmis Oyunu Yukle\nSeciminiz: ");
    scanf("%d", &kayittan_devam);

    if (kayittan_devam == 1) {
        printf("Oyun modunu seciniz:\n1. Insana karsi\n2. Bilgisayara karsi\nSeciminiz: ");
        scanf("%d", &oyun_modu);

        if (oyun_modu == 2) {
            bilgisayaraKarsi = 1;
        } else {
            bilgisayaraKarsi = 0;
        }
        
        printf("Tahtanin boyutunu giriniz: ");
        scanf("%d", &boyut);

        tahta = tahtaOlustur(boyut);
        tahtayiRenklendir(tahta, boyut);
    } else if (kayittan_devam == 2) {
        if (!kayittanYukle(&tahta, &boyut, &bilgisayaraKarsi, &oyuncuSirasi, player1_captured, player2_captured)) {
            return 1;
        }
    } else {
        printf("Gecersiz secim.\n");
        return 1;
    }

    printf("\nBaslangic Tahtasi:\n");
    tahtayiYazdir(tahta, boyut);
    Oyun(tahta, boyut, bilgisayaraKarsi, oyuncuSirasi, player1_captured, player2_captured);

    freeTahta(tahta, boyut);
    return 0;
}

