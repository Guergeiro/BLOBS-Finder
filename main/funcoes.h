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
 * @return 1 caso diferentes, 0 caso iguais
 */
ushort compararPixeis(const struct pixel pixel1, const struct pixel pixel2);

/**
 * Pesquisa se um dado pixel existe nos blobs de uma imagem
 * @see compararPixeis()
 * @param *blob contêm ponteiro para o primeiro blob de uma imagem
 * @param pixel contêm as informações do pixel que se quer pesquisar
 * @return 1 caso exista, 0 caso não exista
 */

ushort pesquisarPixelBlob(struct blob *blob, const struct pixel pixel);

/**
 * Pesquisa todos os pixeis adjacentes numa imagem
 * Utiliza função @see pesquisarPixelBlob()
 * @param *imagem contêm ponteiro para a imagem que estamos a tratar
 * @param row contêm a linha do pixel atual
 * @param col contêm a coluna do pixel atual
 * @param r contêm o valor do canal Red que devemos considerar
 * @param g contêm o valor do canal Green que devemos considerar
 * @param b contêm o valor do canal Blue que devemos considerar
 * @param d contêm o valor de desvio que devemos considerar para todos os canais
 * @param *blob contêm ponteiro para o blob a que estamos adicionar, NULL caso seja o primeiro pixel a pesquisar
 */
void pesquisarPixeis(struct imagem *imagem, ushort row, ushort col, ushort r, ushort g, ushort b, ushort d, struct blob *blob);

/**
 * Calcula e insere os blobs para cada imagem
 * @param *primeiraImagem contêm o ponteiro para a primeira imagem da lista de imagens
 * @param r valor Red a ser considerado para calcular um Blob
 * @param g valor Green a ser considerado para calcular um Blob
 * @param b valor Blue a ser considerado para calcular um Blob
 * @param d valor Desvio a ser considerado para calcular um Blob
 */
void calcularBlobs(struct imagem *primeiraImagem, ushort r, ushort g, ushort b, ushort d);

/**
 * Mostra todos os blobs na lista de blobs
 * @param *blob contêm o ponteiro para o blob
 */
void mostrarBlobs(struct blob *blob, char *nomeImagem);

/**
 * Mostra todas as imagens na lista de imagens
 * @see calcularZonas()
 * @param *primeiraImagem contêm o pointeiro para a primeira imagem da lista de imagens
 */
void mostrarImagens(struct imagem *primeiraImagem);

/**
 * Mostra a imagem com mais blobs
 * @see mostrarImagens()
 * @param *primeiraImagem contêm o pointeiro para a primeira imagem da lista de imagens
 */
void mostrarImagemComMaisBlobs(struct imagem *primeiraImagem);

/**
 * Para todas as imagens, determina e mostra o desvio padrão
 * @param *primeiraImagem contêm o ponteiro para a primeira imagem da lista de imagens
 */
void determinarDesvioPadrao(struct imagem *primeiraImagem);

/**
 * Dado um blob, determina o desvio padrão médio do mesmo (Red + Green + Blue)
 * @param *blob contêm o ponteiro para o blob
 * @return valor do desvio padrão médio
 */
double mediaDesvioPadrao(struct blob *blob);

/**
 * Para todas as imagens, determina e mostra a imagem com menor desvio padrão blob
 * @param *primeiraImagem contêm o ponteiro para a primeira imagem da lista de imagens
 * Utiliza a função @see mediaDesvioPadrao()
 */
void determinarBlobMenorDesvioPadraoImagem(struct imagem *primeiraImagem);

/**
 * Troca 2 blobs
 * @param *a contêm ponteiro para um blob
 * @param *b contêm ponteiro para outro blob
 */
void swapBlobs(struct blob *a, struct blob *b);

/**
 * Ordena os blobs pelo número de pixeis (crescente)
 * @see swapBlobs()
 * @param *primeiroBlob contêm ponteiro para o primeiro blob da lista de blobs
 */
void sortBlobs(struct blob *primeiroBlob);

/**
 * Troca 2 imagens
 * @param *a contêm ponteiro para uma imagem
 * @param *b contêm ponteiro para outra imagem
 */
void swapImagens(struct imagem *a, struct imagem *b);

/**
 * Ordena as imagens pelo número de blobs (crescente)
 * @see swapImagens()
 * @see sortBlobs()
 * @param *primeiraImagem contêm ponteiro para a primeira imagem da lista de imagens
 */
void sortImagens(struct imagem *primeiraImagem);

void destruirImagem(struct imagem *primeiraImagem);

void destruirBlob(struct blob *blob);

#endif /* FUNCOES_H_ */
