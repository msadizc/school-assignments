#include <stdio.h>
#include <stdlib.h>

int fonksiyon(int n);
void print(int* dizi, int eleman, int boyut);

int main(){
	int n;
	
	do{
	    printf("Pozitif bir tam sayi giriniz: ");
	    scanf("%d",&n);
	    if(n<=0) {
	        printf("Hata: Girilen sayi pozitif olmalidir.\n");
	    }
	}while (n<=0);
	
	int *sepet = calloc(2, sizeof(int));
	if(sepet==NULL){
		printf("Hata.");
		return 1;
	}
	
	int boyut = 2;
	int eleman_sayisi = 0;
	
	while(n!=1){
		if(eleman_sayisi==boyut){
			boyut *= 2;
			int *tmp = realloc(sepet,boyut*sizeof(int));
			if(tmp==NULL){
				printf("Hata.");
				return 1;
			}			
		}
		sepet[eleman_sayisi] = n;
		eleman_sayisi++;
		n = fonksiyon(n);
	}
	
	if(eleman_sayisi==boyut){
		boyut *= 2;
		int *tmp = realloc(sepet,boyut*sizeof(int));
		if(tmp==NULL){
			printf("Hata");
			return 1;
		}
	}
	sepet[eleman_sayisi] = 1;
	eleman_sayisi++;
	
	print(sepet,eleman_sayisi,boyut);
	free(sepet);
	
	return 0;
}

int fonksiyon(int n){
	if(n%2 == 1){
		return 3*n+1;
	}
	else{
		return n/2;
	}	
}

void print(int* dizi, int eleman, int boyut){
	int i;
	
	printf("\nSepet = [");
    
	for (i=0;i<eleman;i++){
        printf("%d", dizi[i]);
        if (i!=eleman-1) {
            printf(",");
        }
    }
    
    printf("]\n");
    
	printf("Dizinin eleman sayisi = %d \nDizinin hafizada kapladigi alan = %d\n", eleman, boyut);
	return;
}
