# BLOBS-Finder
## Funcs

### lerFicheiro (Done)
- Lê ficheiro que contêm as imagens
- return: Ponteiro para a primeira imagem da lista de imagens

### pesquisarPixeis (Done)
- Pesquisa recursivamente todos os pixeis adjacentes a um dado pixel
- Utiliza função **pesquisarPixelBlob()**

### calcularBlobs (Done)
- Calcula e insere os blobs para cada imagem
- Utiliza função **pesquisarPixeis**

### mostrarBlobs (Done)
- Mostra todos os blobs na lista de blobs (recursivamente)

### mostrarImagens (Done)
- Mostra todas as imagens na lista de imagens
- Utiliza função **mostrarBlobs**

### mostrarImagensComMaisBlobs (Done)
- Calcula e mostra a imagem com mais blobs
- Utiliza função **mostrarImagem**

### determinarDesvioPadrao (Done)
- Para todas as imagens e para cada blob das mesmas, calcula o desvio padrão de cada blob nos respetivos canais RGB

### mediaDesvioPadrao (Done)
- Passado um blob como parametro calcula a média dos desvios padroes dos canais rgb
- return: valor do desvio padrão do blob

### determinarBlobMenorDesvioPadraoImagem (Done)
- Percorre todos os blobs 
- Determina o blob com menor media de desvio padrao

### swapBlobs (Done)
- Troca 2 blobs

### sortBlobs (Done)
- Ordena os blobs pelo número de pixeis (crescente)
- Utiliza a função **swapBlobs()**

### swapImagens (Done)
- Troca 2 imagens

### sortImagens (Done)
- Ordena as imagens pelo número de blobs (crescente)
- Utiliza a função **swapImagens**
- Utiliza a funçao **sortBlobs**

### destruirBlob (Done)
- Itera recursivamente por todos os blobs e dá free

### destruirImagem (Done)
- Itera recursivamente por todas as imagens e dá free
- Utiliza função **destruirBlob()**
- Func de destruir imagens feita.
