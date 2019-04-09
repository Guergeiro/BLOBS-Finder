/*
 * funcoes.c
 */

#include "funcoes.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 32
#define DELIM " \n"

struct imagem *lerFicheiro(char *nf) {
	FILE *file = fopen(nf, "r");
	// Error open file
	if (!file) {
		printf("Erro abrir ficheiro\n");
		return NULL;
	}

	char buf[BUFFER_SIZE];
	char *aux;

	struct imagem *auxImg = NULL;
	while (!feof(file)) {
		// Alocar nova img
		struct imagem *novaImg = malloc(sizeof(struct imagem));
		if (auxImg)
			novaImg->next = auxImg;

		// Nome img
		fgets(buf, BUFFER_SIZE, file);
		novaImg->nome_img = malloc(strlen(buf) * sizeof(char));
		aux = strtok(buf, DELIM);
		strcpy(novaImg->nome_img, aux);

		// linhas colunas canais
		fgets(buf, BUFFER_SIZE, file);
		aux = strtok(buf, DELIM);
		novaImg->nlinhas = atoi(aux);
		aux = strtok(NULL, DELIM);
		novaImg->ncolunas = atoi(aux);
		aux = strtok(NULL, DELIM);
		novaImg->ncanais = atoi(aux);

		// Creates array Pixeis
		novaImg->array_pixeis = malloc(novaImg->nlinhas * sizeof(struct pixel *));
		for (uint row = 0; row < novaImg->nlinhas; row++) {
			novaImg->array_pixeis[row] = malloc(novaImg->ncolunas * sizeof(struct pixel));
		}

		// Populates array Pixeis
		for (uint row = 0; row < novaImg->nlinhas; row++) {
			for (uint col = 0; col < novaImg->ncolunas; col++) {
				// Saves all pixel values
				fgets(buf, BUFFER_SIZE, file);
				novaImg->array_pixeis[row][col].r = atoi(buf);
				fgets(buf, BUFFER_SIZE, file);
				novaImg->array_pixeis[row][col].g = atoi(buf);
				fgets(buf, BUFFER_SIZE, file);
				novaImg->array_pixeis[row][col].b = atoi(buf);

				// Saves pixel location
				novaImg->array_pixeis[row][col].row = row;
				novaImg->array_pixeis[row][col].col = col;
			}
		}
		// Insere no inicio da lista
		auxImg = novaImg;
	}

	fclose(file);
	return auxImg;
}

void calcularZonas(struct imagem *primeiraImagem, uint r, uint g, uint b, uint d) {
	struct imagem *aux = primeiraImagem;
	while (aux) {
		for (uint row = 0; row < aux->nlinhas; row++) {
			for (uint col = 0; col < aux->ncolunas; col++) {
				// fails red deviation
				if (abs(aux->array_pixeis[row][col].r - r) > d) {
					continue;
				}
				// fails green deviation
				if (abs(aux->array_pixeis[row][col].g - g) > d) {
					continue;
				}
				// fails blue deviation
				if (abs(aux->array_pixeis[row][col].b - b) > d) {
					continue;
				}

			}
		}
		aux = aux->next;
	}
}

void mostrarBlobs(struct blob *blob) {
	if (blob->next) {
		mostrarBlobs(blob->next);
	}
	struct pixel *aux = blob->primeiroPixel;
	printf("[row][col]r g b\n");
	while (aux) {
		printf("[%u][%u]%u %u %u\n", aux->row, aux->col, aux->r, aux->g, aux->b);
		aux = aux->next;
	}
}

void mostrarImagens(struct imagem *primeiraImagem) {
	struct imagem *aux = primeiraImagem;
	while (aux) {
		printf("%s\n", aux->nome_img);
		if (aux->primeiroBlob) {
			mostrarBlobs(aux->primeiroBlob);
		}
		aux = aux->next;
	}
}

void mostrarImagemComMaisZonas(void) {
}

void determinarDesvioPadrao(struct imagem *primeiraImagem) {
}

void determinarZonaMenorDesvioPadraoImagem(void) {
}

void destruirImagem(struct imagem *primeiraImagem) {
	if (primeiraImagem) {
		destruirImagem(primeiraImagem->next);
		destruirBlob(primeiraImagem->primeiroBlob);

		for (uint row = 0; row < primeiraImagem->nlinhas; row++)
			free(primeiraImagem->array_pixeis[row]);
		free(primeiraImagem->array_pixeis);

		free(primeiraImagem->nome_img);

		free(primeiraImagem);
	}
}

void destruirBlob(struct blob *blob) {
	if (blob) {
		destruirBlob(blob->next);
		destruirPixel(blob->primeiroPixel);
		free(blob);
	}
}

void destruirPixel(struct pixel *pixel) {
	if (pixel) {
		destruirPixel(pixel->next);
		free(pixel);
	}
}
