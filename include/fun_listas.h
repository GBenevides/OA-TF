#include <stdio.h>
#include <stdlib.h>
#include "fun_listas.c"

int linetotal(FILE*);
	//Conta as linhas de um arquivo FILE*, retorna o valor obtido

int reg_build(char*, registro**);
	/*Recebe uma string formatada como nos arquivos "lista1.txt" e "lista2.txt"
		Organiza a informação em uma variável do tipo registro
	*/

int reg_buildall(FILE*, registro**);
	/*Recebe um arquivo FILE*, constroi uma lista encadeada de registros
		Para fazer isso, chama a função reg_build() para cada linha do arquivo
		O arquivo de input deve estar formatado como nos arquivos "lista1.txt" e "lista2.txt"
	*/
int reg_run(registro*);
	/*Recebe uma variável do tipo registro*, a partir disso, faz a sua leitura (print em tela)
		e a de todos os elementos da lista subsequente, se existir
	*/
int seek_primario(char* , FILE*);
	/*Recebe uma string, contendo a chave que se deseja buscar, e um ponteiro FILE*, contendo o
		arquivo de índices primários ".ind" onde se deseja fazer a busca. Retorna a posição (linha)
		do registro correspondente (dentro do arquivo lista ".txt").
		Falha ao encontrar o registro resulta em retorno ERROR_TARGET
	*/

int gera_primario(FILE*, registro**);
	/*Recebe um ponteiro FILE* de output, que deve ser um arquivo de índices primários ".ind", e um
		ponteiro para registro por referência, que inicia uma lista de registros em memória primária,
		como lidos do arquivo lista ".txt" através de reg_buildall().
		A função gera, então, um arquivo de índices primários a partir da lista recebida, salvando-o
		no endereço fornecido por FILE* output.
	*/

int gera_secundario(FILE*, registro**);
	/*Recebe um ponteiro FILE* de output, que deve ser um arquivo de índices secundários ".ind", e um
		ponteiro para registro por referência, que inicia uma lista de registros em memória primária,
		como lidos do arquivo lista ".txt" através de reg_buildall().
		A função gera, então, um arquivo de índices secundários a partir da lista recebida, salvando-o
		no endereço fornecido por FILE* output.
	*/

int reg_seek(FILE*, int, registro**);
	/*Recebe um arquivo FILE*, formatado como nos arquivos "lista1.txt" e "lista2.txt", um valor
		referente à linha do arquivo procurado (valor que será obtido através dos arquivos de índice),
		e uma variável do tipo registro**.
		A função acessa o arquivo, acessa a linha referida e processa a informação (através da função
		reg_build()), salvando-a no registro** recebido.
	*/


int reg_destroy(registro*);
	/*Recebe um registro, e então libera metodicamente todo o espaço alocado a partir dela (incluindo
		uma possível lista subsequente) 
	*/

int reg_push( registro* , FILE* );
	/*Recebe um registro e um ponteiro FILE* de output para um arquivo do tipo lista ".txt".
		A função, então, processa os dados recebidos e os organiza em uma string, que é então escrita
		no arquivo final.
	*/