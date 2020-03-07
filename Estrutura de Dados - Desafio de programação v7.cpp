/************************************************/ 
/* Trabalho de Estrutura de Dados               */
/* Atividade:                                   */
/*      1766 - The Dark Elf                     */
/* Professora:                                  */
/*      Daniela Bagatini                        */
/* Código por:                                  */
/*      Filipe Johansson                        */
/*      Leonardo Bang Bécco                     */
/*      Luiz Henrique Martins                   */
/*      Peterson Mashni                         */
/************************************************/ 

#include <stdio.h>                  					// entrada e saída padrão: printf, scanf
#include <stdlib.h>		            					// exit, malloc, system
#include <string.h>                 					// strcmp
#include <locale.h>                 					// setlocale

#define True 1

/***********************************************/ 
/* Definição das structs                       */
/***********************************************/ 
typedef struct{                     					// registro INFORMACAO
	char nome[101];
	int peso;
	int idade;
	float altura;
}INFORMACAO;
       
typedef struct nodo{
       INFORMACAO info;             					// dados do registro
       struct nodo* prox;           					// ponteiro para o próximo registro
}NODO;


/***********************************************/ 
/* Definição das Funções                       */
/***********************************************/ 
void entrada ( NODO *aux);      
void imprime ( int cenario, NODO *aux, int puxarao);
void inclui  ( NODO **l);
void ordena  ( NODO **l);
void destroi ( NODO **l );
int compara ( INFORMACAO *n1, INFORMACAO *n2);

/***********************************************/ 
/* Ponto de entrada do programa                */
/***********************************************/
/**************************************************************************************************
/* OBS: As validações foram comentadas, devido a caso de teste do URI que extrapolava a validação *
/**************************************************************************************************/ 
int main(void) {
	
	NODO *l = NULL;                                     // declaração da lista - ponteiro
	int cenario, casos, totalRenas, puxarao;            // define as variaveis
	fflush(stdin);                                      // limpa buffer do teclado
	scanf("%i", &casos);                                // scaneia o numero de casos
//	if(casos < 0 || casos > 105000)                     // testa se o número de casos está entre 0 e 105000
//		exit(True);                                     // finaliza o programa
	
	cenario = 0;                                        // inicializa contador de cenarios
	while (cenario < casos) {                           // fica no laço enquanto cenario nao alcancar o número de casos
		fflush(stdin);                                  // limpa buffer do teclado
		scanf("%i %i", &totalRenas, &puxarao);          // scaneia o numero total de renas e quantas puxarão o trenó
//		if((totalRenas < 5) || (puxarao > 103))         // testa se o total de renas está entre 5 e 103
//			exit(True);                                 // finaliza o programa
			
		while(totalRenas > 0) {                         // fica no laço enquanto o número de renas for maior que 0
			inclui(&l);                                 // chama a função inclui();
		    totalRenas--;                               // decrementa totalRenas
		}                                               // fim while(totalRenas > 0)
		
		cenario++;                                      // incrementa cenario
		ordena(&l);										// ordena a lista de acordo com a funcao compara
		imprime(cenario, l , puxarao);                  // chama a função imprime();
		destroi(&l);								// destroi a lista para reutilizacao no proximo laco
	}                                                   // fim while (cenario = casos)
	
}                                                       // fim main(void)


/********************************************************
 * entrada                                              *
 * objetivo: realizar a entrada dos valores do registro *
 * entrada : no com registro vazio                      *
 * saida   : no com registro preenchido                 *
 *******************************************************/ 
void entrada(NODO* aux) {                               // cria a função entrada()
    
    fflush(stdin);                                      // limpa buffer do teclado
    scanf("%s %i %i %f", 
		&aux->info.nome, 
		&aux->info.peso, 
		&aux->info.idade, 
		&aux->info.altura);                             // scaneia o nome, peso, idade e altura
		
//	if(aux->info.peso < 1 || aux->info.peso > 300)      // testa se peso está entre 1 e 300
//		exit(True);                                     // finaliza o programa
	
//	if (aux->info.idade < 1 || aux->info.idade > 300)   // testa se idade está entre 1 e 300
//		exit(True);                                     // finaliza o programa
	
//	if (aux->info.altura < 0 || aux->info.altura > 3)   // testa se altura está entre 0 e 3
//		exit(True);                                     // finaliza o programa
  
    aux->prox = NULL;                                   // não aponta
    
}                                                       // fim entrada(NODO *aux)


/**************************************************************
 * inclui                                                     *
 * objetivo: inclui um nó na lista, chamando a funcao entrada *
 * entrada : lista                                            *
 * saida   : lista com nó adicionado e preenchido             *
 *************************************************************/ 
void inclui(NODO* *l) {                                 // cria a função inclui()
	NODO *no = (NODO*) malloc(sizeof(NODO));            // aloca novo espaco em memória
		   
    if(no != NULL) {                                    // verifica se conseguiu alocar memória para o novo registro
		entrada(no);                                    // lê dados
		if(*l == NULL) {                                // verifica se a lista está vazia
			*l = no;                                    // preenche a lista com os dados de no
			
		} 
		else {                                          // se a lista não estiver vazia
			NODO *p;                                    // cria o NODO p
			p = *l;	                                    // p recebe o valor de l
	
			while(p->prox != NULL) {                    // enquanto o ponteiro de p for NULL
				p = p->prox;				            // p aponta para p.próximo
			}
			
			p->prox = no;                               // p aponta para no
			
		}                                               // fim if(*l == NULL)
    
	}                                                   // fim if(no != NULL)
    else                                                // se não conseguiu alocar memória
        printf("[!] Falta de Memória\n");               // printa mensagem de falta de memória
	
}                                                       // fim inclui(NODO* *l)


