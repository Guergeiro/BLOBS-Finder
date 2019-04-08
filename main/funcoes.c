/*
 * funcoes.c
 */

#include "funcoes.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 32

int lerFicheiro(char *nf, IMAGEM *img) {
	char buf[BUFFER_SIZE];
	FILE *file = fopen(nf, "r");

	if (!file)
		return 0;

	char *aux;

	for (uint i = 0; i < sizeof(img) / sizeof(IMAGEM) && !feof(file); i++) {
		// Nome img
		fgets(buf, BUFFER_SIZE, file);
		img[i].nome_img = malloc((strlen(buf) + 1) * sizeof(char));
		aux = strtok(buf, " \n");
		strcpy(img[0].nome_img, aux);

		// linhas colunas canais
		fgets(buf, BUFFER_SIZE, file);
		aux = strtok(buf, " \n");
		img[i].nlinhas = atoi(aux);
		aux = strtok(NULL, " \n");
		img[i].ncolunas = atoi(aux);
		aux = strtok(NULL, " \n");
		img[i].ncanais = atoi(aux);

		// Array Pixeis
		img[i].array_pixeis = malloc(img[0].nlinhas * sizeof(PIXEL *));
		for (uint row = 0; row < img[0].nlinhas; row++) {
			img[i].array_pixeis[row] = malloc(img[i].ncolunas * sizeof(PIXEL));
		}

		for (uint row = 0; row < img[0].nlinhas; row++) {
			for (uint col = 0; col < img[0].ncolunas; col++) {
				fgets(buf, BUFFER_SIZE, file);
				img[i].array_pixeis[row][col].r = atoi(buf);
				fgets(buf, BUFFER_SIZE, file);
				img[i].array_pixeis[row][col].g = atoi(buf);
				fgets(buf, BUFFER_SIZE, file);
				img[i].array_pixeis[row][col].b = atoi(buf);
			}
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
