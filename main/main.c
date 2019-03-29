/*
 * main.c
 */

#include <stdio.h>

#include "funcoes.h"

int menu() {
	printf("1 - Ler de Ficheiro \n");

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
		return 0;
	}

	for (uint cont = 0; cont < argc; cont++)
		printf("parametros[%d] = [%s]\n", cont, argv[cont]);
	return 1;
}
