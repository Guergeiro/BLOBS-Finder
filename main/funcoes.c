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
		struct imagem *novaImg = calloc(1, sizeof(struct imagem));

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
		novaImg->array_pixeis = calloc(novaImg->nlinhas,  sizeof(struct pixel *));
		for (uint row = 0; row < novaImg->nlinhas; row++) {
			novaImg->array_pixeis[row] = calloc(novaImg->ncolunas, sizeof(struct pixel));
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

				// Sets "visitado" to 0
				novaImg->array_pixeis[row][col].visitado = 0;
			}
		}
		// Insere no inicio da lista
		auxImg = novaImg;
	}

	fclose(file);
	return auxImg;
}

int compararPixeis(const struct pixel pixel1, const struct pixel pixel2) {
	return !(abs(pixel1.row - pixel2.row) || abs(pixel1.col - pixel2.col) || abs(pixel1.r - pixel2.r) || abs(pixel1.g - pixel2.g) || abs(pixel1.b - pixel2.b));
}

int pesquisarPixelBlob(struct blob *blob, const struct pixel pixel) {
	struct blob *aux_blob = blob;
	struct pixel *aux_pixel;
	while (aux_blob) {
		aux_pixel = aux_blob->primeiroPixel;
		while (aux_pixel) {
			if (compararPixeis(*aux_pixel, pixel)) {
				return 1;
			}
			aux_pixel = aux_pixel->next;
		}
		aux_blob = aux_blob->next;
	}
	return 0;
}

void pesquisarPixeis(struct imagem *imagem, uint row, uint col, uint r, uint g, uint b, uint d, struct blob *blob) {
	// If pixel was already visited
	if (imagem->array_pixeis[row][col].visitado) {
		return;
	}
	// Fails red
	if (abs(imagem->array_pixeis[row][col].r - r) > d) {
		return;
	}
	// Fails green
	if (abs(imagem->array_pixeis[row][col].g - g) > d) {
		return;
	}
	// Fails blue
	if (abs(imagem->array_pixeis[row][col].b - b) > d) {
		return;
	}

	if (!pesquisarPixelBlob(imagem->primeiroBlob, imagem->array_pixeis[row][col])) {
		// Não está em nenhum blob/não existem blobs.
		if (blob) {
			/*
			 * Estamos perante um pesquisa de profundidade de recursividade.
			 * Adicionamos o pixel ao blob (inicio).
			 */
			imagem->array_pixeis[row][col].next = blob->primeiroPixel;
			blob->primeiroPixel = &imagem->array_pixeis[row][col];
		} else {
			/*
			 * Estamos perante a primeira iteração da recursividade.
			 * Cria-se um blob para os pixeis seguintes.
			 */
			blob = calloc(1, sizeof(struct blob));
			blob->primeiroPixel = &imagem->array_pixeis[row][col];
			if (imagem->primeiroBlob) {
				// Já existe um blob, insere no inicio
				blob->next = imagem->primeiroBlob;
			}
			imagem->primeiroBlob = blob;
			imagem->nblobs++;
		}
		blob->npixeis++;
	}
	// Torna pixel já visitado
	imagem->array_pixeis[row][col].visitado = 1;

	// Pesquisa pixeis adjacentes
	if (row > 0)
		pesquisarPixeis(imagem, row - 1, col, r, g, b, d, blob);
	if (row < imagem->nlinhas - 1)
		pesquisarPixeis(imagem, row + 1, col, r, g, b, d, blob);
	if (col > 0)
		pesquisarPixeis(imagem, row, col - 1, r, g, b, d, blob);
	if (col < imagem->ncolunas - 1)
		pesquisarPixeis(imagem, row, col + 1, r, g, b, d, blob);
}

void calcularZonas(struct imagem *primeiraImagem, uint r, uint g, uint b, uint d) {
	struct imagem *aux = primeiraImagem;
	while (aux) {
		for (uint row = 0; row < aux->nlinhas; row++) {
			for (uint col = 0; col < aux->ncolunas; col++) {
				pesquisarPixeis(aux, row, col, r, g, b, d, NULL);
			}
		}
		aux = aux->next;
	}
}

void mostrarBlobs(struct blob *blob) {
	if (blob->next) {
		mostrarBlobs(blob->next);
	}
	printf("Blob Comeca\n");
	struct pixel *aux = blob->primeiroPixel;
	while (aux) {
		printf("[%u][%u]%u %u %u\n", aux->row, aux->col, aux->r, aux->g, aux->b);
		aux = aux->next;
	}
}

void mostrarImagens(struct imagem *primeiraImagem) {
	struct imagem *aux = primeiraImagem;
	while (aux) {
		printf("[%s] - ", aux->nome_img);
		printf("[row][col]r g b\n");
		if (aux->primeiroBlob) {
			mostrarBlobs(aux->primeiroBlob);
		}
		aux = aux->next;
	}
}

void mostrarImagemComMaisZonas(struct imagem *primeiraImagem) {
	struct imagem *maiorImagem = NULL, *auxImagem = primeiraImagem;
	uint somaMaior = 0, somaAux;
	struct blob *blobAux = NULL;
	while (auxImagem) {
		for (somaAux = 0, blobAux = auxImagem->primeiroBlob; blobAux; somaAux++, blobAux = blobAux->next)
			;
		if (somaAux > somaMaior) {
			somaMaior = somaAux;
			maiorImagem = auxImagem;
		}
		auxImagem = auxImagem->next;
	}
	if (maiorImagem->primeiroBlob) {
		mostrarBlobs(maiorImagem->primeiroBlob);
		printf("%s - %u blobs\n", maiorImagem->nome_img, maiorImagem->nblobs);
	}
}

void determinarDesvioPadrao(struct imagem *primeiraImagem) {
}

void determinarZonaMenorDesvioPadraoImagem(struct imagem *primeiraImagem) {
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
		free(blob);
	}
}
