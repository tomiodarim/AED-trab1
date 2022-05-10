#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "matriz.h"

//é definido ponteiros para matrizes e arquivos de forma global para facilitar a passagem de uma função para outra
Matriz *m1, *m2, *mr;
FILE *f1, *f2;

// Abre os arquivos necessários
// Pré-condição: a função que chamou definir um n 
// Pós-condição: abre um ou dois arquivos
void abrirArquivos(int n){
	char fn[100];
	//abre o primeiro arquivo de matriz
	printf("Entre com o nome do arquivo da matriz: ");
	scanf("%[^\n]%*c", fn);
	f1 = fopen(fn, "r");
	//abre o segundo arquivo de matriz se necessário
	if(n == 2){
		printf("Entre com o nome do arquivo da segunda matriz: ");
		scanf("%[^\n]%*c", fn);
		f2 = fopen(fn, "r");
	}
}

// Fecha os arquivos abertos e desaloca as matrizes conforme necessário
// Pré-condição: a função que chamou definir um n 
// Pós-condição: fecha o(s) arquivo(s) e desaloca a(s) matriz(es) 
void limpa(int n){
	fclose(f1);
	excluir(m1);
	if(n >= 2) excluir(mr);
	if(n >= 3) excluir(m2);
	if(n == 4) fclose(f2);
}

// Executa as operações que tem como input duas matrizes
// Pré-condição: o usuário escolher 1, 2 ou 3 no menu
// Pós-condição: executa a operação
void duasMat(int o){
	abrirArquivos(2); //abre dois arquivos de matrizes
	m1 = lerMatriz(f1); //é definida a primeira matriz com base no primeiro arquivo
	m2 = lerMatriz(f2); //é definida a segunda matriz com base no segundo arquivo
	//executa a operação escolhida pelo usuário
	if(o == 1) mr = soma(m1,m2); 
	if(o == 2) mr = subtrai(m1,m2);
	if(o == 3) mr = multiplica(m1,m2);
	imprimir(mr); //imprime a matriz resultante
	limpa(4);//fecha f1 e f2, e libera m1, m2 e mr
}

// Executa as operações que tem como input apenas uma matriz
// Pré-condição: o usuário escolher 4 ou 5 no menu
// Pós-condição: executa a operação
void umaMat(int o){
	abrirArquivos(1); //abre um arquivo de matriz
	m1 = lerMatriz(f1); //é definida a matriz com base no arquivo
	//executa a operação escolhida pelo usuário
	if(o == 5){
		simetrica(m1); 
		limpa(1); //fecha f1 e libera m1
	}
	else{
		mr = transposta(m1);
		imprimir(mr);
		limpa(2); //fecha f1 e libera m1 e mr
	}
}

// Executa um a operação de arquivo escolhido pelo usuário
// Pré-condição: o usuário escolher essa opção no menu
// Pós-condição: executa a operação do arquivo
void arquivo(){
	char fn[100], ope[10], a[10];
	printf("Entre com o nome do arquivo: ");
	scanf("%[^\n]%*c", fn);
  f1 = fopen(fn, "r"); //abre o arquivo definido pelo usuário
  fscanf(f1 ,"%s", ope); //le a operação que deverá ser executada

	//é feito a operação igual as funçoes anteriores porém lendo do arquivo já aberto
	if(!strcmp(ope, "soma") || !strcmp(ope, "subtracao") || !strcmp(ope, "multiplicacao")){
		m1 = lerMatriz(f1);
		m2 = lerMatriz(f1);
		if(!strcmp(ope, "soma") ) mr = soma(m1 ,m2);
		if(!strcmp(ope, "subtracao")) mr = subtrai(m1 ,m2);
		if(!strcmp(ope, "multiplicacao")) mr = multiplica(m1 ,m2);
		imprimir(mr);
		limpa(3);
	}
	
	if(!strcmp(ope, "transposta") || !strcmp(ope, "simetrica")){
		m1 = lerMatriz(f1);
		if(!strcmp(ope, "simetrica")){
			simetrica(m1);
			limpa(1);
		}
		else{
			mr = transposta(m1);
			imprimir(mr);
			limpa(2);
		}
	}
}

// Imprime o menu do programa
// Pré-condição: nenhuma
// Pós-condição: nenhuma
void imprimeOpcoes(){
	printf("Escolha uma opcao:\n\n");
	printf("1 - Somar duas matrizes\n");
	printf("2 - Subtrair duas matrizes\n");
	printf("3 - Multiplicar duas matrizes\n");
	printf("4 - Calcular a transposta de uma matriz\n");
	printf("5 - Determinar se uma matriz e simetrica\n");
	printf("6 - Executar um arquivo\n");
	printf("7 - Sair\n\n");
}

int main(void) {
  int opc = 0;
	printf("Matrizes Esparsas\nTrabalho I de Algoritmos e Estruturas de Dados\nLucas Tomio Darim e Enzo Bonfante\n\n");
  while(opc != 7){
    imprimeOpcoes(); 
    scanf("%d%*c", &opc);
		//analisa o que o usuário quer fazer
		if(opc == 1 || opc == 2 || opc == 3) duasMat(opc); else
		if(opc == 4 || opc == 5) umaMat(opc); else
		if(opc == 6) arquivo(); else
		if(opc != 7) printf("Opção inválida!\n\n");
  }
  return 0;
}
