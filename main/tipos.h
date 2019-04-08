/*
 * tipos.h
 */

#ifndef TIPOS_H_
#define TIPOS_H_

typedef unsigned int uint;

typedef struct {
	uint r, g, b;
} PIXEL;

typedef struct {
// Lista de Pixeis
// Pilha/Fila de Pixeis
// Hashing/Arvores de Pixeis
} BLOB, ZONA;

typedef struct imagem {
	uint nlinhas, ncolunas, ncanais;
	char nome_img[1];
	PIXEL **array_pixeis;
// Estrutura para guardar os BLOB/Zonas
	struct imagem *next;
} IMAGEM;



#endif /* TIPOS_H_ */
