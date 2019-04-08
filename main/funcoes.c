/*
 * funcoes.c
 */

#include "funcoes.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 32
#define DELIM " \n"

int lerFicheiro(char *nf, IMAGEM *img) {
	FILE *file = fopen(nf, "r");
	// Error open file
	if (!file)
		return 0;

	char buf[BUFFER_SIZE];
	char *aux;

	while (!feof(file)) {
		// Nome img
		fgets(buf, BUFFER_SIZE, file);
		img->nome_img = malloc(strlen(buf) * sizeof(char));
		aux = strtok(buf, DELIM);
		strcpy(img->nome_img, aux);

		// linhas colunas canais
		fgets(buf, BUFFER_SIZE, file);
		aux = strtok(buf, DELIM);
		img->nlinhas = atoi(aux);
		aux = strtok(NULL, DELIM);
		img->ncolunas = atoi(aux);
		aux = strtok(NULL, DELIM);
		img->ncanais = atoi(aux);

		// Creates array Pixeis
		img->array_pixeis = malloc(img->nlinhas * sizeof(PIXEL *));
		for (uint row = 0; row < img->nlinhas; row++) {
			img->array_pixeis[row] = malloc(img->ncolunas * sizeof(PIXEL));
		}

		// Populates array Pixeis
		for (uint row = 0; row < img->nlinhas; row++) {
			for (uint col = 0; col < img->ncolunas; col++) {
				fgets(buf, BUFFER_SIZE, file);
				img->array_pixeis[row][col].r = atoi(buf);
				fgets(buf, BUFFER_SIZE, file);
				img->array_pixeis[row][col].g = atoi(buf);
				fgets(buf, BUFFER_SIZE, file);
				img->array_pixeis[row][col].b = atoi(buf);
			}
		}

		// Alocal nova img + espaco nome img
		IMAGEM *novaImg = malloc(sizeof(IMAGEM));

		// Insere no inicio da lista
		novaImg->next = img;
		img = novaImg;
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
