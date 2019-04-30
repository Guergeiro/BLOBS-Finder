/*
 * main.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "funcoes.h"

short menu() {
	printf("1 - Ler de Ficheiro\n");
	printf("2 - Calcular Blobs\n");
	printf("3 - Mostrar Blobs ordenados pelo numero de pixeis\n");
	printf("4 - Calcular imagem com mais blobs\n");
	printf("5 - Determinar desvio padrão para todos os blobs calculados para cada imagem\n");
	printf("6 - Determinar qual o blob com menor desvio padrão e a que imagem corresponde\n");
	printf("0 - Sair \n");
	printf("Qual a Opcao ");
	short op;
	scanf("%hu", &op);
	return op;
}

void testarMem(char **argv) {
	while (1) {
		struct imagem *primeiraImagem = lerFicheiro(argv[2]);
		calcularBlobs(primeiraImagem, atoi(argv[3]), atoi(argv[4]), atoi(argv[5]), atoi(argv[6]));
		mostrarImagens(primeiraImagem);
		sortImagens(primeiraImagem);
		mostrarImagens(primeiraImagem);
		mostrarImagemComMaisBlobs(primeiraImagem);
		determinarDesvioPadrao(primeiraImagem);
		determinarBlobMenorDesvioPadraoImagem(primeiraImagem);
		destruirImagem(primeiraImagem);
	}
}

int main(int argc, char **argv) {
	if (argc != 8) {
		printf("Numero parametros incorreto.\n");
		return 1;
	}

	for (ushort cont = 0; cont < argc; cont++)
		printf("parametros[%d] = [%s]\n", cont, argv[cont]);

	if (!strcmp(argv[7], "MENUS")) {
		struct imagem *primeiraImagem = NULL;
		short op;
		do {
			op = menu();
			switch (op) {
				case 1:
					primeiraImagem = lerFicheiro(argv[2]);
					break;
				case 2:
					calcularBlobs(primeiraImagem, atoi(argv[3]), atoi(argv[4]), atoi(argv[5]), atoi(argv[6]));
					mostrarImagens(primeiraImagem);
					break;
				case 3:
					sortImagens(primeiraImagem);
					mostrarImagens(primeiraImagem);
					break;
				case 4:
					mostrarImagemComMaisBlobs(primeiraImagem);
					break;
				case 5:
					determinarDesvioPadrao(primeiraImagem);
					break;
				case 6:
					determinarBlobMenorDesvioPadraoImagem(primeiraImagem);
					break;
				case 0:
					destruirImagem(primeiraImagem);
					break;
				default:
					printf("Opcao invalida\n");
			}
		} while (op);
	} else if (!strcmp(argv[7], "ALL")) {
		struct imagem *primeiraImagem = lerFicheiro(argv[2]);
		calcularBlobs(primeiraImagem, atoi(argv[3]), atoi(argv[4]), atoi(argv[5]), atoi(argv[6]));
		sortImagens(primeiraImagem);
		determinarDesvioPadrao(primeiraImagem);
		mostrarImagens(primeiraImagem);
		mostrarImagemComMaisBlobs(primeiraImagem);
		determinarBlobMenorDesvioPadraoImagem(primeiraImagem);
		destruirImagem(primeiraImagem);
	} else if (!strcmp(argv[7], "MEM")) {
		testarMem(argv);
	} else {
		printf("Opcao invalida. Escolhas: MENUS, ALL, MEM\n");
		// tests
	}
}
