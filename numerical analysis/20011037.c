#include <stdio.h>
#include <math.h>

double func(double x,float ar[],int arr_length){
	double sonuc=0;
	int i;
	for(i=0;i<=arr_length;i++){
		sonuc += (pow(x,i) * ar[i]);
		}	
	return sonuc;
}
double turev(double x,float dizi[], int uzunluk){
 	double _turev;
    double h=0.0000001;
    		_turev =(1/h) * (func(x+h,dizi,uzunluk) - func(x-h,dizi,uzunluk));
			_turev /= 2;
	return _turev;
}

double bisection(){
	int a,i;
    
    printf("Polinomun katsayisini giriniz.\n");               
	scanf("%d",&a);
	int uzunluk=a;
	float dizi[a+1];
	
	for(i=a;i>=0;i--){
    	printf("x uzeri %d. elemanin katsayisini giriniz :\t\t",i);
		scanf("%f",&dizi[i]);
		printf("\n");
		}	
		
	for(i=a;i>=0;i--){
	  if(i!=0){
		if(dizi[i]>0)
		  printf("+( %.2f x^ %d )",dizi[i],i);
		else if(dizi[i]<0)
		  printf("-( %.2f x^ %d )",(-1)*(dizi[i]),i);
		else
		  continue;		
		}
	  else{
	  	if(dizi[i]>0)
		  printf("+( %.2f )",dizi[i]);
		else if(dizi[i]<0)
		  printf("-( %.2f )",(-1)*(dizi[i]));
		  }
	}
	
	printf("\nIslem yapmak istediginiz polinomun bu olduguna emin misiniz?(E/H)\n");
	char e_h;
	scanf(" %c",&e_h);
	
	if(e_h == 'H' || e_h == 'h'){
		bisection();
	}
	 
	double alt_sinir, ust_sinir,kok;                                                                 
	printf("Kok bulmak istediginiz araligin alt sinirini giriniz.\n");
	scanf("%lf",&alt_sinir);
	
    printf("\nKok bulmak istediginiz araligin ust sinirini giriniz.\n");
	scanf("%lf",&ust_sinir);
	int yontem,max_iterasyon;
	double hata,istenen_hata;
	printf("\n Islemi ne sekilde sonlandirmak istersiniz? \n 1-) Maksimum iterasyon sayisina ulasildiginda \n 2-) Istenilen hata oranina ulasildiginda\n");
	scanf("%d",&yontem);
	
	switch(yontem){
		case 1:
	printf("\n Maksimum iterasyon sayisini giriniz: ");
	scanf("%d",&max_iterasyon);
	
		
	double altdeger = func(alt_sinir,dizi,uzunluk);
	double ustdeger = func(ust_sinir,dizi,uzunluk);
	int iterasyon=0;
		
	while(iterasyon<max_iterasyon){
		double temp = kok;
		kok = (alt_sinir+ust_sinir)/2;
		double kokdeger = func(kok,dizi,uzunluk);
		if(kokdeger == 0.0){
			printf("\n #####%d######\n ALT SINIR: %lf \n UST SINIR: %lf \n F(ALT SINIR): %lf \n F(UST SINIR): %lf \n HATA: %.20lf \n KOK: %lf \n F(KOK): %lf \n",iterasyon,alt_sinir,ust_sinir,altdeger,ustdeger,hata,kok,kokdeger);
			return;
		}
		else if(kokdeger*altdeger<0){
			ust_sinir = kok;
			ustdeger = kokdeger;
			hata = fabs(kok-temp);
		}
		else{
			alt_sinir = kok;
			altdeger = kokdeger;
			hata = fabs(kok-temp);
		}
		iterasyon++;
		printf("\n #####%d######\n ALT SINIR: %lf \n UST SINIR: %lf \n F(ALT SINIR): %lf \n F(UST SINIR): %lf \n HATA: %.20lf \n KOK: %lf \n F(KOK): %lf \n",iterasyon,alt_sinir,ust_sinir,altdeger,ustdeger,hata,kok,kokdeger);
			}
			break;
		case 2:
	printf("\n Istenen hatayi giriniz. (Kok N - Kok(n-1)) : ");
	scanf("%lf",&istenen_hata);
	
    altdeger = func(alt_sinir,dizi,uzunluk);
	ustdeger = func(ust_sinir,dizi,uzunluk);
	hata = istenen_hata + 1;
	iterasyon=0;
	
	while(hata>=istenen_hata){
		double temp = kok;
		kok = (alt_sinir+ust_sinir)/2;
		double kokdeger = func(kok,dizi,uzunluk);
		if(kokdeger == 0.0){
			printf("\n #####%d######\n ALT SINIR: %lf \n UST SINIR: %lf \n F(ALT SINIR): %lf \n F(UST SINIR): %lf \n HATA: %.20lf \n KOK: %lf \n F(KOK): %lf \n",iterasyon,alt_sinir,ust_sinir,altdeger,ustdeger,hata,kok,kokdeger);
			return;
		}
		else if(kokdeger*altdeger<0){
			ust_sinir = kok;
			ustdeger = kokdeger;
			hata = fabs(kok-temp);
		}
		else{
			alt_sinir = kok;
			altdeger = kokdeger;
			hata = fabs(temp-kok);
		}
		iterasyon++;
		printf("\n #####%d######\n ALT SINIR: %lf \n UST SINIR: %lf \n F(ALT SINIR): %lf \n F(UST SINIR): %lf \n HATA: %.20lf \n KOK: %lf \n F(KOK): %lf \n",iterasyon,alt_sinir,ust_sinir,altdeger,ustdeger,hata,kok,kokdeger);
	}
			break;
	}
	return;}

