/*
 * funcoes.h
 */

#ifndef FUNCOES_H_
#define FUNCOES_H_

#include "tipos.h"

/**
 * Lê o ficheiro que contêm as imagens
 * @param *nf contêm o caminho relativo para o ficheiro
 * @return Ponteiro para a primeira imagem da lista de imagens
 */
struct imagem *lerFicheiro(char *nf);

/**
 * Compara se 2 pixeis são exatamente iguais, quer nas coordenadas, quer nos valores rgb
 * @param pixel1 contêm as informações de um pixel
 * @param pixel2 contêm as informações de um pixel
 * @return 0 caso diferentes, !0 caso iguais
 */
int compararPixeis(const struct pixel pixel1, const struct pixel pixel2);

/**
 * Pesquisa se um dado pixel existe nos blobs de uma imagem
 * Utiliza a função @see compararPixeis()
 * @param *blob contêm ponteiro para o primeiro blob de uma imagem
 * @param pixel contêm as informações do pixel que se quer pesquisar
 * @return 1 caso exista, 0 caso não exista
 */

int pesquisarPixelBlob(struct blob *blob, const struct pixel pixel);

/**
 * Pesquisa todos os pixeis adjacentes numa imagem
 *
 */
void pesquisarPixeis(struct imagem *imagem, uint row, uint col, uint r, uint g, uint b, uint d);

/**
 * Calcula e insere as zonas para cada imagem
 * @param *primeiraImagem contêm o ponteiro para a primeira imagem da lista de imagens
 * @param r valor Red a ser considerado para calcular uma Zona
 * @param g valor Green a ser considerado para calcular uma Zona
 * @param b valor Blue a ser considerado para calcular uma Zona
 * @param d valor Desvio a ser considerado para calcular uma Zona
 */
void calcularZonas(struct imagem *primeiraImagem, uint r, uint g, uint b, uint d);

/**
 * Mostra todos os blobs na lista de blobs
 * @param *blob contêm o ponteiro para o blob
 */
void mostrarBlobs(struct blob *blob);

/**
 * Mostra todas as imagens na lista de imagens
 * Utiliza a função @see calcularZonas()
 * @param *primeiraImagem contêm o pointeiro para a primeira imagem da lista de imagens
 */
void mostrarImagens(struct imagem *primeiraImagem);

void mostrarImagemComMaisZonas(void);

void determinarDesvioPadrao(struct imagem *primeiraImagem);

void determinarZonaMenorDesvioPadraoImagem(void);

void destruirImagem(struct imagem *primeiraImagem);

void destruirBlob(struct blob *blob);

#endif /* FUNCOES_H_ */
