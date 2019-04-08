/*
 * funcoes.c
 */

#include "funcoes.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 32

int lerFicheiro(char *nf, IMAGEM *Imag) {
	char buf[BUFFER_SIZE];
	FILE *file = fopen(nf, "r");

	if (!file)
		return 0;

	char *aux;

	// Nome img
	fgets(buf, BUFFER_SIZE, file);
	Imag[0].nome_img = malloc((strlen(buf) + 1) * sizeof(char));
	aux = strtok(buf, " \n");
	strcpy(Imag[0].nome_img, aux);

	// linhas colunas canais
	fgets(buf, BUFFER_SIZE, file);
	aux = strtok(buf, " \n");
	Imag[0].nlinhas = atoi(aux);
	aux = strtok(NULL, " \n");
	Imag[0].ncolunas = atoi(aux);
	aux = strtok(NULL, " \n");
	Imag[0].ncanais = atoi(aux);

	// Array Pixeis
	Imag[0].array_pixeis = malloc(
			Imag[0].nlinhas * Imag[0].ncolunas * sizeof(PIXEL));

	for (uint row = 0; row < Imag[0].nlinhas; row++) {
		for (uint col = 0; col < Imag[0].ncolunas; col++) {
			fgets(buf, BUFFER_SIZE, file);
			printf("%s ", buf);
			Imag[0].array_pixeis[row][col].r = atoi(buf);
			fgets(buf, BUFFER_SIZE, file);
			printf("%s ", buf);
			Imag[0].array_pixeis[row][col].g = atoi(buf);
			fgets(buf, BUFFER_SIZE, file);
			printf("%s\n", buf);
			Imag[0].array_pixeis[row][col].b = atoi(buf);
		}
	}

	fclose(file);
	return 1;
}

int calcularZonas(IMAGEM *Imag, int R, int G, int B, int D) {

	return 0;
}

void mostrarZonas(IMAGEM *Imag) {

}

void mostrarImagemComMaisZonas(void) {

}

void determinarDesvioPadrao(IMAGEM *Imag) {

}

void determinarZonaMenorDesvioPadraoImagem(void) {

}

void destruirImagem(IMAGEM *img) {

}
