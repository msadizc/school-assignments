#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//Mehmet Þadi Özcan
//20011037

//Tahtayý oluþturmak için yazdýðým fonksiyon. Boyut deðiþkeni girdi olarak alýnýr ve buna göre
//tahtanýn ilk halinin memory allocation'ý dinamik þekilde yapýlýr.
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

//Tahta için ayrýlan belleði temizler.
void freeTahta(char** tahta, int boyut) {
    int i;
    for (i = 0; i < boyut; i++) {
        free(tahta[i]);
    }
    free(tahta);
}

//Mevcut bir tahtayý ekrana yazdýrmak için yazdýðým fonksiyon. 
//hangi elemanýn hangi indiste olduðunun belli olmasý için
//indis numaralarý sað ve üst kenarda yazýlmýþtýr.
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

//Boþ olarak üretilen tahtaya A,B,C,D,E ve . deðerlerini rastgele þekilde
//yazan ve oyun baþýnda rastgele þekilde tahtayý oluþturan fonksiyon.
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

	// k x k'lýk tahtada k çift sayýysa ortadaki 4 yeri; k tek sayýysa sadece en ortadaki yeri boþ býrakýyorum.
    if (boyut % 2 == 0) {
        tahta[(boyut / 2) - 1][(boyut / 2) - 1] = '.';
        tahta[(boyut / 2) - 1][(boyut / 2)] = '.';
        tahta[(boyut / 2)][(boyut / 2) - 1] = '.';
        tahta[(boyut / 2)][(boyut / 2)] = '.';
    } else {
        tahta[(boyut - 1) / 2][(boyut - 1) / 2] = '.';
    }
}

//Oyuncunun yapmak istediði bir hamlenin kurallara uygun olup olmadýðýný kontrol eden fonksiyon.
//Girdi parametreleri:
//tahta: mevcut oyun tahtasý --- boyut: tahtanýn boyutu
//x, y: hamle yapýlmak istenen taþýn baþlangýç koordinatlarý
//jump_x, jump_y: zýplanarak üzerinden geçilecek taþýn koordinatlarý
//empty_x, empty_y: zýplama sonrasýnda taþýn yerleþeceði yeni hücrenin koordinatlarýný tutacak pointerlar
int hamleGecerliMi(char** tahta, int boyut, int x, int y, int jump_x, int jump_y, int *empty_x, int *empty_y) {
    //Hamle yapýlmak istenen taþýn ve zýplanarak üstünden geçilecek taþýn koordinatlarýnýn tahtanýn sýnýrlarý içinde olup olmadýðýný kontrol eder.
    if (x >= 0 && x < boyut && y >= 0 && y < boyut && jump_x >= 0 && jump_x < boyut && jump_y >= 0 && jump_y < boyut) {
        //Hamle yapýlmak istenen hücrelerin boþ olmadýðýný kontrol eder.
        if (tahta[x][y] != '.' && tahta[jump_x][jump_y] != '.') {
            //Hamlenin yatay bir hamle olup olmadýðýný kontrol eder. (Sað sol)
            if (x == jump_x && abs(y - jump_y) == 1) {
                //Üstünden zýplanacak hücrenin saðýnda veya solunda boþ bir hücre olup olmadýðýný kontrol eder.
                if ((jump_y > y && jump_y + 1 < boyut && tahta[x][jump_y + 1] == '.') || (jump_y < y && jump_y - 1 >= 0 && tahta[x][jump_y - 1] == '.')) {
                    //Zýplama sonrasý yerleþilecek hücrenin koordinatlarýný belirler.
                    *empty_x = x;
                    *empty_y = (jump_y > y) ? jump_y + 1 : jump_y - 1;
                    return 1; //Hamle geçerlidir.
                }
            //Hamlenin dikey bir hamle olup olmadýðýný kontrol eder (Yukarý aþaðý).
            } else if (y == jump_y && abs(x - jump_x) == 1) {
                //Üstünden zýplanacak hücrenin yukarýsýnda veya aþaðýsýnda boþ bir hücre olup olmadýðýný kontrol eder.
                if ((jump_x > x && jump_x + 1 < boyut && tahta[jump_x + 1][y] == '.') || (jump_x < x && jump_x - 1 >= 0 && tahta[jump_x - 1][y] == '.')) {
                    *empty_x = (jump_x > x) ? jump_x + 1 : jump_x - 1;
                    *empty_y = y;
                    return 1;
                }
            }
        }
    }
    return 0; //Hamle geçersizdir.
}

