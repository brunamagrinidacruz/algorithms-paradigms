// 03-12-2020

#include <iostream>
#include <stdio.h>
#include <string.h>

using namespace std;

void calcular_borda(long int *borda, char *padrao, long int tamanho_padrao){
	long int i = 0, j = -1; 
	borda[0] = -1;

	while (i < tamanho_padrao){
		while (j>=0 && padrao[i] != padrao[j]) { 
			j = borda[j]; 
		}   
		i++; j++;
		borda[i] = j;
	}
}

void kmp(long int *borda, char *padrao,  long int tamanho_padrao, char *texto,  long int tamanho_texto){
	long int i = 0, j = 0;
	while (i < tamanho_texto){
		while (j >= 0 &&  texto[i] != padrao[j]) {
			j = borda[j];
		}
		i++; j++;
		if (j == tamanho_padrao) { /*!< Encontrou o padrao */
			printf("O padrao foi encontrado na posicao %ld\n", i-j);
			j = borda[j];
		}
	}
}

int main(void){
    char texto[260000];
    char padrao[1000];

    long int borda[1000+10];

    scanf("%s", texto);
    scanf("%s", padrao);

    long int tamanho_texto = strlen(texto);
	long int tamanho_padrao = strlen(padrao);

	texto[tamanho_texto] = '\0';
	padrao[tamanho_padrao] = '\0';

	calcular_borda(borda, padrao, tamanho_padrao);

	kmp(borda, padrao, tamanho_padrao, texto, tamanho_texto);

    return 0;
}