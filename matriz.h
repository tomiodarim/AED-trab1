#ifndef MATRIZ_H_INCLUDED
#define MATRIZ_H_INCLUDED


typedef struct celula {
  int linha, coluna;	     // posicao na matriz
  struct celula *direita; // celula a direita
  struct celula *abaixo;  // celula abaixo
  int valor; 							 // valor do elemento na posicao (linha,coluna)
} Celula;

typedef struct {
	Celula *first;			// endereço da célula de posição -1,-1
	int totalLinhas;		// total de linhas na matriz
	int totalColunas;		// total de colunas na matriz
} Matriz;

// Cria uma matriz
// Pré-condição: ter o numero total de linhas e de colunas
// Pós-condição: é inicializado uma matriz com apenas os cabeçalhos de linhas e colunas
Matriz* inicializar(int l, int c);

// Insere um elemento em determinada matriz na linha e coluna especificada
// Pré-condição: exitir uma matriz que tenha a linha e coluna especificada
// Pós-condição: é inserido o elemento na matriz
void inserir(Matriz *m, int l, int c, int valor);

// Imprime os valores da matriz na tela, caso não exita uma determinada célula é imprimido 0
// Pré-condição: exitir a matriz
// Pós-condição: nenhuma
void imprimir(Matriz *m);

// Soma duas matrizes
// Pré-condição: ambas as matrizes serem de mesma ordem
// Pós-condição: retorna uma matriz resultante da soma
Matriz* soma(Matriz *m1, Matriz *m2);

// Subtrai duas matrizes
// Pré-condição: ambas as matrizes serem de mesma ordem
// Pós-condição: retorna uma matriz resultante da subtração
Matriz* subtrai(Matriz *m1, Matriz *m2);

// Multiplica duas matrizes
// Pré-condição: ambas as matrizes serem de tamanhos compatíveis para a multiplicação
// Pós-condição: retorna uma matriz resultante da multiplicação
Matriz* multiplica(Matriz *m1, Matriz *m2);

// Calcula a transposta de uma matriz
// Pré-condição: existir a matriz
// Pós-condição: retorna uma matriz transposta
Matriz* transposta(Matriz *m1);

// Imprime na tela se uma matriz é simetrica ou não
// Pré-condição: existir a matriz
// Pós-condição: nenhuma
void simetrica(Matriz *m);

// Libera a memória excluindo uma matriz
// Pré-condição: existir a matriz
// Pós-condição: exclui a matriz e libera a memoria
void excluir(Matriz *m);

// Lê uma matriz de um arquivo de texto
// Pré-condição: nenhuma
// Pós-condição: é inicializada uma matriz conforme especificada no arquivo
Matriz* lerMatriz(FILE *f);

#endif // MATRIZ_H_INCLUDED
