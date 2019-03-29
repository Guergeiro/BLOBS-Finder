/*
 * funcoes.h
 */

#ifndef FUNCOES_H_
#define FUNCOES_H_

#include "tipos.h"

int lerFicheiro(char *nf, IMAGEM *Imag);

int calcularZonas(IMAGEM *Imag, int R, int G, int B, int D);

void mostrarZonas(IMAGEM *Imag);

void mostrarImagemComMaisZonas(void);

void determinarDesvioPadrao(IMAGEM *Imag);

void determinarZonaMenorDesvioPadraoImagem(void);

void destruirImagem(IMAGEM *img);


#endif /* FUNCOES_H_ */
