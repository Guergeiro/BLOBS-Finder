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

### pesquisarPixeis (Not Done)
- ***FUNÇÃO ESTÁ A CRIAR UM BLOB PARA CADA PIXEL***
- Pesquisa recursivamente todos os pixeis adjacentes a um dado pixel
- Utiliza função **pesquisarPixelBlob()**

### calcularZonas (Done)
- Calcula e insere as zonas para cada imagem
- Utiliza função **pesquisarPixeis**

### mostrarBlobs (Done)
- Mostra todos os blobs na lista de blobs (recursivamente)

### mostrarImagens (Done)
- Mostra todas as imagens na lista de imagens
- Utiliza função **mostrarBlobs**

### mostrarImagensComMaisZonas (Done)
- Calcula e mostra a imagem com mais zonas
- Utiliza função **mostrarImagem**

### destruirBlob (Done)
- Itera recursivamente por todos os blobs e dá free

### destruirImagem (Done)
- Itera recursivamente por todas as imagens e dá free
- Utiliza função **destruirBlob()**
- Func dde destruir imagens feita.
