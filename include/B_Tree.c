
typedef int dado;
#define ORDEM 4


typedef struct node {

   short int counter;         // Valor auxiliar indicando numero de chaves no no atual
   indice_primario *keys[ ORDEM -1 ];   // Vetor de ponteiros para indices primarios
   struct node* branches[ORDEM];    // Ponteiros para os filhos da B-Tree
   short int leaf;

   } b_tree;

// Maluco nao sei se esata funcao esta completamente certa. Quase certeza que sim. Imagino que sim. Na verdade, espero que sim.
int btree_create(**b_tree node){

	b_tree* aux;
	(aux) = malloc(sizeof(Node));
	aux->counter = 0;
	int i;
	for(i=0; i< ORDEM; i++)
		aux->branches[i] = NULL;
	aux->leaf = 1;
	(*node)=aux;	// Passamos o conteudo de aux para node.
}

int search(**b_tree tree, char* chave_procurada){

	int i = 0;

	while( i <= tree->counter && chave_procurada > tree->keys[i]->key)
		i++;

	if( (i<= tree->counter) && (chave_procurada == tree->keys[i]->key) )
		return tree->keys[i]->line;	// Se encontrarmos o elemento na arvore retornamos o "endereço" dele no arquivo original.
	if(tree->leaf == 1)
		return -1;	// Arvore percorrida e elemento nao-encontrado.
	else
		return search(branches[i], chave_procurada);	// Elemento não está neste nó. Iremos para o próximo Griláááo.

}