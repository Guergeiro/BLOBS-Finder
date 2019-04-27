/*
 * tipos.h
 */

#ifndef TIPOS_H_
#define TIPOS_H_

typedef unsigned short ushort;

struct pixel {
	ushort r, g, b;
	ushort row, col;
	ushort visitado;
	struct pixel *next;
};

struct blob {
	ushort npixeis;
	double desvioRed, desvioGreen, desvioBlue;
	struct blob *next;
	struct pixel *primeiroPixel;
};

struct imagem {
	ushort nlinhas, ncolunas, ncanais, nblobs;
	char *nome_img;
	struct pixel **array_pixeis;
	struct blob *primeiroBlob;
	struct imagem *next;
};

#endif /* TIPOS_H_ */
