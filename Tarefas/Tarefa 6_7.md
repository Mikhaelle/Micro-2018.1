Para cada questão, escreva funções em C e/ou sub-rotinas na linguagem Assembly do MSP430. Reaproveite funções e sub-rotinas de uma questão em outra, se assim desejar. Leve em consideração que as sub-rotinas são utilizadas em um código maior, portanto utilize adequadamente os registradores R4 a R11. As instruções da linguagem Assembly do MSP430 se encontram ao final deste texto.

1.(a) Escreva uma função em C que calcule a raiz quadrada x de uma variável S do tipo float, utilizando o seguinte algoritmo: após n+1 iterações, a raiz quadrada de S é dada por
x(n+1) = (x(n) + S/x(n))/2
O protótipo da função é:

```c
#include <stdio.h>

 float Raiz_Quadrada( float S){
	int n;
	float x=1;

	if (S==0){
		return 1;
	}

	if (S==1) {
		return 1;
	}

	for (n=1; n<1000; n++){
		x = (x +S/x)/2;
	}
	return x;
}

int main() {
	float S;
	float Z;
	scanf("%f",&S );
	Z=Raiz_Quadrada(S);
	printf("A raiz quadrada é: %f\n", Z );
	return 0;
}
```

(b) Escreva a sub-rotina equivalente na linguagem Assembly do MSP430. A variável S é fornecida pelo registrador R15, e a raiz quadrada de S (ou seja, a variável x) é fornecida pelo registrador R15 também.

```
divisao:
        MOV.W   #1,R13
        CMP R14,R15
        JGE div_else
        CLR.W R15
        RET
div_else:
        PUSH.W R13
        SUB.W R14,R15
        CALL #divisao
        POP.W R14
        ADD.W R14,R15
        CLR.W R14
        CLR.W R13
        RET

Raiz_Quadrada:
        mov.w #6, R15 ------ valor a ser tirado a raiz
        mov.w #1000, R8 --------- valor do loop
        mov.w #0, R9   -------- valor de i
        mov.w #1,R14
        cmp #2,R15
        jge Raiz_Quadrada_loop
        mov.w #1,R15
        jmp exit
Raiz_Quadrada_loop:
        cmp R8, R9
        jge exit
        mov.w R15,R13
        call divisao ---------- retorna divisao S/x
        add.w R13,R15 --------- adc o valor inicial de R15 no valor da divisao
        mov.w #2, R14 --------- divisao do valor de (S/x + x) por 2
        call divisao
        mov.w R15, R14
        jmp Raiz_Quadrada

exit:
```

2.(a) Escreva uma função em C que calcule x elevado à N-ésima potência, seguindo o seguinte protótipo:
int Potencia(int x, int N);

```c
#include <stdio.h>

 int Potencia(int x, int n){
	int i=0;
  int z=1;

	for (i=0; i<n; i++){
		z=z*x;
	}
	return z;
}

int main() {
	int n;
	int x;
  int z=0;
	scanf("%d",&x );
  scanf("%d",&n );
	z=Potencia(x,n);
	printf("O resultado é: %d\n", z);
	return 0;
}
```

(b) Escreva a sub-rotina equivalente na linguagem Assembly do MSP430. x e n são fornecidos através dos registradores R15 e R14, respectivamente, e a saída deverá ser fornecida no registrador R15.

```
main:   NOP                             ; main program
        MOV.W   #WDTPW+WDTHOLD,&WDTCTL  ; Stop watchdog timer
        MOV.W   #2,R15                 ; R15 = X
        MOV.W   #10,R14                  ; R14 = n
        MOV.W   #0,R13
        MOV.W   R15,R12
        MOV.W  #1,R11
        CALL    #ELEVADO         ; R15 <= sqrt(R15)              
        JMP $                           ; jump to current location '$'
                                        ; (endless loop)

ELEVADO:
      DEC.W R14
      CMP.W R13,R14
      JGE ELEVADO_ELSE

ELEVADO_ELSE:
      CALL #MULTIPLICACAO

MULTIPLICACAO:
      DEC.W R11
      CMP.W R13,R11
      JGE MULTIPLICACAO_ELSE

MULTIPLICACAO_ELSE:
      JEQ EXIT
      ADD.W R12,R15
      CALL #MULTIPLICACAO

EXIT:
    CMP.W R13,R14
    JEQ EXIT_2
    PUSH.W R12
    PUSH.W R15
    POP.W R11
    POP.W R15
    CALL #ELEVADO

EXIT_2:
      JMP $
END
```
3. Escreva uma sub-rotina na linguagem Assembly do MSP430 que calcula a divisão de a por b, onde a, b e o valor de saída são inteiros de 16 bits. a e b são fornecidos através dos registradores R15 e R14, respectivamente, e a saída deverá ser fornecida através do registrador R15.
```
divisao:
        MOV.W   #1,R13
        CMP R14,R15
        JGE div_else
        CLR.W R15
        RET
div_else:
        PUSH.W R13
        SUB.W R14,R15
        CALL #divisao
        POP.W R14
        ADD.W R14,R15
        CLR.W R14
        CLR.W R13
        RET
```

