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
	


	int op=0, seek;

	FILE *prim, *list, *saida;

	registro *reg, *in;
	i_primario* test_index= (i_primario*) malloc(sizeof(i_primario));

	in = (registro*)malloc(sizeof(registro));

	int oparq;
	int aux;

	char line[120];
	char search[120];

	list=fopen("data/data.txt","r+");

	prim=fopen("data/indicelista.bt","w+");
	
	if(list == NULL || prim == NULL ){
		printf("Erro!\n");
		exit(1);
	}

	b_tree* tree;
	btree_create(&tree);
	build_tree(list,&tree);
	printf("Abri E Criei\n");

	while(op >= 0){

		printf("-----MENU-----\n1 - Add Register\n2 - Search Register\n(-1) - Exit\n");
		scanf("%d", &op);


		if((op==1)){
			//Adiciona registro

			
			//fprintf(list, "\n" );
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


			reg_push(in, list);
			//fclose(arq);
			//system("pause");
			prim_build(list,in,&test_index);
			expose(test_index);
			rewind(list);
			system("pause");
			//i_create(&test_index, stream, counter + 1);
			insert(&tree, test_index);

			printf("Fim da insercao\n");
		}

		else if((op==2)){
			//Procurar registro
			printf("Digite o registro a ser procurado (matricula+4 primeiras letras do nome).\n");
			getchar();
			gets(search);
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

		

		reg_buildall(list, &reg);
		rewind(list);
		//gera_primario(prim,&reg);    //  <-------------Agora gera_primario organiza os indices por arvores-b, essa funcao se chamara terminal_saida(prim, &reg);
		rewind(list);
		//system("cls");
		//printf("Arvore B:\n\n\n");
		tree_run_space(tree, 0);

	
			}

	free(test_index);
	free(in);
	fclose(prim);
	fclose(list);
	tree_burn(&tree);

	printf("End of Execution.\n");



	return 0;
}


int build_tree(FILE* database, b_tree** tree){


	char stream[130];
	i_primario* test_index;

	int counter;

		
	for (counter = 0; counter < 45 ; counter++){

		if (feof(database))
			break;

		fgets(stream, 120, database);
		
		i_create(&test_index, stream, counter + 1);
			
		//expose(test_index);
	
		insert(tree, test_index); 

		}
		rewind(database);
		return FUNCTION_OK;
}