double regula_falsi(){
	int a,i;
    
    printf("Polinomun katsayisini giriniz.\n");              
	scanf("%d",&a);
	int uzunluk=a;
	float dizi[a+1];
	
	for(i=a;i>=0;i--){
    	printf("x uzeri %d. elemanin katsayisini giriniz :\t\t",i);
		scanf("%f",&dizi[i]);
		printf("\n");
		}	
		
	for(i=a;i>=0;i--){
	  if(i!=0){
		if(dizi[i]>0)
		  printf("+( %f x^ %d )",dizi[i],i);
		else if(dizi[i]<0)
		  printf("-( %f x^ %d )",(-1)*(dizi[i]),i);
		else
		  continue;		
		}
	  else{
	  	if(dizi[i]>0)
		  printf("+( %f )",dizi[i]);
		else if(dizi[i]<0)
		  printf("-( %f )",(-1)*(dizi[i]));
		  }
	}
	
	printf("\nIslem yapmak istediginiz polinomun bu olduguna emin misiniz?(E/H)\n");
	char e_h;
	scanf(" %c",&e_h);
	
	if(e_h == 'H' || e_h == 'h'){
		regula_falsi();
	}
	 
	double alt_sinir, ust_sinir,kok;                                                                
	printf("Kok bulmak istediginiz araligin alt sinirini giriniz.\n");
	scanf("%lf",&alt_sinir);
	
    printf("\nKok bulmak istediginiz araligin ust sinirini giriniz.\n");
	scanf("%lf",&ust_sinir);
	
	int yontem,max_iterasyon;
	double hata,istenen_hata;
	printf("\n Islemi ne sekilde sonlandirmak istersiniz? \n 1-) Maksimum iterasyon sayisina ulasildiginda \n 2-) Istenilen hata oranina ulasildiginda\n");
	scanf("%d",&yontem);
	
	switch(yontem){
		case 1:
		printf("\n Maksimum iterasyon sayisini giriniz: ");
		scanf("%d",&max_iterasyon);
	
	
	double altdeger = func(alt_sinir,dizi,uzunluk);
	double ustdeger = func(ust_sinir,dizi,uzunluk);
	double hata;
	int iterasyon=0;
		
	while(iterasyon<max_iterasyon){
		double temp = kok;
		kok = ((alt_sinir * ustdeger) - (ust_sinir * altdeger)) / (ustdeger - altdeger);
		double kokdeger = func(kok,dizi,uzunluk);
		if(kokdeger == 0.0){
		printf("\n #####%d######\n ALT SINIR: %lf \n UST SINIR: %lf \n F(ALT SINIR): %lf \n F(UST SINIR): %lf \n HATA: %.20lf \n KOK: %lf \n F(KOK): %lf \n",iterasyon,alt_sinir,ust_sinir,altdeger,ustdeger,hata,kok,kokdeger);
			return;
		}
		else if(kokdeger*altdeger<0){
			ust_sinir = kok;
			ustdeger = kokdeger;
			hata = fabs(kok-temp);
		}
		else{
			alt_sinir = kok;
			altdeger = kokdeger;
			hata = fabs(temp-kok);
		}
		iterasyon++;
		printf("\n #####%d######\n ALT SINIR: %lf \n UST SINIR: %lf \n F(ALT SINIR): %lf \n F(UST SINIR): %lf \n HATA: %.20lf \n KOK: %lf \n F(KOK): %lf \n",iterasyon,alt_sinir,ust_sinir,altdeger,ustdeger,hata,kok,kokdeger);
	}
	break;
	
		case 2:
			printf("\n Istenen hatayi giriniz. (Kok N - Kok(n-1)) : ");
			scanf("%lf",&istenen_hata);
	
    altdeger = func(alt_sinir,dizi,uzunluk);
	ustdeger = func(ust_sinir,dizi,uzunluk);
	hata = istenen_hata + 1;
	iterasyon=0;
	
	while(hata>=istenen_hata){
		double temp = kok;
		kok = ((alt_sinir * ustdeger) - (ust_sinir * altdeger)) / (ustdeger - altdeger);
		double kokdeger = func(kok,dizi,uzunluk);
		if(kokdeger == 0.0){
			printf("\n #####%d######\n ALT SINIR: %lf \n UST SINIR: %lf \n F(ALT SINIR): %lf \n F(UST SINIR): %lf \n HATA: %.20lf \n KOK: %lf \n F(KOK): %lf \n",iterasyon,alt_sinir,ust_sinir,altdeger,ustdeger,hata,kok,kokdeger);
			return;
		}
		else if(kokdeger*altdeger<0){
			ust_sinir = kok;
			ustdeger = kokdeger;
			hata = fabs(kok-temp);
		}
		else{
			alt_sinir = kok;
			altdeger = kokdeger;
			hata = fabs(temp-kok);
		}
		iterasyon++;
		printf("\n #####%d######\n ALT SINIR: %lf \n UST SINIR: %lf \n F(ALT SINIR): %lf \n F(UST SINIR): %lf \n HATA: %.20lf \n KOK: %lf \n F(KOK): %lf \n",iterasyon,alt_sinir,ust_sinir,altdeger,ustdeger,hata,kok,kokdeger);
	}
	break;
	}
	
	return;}
	
