#include <stdio.h>
#include <stdlib.h>

typedef int dado;
#define ORDEM 4
#define t (ORDEM/2)		// t-1 ----->  2t-1   t = 2
#define FUNCTION_OK 0
#define KEYSIZE1	50


// Tá!! Tá la dentro! Magrão é melhor que shevchenko!!

typedef struct indice_primario{

	int key; // Mudei para int para fins de teste.
	int line; // prr

	}i_primario;



typedef struct node {

   int counter;         // Valor auxiliar indicando numero de chaves no no atual
   i_primario *keys[ ORDEM ];   // Vetor de ponteiros para indices primarios, as chaves.
   struct node* branches[ORDEM+1];    // Ponteiros para os filhos da B-Tree
   int leaf;

   } b_tree;


// Maluco nao sei se esta funcao esta completamente certa. Quase certeza que sim. Imagino que sim. Na verdade, espero que sim.
int btree_create(b_tree ** node){

	b_tree* aux;
	(aux) =(b_tree*) malloc(sizeof(node));
	aux->counter = 0;
	int i;
	for(i=0; i< ORDEM; i++)
		aux->branches[i] = NULL;
	aux->leaf = 1;
	(*node)=aux;	// Passamos o conteudo de aux para node.

	return FUNCTION_OK;
}

int search(b_tree** tree, i_primario* chave_procurada){

	int i = 0;
	b_tree* arv = (*tree);

	while( (i <= arv->counter) && (chave_procurada->key > arv->keys[i]->key) )
		i++;

	if( (i<= arv->counter) && (chave_procurada->key == arv->keys[i]->key) )
		return arv->keys[i]->line;	// Se encontrarmos o elemento na arvore retornamos o "endereço" dele no arquivo original.
	if(arv->leaf == 1)
		return -1;	// Arvore percorrida e elemento nao-encontrado.
	else
		return search(&arv->branches[i], chave_procurada);	// Elemento não está neste nó. Iremos para o próximo Griláááo.

}


b_tree* splitting(b_tree** x, int i, b_tree** y){	

	b_tree* z;
	z = (b_tree*) malloc(sizeof(b_tree));

	z->leaf = (*y)->leaf;

	z->counter = (t-1);

	int j;

	for(j = 1; j < (t-1) ; j++)
		z->keys[j] = (*y)->keys[j+t];
	if (((*y)->leaf) == 0 ){

		for(j = 1; j < t; j++)
			z->branches[j] = (*y)->branches[j+t];
	}
	(*y)->counter = t-1;
	
	for(j = (*x)->counter+1; j > i+1 ; j--)
		(*x)->branches[j+1] = (*x)->branches[j];
	(*x)->branches[i+1] = z;

	for(j = (*x)->counter; j > i; j--)
		(*x)->keys[j+1] = (*x)->keys[j];

	(*x)->keys[i] = (*y)->keys[t];
	(*x)->counter++;

	return (*x);
}

int insert (b_tree** root ,  i_primario* k ){	//k is the insertion_key


	b_tree *r = (*root);

	if(r->counter = (2*t-1)){

		b_tree* s = (b_tree*) malloc(sizeof(b_tree));
		
		(*root) = s;
		s->leaf = 0;
		s->counter = 0;
		s->branches[0] = r;

		splitting(&s, 1, &r);
		insert_nonfull(&s, k);
		return FUNCTION_OK;
	}else
		insert_nonfull(r, k);
}

int insert_nonfull(b_tree** root, i_primario* k){

	int i = (*root)->counter;
	if ((*root)->leaf == 1){

		while( (i>=1) && ( (k->key) <  ((*root)->keys[i]->key) ) ){

			(*root)->keys[i+1] = (*root)->keys[i];
			i--;
		}
		(*root)->keys[i+1] = k;
		(*root)->counter++;
	}else{

		while(i >= 1 && k < (*root)->keys[i])
			i--;

		i++;
		if((*root)->branches[i]->counter == (2*t-1)){
			splitting(root, i, &((*root)->branches[i]) );
			if( k > (*root)->keys[i])
				i++;
		}
		insert_nonfull(&((*root)->branches[i]), k);
	}
}




int main(int argc, char const *argv[])
{
	printf("Aqui faremos testes e mais testes... Infinitos testes! Muahahahahahha\n");
	return 0;
}























