#include <stdio.h>
#include <stdlib.h>
#include "matriz.h"

// Faz a inicialização dos cabeçalhos das linhas e colunas, essa função é chamada apenas pela função inicializar()
// Pré-condição: nenhuma
// Pós-condição: inicializa a célula do cabeçalho
Celula* inicializaCelula(int l, int c, Celula *f){
	Celula *next = (Celula*) malloc(sizeof(Celula));
	next->linha = l;
	next->coluna = c;
	next->valor = 0;
	next->direita = (l == 0 ? f : next);
	next->abaixo = (l == 0 ? next : f);

	return next;
}

// Cria uma matriz
// Pré-condição: ter o numero total de linhas e de colunas
// Pós-condição: é inicializado uma matriz com apenas os cabeçalhos de linhas e colunas
Matriz* inicializar (int l, int c) {
	int i; Celula *aux, *next;

	Matriz* mat = (Matriz*) malloc(sizeof(Matriz)); //aloca matriz
	mat->totalLinhas = l;
	mat->totalColunas = c;

	Celula* first = (Celula*) malloc(sizeof(Celula)); //aloca a célula -1,-1
	first->linha = -1;
	first->coluna = -1;
 	first->valor = 0;
	first->direita = first;
	first->abaixo = first;

	mat->first = first; //define na matriz o ponteiro para a primeira célula

	//aloca o cabeçalho das linhas
	for(aux = first, i = c; i > 0; i--) {
		next = inicializaCelula(0, -1, first);
		aux->direita = next;
		aux = next;
	}
    
	//aloca o cabeçalho das colunas	
  for(aux = first, i = l; i > 0; i--) {
		next = inicializaCelula(-1, 0, first);
		aux->abaixo = next;
		aux = next;
  }

	return mat; //retorna o ponteiro para a matriz
}

// Insere um elemento em determinada matriz na linha e coluna especificada
// Pré-condição: exitir uma matriz que tenha a linha e coluna especificada
// Pós-condição: é inserido o elemento na matriz
void inserir(Matriz *m, int l, int c, int v){
	//analisa se existe a linha e coluna na matriz
	if(m->totalLinhas < l || m->totalColunas < c){
		printf("Linha e/ou coluna inexistente!\n");
		return;
	}
	int i;
  Celula *firstLinha, *firstColuna, *antLinha, *antColuna, *newCelula;

	for(firstLinha = m->first, i = 0; i < l; i++) //encontra o cabeçalho da linha
	  firstLinha = firstLinha->abaixo;
	    
	for(firstColuna = m->first, i = 0; i < c; i++) //encontra o cabeçalho da coluna
	  firstColuna = firstColuna->direita;
	
	antLinha = firstLinha;
	antColuna = firstColuna;

  while(antLinha->direita != firstLinha) antLinha = antLinha->direita; //encontra na linha a célula anterior a que vai ser inserida
	while(antColuna->abaixo != firstColuna) antColuna = antColuna->abaixo; //encontra na coluna a célula anterior a que vai ser inserida
    
	//aloca a celula inserida e define suas variaveis
	newCelula = (Celula*) malloc(sizeof(Celula));
	newCelula->linha = l;
	newCelula->coluna = c;
	newCelula->valor = v;
	newCelula->direita = firstLinha;
	newCelula->abaixo = firstColuna;
	antLinha->direita = newCelula;
	antColuna->abaixo = newCelula;
	
}

// Imprime os valores da matriz na tela, caso não exita uma determinada célula é imprimido 0
// Pré-condição: exitir a matriz
// Pós-condição: nenhuma
void imprimir(Matriz *m){
	if(m == NULL){
		printf("Ponteiro nulo!");
		return;
	}
	Celula *firstLinha = m->first->abaixo;
	Celula *atual = firstLinha->direita;
	int i, j;	
	printf("\n");
	//avança nas linha
	for(i = 1; i <= m->totalLinhas; i++){
		//avança nas colunas imprimindo o valor de cada célula ou 0 se a célula não existir
		for(j = 1; j <= m->totalColunas; j++){
			if(atual->linha == i && atual->coluna == j){
				printf("%3d ", atual->valor);
				atual = atual->direita;
			}
			else
				printf("  0 ");
		}
		printf("\n");
		firstLinha = firstLinha->abaixo;
		atual = firstLinha->direita;
	}
	printf("\n\n");
}