4.Escreva uma sub-rotina na linguagem Assembly do MSP430 que calcula o resto da divisão de a por b, onde a, b e o valor de saída são inteiros de 16 bits. a e b são fornecidos através dos registradores R15 e R14, respectivamente, e a saída deverá ser fornecida através do registrador R15.
```
divisao:
        CMP R14,R15
        JGE div_else
        RET
div_else:
        SUB.W R14,R15
        CALL #divisao
        CLR.W R14
        RET
```
5.(a) Escreva uma função em C que indica a primalidade de uma variável inteira sem sinal, retornando o valor 1 se o número for primo, e 0, caso contrário. Siga o seguinte protótipo:

```c
int Primalidade(unsigned int x){
   int n=0;

  for (n=2; n<x; n++)
  {
    if(x%n == 0){
      return 0;
    }
    else {
      return 1;
    }
  }
  return 0;
}

int main() {
	int x;
  int z;
	scanf("%d",&x );
  z= Primalidade(x);
	printf("O resultado é: %d\n", z);
	return 0;
}
```

int Primalidade(unsigned int x);
(b) Escreva a sub-rotina equivalente na linguagem Assembly do MSP430. A variável de entrada é fornecida pelo registrador R15, e o valor de saída também.
```
main:   NOP                             ; main program
        MOV.W   #WDTPW+WDTHOLD,&WDTCTL  ; Stop watchdog timer
        MOV.W   #10,R15                 ; R15 = X
        MOV.W   #1,R14                  ; R14 = n
        MOV.W   #0,R13
        MOV.W  R15,R12
        CALL    #LOOP         ; R15 <= sqrt(R15)              
        JMP $                           ; jump to current location '$'
                                        ; (endless loop)

;=====================================================
;==================incrementando o divisor============
;=====================================================
LOOP:   
        ADD.W #1, R14
        CMP R14,R12
        JEQ PRIMO
        mov.w R12,R15
        call #divisao
        call #PRIMO

;===================================================
;=================pegando o resto===================
;===================================================
divisao:
        CMP R14,R15
        JGE div_else
        ret
div_else:
        SUB.W R14,R15
        CALL #divisao
        RET

;===============================================
;====conferindo primalidade comparando com 0 ===
;===============================================
PRIMO:
        CMP R13,R15
        JEQ NPRIMO
        JMP EPRIMO
NPRIMO:
        CLR.W R15
        JMP $
EPRIMO:
        CMP R14,R12
        JEQ END1
        CALL #LOOP
END1:
        MOV.W #1, R15
        JMP $

END
```

6. Escreva uma função em C que calcula o duplo fatorial de n, representado por n!!. Se n for ímpar, n!! = 135*...n, e se n for par, n!! = 246...n. Por exemplo, 9!! = 13579 = 945 e 10!! = 2468*10 = 3840. Além disso, 0!! = 1!! = 1. O protótipo da função é:
unsigned long long DuploFatorial(unsigned long long n);

7.(a) Escreva uma função em C que calcula a função exponencial utilizando a série de Taylor da mesma. Considere o cálculo até o termo n = 20. O protótipo da função é double ExpTaylor(double x);
(b) Escreva a sub-rotina equivalente na linguagem Assembly do MSP430, mas considere que os valores de entrada e de saída são inteiros de 16 bits. A variável de entrada é fornecida pelo registrador R15, e o valor de saída também.

8.Escreva uma sub-rotina na linguagem Assembly do MSP430 que indica se um vetor esta ordenado de forma decrescente. Por exemplo: [5 4 3 2 1] e [90 23 20 10] estão ordenados de forma decrescente. [1 2 3 4 5] e [1 2 3 2] não estão. O primeiro endereço do vetor é fornecido pelo registrador R15, e o tamanho do vetor é fornecido pelo registrador R14. A saída deverá ser fornecida no registrador R15, valendo 1 quando o vetor estiver ordenado de forma decrescente, e valendo 0 em caso contrário.

9.Escreva uma sub-rotina na linguagem Assembly do MSP430 que calcula o produto escalar de dois vetores, a e b. O primeiro endereço do vetor a deverá ser passado através do registrador R15, o primeiro endereço do vetor b deverá ser passado através do registrador R14, e o tamanho do vetor deverá ser passado pelo registrador R13. A saída deverá ser fornecida no registrador R15.

10.(a) Escreva uma função em C que indica se um vetor é palíndromo. Por exemplo: [1 2 3 2 1] e [0 10 20 20 10 0] são palíndromos. [5 4 3 2 1] e [1 2 3 2] não são. Se o vetor for palíndromo, retorne o valor 1. Caso contrário, retorne o valor 0. O protótipo da função é:

int Palindromo(int vetor[ ], int tamanho);
(b) Escreva a sub-rotina equivalente na linguagem Assembly do MSP430. O endereço do vetor de entrada é dado pelo registrador R15, o tamanho do vetor é dado pelo registrador R14, e o resultado é dado pelo registrador R15.
