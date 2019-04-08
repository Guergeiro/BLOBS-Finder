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

typedef struct {
	uint nlinhas, ncolunas, ncanais;
	char *nome_img;
	PIXEL **array_pixeis;
// Estrutura para guardar os BLOB/Zonas
} IMAGEM;

#endif /* TIPOS_H_ */
