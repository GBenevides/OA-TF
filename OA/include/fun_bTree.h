#include <stdio.h>
#include <stdlib.h>
#include "fun_bTree.c"




b_tree* splitting(b_tree**, int , b_tree** );

int insert (b_tree**  ,  i_primario* );

int insert_nonfull(b_tree** , i_primario* k);

int i_create(i_primario** , char* , int );

int keygen(i_primario** , char* );

int expose(i_primario* );

int key_compare(char* , char* );

int tree_run(b_tree* );

int key_seek(b_tree* , char* );

int tree_burn(b_tree** );

int btree_create(b_tree ** );

int tree_run_space(b_tree* , int );

int build_tree(FILE* , b_tree** );
