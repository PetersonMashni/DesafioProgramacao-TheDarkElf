/************************************************/ 
/* Trabalho de Estrutura de Dados               */
/* Atividade:                                   */
/*      1766 - The Dark Elf                     */
/* Professora:                                  */
/*      Daniela Bagatini                        */
/* C�digo por:                                  */
/*      Filipe Johansson                        */
/*      Leonardo Bang B�cco                     */
/*      Luiz Henrique Martins                   */
/*      Peterson Mashni                         */
/************************************************/ 

#include <stdio.h>                  					// entrada e sa�da padr�o: printf, scanf
#include <stdlib.h>		            					// exit, malloc, system
#include <string.h>                 					// strcmp
#include <locale.h>                 					// setlocale

#define True 1

/***********************************************/ 
/* Defini��o das structs                       */
/***********************************************/ 
typedef struct{                     					// registro INFORMACAO
	char nome[101];
	int peso;
	int idade;
	float altura;
}INFORMACAO;
       
typedef struct nodo{
       INFORMACAO info;             					// dados do registro
       struct nodo* prox;           					// ponteiro para o pr�ximo registro
}NODO;


/***********************************************/ 
/* Defini��o das Fun��es                       */
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
/* OBS: As valida��es foram comentadas, devido a caso de teste do URI que extrapolava a valida��o *
/**************************************************************************************************/ 
int main(void) {
	
	NODO *l = NULL;                                     // declara��o da lista - ponteiro
	int cenario, casos, totalRenas, puxarao;            // define as variaveis
	fflush(stdin);                                      // limpa buffer do teclado
	scanf("%i", &casos);                                // scaneia o numero de casos
//	if(casos < 0 || casos > 105000)                     // testa se o n�mero de casos est� entre 0 e 105000
//		exit(True);                                     // finaliza o programa
	
	cenario = 0;                                        // inicializa contador de cenarios
	while (cenario < casos) {                           // fica no la�o enquanto cenario nao alcancar o n�mero de casos
		fflush(stdin);                                  // limpa buffer do teclado
		scanf("%i %i", &totalRenas, &puxarao);          // scaneia o numero total de renas e quantas puxar�o o tren�
//		if((totalRenas < 5) || (puxarao > 103))         // testa se o total de renas est� entre 5 e 103
//			exit(True);                                 // finaliza o programa
			
		while(totalRenas > 0) {                         // fica no la�o enquanto o n�mero de renas for maior que 0
			inclui(&l);                                 // chama a fun��o inclui();
		    totalRenas--;                               // decrementa totalRenas
		}                                               // fim while(totalRenas > 0)
		
		cenario++;                                      // incrementa cenario
		ordena(&l);										// ordena a lista de acordo com a funcao compara
		imprime(cenario, l , puxarao);                  // chama a fun��o imprime();
		destroi(&l);								// destroi a lista para reutilizacao no proximo laco
	}                                                   // fim while (cenario = casos)
	
}                                                       // fim main(void)


/********************************************************
 * entrada                                              *
 * objetivo: realizar a entrada dos valores do registro *
 * entrada : no com registro vazio                      *
 * saida   : no com registro preenchido                 *
 *******************************************************/ 
void entrada(NODO* aux) {                               // cria a fun��o entrada()
    
    fflush(stdin);                                      // limpa buffer do teclado
    scanf("%s %i %i %f", 
		&aux->info.nome, 
		&aux->info.peso, 
		&aux->info.idade, 
		&aux->info.altura);                             // scaneia o nome, peso, idade e altura
		
//	if(aux->info.peso < 1 || aux->info.peso > 300)      // testa se peso est� entre 1 e 300
//		exit(True);                                     // finaliza o programa
	
//	if (aux->info.idade < 1 || aux->info.idade > 300)   // testa se idade est� entre 1 e 300
//		exit(True);                                     // finaliza o programa
	
//	if (aux->info.altura < 0 || aux->info.altura > 3)   // testa se altura est� entre 0 e 3
//		exit(True);                                     // finaliza o programa
  
    aux->prox = NULL;                                   // n�o aponta
    
}                                                       // fim entrada(NODO *aux)


