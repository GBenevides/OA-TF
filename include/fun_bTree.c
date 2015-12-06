#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct node {

   short int i_counter;         	// Valor auxiliar indicando numero de chaves no no atual
   short int leaf;					// Valor booleano indicando se o nó é uma folha (não possui filhos)

   i_primario*	index[ORDEM-1]; 	// Vetor de ponteiros para indices primarios, as chaves.
   struct node* branches[ORDEM];	// Ponteiros para os filhos da B-Tree
   struct node* up;					// Ponteiros para o pai do nó

   } b_tree;





b_tree* splitting(b_tree** root, int position, b_tree** splitting_target){	

	/*	VARIÁVEIS:
			~ root: endereço do nó que se torna o novo pai.
			~ position: posição de separação
			~ splitting_target: endereço do nó que será dividido
	*/

	int j;
	b_tree *target, *parent;

	target 	= *splitting_target;
	parent 	= *root;


		/*Definição de aux: nó irmão do nó que está sendo 
			dividido (target). Compartilha o nó pai (parent),
		*/
	b_tree* aux;
	btree_create(&aux);

	aux->leaf 		= target->leaf;
	aux->i_counter 	= 0;

	
		//Transferência de filhos
	if ( (target->leaf) == 0 ){
		
		for(j = 0; j + DIVISOR + 1 < ORDEM; j++){
			aux->branches[j] = target->branches[j + DIVISOR + 1];

		target->branches[j + DIVISOR + 1] = NULL;
		}
	}


		//Transferência de chaves imediatas
	for(j = 0; j + DIVISOR + 1< ORDEM - 1; j++){
		aux->index[j] 	= target->index[j + (DIVISOR + 1)];
		target->index[j + (DIVISOR + 1)] = NULL;
		

		if (aux->index[j] != NULL)
			aux->i_counter++;	

	}





		//Posicionamento dos filhos
	for(j = parent->i_counter; j > position; j--)
		parent->branches[j+1] = parent->branches[j];
	parent->branches[position + 1] 		= aux;
	parent->branches[position] 			= target;




		//Eleição do divisor
	for(j = parent->i_counter + 1; j > position; j--)
		parent->index[j] = parent->index[j-1];	//a função não entrou nesse loop durante o primeiro split. propenso a erros futuros


	parent->index[position] = target->index[DIVISOR];
	parent->i_counter++;
	target->index[DIVISOR] 	= NULL;
	target->i_counter 		= DIVISOR;
	

		(*root)				= parent;
		(*splitting_target)	= target;

	return parent;
}


int insert (b_tree** root ,  i_primario* element){	//k is the insertion_key

	int j;
	b_tree* aux = (*root);


	if(aux->i_counter == (ORDEM-1)){
		// NÓ ESTÁ CHEIO

			//Criação de um novo nó pai
		b_tree* parent;
		btree_create(&parent);

			//Definição das informações do novo nó pai
		parent->leaf 		= 0;
		parent->branches[0] = aux;
		(*root) 			= parent;

		splitting(root, 0, &aux);

		
		insert_nonfull(&parent, element);
		
		return FUNCTION_OK;
	}else{
		// NÓ NÃO ESTÁ CHEIO
		insert_nonfull(&aux, element);

	}
	return FUNCTION_OK;
}



int insert_nonfull(b_tree** root, i_primario* k){

	int i = (*root)->i_counter;

	if ((*root)->leaf == 1){	//CASO LEAF FUNCIONA, CHECAR CASO NÃO-LEAF
		while ( i >= 0 ){
			if ((*root)->index[i] != NULL){
				
				if ( key_compare((*root)->index[i]->key, k->key) == 1){
					(*root)->index[i+1] = (*root)->index[i];					
				}else{
					break;					
				}
			}

			i--;
		}
		i++;
		
		(*root)->index[i] = k;
		(*root)->i_counter++;

		return FUNCTION_OK;



	}else{

		//printf("not leaf => i_counter: %d // ", (*root)->i_counter);
			

		for(i = (*root)->i_counter - 1; i >= 0; i--){
				if((*root)->index[i] != NULL){
					if (key_compare((*root)->index[i]->key, k->key) == 2){
					//i++;
					break;
				}
			}
		}
		i++;


		if((*root)->branches[i]->i_counter == (ORDEM-1)){
			splitting(root, i, &((*root)->branches[i]) );
			insert_nonfull(root, k);

		}else{
			insert_nonfull(&((*root)->branches[i]) , k);
			

		}
	}
	return FUNCTION_OK;
}


int i_create(i_primario** target, char* stream, int line){
	i_primario* output;

	
	if (stream == NULL)
		return ERROR_STREAM;

	if ( (output = (i_primario*) malloc(sizeof(i_primario))) != NULL)
		if (keygen(&output, stream) == ERROR_STREAM)
			return ERROR_STREAM;

	output->line = line;

	(*target) = output;
	return FUNCTION_OK;
}