// Soma duas matrizes
// Pré-condição: ambas as matrizes serem de mesma ordem
// Pós-condição: retorna uma matriz resultante da soma
Matriz* soma(Matriz *m1, Matriz *m2){
	int i, j;
  Matriz *resultante;
	Celula *m1Linha = m1->first->abaixo;
	Celula *m1Atual = m1Linha->direita;
	Celula *m2Linha = m2->first->abaixo;
	Celula *m2Atual = m2Linha->direita;

	//analisa se as matrizes são de mesma ordem
	if(m1->totalLinhas != m2->totalLinhas || m1->totalColunas != m2->totalColunas){
		printf("Matrizes de ordens diferentes!\n");
		return NULL;
	}
	else{
		resultante = inicializar(m1->totalLinhas, m1->totalColunas); 		//inicializa a matriz resultante
		//avança nas linhas
		for(i = 1; i <= m1->totalLinhas; i++){
			//avança nas colunas
			for(j = 1; j <= m1->totalColunas; j++){
				//caso a célula só exista na primeira matriz é inserido o valor dela
				if(m1Atual->coluna == j && m2Atual->coluna != j ){
					inserir(resultante,i,j,m1Atual->valor);
					m1Atual = m1Atual->direita;
				}
				//caso a célula só exista na segunda matriz é inserido o valor dela
				if(m2Atual->coluna == j && m1Atual->coluna != j ){
					inserir(resultante,i,j,m2Atual->valor);
					m2Atual = m2Atual->direita;
				}
				//caso a célula exista nas duas matrizes é inserido o valor da soma
				if(m1Atual->coluna == j && m2Atual->coluna == j ){
					inserir(resultante,i,j,m1Atual->valor + m2Atual->valor);
					m1Atual = m1Atual->direita;
				  m2Atual = m2Atual->direita;
				}
			}
			m1Linha = m1Linha->abaixo;
			m1Atual = m1Linha->direita;
			m2Linha = m2Linha->abaixo;
			m2Atual = m2Linha->direita;
		}
	}
	return resultante;
}

// Subtrai duas matrizes
// Pré-condição: ambas as matrizes serem de mesma ordem
// Pós-condição: retorna uma matriz resultante da subtração
Matriz* subtrai(Matriz *m1, Matriz *m2){
	int i, j;
  Matriz *resultante;
	Celula *m1Linha = m1->first->abaixo;
	Celula *m1Atual = m1Linha->direita;
	Celula *m2Linha = m2->first->abaixo;
	Celula *m2Atual = m2Linha->direita;
	
	//analisa se as matrizes são de mesma ordem
	if(m1->totalLinhas != m2->totalLinhas || m1->totalColunas != m2->totalColunas){
		printf("Matrizes de ordens diferentes!\n");
		return NULL;
	}
	else{
		resultante = inicializar(m1->totalLinhas, m1->totalColunas); 	//inicializa a matriz resultante
		//avança nas linhas
		for(i = 1; i <= m1->totalLinhas; i++){
			//avança nas colunas
			for(j = 1; j <= m1->totalColunas; j++){
				//caso a célula só exista na primeira matriz é inserido o valor dela
				if(m1Atual->coluna == j && m2Atual->coluna != j ){
					inserir(resultante,i,j,m1Atual->valor);
					m1Atual = m1Atual->direita;
				}
				//caso a célula só exista na segunda matriz é inserido o negativo do valor dela
				if(m2Atual->coluna == j && m1Atual->coluna != j ){
					inserir(resultante,i,j,-m2Atual->valor);
					m2Atual = m2Atual->direita;
				}
				//caso a célula exista nas duas matrizes é inserido o valor da subtração da primeira pela segunda
				if(m1Atual->coluna == j && m2Atual->coluna == j ){
					inserir(resultante,i,j,m1Atual->valor - m2Atual->valor);
					m1Atual = m1Atual->direita;
				  m2Atual = m2Atual->direita;
				}
			}
			m1Linha = m1Linha->abaixo;
			m1Atual = m1Linha->direita;
			m2Linha = m2Linha->abaixo;
			m2Atual = m2Linha->direita;
		}
	}
	return resultante;
}