double newton_raphson(){
	int a,i;
    printf("Polinomun katsayisini giriniz.\n");              
	scanf("%d",&a);
	int uzunluk=a+1;
	float dizi[a+1];
	
	for(i=a;i>=0;i--){
    	printf("x uzeri %d. elemanin katsayisini giriniz :\t\t",i);
		scanf("%f",&dizi[i]);
		printf("\n");
		}	
		
	for(i=a;i>=0;i--){
	  if(i!=0){
		if(dizi[i]>0)
		  printf("+( %f x^ %d )",dizi[i],i);
		else if(dizi[i]<0)
		  printf("-( %f x^ %d )",(-1)*(dizi[i]),i);
		else
		  continue;		
		}
	  else{
	  	if(dizi[i]>0)
		  printf("+( %f )",dizi[i]);
		else if(dizi[i]<0)
		  printf("-( %f )",(-1)*(dizi[i]));
		  }
	}
	
	printf("\nIslem yapmak istediginiz polinomun bu olduguna emin misiniz?(E/H)\n");
	char e_h;
	scanf(" %c",&e_h);
	
	if(e_h == 'H' || e_h == 'h'){
		newton_raphson();
	}
	
	double alt_sinir, ust_sinir,kok;                                                                
	printf("Kok bulmak istediginiz araligin alt sinirini giriniz.\n");
	scanf("%lf",&alt_sinir);
	
    printf("\nKok bulmak istediginiz araligin ust sinirini giriniz.\n");
	scanf("%lf",&ust_sinir);
	double ilk_alt_sinir = alt_sinir, ilk_ust_sinir = ust_sinir;
	
	printf("\nBaslangic noktasini seciniz.\n");
	scanf("%lf",&kok);
	
	double istenen_hata;
	printf("\n Istenen hatayi giriniz. (Kok N - Kok(n-1)) : ");
	scanf("%lf",&istenen_hata);
	
    double altdeger = func(alt_sinir,dizi,uzunluk);
	double ustdeger = func(ust_sinir,dizi,uzunluk);
	double hata = istenen_hata + 1;
	double kokdeger;
	int iterasyon=0;
	printf("\n #####%d######\n ALT SINIR: %lf \n UST SINIR: %lf \n ALT DEGER: %lf \n UST DEGER: %lf \n HATA: %.20lf \n KOK: %lf \n KOK DEGER: %lf \n",iterasyon,alt_sinir,ust_sinir,altdeger,ustdeger,hata,kok,kokdeger);
	
	while(hata>=istenen_hata){
		if(alt_sinir<ilk_alt_sinir || ust_sinir>ilk_ust_sinir || alt_sinir>ilk_ust_sinir || ust_sinir<ilk_alt_sinir){
			printf("\n\n Kok baslangic araliginin disina cikti. Lutfen yeni bir baslangic degeri giriniz.\n\n");
			scanf("%lf",&kok);
			ust_sinir = ilk_ust_sinir;
			alt_sinir = ilk_alt_sinir;
			hata = istenen_hata+1;
			iterasyon=0;
		}
		double temp = kok;
		kok = kok - ( (func(kok,dizi,uzunluk)) / turev(kok,dizi,uzunluk) );
		kokdeger = func(kok,dizi,uzunluk);
		
		if(kokdeger == 0.0){
			printf("\n Kok = %lf\n",kok);
			return;
		}
		else if(kokdeger*altdeger<0){
			ust_sinir = kok;
			ustdeger = kokdeger;
			hata = fabs(kok-temp);
		}
		else{
			alt_sinir = kok;
			altdeger = kokdeger;
			hata = fabs(temp-kok);
		}
		iterasyon++;
		printf("\n #####%d######\n ALT SINIR: %lf \n UST SINIR: %lf \n ALT DEGER: %lf \n UST DEGER: %lf \n HATA: %.20lf \n KOK: %lf \n KOK DEGER: %lf \n",iterasyon,alt_sinir,ust_sinir,altdeger,ustdeger,hata,kok,kokdeger);
	}
	return;}



