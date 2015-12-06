#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fun_errorcodes.h"

#define ORDEM 	(8)			//UPPER BOUNDARY: ORDEM
#define MEDIANA (ORDEM/2)		//LOWER BOUNDARY: DIVISOR
#define DIVISOR (MEDIANA - 1)


#define KEYSIZE 11

#define NAMEMAX 40
#define LINEMAX 120
#define M_SIZE 	7
	//Essential Macros


#define CURSOMAX 	4
#define TAMCURSO 	3
#define OP_OFFSET 	48
#define KEYSIZE1	50

	//Essential Type Definitions



typedef struct indice_primario{

	char key[KEYSIZE]; // Mudei para int para fins de teste.
	int line; // prr

	}i_primario;

typedef struct data{
	char matric[7];
	char nome[LINEMAX];
	int op;
	char curso[CURSOMAX];
	char turma;

	struct data *next;

	}registro;



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

	
	//printf("Registro: %s\n", stream );
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

int prim_build(FILE* ptr, registro*reg, i_primario** out){

			int caux;
			rewind(ptr);
			int lines=linetotal(ptr);
			char chave[16];
			strcpy(chave,reg->matric);

			for (caux = 0; caux < 9; caux++)
				chave[caux+6] = reg->nome[caux];
			chave[15] = '\0';
			//strcat(chave,p->nome);
			//strcat(chave,'\0');
			strcpy((*out)->key, chave);
			(*out)->line=lines+1;
			printf("%s %d\n", (*out)->key, (*out)->line);
			return FUNCTION_OK;
}

// ------------------------------------------------------------------------------------------------

int reg_seek(FILE* stream, int target, registro** output){

		char source_string[120];
		int counter = 0;

		if (target < 0)
			return ERROR_STREAM;
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
		return ERROR_STREAM;

	return retorno;

	}


//Imprimir registro no Arquivo
int reg_push( registro* reg, FILE* source ){


	char line[120];

	do{

		fgets( line, 120, source );

	}while(!feof(source));

	fprintf(source, "\n%s ", reg->matric);
	fprintf(source, "%s", reg->nome);
	fprintf(source, "%d  ", reg->op);
	fprintf(source, "%s       ", reg->curso);
	fprintf(source, "%c", reg->turma);
	rewind(source);
	
	return FUNCTION_OK;
}

