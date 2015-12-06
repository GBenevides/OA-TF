#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include  "include/fun_errorcodes.h"
#include "include/fun_register.h"
#include "include/fun_bTree.h"

#define LISTA			"data/lista.txt"

#define PRIMARIO 		"data/indicelista.bt"

int build_tree(FILE*, b_tree**);

int main(int argc, char const *argv[]){
	


	int op=0;;

	FILE *prim, *list, *saida;

	registro *reg, *in;

	int oparq;
	int aux;

	char line[120];

	list=fopen("data/lista.txt","r+");


	prim=fopen(PRIMARIO,"r+");
	
	if(list== NULL ){
		printf("Erro!\n");
		exit(1);
	}

	b_tree* tree;
	btree_create(&tree);

	build_tree(list,&tree);

	while(op >= 0){

		printf("-----MENU-----\n1 - Add Register\n2 - Search Register\n(-1) - Exit\n");
		scanf("%d", &op);


		if((op==1)){
			//Adiciona registro

			in = (registro*)malloc(sizeof(registro));
			
			printf("Digite o registro:\n");
			printf("Matricula: ");
			scanf("%s", line);
			getchar(); 
			strcpy(in->matric,line);
			printf("\nNome: ");
			//scanf("%s", line);
			//getchar();
			gets(line);
			//getchar();
			
			if(strlen(line)<LINEMAX){
				do{
					strcat(line," ");
				}while(strlen(line)<LINEMAX -1);
			} 
			strcpy(in->nome,line);
			printf("\nOption: ");
			scanf("%s", line);
			getchar();
			aux = atoi(line);
			in->op = aux;
			printf("\nCurso:");
			scanf("%s",line);
			getchar();
			strcpy(in->curso,line);
			printf("\nTurma: (1)Turma A  (2) Turma B: ");
			scanf("%d",&oparq);
			if(oparq==1)
				in->turma='A';
			else
				in->turma='B';


			reg_push(in, list);
			//fclose(arq);
			//system("pause");
			
			rewind(list);
			printf("Fim da insercao\n");
		}

		else if((op==2))
			//Procurar registro
			printf("Opcao indisponivel.\n");

		else
			op = -1;



		// Atualizacao dos arquivos!

		

		reg_buildall(list, &reg);
		rewind(list);
			
		//gera_primario(prim,&reg);    //  <-------------Agora gera_primario organiza os indices por arvores-b, essa funcao se chamara terminal_saida(prim, &reg);
		rewind(list);

		free(in);

			}




	fclose(prim);
	fclose(list);

	tree_burn(&tree);

	printf("End of Execution.\n");



	return 0;
}


int build_tree(FILE* ptr, b_tree** tree){


	char* stream;
	FILE* 		database;
	i_primario* test_index;
	b_tree*		test_tree;
	int counter;

	for (counter = 0; counter < 45 ; counter++){

		if (feof(database))
			break;

		fgets(stream, LINEMAX, database);
		i_create(&test_index, stream, counter + 1);
		expose(test_index);
		
		insert(&test_tree, test_index); 

		}

		return FUNCTION_OK;
}