double sayisalturev(){
		
		int a,i;
    
    printf("Polinomun katsayisini giriniz.\n");               
	scanf("%d",&a);
	int uzunluk=a;
	float dizi[a];
	
	for(i=a;i>=0;i--){
    	printf("x uzeri %d. elemanin katsayisini giriniz :\t\t",i);
		scanf("%f",&dizi[i]);
		printf("\n");
		}	
		
	for(i=a;i>=0;i--){
	  if(i!=0){
		if(dizi[i]>0)
		  printf("+( %f x^ %d )",dizi[i],i);
		else if(dizi[i]<0)
		  printf("-( %f x^ %d )",(-1)*(dizi[i]),i);
		else
		  continue;		
		}
	  else{
	  	if(dizi[i]>0)
		  printf("+( %f )",dizi[i]);
		else if(dizi[i]<0)
		  printf("-( %f )",(-1)*(dizi[i]));
		  }
	}
	
	printf("\nIslem yapmak istediginiz polinomun bu olduguna emin misiniz?(E/H)\n");
	char e_h;
	scanf(" %c",&e_h);
	
	if(e_h == 'H' || e_h == 'h'){
		sayisalturev();
	}
	
	printf("\n Sayisal Turevi hangi yontem ile almak istersiniz? \n 1- Geri Farklar \n 2- Ileri Farklar \n 3- Merkezi Farklar\n 4- Tumunu goster\n");
	int secim;
	scanf("%d",&secim);
	double h, x, turev;
	switch(secim)
	{
		case 1:
			printf("Hangi deger icin turev almak istediginizi ve 'h' degerini sirasiyla giriniz.\n");
			scanf("%lf",&x);
			scanf("%lf",&h);
			turev = (func(x,dizi,uzunluk) - func(x-h,dizi,uzunluk)) / h;
			printf("\n Fonksiyonun %lf noktasindaki turevinin degeri : %lf",x,turev);
			break;
		case 2:
			printf("Hangi deger icin turev almak istediginizi ve 'h' degerini sirasiyla giriniz.\n");
			scanf("%lf",&x);
			scanf("%lf",&h);
			turev = (func(x+h,dizi,uzunluk) - func(x,dizi,uzunluk)) / h;
			printf("\n Fonksiyonun %lf noktasindaki turevinin degeri : %lf",x,turev);
			break;
		case 3:
			printf("Hangi deger icin turev almak istediginizi ve 'h' degerini sirasiyla giriniz.\n");
			scanf("%lf",&x);
			scanf("%lf",&h);
			turev =(1/h) * (func(x+h,dizi,uzunluk) - func(x-h,dizi,uzunluk));
			turev /= 2;
			printf("\n Fonksiyonun %lf noktasindaki turevinin degeri : %lf",x,turev);
			break;
		case 4:
			printf("Hangi deger icin turev almak istediginizi ve 'h' degerini sirasiyla giriniz.\n");
			scanf("%lf",&x);
			scanf("%lf",&h);
			double turevileri = (func(x+h,dizi,uzunluk) - func(x,dizi,uzunluk)) / h;
			double turevgeri = (func(x,dizi,uzunluk) - func(x-h,dizi,uzunluk)) / h;
			turev =(1/h) * (func(x+h,dizi,uzunluk) - func(x-h,dizi,uzunluk));
			turev /= 2;
			printf("\n Fonksiyonun %lf noktasindaki turevinin degeri: \n Geri farklar yontemiyle : %lf \n Merkezi farklar yontemiyle : %lf \n Ileri farklar yontemiyle : %lf",x,turevgeri,turev,turevileri);
			break;
	  }
	
return turev;
}

