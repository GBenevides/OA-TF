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
	FILE *source1, *source2;
	FILE *outprim1, *outprim2;
	FILE *outsec1, *outsec2;

	registro *l1, *l2;
	registro *p;

	// Processo de leitura das listas

	if ((source1 = fopen(LISTA1, "r")) != NULL){
		if ((source2 = fopen(LISTA2, "r")) != NULL){

				// Ler arquivos e salvar nas listas de registros
				reg_buildall(source1, &l1);
				reg_buildall(source2, &l2);
				
				//reg_run(l1);
				//reg_run(l2);
				
				
		}
	}	
	fclose(source1);
	fclose(source2);

	// Processo de escrita dos arquivos de indicew

	outprim1 = fopen(PRIMARIO1,"w");
	outprim2 = fopen(PRIMARIO2, "w");


	gera_primario(outprim1, &l1);
	gera_primario(outprim2, &l2);

			
	fclose(outprim1);
	fclose(outprim2);


	outsec1 = fopen(SECUNDARIO1,"w");
	outsec2 = fopen(SECUNDARIO2,"w");


	gera_secundario(outsec1, &l1);
	gera_secundario(outsec2, &l2);

	fclose(outsec1);
	fclose(outsec2);



	return 0;
}


