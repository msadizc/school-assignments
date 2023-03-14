#include <stdio.h>
#include <stdlib.h>

struct stack{
	int top;
	char *array;	
};

int count = 0;

void DecimalBinary(int sayi, char **string);
void TwosComplement(int sayi, char *str);
int isFull(int sayi,struct stack *s);
int isEmpty(struct stack *s);
void push(struct stack *s, int item, int sayi);
void pop(struct stack *s);
void printStack(struct stack *s);
int ArrayLength(int number);
int power(int a,int b);

int main(){
	int i,sayi,secim=1;
	
	while(secim==1){
		struct stack *ar = (struct stack*)malloc(sizeof(struct stack));
		char *strs;
		ar->top = -1;
		printf("--------------------------------------------------------------\n");
		printf("Binary'ye cevirmek istediginiz sayiyi girin: ");
		scanf("%d",&sayi);
		ar->array = (char*)malloc(ArrayLength(sayi)*sizeof(char));
		DecimalBinary(sayi,&strs);
		printf("\n");
		for(i=0;i<(ArrayLength(sayi));i++){
			printf("%d",strs[i]);
		}
		for(i=0;i<ArrayLength(sayi);i++){
			if(ar->top==-1 || strs[i]==(ar->array[ar->top])){
				push(ar,strs[i],ArrayLength(sayi));}
			else{
				pop(ar);
			}
		}
		if(ar->top==-1){
			printf("\n0'lar ve 1'ler esit sayidadir.\n");}
		else if(ar->array[ar->top]==1){
			printf("\n1 sayisi fazladir. Ek %d adet 0 gereklidir.\n",(ar->top)+1);
		}
		else if(ar->array[ar->top]==0){
			printf("\n0 sayisi fazladir. Ek %d adet 1 gereklidir.\n",(ar->top)+1);
		}
		free(ar);
		free(strs);
		printf("\nDevam etmek ister misiniz? Evet: 1 Hayir: 0\n");
		scanf("%d",&secim);
	}
	return 0;
}


void DecimalBinary(int sayi, char **string){
	int num;
	int n=2,cnt=1,i;
	char *str = (char*)calloc(ArrayLength(sayi),sizeof(char));
	
	if(sayi<0){
		num = sayi*(-1);
	}
	else if(sayi>=0){
		num = sayi;
	}
	n = power(2,ArrayLength(sayi)-1);
	cnt = ArrayLength(sayi);
	for(i=0;i<cnt;i++){
		str[i]=num/n;
		num=num % n;
		n= n/2;
	}
	if(sayi<0){
	 TwosComplement(sayi,str);
	}
	*string = str;
	return;
}

void TwosComplement(int sayi, char *str){
	int i,elde=1;
	for(i=0;i<ArrayLength(sayi);i++){
			if(str[i]==0){
				str[i]=1;
			}
			else if(str[i]==1){
				str[i]=0;
			}
		}	
		i= ArrayLength(sayi)-1;
		while(elde==1){
			if(str[i]==1){
			str[i] = 0;
			elde=1;
			}
			else{
			str[i] = 1;
			elde=0;
			}
			i--;
		}
		str[0]=1;
		
}

int isFull(int sayi,struct stack *s){
	if(s->top == sayi-1){
		return 1;
	}
	else
		return 0;
}

int isEmpty(struct stack *s){
	if(s->top == -1){
		return 1;
	}
	else
		return 0;
}

void push(struct stack *s, int item, int size){
	if(isFull(size,s)){
		printf("Stack is full.");
		return;
	}
	else{
		s->top++;
		s->array[s->top] = item;
	}
	count++;
	return;
}

void pop(struct stack *s){
	if(isEmpty(s)){
		printf("Stack is empty.");
		return;
	}
	else{
		s->top--;
	}
	count--;
	return;
}

void printStack(struct stack *s){
	int i;
	for(i=0;i<count;i++){
		printf("%d",s->array[i]);
	}
	return;
}

int ArrayLength(int number){
	int i = 0,k=0;
	while(number<(power(-2,i)) || number>(power(2,i))-1){
		i++;
	}
	k = i/8;
	k++;
	i = 8*k;
	return i;
}

int power(int a, int b){
	int i, c=a;
	for(i=1;i<b;i++){
		a *= c;
	}
	if(b==0){
		return 1;
	}
	return a;
}