double trapez(){
	int a,i;
    
    printf("Polinomun katsayisini giriniz.\n");              
	scanf("%d",&a);
	int uzunluk=a;
	float dizi[a];
	
	for(i=a;i>=0;i--){
    	printf("x uzeri %d. elemanin katsayisini giriniz :\t\t",i);
		scanf("%f",&dizi[i]);
		printf("\n");
		}	
		
	for(i=a;i>=0;i--){
	  if(i!=0){
		if(dizi[i]>0)
		  printf("+( %f x^ %d )",dizi[i],i);
		else if(dizi[i]<0)
		  printf("-( %f x^ %d )",(-1)*(dizi[i]),i);
		else
		  continue;		
		}
	  else{
	  	if(dizi[i]>0)
		  printf("+( %f )",dizi[i]);
		else if(dizi[i]<0)
		  printf("-( %f )",(-1)*(dizi[i]));
		  }
	}
	
	printf("\nIslem yapmak istediginiz polinomun bu olduguna emin misiniz?(E/H)\n");
	char e_h;
	scanf(" %c",&e_h);
	
	if(e_h == 'H' || e_h == 'h'){
		trapez();
	}
	double altsinir, ustsinir, h, alan;
	int n;
	printf("Integralin alt ve ust sinirlarini sirasiyla giriniz.\n");
	scanf("%lf",&altsinir);
	scanf("%lf",&ustsinir);
	printf("\n Araligi kac parcaya bolmek istediginizi yaziniz. \n");
	scanf("%d",&n); 
	h = (ustsinir - altsinir) / n;
	for(i=0;i<n;i++){
		alan += h/2 * (func(altsinir+(i*h),dizi,uzunluk) + func(altsinir+((i+1)*h),dizi,uzunluk) );
	}
	printf("\n Integralin yaklasik degeri : %lf",alan);
	
return alan;	
}

double simpson_1bolu3(){
	int a,i;
    
    printf("Polinomun katsayisini giriniz.\n");               
	scanf("%d",&a);
	int uzunluk=a;
	float dizi[a];
	
	for(i=a;i>=0;i--){
    	printf("x uzeri %d. elemanin katsayisini giriniz :\t\t",i);
		scanf("%f",&dizi[i]);
		printf("\n");
		}	
		
	for(i=a;i>=0;i--){
	  if(i!=0){
		if(dizi[i]>0)
		  printf("+( %f x^ %d )",dizi[i],i);
		else if(dizi[i]<0)
		  printf("-( %f x^ %d )",(-1)*(dizi[i]),i);
		else
		  continue;		
		}
	  else{
	  	if(dizi[i]>0)
		  printf("+( %f )",dizi[i]);
		else if(dizi[i]<0)
		  printf("-( %f )",(-1)*(dizi[i]));
		  }
	}
	
	printf("\nIslem yapmak istediginiz polinomun bu olduguna emin misiniz?(E/H)\n");
	char e_h;
	scanf(" %c",&e_h);
	
	if(e_h == 'H' || e_h == 'h'){
		simpson_1bolu3();
	}
	double altsinir, ustsinir, h, alan;
	int n;
	printf("Integralin alt ve ust sinirlarini sirasiyla giriniz.\n");
	scanf("%lf",&altsinir);
	scanf("%lf",&ustsinir);
	do{
	printf("\n Araligi kac parcaya bolmek istediginizi yaziniz. \n");
	scanf("%d",&n); 
	if(n % 2 != 0){
		printf("Aralik sayisi cift olmalidir.\n");
	}
	}while(n % 2 != 0);
	h = (ustsinir - altsinir) / n;
	for(i=0;i<n;i++){
		if(i == 0 || i == n){
		alan += h/3 * (func(altsinir,dizi,uzunluk));
		}
		if(i % 2 == 0){
		alan += h/3 * 2 * func(altsinir+(i*h),dizi,uzunluk);
		}
		if(i%2 == 1){
		alan += h/3 * 4 * func(altsinir+(i*h),dizi,uzunluk);
		}
	}
	printf("\n Integralin yaklasik degeri : %lf",alan);
	
return;	
}

