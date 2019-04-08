# BLOBS-Finder
## Funcs

### lerFicheiro
- Func de ler ficheiro feita.
- @help: Existe um problema com esta funcao. Ao fazermos fclose(file) ocorre memory leak que não estou a conseguir identificar. Consigo dar printf de um dos parametros da img (usei nome por simplicidade) de todos os elementos quando esta função encontra-se antes do fclose. Exatamente o mesmo print deixa de funcionar depois do fclose e por consequencia, perdemos o ponteiro no resto do programa.

### calcularZonas
- Func de calcular zonas feita.
- Ainda não foi possível testar uma fez que estou com mem leak em cima.

### destruirImagem
- Func dde destruir imagens feita.
- Em principio funciona, uma vez que usei recursividade para tratar disto. Testa-se no fim.
