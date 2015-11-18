#include <stdio.h>
#include <stdlib.h>

#include "include/fun_listas.h"

#define LISTA			"data/lista1.txt"


#define PRIMARIO 		"data/indicelista.bt"


int main(int argc, char const *argv[]){
	


int op=0;;

	FILE *prim, *list, *saida;

	registro *reg, *in;

	int oparq;
	int aux;

	char line[120];

	list=fopen(LISTA,"r+");
	prim=fopen(PRIMARIO,"r+");
	
	// AQUI VAMOS CALCULAR OS INDICES PRIMARIOS. Usando ARVORES-B?
	//terminal_saida(prim,&reg);----> funcao de indices primarios.

	while(op >= 0){

		printf("-----MENU-----\n1 - Add Register\n2 - Search Register\n(-1) - Exit\n");
		scanf("%d", &op);

		if(op>3 || op<0){
			
		}


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
		}

		else if((op==2))
			//Procurar registro
			printf("Opcao indisponivel.\n");

		else
			op = -1;



		// Atualizacao dos arquivos!

		

		reg_buildall(list, &reg);
		rewind(list);
			
		gera_primario(prim,&reg);    //  <-------------Agora gera_primario organiza os indices por arvores-b, essa funcao se chamara terminal_saida(prim, &reg);
		rewind(list);

		free(in);

			}




	fclose(prim);
	fclose(list);

	printf("End of Execution.\n");



	return 0;
}