//Tahtada yapýlabilecek geçerli hamle kalýp kalmadýðýný kontrol eden fonksiyon.
int gecerliHamleKaldiMi(char** tahta, int boyut) {
    int x, y, empty_x, empty_y;

    for (x = 0; x < boyut; x++) {
        for (y = 0; y < boyut; y++) {
            if (tahta[x][y] != '.') {
                //Yatay hareketleri kontrol eder.
                //x+1 koordinatýnýn tahtanýn sýnýrlarý içinde olup olmadýðý, x+1 koordinatýndaki hücrenin boþ olmadýðý
                //x+2 koordinatýnýn tahtanýn sýnýrlarý içinde olup olmadýðý, x+2 koordinatýndaki hücrenin boþ olduðu kontrol edilir.
                //eðer 1 döndürülürse yatayda saða doðru yapýlabilecek hamle var demektir.
                if (x + 1 < boyut && tahta[x + 1][y] != '.' && x + 2 < boyut && tahta[x + 2][y] == '.') {
                    return 1;
                }
                //x-1 koordinatýnýn tahtanýn sýnýrlarý içinde olup olmadýðý, x-1 koordinatýndaki hücrenin boþ olmadýðý
                //x-2 koordinatýnýn tahtanýn sýnýrlarý içinde olup olmadýðý, x-2 koordinatýndaki hücrenin boþ olduðu kontrol edilir.
                //eðer 1 döndürülürse yatayda sola doðru yapýlabilecek hamle var demektir.
                if (x - 1 >= 0 && tahta[x - 1][y] != '.' && x - 2 >= 0 && tahta[x - 2][y] == '.') {
                    return 1;
                }
                //Aþaðýda ayný iþlemler dikey hareketler için kontrol edilir.
				if (y + 1 < boyut && tahta[x][y + 1] != '.' && y + 2 < boyut && tahta[x][y + 2] == '.') {
                    return 1;
                }
                if (y - 1 >= 0 && tahta[x][y - 1] != '.' && y - 2 >= 0 && tahta[x][y - 2] == '.') {
                    return 1;
                }
            }
        }
    }
    return 0; //0 döndürülürse tahtada geçerli hareket kalmamýþ ve oyun bitmiþ demektir.
}

//Bir taþýn atlama yaptýktan sonra çoklu atlama yapýp yapamayacaðýný kontrol eder.
int cokluAtlamaKontrol(char** tahta, int boyut, int x, int y) {
    int dx, dy, empty_x, empty_y;
    //dx ve dy ile taþýn komþularý kontrol edilir.
    for (dx = -1; dx <= 1; dx++) {
        for (dy = -1; dy <= 1; dy++) {
        	//dx ve dy 0 ise taþýn kendi konumu temsil edildiði için burada kontrol yapýlmayacaktýr.
            if (dx == 0 && dy == 0) continue;
            //belirtilen yönde baþka bir hamle yapýlýp yapýlmayacaðý hamleGecerliMi fonksiyonu çaðrýlarak kontrol edilir.
            if (hamleGecerliMi(tahta, boyut, x, y, x + dx, y + dy, &empty_x, &empty_y)) {
                return 1;
            }
        }
    }
    return 0;
}

//Hamle yapýldýðýnda tahtadaki deðiþiklikleri yapan fonksiyon.
//deðiþkenler hamleGecerliMi fonksiyonunda açýklanmýþtýr.
//ekstra olarak captured_pieces deðiþkeni kullanýlmýþtýr. Bu deðiþken oyuncu tarafýndan yenilen taþlarý tutan bir karakter dizisini temsil eder.
void makeMove(char** tahta, int x, int y, int jump_x, int jump_y, int empty_x, int empty_y, char* captured_pieces) {
    tahta[empty_x][empty_y] = tahta[x][y];
    captured_pieces[strlen(captured_pieces)] = tahta[jump_x][jump_y];
    tahta[jump_x][jump_y] = '.';
    tahta[x][y] = '.';
}

