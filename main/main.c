/*
 * main.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "funcoes.h"

int menu() {
	printf("1 - Ler de Ficheiro\n");
	printf("2 - Calcular zonas (BLOB)\n");
	printf("3 - Calcular zonas ordenadas pelo numero de pixeis\n");
	printf("4 - Calcular imagem com mais zonas\n");
	printf(
			"5 - Determinar desvio padrão para todas as zonas calculadas para cada imagem\n");
	printf(
			"6 - Determinar qual a zona com menor desvio padrão e a que imagem corresponde\n");
	printf("0 - Sair \n");
	printf("Qual a Opcao ");
	int op;
	scanf("%d", &op);
	return op;
}

void testarMem() {
	while (1) {

	}
}

int main(int argc, char **argv) {
	if (argc != 8) {
		printf("Numero parametros incorreto.\n");
		return 1;
	}

	for (uint cont = 0; cont < argc; cont++)
		printf("parametros[%d] = [%s]\n", cont, argv[cont]);

	IMAGEM *Imag = malloc(sizeof(IMAGEM));
	if (!strcmp(argv[7], "MENUS")) {
		uint op;
		do {
			op = menu();
			switch (op) {
			case 1:
				lerFicheiro(argv[2], Imag);
				printf("%s\n", Imag[0].nome_img);
				printf("%u %u %u\n", Imag[0].nlinhas, Imag[0].ncolunas,
						Imag[0].ncanais);
				for (uint row = 0; row < Imag[0].nlinhas; row++) {
					for (uint col = 0; col < Imag[0].ncolunas; col++) {
						printf("%u %u %u\n", Imag[0].array_pixeis[row][col].r,

						Imag[0].array_pixeis[row][col].g,

						Imag[0].array_pixeis[row][col].b);
					}
				}
				break;
			case 2:
				//calcularZonas(IMAGEM *Imag, int R, int G, int B, int D);
				//mostrarZonas(IMAGEM *Imag);
				break;
			case 3:

				break;
			case 4:
				//mostrarImagemComMaisZonas(void);
				break;
			case 5:
				//determinarDesvioPadrao(IMAGEM *Imag);
				break;
			case 6:
				//determinarZonaMenorDesvioPadraoImagem(void);
				break;
			case 0:
				break;
			default:
				printf("Opcao invalida\n");
			}
		} while (op);
	} else if (!strcmp(argv[7], "ALL")) {
		//lerFicheiro(char *nf, IMAGEM *Imag);
		//calcularZonas(IMAGEM *Imag, int R, int G, int B, int D);
		//mostrarZonas(IMAGEM *Imag);
		//mostrarImagemComMaisZonas(void);
		//determinarDesvioPadrao(IMAGEM *Imag);
		//determinarZonaMenorDesvioPadraoImagem(void);
		//destruirImagem(IMAGEM *img);
	} else if (!strcmp(argv[7], "MEM")) {

	} else {
		return 1;
	}
}