/**************************************************************
 * inclui                                                     *
 * objetivo: inclui um n� na lista, chamando a funcao entrada *
 * entrada : lista                                            *
 * saida   : lista com n� adicionado e preenchido             *
 *************************************************************/ 
void inclui(NODO* *l) {                                 // cria a fun��o inclui()
	NODO *no = (NODO*) malloc(sizeof(NODO));            // aloca novo espaco em mem�ria
		   
    if(no != NULL) {                                    // verifica se conseguiu alocar mem�ria para o novo registro
		entrada(no);                                    // l� dados
		if(*l == NULL) {                                // verifica se a lista est� vazia
			*l = no;                                    // preenche a lista com os dados de no
			
		} 
		else {                                          // se a lista n�o estiver vazia
			NODO *p;                                    // cria o NODO p
			p = *l;	                                    // p recebe o valor de l
	
			while(p->prox != NULL) {                    // enquanto o ponteiro de p for NULL
				p = p->prox;				            // p aponta para p.pr�ximo
			}
			
			p->prox = no;                               // p aponta para no
			
		}                                               // fim if(*l == NULL)
    
	}                                                   // fim if(no != NULL)
    else                                                // se n�o conseguiu alocar mem�ria
        printf("[!] Falta de Mem�ria\n");               // printa mensagem de falta de mem�ria
	
}                                                       // fim inclui(NODO* *l)


/*********************************************************************
 * imprime                                                           *
 * objetivo: imprime a lista de renas limitando pela quant informada * 
 * entradas: id do cenario                                           *
 *           lista       											 *
 *           quant. de renas                                         *
 * saida   : nenhuma                                                 *
 ********************************************************************/ 
void imprime(int cenario, NODO *aux, int puxarao) {     // cria a fun��o imprime()
    printf("CENARIO {%i}\n", cenario);
    int i=1;                                            // indica n�mero de registro na lista
	 
    if(aux == NULL) {                                   // verifica se lista vazia
        printf( "[!] A lista est� vazia\n" );           // printa que a lista est� vazia
        
    } else {                                            // se a lista n�o estiver vazia
        
        while(aux!=NULL && i<=puxarao) {                // enquanto a lista n�o apontar para NULL
		   
		   printf("%i - %s\n", i, aux->info.nome);
           
           aux = aux->prox;                             // aponta para o pr�ximo registro da lista
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
             NODO *ant = *l;                        // posiciona ponteiro auxiliar para anterior no in�cio da lista
             NODO *p   = ant->prox;                 //posiciona ponteiro auxiliar que ir� caminhar pela lista para comparar com ant
    
             while( ant->prox != NULL ){            // enquanto n�o for final de lista 
                    while( p != NULL ){             // enquanto n�o compara ant com todos posteriores
                           if( compara(&ant->info, &p->info) > 0 ){ // compara (peso (desc), idade, altura, nome) e retorna se ant > p 
                               aux      = p->info;  // faz a troca (algoritmo de ordena��o Bolha)
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
									   // padr�es de retorno semelhantes � fun��o strcmp()
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
	  
    int i= 0;                      // indica n�mero de registro na lista
	 
    if( *l == NULL )               // verifica se lista vazia
        printf( "Lista vazia!\n" );
	else{
	    NODO *aux = *l;
        while( aux != NULL ){      // ponteiro auxiliar para percorrer a lista
			   *l = aux->prox;     // aponta para o pr�ximo registro da lista
               free( aux );        // libera mem�ria
			   aux = *l;           // reposiciona ponteiro auxiliar no in�cio      
               i++;
		 } // fim while( aux != NULL )
	} // fim if( aux == NULL )

}

/* FIM */
