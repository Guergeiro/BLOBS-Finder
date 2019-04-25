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
	printf("5 - Determinar desvio padrão para todas as zonas calculadas para cada imagem\n");
	printf("6 - Determinar qual a zona com menor desvio padrão e a que imagem corresponde\n");
	printf("0 - Sair \n");
	printf("Qual a Opcao ");
	int op;
	scanf("%d", &op);
	return op;
}

void testarMem(char **argv) {
	while (1) {
		struct imagem *primeiraImagem = lerFicheiro(argv[2]);
		calcularZonas(primeiraImagem, atoi(argv[3]), atoi(argv[4]), atoi(argv[5]), atoi(argv[6]));
		determinarDesvioPadrao(primeiraImagem);
		destruirImagem(primeiraImagem);
	}
}

int main(int argc, char **argv) {
	if (argc != 8) {
		printf("Numero parametros incorreto.\n");
		return 1;
	}

	for (uint cont = 0; cont < argc; cont++)
		printf("parametros[%d] = [%s]\n", cont, argv[cont]);

	if (!strcmp(argv[7], "MENUS")) {
		struct imagem *primeiraImagem = NULL;
		uint op;
		do {
			op = menu();
			switch (op) {
			case 1:
				primeiraImagem = lerFicheiro(argv[2]);
				break;
			case 2:
				calcularZonas(primeiraImagem, atoi(argv[3]), atoi(argv[4]), atoi(argv[5]), atoi(argv[6]));
				mostrarImagens(primeiraImagem);
				break;
			case 3:

				break;
			case 4:
				mostrarImagemComMaisZonas(primeiraImagem);
				break;
			case 5:
				determinarDesvioPadrao(primeiraImagem);
				break;
			case 6:
				determinarZonaMenorDesvioPadraoImagem(primeiraImagem);
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
		calcularZonas(primeiraImagem, atoi(argv[3]), atoi(argv[4]), atoi(argv[5]), atoi(argv[6]));
		mostrarImagens(primeiraImagem);

		mostrarImagemComMaisZonas(primeiraImagem);
		//mostrarImagemComMaisZonas(void);
		determinarDesvioPadrao(primeiraImagem);
		determinarZonaMenorDesvioPadraoImagem(primeiraImagem);
		destruirImagem(primeiraImagem);
	} else if (!strcmp(argv[7], "MEM")) {
		testarMem(argv);
	} else {
		printf("Opcao invalida. Escolhas: MENUS, ALL, MEM");
		// tests
	}
	return 1;
}
