/*
 * funcoes.h
 */

#ifndef FUNCOES_H_
#define FUNCOES_H_

#include "tipos.h"

int lerFicheiro(char *nf, struct imagem *primeiraImagem);

void inserirPixel(struct blob *blob, struct pixel primeiroPixel);

int calcularZonas(struct imagem *primeiraImagem, uint r, uint g, uint b, uint d);

void mostrarZonas(struct imagem *primeiraImagem);

void mostrarImagemComMaisZonas(void);

void determinarDesvioPadrao(struct imagem *primeiraImagem);

void determinarZonaMenorDesvioPadraoImagem(void);

void destruirImagem(struct imagem *primeiraImagem);

void destruirBlob(struct blob *blob);

void destruirPixel(struct pixel *primeiroPixel);

#endif /* FUNCOES_H_ */