//Yenilen taþlardan kaç tam set ve ekstra taþ olduðunu bularak puan hesaplayan fonksiyon.
//Girdi parametreleri:
//captured: yakalanan taþlarý tutan karakter dizisi
//set: tam set sayýsýný tutacak pointer
//ekstra: ekstra taþ sayýsýný tutacak pointer
void puanHesapla(char* captured, int* set, int* ekstra) {
    char colors[] = {'A', 'B', 'C', 'D', 'E'};
    int color_count[5] = {0, 0, 0, 0, 0};
    int i, j;

    //Yakalanan taþlar dizisinde her rengin kaç kez geçtiðini sayar.
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

    //Tam setleri çýkardýktan sonra kalan ekstra taþ sayýsýný hesaplar.
    *ekstra = 0;
    for (i = 0; i < 5; i++) {
        *ekstra += (color_count[i] - *set);
    }
}

//Oyundaki mevcut puanlarý yazdýrýr.
void mevcutPuaniYazdir(char* player1_captured, char* player2_captured) {
    int player1_sets, player1_extra, player2_sets, player2_extra;

    puanHesapla(player1_captured, &player1_sets, &player1_extra);
    puanHesapla(player2_captured, &player2_sets, &player2_extra);

    printf("Oyuncu 1: %d set, %d ekstra tas (Yenilen taslar: %s)\n", player1_sets, player1_extra, player1_captured);
    printf("Oyuncu 2: %d set, %d ekstra tas (Yenilen taslar: %s)\n", player2_sets, player2_extra, player2_captured);
}

//Oyun sonundaki puanlarý yazdýrýr.
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

//Tahtayý kopyalamak için kullanýlýr.
void tahtayiKopyala(char** src, char** dest, int boyut) {
    int i, j;
    for (i = 0; i < boyut; i++) {
        for (j = 0; j < boyut; j++) {
            dest[i][j] = src[i][j];
        }
    }
}