// Multiplica duas matrizes
// Pré-condição: ambas as matrizes serem de tamanhos compatíveis para a multiplicação
// Pós-condição: retorna uma matriz resultante da multiplicação
Matriz* multiplica(Matriz *m1, Matriz *m2){
	//analisa se as matrizes são compatíveis para a multiplicação
	if(m1->totalColunas != m2->totalLinhas){
		printf("Nao e possível realizar essa multiplicacao!\n");
		return NULL;
	}

	Matriz *resultante;
	resultante = inicializar(m1->totalLinhas, m2->totalColunas); //inicializa a matriz resultante
	int i, j, k, soma;
	Celula *m1Linha = m1->first->abaixo;
	Celula *m1Atual = m1Linha->direita;
	Celula *m2Coluna = m2->first->direita;
	Celula *m2Atual = m2Coluna->abaixo;

	//avança as linhas da primeira
	for(i = 1; i <= m1->totalLinhas; i++) {
		//avança as colunas da segunda
		for(j = 1, soma = 0; j <= m2->totalColunas; j++, soma = 0) {
			//avança as colunas da primeira e linhas da segunda
			for(k = 1; k <= m1->totalColunas; k++) {
				//caso exista a célula apenas na primeira matriz avança para a próxima
				if((m1Atual->linha == i && m1Atual->coluna == k) && (m2Atual->linha != k || m2Atual->coluna != j))
					m1Atual = m1Atual->direita;
				//caso exista a célula apenas na segunda matriz avança para a próxima
				if((m1Atual->linha != i || m1Atual->coluna != k) && (m2Atual->linha == k && m2Atual->coluna == j))
					m2Atual = m2Atual->abaixo;
				//caso exista a célula nas duas matrizes é feito a multiplicação e somado a variavel auxiliar 
				if((m1Atual->linha == i && m1Atual->coluna == k) && (m2Atual->linha == k && m2Atual->coluna == j)){
					soma += m1Atual->valor * m2Atual->valor;
					m1Atual = m1Atual->direita;
					m2Atual = m2Atual->abaixo;
				}
			}
			//insere a célula resultante da multiplicação de uma das linha por uma das colunas na matriz resultante
			inserir(resultante,i,j,soma);
			m1Atual = m1Linha->direita;
			m2Coluna = m2Coluna->direita;
			m2Atual = m2Coluna->abaixo;
		}
		m1Linha = m1Linha->abaixo;
		m1Atual = m1Linha->direita;
		m2Coluna = m2Coluna->direita;
		m2Atual = m2Coluna->abaixo;
	}

	return resultante;
}

// Calcula a transposta de uma matriz
// Pré-condição: nenhuma
// Pós-condição: retorna uma matriz transposta
Matriz* transposta(Matriz *m){
  Matriz *resultante; Celula *firstLinha, *aux;
  firstLinha = m->first->abaixo;
  resultante = inicializar(m->totalColunas, m->totalLinhas); //inicializa a matriz resultante
  
	//avança as linhas
  while(firstLinha != m->first){
    aux = firstLinha->direita;
		//avança as colunas
    while(aux != firstLinha){
      inserir(resultante,aux->coluna,aux->linha,aux->valor); //insere a célula a matriz resultante com o valor das linha e colunas invertido 
      aux = aux->direita;
    }
    firstLinha = firstLinha->abaixo;
  }
    
  return resultante;
}

