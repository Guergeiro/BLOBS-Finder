# BLOBS-Finder
## Funcs

### lerFicheiro (Done)
- Lê ficheiro que contêm as imagens
- return: Ponteiro para a primeira imagem da lista de imagens

### compararPixeis (Done)
- Compara se 2 pixeis são exatamente iguais, quer nas coordenadas, quer nos valores rgb
- return: 0 caso diferentes, !0 caso iguais

### pesquisarPixelBlob (Done)
- Pesquisa se um dado pixel existe nos blobs de uma imagem
- Utiliza função **compararPixeis()**
- return: 1 caso exista, 0 caso não exista

### calcularZonas
- Devido a umas exceções, o algoritmo vai ter de ser alterado.

### destruirBlob (Done)
- Itera recursivamente por todos os blobs e dá free

### destruirImagem (Done)
- Itera recursivamente por todas as imagens e dá free
- Utiliza função **destruirBlob()**
- Func dde destruir imagens feita.
