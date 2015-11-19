#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fun_errorcodes.h"

	//Essential Macros

#define LINEMAX 	42
#define CURSOMAX 	4
#define TAMCURSO 	3
#define OP_OFFSET 	48
#define KEYSIZE1	50

	//Essential Type Definitions

typedef struct data{
	char matric[7];
	char nome[LINEMAX];
	int op;
	char curso[CURSOMAX];
	char turma;

	struct data *next;

	}registro;

typedef struct indice_primario{

	char key[KEYSIZE1];
	int line;

	}i_primario;

typedef struct indice_secundario{

	char curso[CURSOMAX];
	char key[KEYSIZE1];
	int index;

	//struct indice_secundario *next;
	}i_secundario;



typedef struct course_list{

	char curso[CURSOMAX];
	int current;

	struct course_list *next;
	}listacurso;

// FUNÇÕES

int linetotal(FILE* stream){
	char ch = '\0';
	int counter = 0;

	if (stream == NULL)
		return ERROR_STREAM;
	else
	while (ch != EOF){
    	ch = fgetc(stream);
    	if(ch == '\n')	
    		counter++;
	}
	rewind(stream);
	return counter;
}

// ------------------------------------------------------------------------------------------------

int reg_build(char* stream, registro** output){

	
	printf("Registro: %s\n", stream );
	int counter = 0;
	char* field;
	char op[3];
	char nome[LINEMAX];
	registro * aux;
		
	aux = *output;
	aux = (registro*) malloc(sizeof(registro));
	aux->next = NULL;

	if (stream == NULL)
		return ERROR_STREAM;
	else{

		op[0]=stream[OP_OFFSET];
		op[1]=stream[OP_OFFSET+1];
		op[2]='\0';

		field = strtok(stream, " ");
			strcpy(aux->matric, field);
				//fills out matric field

		while(1){
			field = strtok(NULL, " ");
			if (counter == 0){
				counter++;
				strcpy(nome, field);
			}else if (!strcmp(op, field)){
				break;
			}else 
				strcat(nome,field);
		}
			strcpy(aux->nome, nome);
				//fills out name field

		//field = strtok(NULL, " ");
			aux->op = atoi (field);
				//fills out op field

		field = strtok(NULL, " ");
			strcpy(aux->curso, field);
				//fills out curso field

		field = strtok(NULL, " ");
			aux->turma = field[0];
				//fills out turma field
		
	}

	(*output) = aux;
	return FUNCTION_OK;
}

// ------------------------------------------------------------------------------------------------

int reg_buildall(FILE* stream, registro** output){
	
	
	char source_string[120];
	registro* reg, *aux1, *aux2;
	int root =0;

	*output = NULL;

	if (stream == NULL)
		return ERROR_STREAM;
	else{
		while (( fgets(source_string, 120, stream)) != NULL){	
			reg_build(source_string, &aux1);
				if(root == 0){

				root++;
				(*output) = aux1;
				aux2   = aux1;
				aux1   = aux1->next;

			}else{

				aux2->next = aux1;
				aux2 = aux1;
				aux1 = aux1->next;
			}
		}
	}
	
	return FUNCTION_OK;
}

// ------------------------------------------------------------------------------------------------

int reg_run(registro* source){
	registro *p;
	p = source;
	while (p != NULL){
		printf("MATRIC: %s\t NOME: %s\t OP: %d\t CURSO: %s\t TURMA: %c\n",
                p->matric,   p->nome,   p->op,   p->curso,   p->turma);
				p = p->next;
	}
	return FUNCTION_OK;
}


// ------------------------------------------------------------------------------------------------

int gera_primario(FILE* output, registro** reg){

	registro* p;
	int counter=0, caux;
	char chave[KEYSIZE1];
	i_primario* ind;

	ind = (i_primario*) malloc(sizeof(i_primario));

	for(p = (*reg); p != NULL;  p = p->next){
			// concatenacao
			strcpy(chave,p->matric);

			for (caux = 0; caux < 9; caux++)
				chave[caux+6] = p->nome[caux];
			chave[15] = '\0';
			//strcat(chave,p->nome);
			//strcat(chave,'\0');
			strcpy(ind->key, chave);

			ind->line = counter; //Denotando a linha na qual se encontra a chave primaria no arquivo de dados
			counter++;

			fprintf(output, "%s %d\n", ind->key, ind->line);
	}
	free(ind);
	return FUNCTION_OK;
}

