/*
 * funcoes.c
 */

#include "funcoes.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 32

int lerFicheiro(char *nf, IMAGEM *img) {
	FILE *file = fopen(nf, "r");
	// Error open file
	if (!file)
		return 0;

	char buf[BUFFER_SIZE];
	char *aux;

	while(!feof(file)) {
		// Alocal nova img + espaco nome img
		IMAGEM *new_image = malloc(sizeof(IMAGEM));

		// Nome img
		fgets(buf, BUFFER_SIZE, file);
		new_image->nome_img = malloc(strlen(buf) * sizeof(char));
		strcpy(new_image->nome_img, buf);

		// linhas colunas canais
		fgets(buf, BUFFER_SIZE, file);
		aux = strtok(buf, " \n");
		new_image->nlinhas = atoi(aux);
		aux = strtok(NULL, " \n");
		new_image->ncolunas = atoi(aux);
		aux = strtok(NULL, " \n");
		new_image->ncanais = atoi(aux);

		// Creates array Pixeis
		new_image->array_pixeis = malloc(new_image->nlinhas * sizeof(PIXEL *));
		for (uint row = 0; row < new_image->nlinhas; row++) {
			new_image->array_pixeis[row] = malloc(new_image->ncolunas * sizeof(PIXEL));
		}

		// Populates array Pixeis
		for (uint row = 0; row < new_image->nlinhas; row++) {
			for (uint col = 0; col < new_image->ncolunas; col++) {
				fgets(buf, BUFFER_SIZE, file);
				new_image->array_pixeis[row][col].r = atoi(buf);
				fgets(buf, BUFFER_SIZE, file);
				new_image->array_pixeis[row][col].g = atoi(buf);
				fgets(buf, BUFFER_SIZE, file);
				new_image->array_pixeis[row][col].b = atoi(buf);
			}
		}

		// Insere no inicio da lista
		new_image->next = img;
		img = new_image;
	}
	printf("%s\n", img->nome_img);

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
