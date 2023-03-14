myss SEGMENT PARA STACK 's'
        DW 20 DUP(?)
myss ENDS
myds SEGMENT PARA 'd'
		n dw 10
myds ENDS
mycs SEGMENT PARA 'c'
    ASSUME CS:mycs, DS:myds, SS:myss

ANA PROC FAR
	PUSH DS               
	XOR AX, AX
	PUSH AX
	MOV AX, myds        
	MOV DS, AX
	
	PUSH n
	CALL FAR PTR DNUM      
	POP AX
	CALL PRINTINT

	RETF                           
ANA ENDP                        

DNUM PROC FAR
     PUSH AX		; Fonksiyonda kullanacağımız registerları stackte yedekliyoruz.
     PUSH BX
     PUSH CX
     PUSH BP

     MOV BP,SP		; SP'nin yerini kaybetmemek için BP'de yedekliyoruz.
     MOV AX,[BP+12] ; 4 adet word değer pushladık. 2 word değer de proc far çağrısından dolayı pushlandı.
					; Fonksiyon çağrılmadan önce pushlanan n değeri stack'te 12 byte geride kaldığı için AX'i BP+12'ye eşitledik.
	 MOV BX,AX	    ; AX'i BX'de yedekledim.        

	 CMP AX,0		; AX'in 0,1 ya da 2'ye eşit olup olmama durumları kontrol edilip buna göre jump yapılacak.
	 JZ sifir
	 CMP AX,1
	 JZ bir_iki
	 CMP AX,2 		; Hiçbirine eşit değilse dallanma yapılmadan rekörsif kısma geçilecek.
	 JZ bir_iki        

rekorsif:
	 DEC AX  		; AX = N-1
	 PUSH AX        ; Fonksiyonda kullanmak üzere AX değerini pushluyorum.        
	 CALL DNUM		
	 POP CX 		; CX = D(N-1) 

	 PUSH CX               
	 CALL DNUM
	 POP CX			; CX = D( D(N-1) ) --> Rekürans bağıntısında toplamanın solunda kalan kısmı elde ettik.
	 
	 DEC BX 		; BX = N-1
	 MOV AX,BX 		; AX = N-1
	 DEC AX 		; AX = N-2
	 PUSH AX
	 CALL DNUM
	 POP AX 		; AX = D(N-2)
	 
	 SUB BX,AX		; BX = (N-1) - D(N-2)
	 PUSH BX
	 CALL DNUM
	 POP BX	 		; BX = D((N-1)-D(N-2)) --> Rekürans bağıntısında toplamanın sağında kalan kısım da elde edildi.

 	 ADD BX,CX	 	; BX = D( D(N-1) ) + D((N-1)-D(N-2))
	 MOV AX,BX 		; Sonucu AX registerına aldım.
 	 JMP son

sifir:
	 XOR AX,AX 		; Sonuç 0 AX'de saklandı.
	 JMP son

bir_iki: 
	 MOV AX,1		; Sonuç 1 AX'de saklandı.

son:
	 MOV [BP+12],AX ; İçteki prosedür çağırılmadan önce pushlanan değerin olduğu stack kısmına sonucu yazdım. 
	 POP BP
	 POP CX
	 POP BX
	 POP AX		 	; Registerlar prosedür başlamadan önceki değerlerini aldı.
	 RETF
DNUM ENDP

PRINTINT PROC
	MOV BX,10          ; 10'a bölüm yapılacağı için BX = 10 yapıldı.
	MOV CX,0           ; CX'te digit sayısı tutulacak. Başlangıç değeri 0 yapıldı.
	
	; AX'deki hex değeri decimale çeviriyoruz
dongu:
    XOR DX,DX       ; DX'i sıfırla.
    DIV BX           ; AX'i BX'e böl. Bölümü AX kalanı DX'te sakla.
    ADD DL,'0'      ; Kalan kısmın ASCII kodunu bulmak için kalan kısmına 0'ın ASCII değeri eklendi.
    PUSH DX          ; Bulunan değer stack'e pushlandı.
    INC CX           ; Digit sayısı artırıldı.
    CMP AX,0        ; Bölüm 0 ile karşılaştırıldı. Eğer 0'landıysa döngü bitirilecek ve yazdırma işlemine geçilecek.
    JNE dongu        ; Eğer bölüm 0 değilse decimale çevirmeye devam etmek üzere döngü kısmının başına dönülecek.
	
	; Ters sırayla basamakları yazdırıyoruz.	
yazdir:
    POP DX           ; Stack'teki son basamağı okuyoruz. (En büyük basamak)
    MOV AH,02H      ; 02H yani karakter gösterme fonksiyonunu set up ediyoruz.
    INT 21H          ; Basamağı yazdırıyoruz.
    LOOP yazdir
	
	MOV AH,4CH        ; Programı kapatma fonksiyonunu set up ediyoruz.
	INT 21H            
	RETF
PRINTINT ENDP

mycs ENDS
END ANA