// ------------------------------------------------------------------------------------------------

int reg_seek(FILE* stream, int target, registro** output){

		char source_string[120];
		int counter = 0;

		if (target < 0)
			return ERROR_TARGET;
		else while (counter < target){
			fgets(source_string, 120, stream);
			counter++;
		}

		
		fgets(source_string, 120, stream);
		reg_build(source_string, output);
		//(*output) = 

		return FUNCTION_OK;
	}

// ------------------------------------------------------------------------------------------------

int reg_destroy (registro* target){
	if (target != NULL){
		registro *aux1 = target;
		registro *aux2 = target->next;
			
		while (aux2 != NULL){
			free (target->matric);
			free (target->nome);
			free (target->curso);
			free (aux1);
				
			aux1 = aux2;
			aux2 = aux2->next;
		} free (aux1);	
	}
    return FUNCTION_OK;
}

// ------------------------------------------------------------------------------------------------

int seek_primario(char* chave , FILE* input){

	int retorno = -1;
	char linha[120];
	char* palavra; // Tamanho de cada chave
	int nLinhas = linetotal(input);
	int i;

	printf("Chave:  %s\n",chave);

	for(i = 0 ; i < nLinhas; i++){

		//PROCURA A CHAVE
		fgets(linha, 120, input);
		palavra= strtok(linha, " ");
		
		if(strcmp(palavra, chave) == 0)
			retorno = i;

	}

	rewind(input);

	if(retorno == -1 || retorno > nLinhas)
		return ERROR_TARGET;

	return retorno;

	}

// ------------------------------------------------------------------------------------------------
/*
int gera_secundario(FILE* output, registro** reg){
	registro *p;
	i_secundario *ind, *first;
	listacurso *course_root, *course_p1, *course_p2;

	char chave[KEYSIZE1];
	int counter = 0, listtrigger=0, caux = 0;

	course_root = NULL;
	course_p1 	= NULL;
	ind 		= NULL;
	first 		= NULL;
	course_p2 	= NULL;

	ind = (i_secundario*) malloc(sizeof(i_secundario));
	p 	= (*reg);

	while(p != NULL){
		strcpy(chave,p->matric);
			// Definição da Chave Primária
		for (caux = 0; caux < 9; caux++)
			chave[caux+6] = p->nome[caux];
		chave[15] = '\0';
			// Data Retrieving
		strcpy(ind->key,   chave);					//Chave Primária
		strcpy(ind->curso, p->curso);				//Curso

			// Consolidating Inverted List
		
		ind->index = -1;

		caux = 0;
		course_p1 = course_root;
		while(course_p1 != NULL){

			if (strcmp(ind->curso, course_p1->curso) == 0){
				ind->index = course_p1->current;
				course_p1->current = counter;
				caux++;
			}
			course_p1 = course_p1->next;
		}

			if (caux==0){
				course_p1 			= (listacurso*) malloc (sizeof(listacurso));
				course_p1->next 	= NULL;
				course_p1->current 	= counter;
				strcpy(course_p1->curso, ind->curso);

				if (course_root == NULL){
					course_root = course_p1;
					course_p2 	= course_p1;
				}else{
				course_p2->next = course_p1;
				}

				course_p2 = course_p1;
				course_p1 = course_p1->next;
			}


			//File Printing
		fprintf (output, "%s %s %d\n", 	ind->curso,
										ind->key,
										ind->index);
			//Iterate
		counter++;
		p = p->next;
	}

	course_p1 = course_root;
	while (course_p1 != NULL){
		course_p2 = course_p1->next;
		free(course_p1);
		course_p1 = course_p2;
	}

	return FUNCTION_OK;
}
*/
// ------------------------------------------------------------------------------------------------

int reg_push( registro* reg, FILE* source ){


	char line[120];

	do{

		fgets( line, 120, source );

	}while(!feof(source));

	fprintf(source, "%s ", reg->matric);
	fprintf(source, "%s", reg->nome);
	fprintf(source, "%d  ", reg->op);
	fprintf(source, "%s       ", reg->curso);
	fprintf(source, "%c\n", reg->turma);
	rewind(source);
	
	return FUNCTION_OK;
}