double simpson_3bolu8(){
	int a,i;
    
    printf("Polinomun katsayisini giriniz.\n");               
	scanf("%d",&a);
	int uzunluk=a;
	float dizi[a];
	
	for(i=a;i>=0;i--){
    	printf("x uzeri %d. elemanin katsayisini giriniz :\t\t",i);
		scanf("%f",&dizi[i]);
		printf("\n");
		}	
		
	for(i=a;i>=0;i--){
	  if(i!=0){
		if(dizi[i]>0)
		  printf("+( %f x^ %d )",dizi[i],i);
		else if(dizi[i]<0)
		  printf("-( %f x^ %d )",(-1)*(dizi[i]),i);
		else
		  continue;		
		}
	  else{
	  	if(dizi[i]>0)
		  printf("+( %f )",dizi[i]);
		else if(dizi[i]<0)
		  printf("-( %f )",(-1)*(dizi[i]));
		  }
	}
	
	printf("\nIslem yapmak istediginiz polinomun bu olduguna emin misiniz?(E/H)\n");
	char e_h;
	scanf(" %c",&e_h);
	
	if(e_h == 'H' || e_h == 'h'){
		simpson_3bolu8();
	}
	double altsinir, ustsinir, h, alan;
	int n;
	printf("Integralin alt ve ust sinirlarini sirasiyla giriniz.\n");
	scanf("%lf",&altsinir);
	scanf("%lf",&ustsinir);
	printf("\n Araligi kac parcaya bolmek istediginizi yaziniz. \n");
	scanf("%d",&n); 
	
	h = (ustsinir - altsinir) / (n);
	int j;
	    
		double yeni_h = (ustsinir - altsinir) / (n*3); 
		double topla;
		alan = 0;
	for(i=0;i<n;i++){		
		double yenialtsinir =  altsinir+((i*h));
		double yeniustsinir =  altsinir+((i+1)*h);
		for(j=0;j<=3;j++){			
		topla = 0;
		if(j==0 || j==3){
			topla = (yeniustsinir-yenialtsinir) * (func((yenialtsinir+(j*yeni_h)),dizi,uzunluk) /8);
			alan += topla ;
		}
		if(j==1 || j==2){
			topla = (yeniustsinir-yenialtsinir) * (func(yenialtsinir+(j*yeni_h),dizi,uzunluk) /8);
			topla *= 3;
			alan+= topla;
		}
		}
		
		}
	printf("\n Integralin yaklasik degeri : %lf",alan);
	
return;	
}

double kombinasyon(double k, int i){
	int j,faktoriyel=1;
	double k1=k;
	if(i==0){
		return 1;
	}
	for(j=1; j<i; j++){
		k = k * (k1-j);
		}
	for(j=2; j<=i ;j++){
		faktoriyel *= j;
			}
	k = k / faktoriyel;
	return k;
}

