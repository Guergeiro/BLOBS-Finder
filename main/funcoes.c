/*
 * funcoes.c
 */

#include "funcoes.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

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
		novaImg->array_pixeis = calloc(novaImg->nlinhas, sizeof(struct pixel *));
		for (ushort row = 0; row < novaImg->nlinhas; row++) {
			novaImg->array_pixeis[row] = calloc(novaImg->ncolunas, sizeof(struct pixel));
		}

		// Populates array Pixeis
		for (ushort row = 0; row < novaImg->nlinhas; row++) {
			for (ushort col = 0; col < novaImg->ncolunas; col++) {
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

void pesquisarPixeis(struct imagem *imagem, ushort row, ushort col, ushort r, ushort g, ushort b, ushort d, struct blob *blob) {
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

void calcularBlobs(struct imagem *primeiraImagem, ushort r, ushort g, ushort b, ushort d) {
	if (!primeiraImagem) {
		// Não existem imagens
		return;
	}
	struct imagem *aux = primeiraImagem;
	while (aux) {
		for (ushort row = 0; row < aux->nlinhas; row++) {
			for (ushort col = 0; col < aux->ncolunas; col++) {
				pesquisarPixeis(aux, row, col, r, g, b, d, NULL);
			}
		}
		aux = aux->next;
	}
}

void mostrarBlobs(struct blob *blob, char *nomeImagem) {
	if (blob->next) {
		mostrarBlobs(blob->next, nomeImagem);
	}
	printf("%s [%hu][%hu] %hu Pixeis e Desvio Padrao (%f,%f,%f)\n", nomeImagem, blob->primeiroPixel->row, blob->primeiroPixel->col, blob->npixeis, blob->desvioRed, blob->desvioGreen, blob->desvioBlue);
}

void mostrarImagens(struct imagem *primeiraImagem) {
	if (!primeiraImagem) {
		// Não existem imagens
		return;
	}

	struct imagem *aux = primeiraImagem;

	while (aux) {
		if (aux->primeiroBlob) {
			mostrarBlobs(aux->primeiroBlob, aux->nome_img);
		}
		aux = aux->next;
	}
}

void mostrarImagemComMaisBlobs(struct imagem *primeiraImagem) {
	if (!primeiraImagem) {
		// Não existem imagens
		return;
	}
	struct imagem *maiorImagem = NULL, *auxImagem = primeiraImagem;
	ushort somaMaior = 0, somaAux;
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
		//mostrarBlobs(maiorImagem->primeiroBlob);
		printf("%s - %hu blobs\n", maiorImagem->nome_img, maiorImagem->nblobs);
	}
}

void determinarDesvioPadrao(struct imagem *primeiraImagem) {
	if (!primeiraImagem) {
		// Não existem imagens
		return;
	}
	struct imagem *auxImagem = primeiraImagem;
	struct blob *auxBlob = NULL;
	struct pixel *auxPixel = NULL;

	// Calculates std.deviation
	double sumRed = 0, sumGreen = 0, sumBlue = 0, stdRed = 0, stdGreen = 0, stdBlue = 0;

	while (auxImagem) {
		auxBlob = auxImagem->primeiroBlob;
		while (auxBlob) {
			auxPixel = auxBlob->primeiroPixel;
			// Sum
			while (auxPixel) {
				sumRed += auxPixel->r;
				sumGreen += auxPixel->g;
				sumBlue += auxPixel->b;
				auxPixel = auxPixel->next;
			}
			// StdRed
			auxPixel = auxBlob->primeiroPixel;
			while (auxPixel) {
				stdRed += pow(auxPixel->r - (sumRed / auxBlob->npixeis), 2);
				stdGreen += pow(auxPixel->g - (sumGreen / auxBlob->npixeis), 2);
				stdBlue += pow(auxPixel->b - (sumBlue / auxBlob->npixeis), 2);
				auxPixel = auxPixel->next;
			}
			auxBlob->desvioRed = sqrt(stdRed / auxBlob->npixeis);
			auxBlob->desvioGreen = sqrt(stdGreen / auxBlob->npixeis);
			auxBlob->desvioBlue = sqrt(stdBlue / auxBlob->npixeis);
			auxBlob = auxBlob->next;
			// Resetar valores
			sumRed = 0, sumGreen = 0, sumBlue = 0, stdRed = 0, stdGreen = 0, stdBlue = 0;
		}
		auxImagem = auxImagem->next;
	}

	auxImagem = primeiraImagem;
	auxBlob = NULL;

	// Prints std.deviation
	while (auxImagem) {
		auxBlob = auxImagem->primeiroBlob;
		while (auxBlob) {
			printf("%s - [%hu,%hu] - (%lf, %lf, %lf)\n", auxImagem->nome_img, auxBlob->primeiroPixel->row, auxBlob->primeiroPixel->col, auxBlob->desvioRed, auxBlob->desvioGreen, auxBlob->desvioBlue);
			auxBlob = auxBlob->next;
		}
		auxImagem = auxImagem->next;
	}
}

double mediaDesvioPadrao(struct blob *blob) {
	return sqrt((blob->desvioRed + blob->desvioGreen + blob->desvioBlue) / blob->npixeis);
}

void determinarBlobMenorDesvioPadraoImagem(struct imagem *primeiraImagem) {
	if (!primeiraImagem) {
		// Não existem imagens
		return;
	}
	struct imagem *auxImagem = primeiraImagem->next, *minStdDevImagem = primeiraImagem;
	struct blob *auxBlob = NULL, *minStdDevBlob = primeiraImagem->primeiroBlob;
	double minStdDev = mediaDesvioPadrao(minStdDevBlob), auxStdDev;

	while (auxImagem) {
		auxBlob = auxImagem->primeiroBlob;
		while (auxBlob) {
			auxStdDev = mediaDesvioPadrao(auxBlob);
			if (auxStdDev < minStdDev) {
				minStdDevBlob = auxBlob;
				minStdDev = auxStdDev;
				minStdDevImagem = auxImagem;
			}
			auxBlob = auxBlob->next;
		}
		auxImagem = auxImagem->next;
	}

	printf("BLOB (%hu,%hu) com %hu pixeis e media de desvio padrao (%f) da imagem [%s].\n", minStdDevBlob->primeiroPixel->row, minStdDevBlob->primeiroPixel->col, minStdDevBlob->npixeis, minStdDev, minStdDevImagem->nome_img);
}

void swapBlobs(struct blob *a, struct blob *b) {
	struct blob *aux = calloc(1, sizeof(struct blob));
	aux->desvioBlue = a->desvioBlue;
	aux->desvioRed = a->desvioRed;
	aux->desvioGreen = a->desvioGreen;
	aux->npixeis = a->npixeis;
	aux->primeiroPixel = a->primeiroPixel;

	// primeira troca
	a->desvioBlue = b->desvioBlue;
	a->desvioRed = b->desvioRed;
	a->desvioGreen = b->desvioGreen;
	a->npixeis = b->npixeis;
	a->primeiroPixel = b->primeiroPixel;

	// Segunda troca
	b->desvioBlue = aux->desvioBlue;
	b->desvioRed = aux->desvioRed;
	b->desvioGreen = aux->desvioGreen;
	b->npixeis = aux->npixeis;
	b->primeiroPixel = aux->primeiroPixel;
	free(aux);
}

void sortBlobs(struct blob *primeiroBlob) {
	int swapped;
	struct blob *ptr1, *lptr = NULL;

	if (!primeiroBlob)
		return;

	do {
		swapped = 0;
		ptr1 = primeiroBlob;

		while (ptr1->next != lptr) {
			if (ptr1->npixeis > ptr1->next->npixeis) {
				swapBlobs(ptr1, ptr1->next);
				swapped = 1;
			}
			ptr1 = ptr1->next;
		}
		lptr = ptr1;
	} while (swapped);
}

void swapImagens(struct imagem *a, struct imagem *b) {
	struct imagem *aux = calloc(1, sizeof(struct imagem));

	// Primeira troca
	aux->nlinhas = a->nlinhas;
	aux->ncolunas = a->ncolunas;
	aux->ncanais = a->ncanais;
	aux->nblobs = a->nblobs;
	aux->nome_img = a->nome_img;
	aux->array_pixeis = a->array_pixeis;
	aux->primeiroBlob = a->primeiroBlob;

	// Segunda troca
	a->nlinhas = b->nlinhas;
	a->ncolunas = b->ncolunas;
	a->ncanais = b->ncanais;
	a->nblobs = b->nblobs;
	a->nome_img = b->nome_img;
	a->array_pixeis = b->array_pixeis;
	a->primeiroBlob = b->primeiroBlob;

	// Terceira troca
	b->nlinhas = aux->nlinhas;
	b->ncolunas = aux->ncolunas;
	b->ncanais = aux->ncanais;
	b->nblobs = aux->nblobs;
	b->nome_img = aux->nome_img;
	b->array_pixeis = aux->array_pixeis;
	b->primeiroBlob = aux->primeiroBlob;

	free(aux);
}

void sortImagens(struct imagem *primeiraImagem) {
	int swapped;
	struct imagem *ptr1, *lptr = NULL;

	if (!primeiraImagem)
		return;

	do {
		swapped = 0;
		ptr1 = primeiraImagem;

		while (ptr1->next != lptr) {
			if (ptr1->nblobs > ptr1->next->nblobs) {
				swapImagens(ptr1, ptr1->next);
				swapped = 1;
			}
			ptr1 = ptr1->next;
		}
		lptr = ptr1;
	} while (swapped);

	struct imagem *auxImagem = primeiraImagem;
	while (auxImagem) {
		sortBlobs(auxImagem->primeiroBlob);
		auxImagem = auxImagem->next;
	}
}

void destruirBlob(struct blob *blob) {
	if (blob) {
		destruirBlob(blob->next);
		free(blob);
	}
}

void destruirImagem(struct imagem *imagem) {
	if (imagem) {
		destruirImagem(imagem->next);
		destruirBlob(imagem->primeiroBlob);

		for (ushort row = 0; row < imagem->nlinhas; row++)
			free(imagem->array_pixeis[row]);
		free(imagem->array_pixeis);

		free(imagem->nome_img);

		free(imagem);
	}
}