/*********************************************************************
 * imprime                                                           *
 * objetivo: imprime a lista de renas limitando pela quant informada * 
 * entradas: id do cenario                                           *
 *           lista       											 *
 *           quant. de renas                                         *
 * saida   : nenhuma                                                 *
 ********************************************************************/ 
void imprime(int cenario, NODO *aux, int puxarao) {     // cria a função imprime()
    printf("CENARIO {%i}\n", cenario);
    int i=1;                                            // indica número de registro na lista
	 
    if(aux == NULL) {                                   // verifica se lista vazia
        printf( "[!] A lista está vazia\n" );           // printa que a lista está vazia
        
    } else {                                            // se a lista não estiver vazia
        
        while(aux!=NULL && i<=puxarao) {                // enquanto a lista não apontar para NULL
		   
		   printf("%i - %s\n", i, aux->info.nome);
           
           aux = aux->prox;                             // aponta para o próximo registro da lista
           i++;                                         // incrementa i
            
        }                                               // fim while(aux != NULL)
        
	}                                                   // fim if(aux == NULL)
	
}                                                       // fim imprime(NODO *aux)


/*********************************************************************
 * ordena                                                            *
 * objetivo: ordenar a lista de renas de acordo com a funcao compara *
 * entrada : lista original                                          *
 * saida   : lista ordenada                                          *
 ********************************************************************/ 
void ordena(NODO **l) {
     
    if( *l == NULL )                                // verifica se a lista esta vazia 
        printf( "Lista vazia!\n" );
    else {
        if( (*l)->prox == NULL )                    // verifica se a lista esta vazia 
             printf( "Lista com apenas 1 elemento!\n" );
        else{
             INFORMACAO aux;                        // auxiliar para a troca de dados
             NODO *ant = *l;                        // posiciona ponteiro auxiliar para anterior no início da lista
             NODO *p   = ant->prox;                 //posiciona ponteiro auxiliar que irá caminhar pela lista para comparar com ant
    
             while( ant->prox != NULL ){            // enquanto não for final de lista 
                    while( p != NULL ){             // enquanto não compara ant com todos posteriores
                           if( compara(&ant->info, &p->info) > 0 ){ // compara (peso (desc), idade, altura, nome) e retorna se ant > p 
                               aux      = p->info;  // faz a troca (algoritmo de ordenação Bolha)
                               p->info  = ant->info;
                               ant->info= aux;
                           } // fim if( compara() )
                           p= p->prox;
                    } // fim while ( p != NULL )  
                    ant= ant->prox;                 // atualiza ponteiros
                    p= ant->prox;  
             } // fim while ( ant->prox != NULL )        
         } // fim else
    }

}

/******************************************************
 * compara                                            *
 * objetivo: comparar duas renas para ordenacao       *
 * entradas: rena1 e rena2                            *
 * saida   : -1 rena1 antes, 1 rena2 antes            *
 ******************************************************/ 
int compara (INFORMACAO * n1, INFORMACAO * n2){
	int ret = 0;                       // variavel de controle da comparacao
									   // padrões de retorno semelhantes à função strcmp()
									   //  0 => elementos iguais
									   // -1 => elemento1 < elemento 2 
									   //  1 => elemento2 > elemento 1 
	
	
	if (n1->peso < n2->peso)           // compara pesos. peso1 < peso2? 
		ret = -1;                      // resulta -1
	else if (n1->peso > n2->peso)	   // peso1 > peso2? 
		ret = 1;                       // resulta 1
	
	ret = ret * -1;                    // inverte resultado, pois o peso deve ser descrescrente

	
	if(ret == 0 & n1->idade < n2->idade)         // verifica se comparacao anterior resultou em igual, compara idades. idade1 < idade2?
		ret = -1;                                // resulta -1
	else if (ret == 0 & n1->idade > n2->idade)   // verifica se comparacao anterior resultou em igual, compara idades. idade1 > idade2?
		ret = 1;                                 // resulta 1

	
	if(ret == 0 & n1->altura < n2->altura)       // verifica se comparacao anterior resultou em igual, compara altura. altura1 < altura2?
		ret = -1;                                // resulta -1
	else if (ret == 0 & n1->altura > n2->altura) // verifica se comparacao anterior resultou em igual, compara idades. altura1 > altura2?
		ret = 1;                                 // resulta 1

	
	if(ret == 0)                             // verifica se comparacao anterior resultou em igual, compara nome. nome1 < nome2?
		ret = strcmp(n1->nome, n2->nome);    // retorna com -1 se nome1 < nome2; 1 se nome1 > nome2
	
	return ret;                              // retorna resultado final
}

/*************************************************
 * destroi                                       *
 * objetivo: rotina para apagar lista            *
 * entrada : lista                               *
 * saida   : lista vazia                         *
 *************************************************/ 
void destroi  ( NODO* *l ){
	  
    int i= 0;                      // indica número de registro na lista
	 
    if( *l == NULL )               // verifica se lista vazia
        printf( "Lista vazia!\n" );
	else{
	    NODO *aux = *l;
        while( aux != NULL ){      // ponteiro auxiliar para percorrer a lista
			   *l = aux->prox;     // aponta para o próximo registro da lista
               free( aux );        // libera memória
			   aux = *l;           // reposiciona ponteiro auxiliar no início      
               i++;
		 } // fim while( aux != NULL )
	} // fim if( aux == NULL )

}

/* FIM */
