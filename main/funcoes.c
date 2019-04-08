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
		// Nome img
		fgets(buf, BUFFER_SIZE, file);

		// Alocal nova img + espaco nome img
		IMAGEM *new = malloc(sizeof(IMAGEM) + sizeof(char) * strlen(buf));
		strncpy(new->nome_img, buf, strlen(buf) - 1);

		// linhas colunas canais
		fgets(buf, BUFFER_SIZE, file);
		aux = strtok(buf, " \n");
		new->nlinhas = atoi(aux);
		aux = strtok(NULL, " \n");
		new->ncolunas = atoi(aux);
		aux = strtok(NULL, " \n");
		new->ncanais = atoi(aux);

		// Creates array Pixeis
		new->array_pixeis = malloc(new->nlinhas * sizeof(PIXEL *));
		for (uint row = 0; row < new->nlinhas; row++) {
			new->array_pixeis[row] = malloc(new->ncolunas * sizeof(PIXEL));
		}

		// Populates array Pixeis
		for (uint row = 0; row < new->nlinhas; row++) {
			for (uint col = 0; col < new->ncolunas; col++) {
				fgets(buf, BUFFER_SIZE, file);
				new->array_pixeis[row][col].r = atoi(buf);
				fgets(buf, BUFFER_SIZE, file);
				new->array_pixeis[row][col].g = atoi(buf);
				fgets(buf, BUFFER_SIZE, file);
				new->array_pixeis[row][col].b = atoi(buf);
			}
		}

		// Insere no inicio da lista
		new->next = img;
		img = new;
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
