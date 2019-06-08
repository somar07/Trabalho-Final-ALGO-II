#include<stdio.h>
#include<stddef.h>


// FUNÇÕES

//Recebe duas palavras, realiza a correção, retorna um vetor unico contendo as duas strings corrigidas.
char correcao(char *string1[], char *string2[], int *temp1[],int temp2[]);

//Recebe o vetor contendo as duas palavras corrigidas retornada pela função correcao, 
//retorna 1 para troca autorizada(palavra contem no dicionario), 0 para permissao nao autorizada.
void compara(char *palavraCorrecao);

//Sobrescreve a dupla de palavras com o vetor de palavra corrigida.
void troca(char *palavraCorrecao);//Chamada dentro da função compara.

char correcao(char *string1[], char *string2[], int *temp[],int temp2[]){


}


int main(){
	
    return 0;
}


/*

jun 08 : funçoes de verificação de tempo e troca de letras ou correção de palavras.


Primeiro fazer verificação de quantidade de erros, e colocar occorrencias de erros em pendencias, ate finalização de verificação de quantidade de erros,


Fazer verificação de duplas de palavras comparando a primeira palavra com todas as palavras do dicionario, fazer isso com a segunda palavra tambem
fazer verificaçao da palavra corrigida com as palavras do dicionario para saber se elas realmente existem.

A correção so sera feita na ultima ocorrencia de erro identificada.

*/