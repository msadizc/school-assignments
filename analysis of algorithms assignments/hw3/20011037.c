#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

void rotate_right(int array[],int n);
int control(int board[][8],int n,int row);
int update_board(int board[][8],int n, int row,int mode);

int main(){
	setlocale(LC_ALL,"turkish");
	int i,j,n,k,mode_select;
	int board[8][8];
	char colors[8][8][20];
	
	do{
		printf("Tahtanýn boyutunu 3 ile 8 arasýnda giriniz: ");
		scanf("%d",&n);
	}while(n<3 || n>8);
	
	for(i=0;i<n;i++){
		for(j=0;j<n;j++){
			printf("Tahtanýn [%d][%d]'deki elemanýný giriniz: ",i,j);
			scanf("%s",colors[i][j]);
		}
	}
	
	do{
		printf("\nNormal mod için 0, detay mod için 1 tuþuna basýnýz: ");
  		scanf("%d",&mode_select);
	}while(mode_select!=0 && mode_select!=1);
	
	printf("\nGirilen renk matrisi:\n");
	for (i = 0; i < n; i++) {
    	for (j = 0; j < n; j++) {
      		printf("%s\t\t",colors[i][j]);
    	}
    	printf("\n");
	}
	
	for (i = 0; i < n; i++) {				// Girilen renk matrisi bir sayý matrisine dönüþtürülüp board matrisinde saklanýr. 
    	for (j = 0; j < n; j++) {			// Matriste renklere sayý verilirken renk matrisinin ilk sütununda o rengin indeksine bakýlýr.
      		for (k = 0; k < n; k++) {
        		if (!strcmp(colors[i][j],colors[0][k])) {
          		board[i][j] = k;
        		}
      		}
    	}
  	}
  	
  	printf("\nSayýlara çevrilmiþ matris:\n");
	for (i = 0; i < n; i++) { 
    	for (j = 0; j < n; j++) { 
        	printf("%d ", board[i][j]); 
      	}  
      	printf("\n"); 
    }
    
    if(update_board(board,n,0,mode_select)){
    	printf("\nSonuç:\n");
    	for(i=0;i<n;i++){
    		for(j=0;j<n;j++){
    			printf("%s\t\t",colors[0][board[i][j]]);
			}
			printf("\n");
		}
		printf("\nSayýlara çevrilmiþ matriste sonuç:\n");
		for(i=0;i<n;i++){
    		for(j=0;j<n;j++){
    			printf("%d ",board[i][j]);
			}
			printf("\n");
		}
	}
	else{
		printf("\nGirilen matris için sonuç bulunmamaktadýr.\n");
	}
	
	return 0;
}

void rotate_right(int array[],int n){	// Bir diziyi saða kaydýrmak için kullanýlan fonksiyon.
	int temp[8];
	int i;
	for(i=0;i<n;i++){					// Dizinin saða kaydýrýlmýþ halini temp dizisinde kaydeder.
		temp[i] = array[(i-1+n)%n];
	}
	for(i=0;i<n;i++){					// Temp dizisini array dizisine yazar.
		array[i] = temp[i];
	}
}

int control(int board[][8],int n,int row){	// Girilen satýr deðerinden yukarýya doðru bakarak tahtanýn mevcut halinin kurallara uyup uymadýðýný kontrol eder.
	int i,j;
	for(i=0;i<row;i++){		
		for(j=0;j<n;j++){
			if(board[i][j] == board[row][j]){			// Daha üstteki bir satýrýn ayný sütununda ayný deðerle karþýlaþýlýrsa 0 döndürür.
				return 0;
			}
		}
	}
	return 1;
}

int update_board(int board[][8],int n, int row,int mode){	// Tahtanýn durumunu girilen satýrý saða kaydýrarak ve kurallara uyup uymadýðýný kontrol ederek günceller.
	int i,j,k;
	if(row>=n){		// Girilen sütun sayýsý toplam sütun sayýsýndan büyük veya eþitse tahta baþarýlý bir þekilde güncellenmiþ demektir.
		return 1;
	}
	
	for(i=0;i<n;i++){	// Mevcut satýr için kaydýrýlarak oluþturulacak bütün olasýlýklarý dener.
		if(mode==1){
			printf("\nGüncelleniyor:\n");
			for(j=0;j<=row;j++){
				for(k=0;k<n;k++){
					printf("%d ",board[j][k]);
				}
				printf("\n");
			}
			printf("*********************\n");
		}
		if(control(board,n,row)){				// Eðer mevcut durum kurallara uyuyorsa bir sonraki sütun için fonksiyon çaðrýlýr.
			if(update_board(board,n,row+1,mode)){	
				return 1;
			}
		}
		rotate_right(board[row],n);	// Mevcut sütunun deðerleri saða döndürülür.
	}
	
	return 0;
}