// Analisa se uma matriz é simetrica, essa função é chamada apenas pela função simetrica()
// Pré-condição: nenhuma
// Pós-condição: retorna 1 caso seja simetrica e 0 caso contrário
int isSimetrica(Matriz *m1){
	//analisa se é uma matriz quadrada
  if(m1->totalLinhas != m1->totalColunas)
    return 0;
		  
  Matriz *m2;
  m2 = transposta(m1); //gera uma matriz transposta
    
  Celula *m1Atual, *m2Atual;
  Celula *m1Linha = m1->first->abaixo;
	Celula *m2Linha = m2->first->abaixo;
	
	//avança nas linhas
	while(m1Linha != m1->first){
  	m1Atual = m1Linha->direita;
    m2Atual = m2Linha->direita;
		//avança nas colunas
    while(m1Atual != m1Linha){
			//se uma célula existir em for diferente na matriz e na transposta, então não será simetrica
      if(m1Atual->linha != m2Atual->linha || m1Atual->coluna != m2Atual->coluna || m1Atual->valor != m2Atual->valor)
        return 0;
      m1Atual = m1Atual->direita;
      m2Atual = m2Atual->direita;
    }
    m1Linha = m1Linha->abaixo;
    m2Linha = m2Linha->abaixo;
  }
	excluir(m2);
	//caso todas as células da matriz e da transposta forem iguais a mtriz será simetrica
	return 1;
}

// Imprime na tela se uma matriz é simetrica ou não
// Pré-condição: nenhuma
// Pós-condição: nenhuma
void simetrica(Matriz *m){
	if(isSimetrica(m)) printf("\nsimetrica: SIM\n\n");
	else printf("\nsimterica: NAO\n\n");
}

// Libera a memória excluindo uma matriz
// Pré-condição: existir a matriz
// Pós-condição: exclui a matriz e libera a memoria
void excluir(Matriz *m){
	int i;
	Celula *firstLinha = m->first->abaixo;
	Celula *atual, *next;
	
	while(firstLinha != m->first){
		atual = firstLinha->direita;
		while(atual != firstLinha){
			next = atual->direita; //guarda a proxima célula
			free(atual); //libera a célula atual
			atual = next; //avança para a proxima célula
		}
		next = firstLinha->abaixo; //guarda a proxima linha
		free(firstLinha); //libera o cabeçalho da linha
		firstLinha = next; //avança para a proxima linha
	}
	atual = m->first->direita;
	while(atual != m->first){
		next = atual->direita; //guarda a proxima coluna
		free(atual); //libera o cabeçalho da coluna
		atual = next; //avança para a proxima coluna
	}
	free(m->first); //libera a célula -1,-1
	free(m); //libera a matriz
}

// Interpreta a linha lida no arquivo pela função lerMatriz()
// Pré-condição: ter uma string
// Pós-condição: transforam a linha de string para três inteiros 
void  interpretaLinha(char *linha, int *l, int *c, int *v){
  int neg = 0;
	//determina a linha
  for(; *linha != ','; linha++)
	  *l = 10 * *l + *linha - '0';
  linha++;
	//determina a coluna
  for(; *linha != ','; linha++)
    *c = 10 * *c + * linha - '0';
  linha++;
	//determina se o valor é negativo
	if(*linha == '-'){
		neg = 1;
		linha++;
	}
	//determina o valor
	for(; *linha; linha++)
   	*v = 10 * *v + * linha - '0';
	if(neg) *v = -1 * *v;
}

// Lê uma matriz de um arquivo de texto
// Pré-condição: nenhuma
// Pós-condição: é inicializada uma matriz conforme especificada no arquivo
Matriz* lerMatriz(FILE *f){
  Matriz *m; char linha[25]; int l, c, valor;
  fscanf(f ,"%d%*c%d%*c", &l, &c); //escanei o arquivo para saber o tamanho da matriz
  m = inicializar(l,c); //inicializa a matriz
	
	fscanf(f,"%s", linha); //le uma linha do arquivo
  while(linha[0] != 'f' && linha[1] != 'i' && linha[2] != 'm'){
		l = c = valor = 0;
		interpretaLinha(linha, &l, &c, &valor); //tranforma de string para int
  	inserir(m,l,c,valor); //insere a célula lida na linha
		fscanf(f,"%s", linha);
  }
	return m;
}