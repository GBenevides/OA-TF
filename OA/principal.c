#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include  "include/fun_errorcodes.h"
#include "include/fun_register.h"
#include "include/fun_bTree.h"

/*

	Trabalho 2 de Organização de Arquivos
	Gabriel Benevides - 14/0139907
	Rafael Batista	- 14/0159355
	Thales Grilo - 14/0163603

	Nesse trabalho implementamos a estrutura de dados árvores-B para usarmos-a
	ao longo do processamento. Foram implementadas opções para inserção e busca
	de registros usando a arvore-b. 

	A árvore é montada ao fim de cada iteração novamente para contemplar possíveis registros
	adicionados.

	O projeto foi modularizado na seguinte forma:
		-fun_register.c e .h:
			Contém o código das funções que lidam com registros, como criação de indices
			primários, busca de registros, inserção de listas, etc...
			Contém definições de structs para registros, indices, etc...

		-fun_bTree.c e .h:
			Contém as funções que contemplam a estruturas de dados árvores-b em si. 
			Também contém as definições das structs da arvore e etc...

		-principal.c:
			É a parte que dá vida ao trabalho. Há um menu que pede a opção do usuário e imprime a árvore na tela.
			Ao fim gera-se o arquivo de indices primários e salvamos-o em "indicelista.bt"
		-fun_errocodes.h
			Contém macros e defines básicos a serem usados para o retorno de funções.

*/


int main(int argc, char const *argv[]){
	

	int op=0, seek;

	FILE *prim, *list, *saida;

	registro *reg, *in;
	i_primario* test_index= (i_primario*) malloc(sizeof(i_primario));

	in = (registro*)malloc(sizeof(registro));

	int oparq;
	int aux;

	char line[120];
	char search[11];

	list=fopen("data/lista.txt","r+");
	rewind(list);
	prim=fopen("data/indicelista.bt","w+");
	
	if(list == NULL || prim == NULL ){
		printf("Erro!\n");
		exit(1);
	}



	b_tree* tree;
	btree_create(&tree);
	build_tree(list,&tree);

	tree_run_space(tree, 0);
	reg_buildall(list, &reg);  

	gera_primario(prim,&reg);
	reg_run(reg);

	while(op >= 0){

		printf("-----MENU-----\n1 - Add Register\n2 - Search Register\n(-1) - Exit\n");
		scanf("%d", &op);


		if((op==1)){

			//Adiciona registro
			
			printf("Digite o registro:\n");
			printf("Matricula: ");
			scanf("%s", line);
			getchar(); 
			strcpy(in->matric,line);
			printf("\nNome: ");
			
			gets(line);
			
			
			if(strlen(line)<NAMEMAX){
				do{
					strcat(line," ");
				}while(strlen(line)<NAMEMAX + 1);
			} 
			strcpy(in->nome,line);
			

			printf("\nOption: ");
			scanf("%s", line);
			getchar();
			aux = atoi(line);
			in->op = aux;

			printf("\nCurso: ");
			scanf("%s",line);
			getchar();
			strcpy(in->curso,line);
			printf("\nTurma: (1)Turma A  (2) Turma B: ");
			scanf("%d",&oparq);
			if(oparq==1)
				in->turma='A';
			else
				in->turma='B';

			// Imprimir registro no arquivo
			reg_push(in, list);
			//Inserir na lista


			prim_build(list,in,&test_index);
			printf("nome %s\n",test_index->key);
			
			tree_run_space(tree, 0);
			insert(&tree, test_index);
			tree_run_space(tree, 0);
			
			printf("Fim da insercao\n");
		}

		else if((op==2)){
			//Procurar registro
			printf("Digite o registro a ser procurado (matricula+4 primeiras letras do nome).\n");
			getchar();
			scanf("%s",search);
			seek = key_seek(tree, search);
			switch (seek){

				case ERROR_DATA:
						printf("Chave não encontrada.\n");
						break;
				case ERROR_STREAM:
						printf("Erro do tipo Bad Input;\n");
						break;
				default:
					printf("Registro Encontrado!Na linha %d do arquivo original.\n", seek );



			}


		}else
			op = -1;

		//Destruimos a arvore para poder então reconstruíla.
		tree_burn(&tree);
		btree_create(&tree);
		rewind(list);	

		build_tree(list,&tree);
		reg_buildall(list, &reg);   

		rewind(list);
		rewind(prim);
		//gera_primario(prim,&reg); 
		tree_run_space(tree, 0);

	
			}

	gera_primario(prim,&reg); 
	free(test_index);
	free(in);
	fclose(prim);
	fclose(list);
	tree_burn(&tree);

	printf("End of Execution.\n");



	return 0;
}