//Bilgisayar hamlesini hesaplayan fonksiyon.
//Girdi olarak tahta, boyut ve bilgisayarýn yemiþ olduðu taþlar verilmektedir.
void computerMove(char** tahta, int boyut, char* captured_pieces) {
    int x, y, jump_x, jump_y, empty_x, empty_y;
    //Bilgisayar yapacaðý hamleyi; yapabileceði rastgele hamleler arasýndan set tamamlamasý 
    //için en çok ihtiyacý olan hamleyi seçerek yapacaktýr.
	srand(time(0));

    char required_piece = '\0';
    int color_count[5] = {0};
    char colors[5] = {'A', 'B', 'C', 'D', 'E'};
    int i, j;

    //Yenilen taþlarýn renk sayýlarý hesaplanýr
    for (i = 0; captured_pieces[i] != '\0'; i++) {
        for (j = 0; j < 5; j++) {
            if (captured_pieces[i] == colors[j]) {
                color_count[j]++;
                break;
            }
        }
    }

    //Sahip olduðu taþlar arasýnda en az sahip olduðu taþý bulur ve required_piece deðiþkenine bu rengi atar.
    int min_count = color_count[0];
    required_piece = colors[0];
    for (i = 1; i < 5; i++) {
        if (color_count[i] < min_count) {
            min_count = color_count[i];
            required_piece = colors[i];
        }
    }

    //Bulduðu rastgele hamleler arasýndan en çok iþine yarayacak hamleyi bulmak için çeþitli kontroller yapar.
    while (1) {
        x = rand() % boyut;
        y = rand() % boyut;
        if (tahta[x][y] == '.') continue; //Seçilen rastgele koordinattaki hücre boþsa döngünün baþýna dönülür ve farklý bir hamle seçilir.
		int dx, dy;
        for (dx = -1; dx <= 1; dx++) {
            for (dy = -1; dy <= 1; dy++) {
                if (dx == 0 && dy == 0) continue;
                jump_x = x + dx;
                jump_y = y + dy;
                if (hamleGecerliMi(tahta, boyut, x, y, jump_x, jump_y, &empty_x, &empty_y)) {
                    if (tahta[jump_x][jump_y] == required_piece) {
                    	//Bulduðu rastgele hamlelerden birisi ihtiyacý olan taþ ise, bu hamleyi yapar ve fonksiyondan çýkýlýr.
                        makeMove(tahta, x, y, jump_x, jump_y, empty_x, empty_y, captured_pieces);
                        return;
                    }
                }
            }
        }
    }

    //Eðer required_piece'i bulmasýna yardým edecek bir hamle bulamazsa rastgele bir hamle yapar.
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

//Oyunu saved_game.txt dosyasýna kaydeder. Kaydedilen bilgiler sýrasýyla: tahta boyutu, bilgisayara karþý olma durumu, oyuncu sýrasý, tahta durumu ve iki oyuncunun sahip olduðu taþlardýr.
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

//saved_game.txt dosyasýndaki verileri okuyarak oyun oluþturur.
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

//Oyun içini yöneten fonksiyon:
//Girdi olarak tahta, boyut, bilgisayar karþý olma durumu, oyuncu sýrasý ve elde edilen taþlar alýnýr.
void Oyun(char** tahta, int boyut, int bilgisayaraKarsi, int oyuncuSirasi, char* player1_captured, char* player2_captured) {
    int oyunSonu = 0;								//Oyunun devam edip etmediðini temsil eden deðiþken
    char previous_player1_captured[50] = "";		//1.ve 2.oyuncularýn yediði taþlarý gösteren diziler.
    char previous_player2_captured[50] = "";
    char** eski_tahta = tahtaOlustur(boyut);		//Hamle yapýlmadan önceki tahtayý tutar.
    int current_x, current_y;						//Mevcut hamle koordinatlarý
    int ilk_hamle = 1;								//Ayný taþla çoklu hamle yapýlabileceði durumlarda hamlenin yapýlan ilk hamle mi yoksa sonraki hamlelerden mi olduðunu belirtir.

    printf("Skippity oyunu basliyor.\n");

    while (!oyunSonu) {
        if (!bilgisayaraKarsi) {
            system("cls"); //Bilgisayara karþý oynanmayan durumda ekraný temizler. Bilgisayara karþý oyun modunda bilgisayar hamle yaptýktan hemen sonra tahta yenilendiði ve bilgisayarýn yaptýðý
        }					//hamle tam olarak anlaþýlmadýðý için ekraný temizlememeyi tercih ettim.

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
            //Oyuncunun sýrasý
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
                //Undo yapýlabileceði için mevcut durum kaydedilir
                tahtayiKopyala(tahta, eski_tahta, boyut);
                strcpy(previous_player1_captured, player1_captured);
                strcpy(previous_player2_captured, player2_captured);
				//Hamle gerçekleþtirilir.
                if (oyuncuSirasi == 1) {
                    makeMove(tahta, x, y, jump_x, jump_y, empty_x, empty_y, player1_captured);
                } else {
                    makeMove(tahta, x, y, jump_x, jump_y, empty_x, empty_y, player2_captured);
                }
                current_x = empty_x;
                current_y = empty_y;
                printf("Gecerli hamle.\n");

                //Sonuçlarý yazdýrýr.
                mevcutPuaniYazdir(player1_captured, player2_captured);

                //Undo yapýlmak istenip istenmediði kullanýcýya sorulur
                char undo;
                printf("Hamleyi geri almak istiyor musunuz? (e/h): ");
                scanf(" %c", &undo);
                if (undo == 'e' || undo == 'E') {
                    //Bir önceki duruma dönülür.
                    tahtayiKopyala(eski_tahta, tahta, boyut);
                    strcpy(player1_captured, previous_player1_captured);
                    strcpy(player2_captured, previous_player2_captured);
                    printf("Hamle geri alindi.\n");
                    printf("Yeni bir hamle yapmalisiniz.\n");
                    continue;
                }

                //Kullanýcýnýn oyunu kaydetmek isteyip istemediði sorulur.
                char save;
                printf("Oyunu kaydetmek istiyor musunuz? (e/h): ");
                scanf(" %c", &save);
                if (save == 'e' || save == 'E') {
                    oyunuKaydet(tahta, boyut, bilgisayaraKarsi, oyuncuSirasi, player1_captured, player2_captured);
                    continue;
                }
				//Çoklu atlama kontrolü yapýlýr ve böyle bir durum mevcutsa kullanýcýya ayný taþla baþka bir hamle yaptýrýlýr.
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

