/*
 * funcoes.c
 */

#include "funcoes.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 32
#define DELIM " \n"

int lerFicheiro(char *nf, struct imagem *primeiraImagem) {
	FILE *file = fopen(nf, "r");
	// Error open file
	if (!file)
		return 0;

	char buf[BUFFER_SIZE];
	char *aux;

	struct imagem *novaImg;

	while (!feof(file)) {
		// Alocal nova img
		novaImg = malloc(sizeof(struct imagem));

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
		novaImg->next = primeiraImagem;
		primeiraImagem = novaImg;

	}


	fclose(file);
	printf("%s\n", primeiraImagem->next->next->next->nome_img);
	return 1;
}

void inserirPixel(struct blob *blob, struct pixel pixel) {
	// nao existem blobs
	if (!blob) {
		blob = malloc(sizeof(blob));
		blob->primeiroPixel = &pixel;
	} else {
		struct pixel *aux = blob->primeiroPixel;
		while (aux) {
			// Pixel encontra-se na vizinhança
			if (abs(aux->row - pixel.row) == 1 || abs(aux->col - pixel.col) == 1) {
				// Insere no inicio da lista
				pixel.next = blob->primeiroPixel;
				blob->primeiroPixel = &pixel;
				return;
			}
			aux = aux->next;
		}
	}

	// Nao se enquadra em nenhum blob, necessario criar um novo
	struct blob *novoBlob = malloc(sizeof(blob));
	novoBlob->primeiroPixel = &pixel;

	// Insere novoBlob inicio da lista
	novoBlob->next = blob;
	blob = novoBlob;

}

int calcularZonas(struct imagem *primeiraImagem, uint r, uint g, uint b, uint d) {
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

				inserirPixel(aux->primeiroBlob, aux->array_pixeis[row][col]);

			}
		}
		aux = aux->next;
	}
	return 0;
}

void mostrarZonas(struct imagem *primeiraImagem) {
	struct imagem *aux = primeiraImagem;
	while (aux) {
		printf("%s\n", aux->nome_img);
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