int keygen(i_primario** output, char* stream){
	int counter=0;

	char* field;
	char chave[KEYSIZE];

	if (stream == NULL)
		return ERROR_STREAM;

	// concatenacao
	field = strtok(stream, " ");
	strcpy(chave, field);

	field = strtok(NULL, " ");
	
	for (counter = 0; counter < (KEYSIZE - 1 - 6); counter++)
		chave[counter+6] = field[counter];
	chave[KEYSIZE - 1] = '\0';
	strcpy((*output)->key, chave);
	//fprintf(output, "%s %d\n", ind->key, ind->line);
	return FUNCTION_OK;
}


int expose(i_primario* target){
	if (target == NULL)
		return ERROR_STREAM;

	if (target->key == NULL)
		return ERROR_DATA;

	printf("\tKey: %s\t Line: %d\n", target->key, target->line);
	return FUNCTION_OK;
}


int key_compare(char* object, char* comparison){
	/*
		RECEBE:
			- Duas chaves, formatadas como especificado, em forma de string
		RETORNA:
			- 1, caso a primeira chave seja alfabeticamente maior
			- 2, caso a segunda chave seja alfabeticamente maior
			- 0, caso sejam iguais
	*/
	short int counter;

	if (object == NULL || comparison == NULL)
		return ERROR_STREAM;

	for (counter = 0; counter < KEYSIZE; counter++){
		if (object[counter] > comparison[counter])
			return 1;
		if (comparison[counter] > object[counter])
			return 2;
	}

	return FUNCTION_OK;
}


int tree_run(b_tree* target){
	short int counter;

	if (target == NULL)
		return ERROR_STREAM;

	for (counter = 0; counter < ORDEM - 1; counter++){
		//if (target->branches[counter] != NULL)
		if ((target->branches[counter]) != NULL)
			printf("\n");
		tree_run(target->branches[counter]);

		if ((target->index[counter]) != NULL){
			printf("\t position: %d", counter);
			expose(target->index[counter]);
		}
	}

	printf("\n");
	tree_run(target->branches[ORDEM - 1]);

	return FUNCTION_OK;	
}

	
int key_seek(b_tree* data, char* trigger){
	/*
		RECEBE:
			Endereço da b-tree a ser percorrida
			Chave (string)

		RETORNA:
			Linha associada à chave, caso encontrada
			ERROR_DATA, caso não encontrada
			ERROR_STREAM, caso bad input
	*/

	short int code;			
	short int counter = 0;
	b_tree* source = data;

		//Só verificando que tá tudo no lugar
	if (trigger == NULL)
		return ERROR_STREAM;
	if (data == NULL)
		return ERROR_DATA;

	for (counter = 0; counter < ORDEM - 1; counter++){
		//if (data->branches[counter] != NULL)
			//key_seek(data->branches[counter], trigger);

		code = key_compare(source->index[counter]->key, trigger);
			//CASO I: trigger pertence ao nó presente
		if (code == 0)
			return source->index[counter]->line;

			//CASE II: trigger é menor que a chave presente (procurar filho anterior)
		if (code == 1)
			return key_seek(source->branches[counter], trigger);

	}
	
		//CASE III: trigger é maior que todos os elementos do nó (buscar último filho)
	return key_seek(source->branches[ORDEM - 1], trigger);
}

int tree_burn(b_tree** target){
	short int counter;

	if (target == NULL)
		return ERROR_FORMAT;
	if (*target == NULL)
		return ERROR_STREAM;

	b_tree* subtarget;
	subtarget = (*target);

	for (counter = 0; counter < ORDEM - 1; counter++){
		//if (target->branches[counter] != NULL)
		tree_burn(&(subtarget->branches[counter]));

		if ((subtarget->index[counter]) != NULL){
			free(subtarget->index[counter]);
			//printf("counter: %d\n", coAunter);
		}
	}


	tree_burn(&(subtarget->branches[ORDEM - 1]));
}



int btree_create(b_tree ** node){

	b_tree* aux;
	int counter;

	aux =(b_tree*) malloc(sizeof(b_tree));
	if (aux == NULL)
		exit(ERROR_MALLOC);

	aux->i_counter = 0;


		//ORDEM = Número de filhos // ORDEM-1 = counter do último filho
	for(counter=0; counter < ORDEM - 1; counter++){
		aux->index[counter] 	= NULL;
		aux->branches[counter] 	= NULL;
	}

	aux->branches[ORDEM - 1] 	= NULL;
	aux->up 					= NULL;
	aux->leaf 					= 1;

	(*node)=aux;	// Passamos o conteudo de aux para node.
	return FUNCTION_OK;
}



int tree_run_space(b_tree* target, int offset){
	short int counter;
	int i;

	if (target == NULL)
		return ERROR_STREAM;

	for (counter = 0; counter < ORDEM - 1; counter++){
		//if (target->branches[counter] != NULL)
		if ((target->branches[counter]) != NULL)
			printf("\n");
		tree_run_space(target->branches[counter], offset+1);

		if ((target->index[counter]) != NULL){
			printf("\t");
			for (i = 0; i <= offset; i++)
				printf("  ");
			printf("Key: %s\t", target->index[counter]->key);

			for (i = 0; i <= offset; i++)
				printf("  ");
			printf("- Line: %d" , target->index[counter]->line);

			for (i = 0; i <= offset; i++)
				printf("  ");
			printf("\tPosition: %d\n", counter);
			
		}
	}

	printf("\n");
	tree_run_space(target->branches[ORDEM - 1], offset+1);
	
}