double gregory_newton(){
	int a,i,j;
   printf("\n Kac x degeri gireceksiniz?\n");
   scanf("%d",&a);
   double dizi[a], degerler[a][a],fark,sum = 0,faktoriyel=1;
   
   for(i=0;i<a;i++){
   	printf("\n Gireceginiz %d. x noktasi ve fonksiyondaki degerini sirasiyla giriniz.\n x(%d)=",i,i);
   	scanf("%lf",&dizi[i]);
   	fark = dizi[1]-dizi[0];
   	if(i>0 && dizi[i]-dizi[i-1]!=fark){
   		printf("\n X noktalari arasindaki fark birbirine esit olmalidir.");
   		gregory_newton();
   		return;
	   }
   	printf("\t y(%d)=",i);
   	scanf("%lf",&degerler[i][0]);
   }
   
   for(i=1; i<a ;i++){
   	   for(j=a-1;j>=i;j--){
   	   	degerler[j][i] = degerler[j][i-1] - degerler[j-1][i-1];
   	   	  }
   }
   printf("\n Degerini hesaplamak istediginiz noktayi giriniz.\n");
   double x;
   scanf("%lf",&x);
   double k = (x - dizi[0]) / fark;
   printf("\n ##ILERI FARK TABLOSU##\n");
   for(i=0;i<a;i++){
   	for(j=0;j<=i;j++){ 
	    printf("%lf \t",degerler[i][j]);
 	   }
 	printf("\n");
   }
   for(i=0;i<a;i++){
	   sum += degerler[i][i] * kombinasyon(k,i); 
    }
   printf("\n\n %lf degerinde enterpolasyonun sonucu = %lf\n",x,sum);
 
   return;
   }

double gauss_seidel(){
	int i,j,a;
	double hata, istenen_hata,sum=0;
	printf("Toplam denklem sayisini giriniz.\n UYARI: Denklemleri kosegen baskin matris sekilde girmeniz gerekmektedir.\n");
	scanf("%d",&a);
	double matris[a][a+1];
	for(i=0;i<a;i++){
		for(j=0;j<a+1;j++){
			if(j==a){
				printf("\n %d. denklemin sonucunu giriniz: ",i+1);
				scanf("%lf",&matris[i][j]);
			}
			else{
			printf("\n %d. denklemde x(%d) elemaninin katsayisini giriniz: ",i+1,j+1);
			scanf("%lf",&matris[i][j]);}
		}
	}
	printf("\n Istediginiz hata degerini girin: ");
	scanf("%lf",&istenen_hata);

	double tahminler[a+1],temp;
	for(i=0;i<a;i++){
		tahminler[i]=0;
	}
	printf("\n\n Iterasyon Sonuclari\n\n");
	for(i=0;i<a;i++){
		printf("x(%d)\t\t",i+1);
	}
	printf("\n\n");
	
	do{
	 for(i=0;i<a;i++){
		sum=0;
		for(j=0;j<a;j++){
			if(j != i){
				sum += matris[i][j] * tahminler[j];
			}
		}
		temp = (matris[i][a] - sum) / matris[i][i];
		hata = fabs(tahminler[i] - temp);
		tahminler[i] = temp;
		for(j=0;j<a;j++){
		 printf("%lf\t",tahminler[j]);
		}
		printf("\n");
	}
	}while(hata>istenen_hata);	
		
	return;}

int main(){
printf("Yapmak istediginiz islemi seciniz.\n 1-) Bisection Metodu ile Polinom Koku Bulma \n 2-) Regula-Falsi Metodu ile Polinom Koku Bulma \n 3-) Newton-Raphson Metodu ile Polinom Koku Bulma \n 4-) Sayisal Turev Hesaplama \n 5-) Trapez Kurali ile Sayisal Integral Hesaplama \n 6-) Simpson 1/3 Kurali ile Sayisal Integral Hesaplama \n 7-) Simpson 3/8 Kurali ile Sayisal Integral Hesaplama \n 8-) Gregory - Newton Enterpolasyonu Hesaplama \n 9-) Gauss-Seidel Yontemi ile Kok Bulma\n");
int secim;
scanf("%d",&secim);
int secim2;
switch(secim){
	case 1:
		bisection();
		break;
	case 2:
		regula_falsi();
		break;
	case 3:
		newton_raphson();
		break;
	case 4:
		sayisalturev();
		break;
	case 5:
		trapez();
		break;
	case 6:
		simpson_1bolu3();
		break;
	case 7:
		simpson_3bolu8();
		break;
	case 8:
		gregory_newton();
		break;
	case 9:
		gauss_seidel();
		break;
	default:
		printf("\n Lutfen farkli bir sayi giriniz.\n\n");
		main();
		break;
		}
		
		printf("\n\n Programdan cikmak istiyor musunuz?\n1-)Evet\n2-)Hayir\n");
		scanf("%d",&secim2);
		if(secim2==1){
			return 0;}
		if(secim2==2){
			main();
		}
return;}
	
	
