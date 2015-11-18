#include <stdio.h>
#include <stdlib.h>

#include "include/fun_listas.h"

#define LISTA1 			"data/lista1.txt"
#define LISTA2 			"data/lista2.txt"

#define PRIMARIO1 		"data/indiceprimario1.ind"
#define PRIMARIO2 		"data/indiceprimario2.ind"
#define SECUNDARIO1 	"data/indicesecundario1.ind"
#define SECUNDARIO2 	"data/indicesecundario2.ind"



int main(){

	int op=0;;

	FILE *p1, *p2, *l1, *l2, *s1, *s2, *arq;

	registro *reg, *in;

	int oparq;
	int aux;

	char line[120];

	p1=fopen(PRIMARIO1,"r+");
	p2=fopen(PRIMARIO2,"r+");
	l1=fopen(LISTA1,"r+");
	l2=fopen(LISTA2,"r+");
	s1=fopen(SECUNDARIO1,"r+");
	s2=fopen(SECUNDARIO2,"r+");

	while(op >= 0){

		printf("-----MENU-----\n1 - Add Register\n2 - Remove Register\n3 - Update Register\n(-1) - Exit\n");
		scanf("%d", &op);

		if(op>3 || op<0){
			break;
		}

		printf("Selecione entre arquivos 1 e 2:\n" );
			scanf("%d",&oparq);
			if(oparq ==1)
				arq=l1;
			else
				arq=l2;



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
			printf("oi: %s\n",line );
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

			if(oparq==1)
				in->turma='A';
			else
				in->turma='B';


			reg_push(in, arq);
			//fclose(arq);
			//system("pause");
			
			rewind(arq);
		}

		else if((op==2))
			//Remove registro
			printf("Opcao indisponivel.\n");
			
		else if((op==3))
			//Atualiza registro
			printf("Opcao indisponivel.\n");
		else
			op = -1;



		// Atualizacao dos arquivos!

		if(oparq==1){

		reg_buildall(l1, &reg);
		rewind(l1);
			
		gera_primario(p1,&reg);
		rewind(l1);

		gera_secundario(s1, &reg);

		}else{
					
		reg_buildall(l2, &reg);
		
		rewind(l2);
			
		gera_primario(p2, &reg);
		
		rewind(l2);

		gera_secundario(s2, &reg);
					
							
					}


		free(in);

			}




	fclose(p1);
	fclose(p2);
	fclose(l1);
	fclose(l2);
	fclose(s1);
	fclose(s2);

	printf("End of Execution.\n");

	return 0;
}


