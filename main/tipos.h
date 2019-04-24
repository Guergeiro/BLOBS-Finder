/*
 * tipos.h
 */

#ifndef TIPOS_H_
#define TIPOS_H_

typedef unsigned int uint;

struct pixel {
	uint r, g, b;
	uint row, col;
	uint visitado;
	struct pixel *next;
};

struct blob {
	struct blob *next;
	struct pixel *primeiroPixel;
};

struct imagem {
	uint nlinhas, ncolunas, ncanais, nblobs;
	char *nome_img;
	struct pixel **array_pixeis;
	struct blob *primeiroBlob;
	struct imagem *next;
};

#endif /* TIPOS_H_ */
