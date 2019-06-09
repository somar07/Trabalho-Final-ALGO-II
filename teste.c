#include <stdio.h>
#include <string.h>
#include<stdlib.h>
#include<ctype.h>

int procura(char string1[], char string2[]);
void troca(char string1[], char string2[]);
void juntarDuas(char string1[],char string2[]);

char *strTolower(const char *src, char *dest);//função que recebe a string original e tranforma todas as letras em minusculas para fazer busca no dicionario.
char compara1[100]="\0",compara2[100]="\0",final[100];
int main ()
{
   int i,j,pos=0,k,tam,consta;
   char str1[] = "a bbb aab a b";
   int tempo[] = {1,2,3,4,5,6,7,8,9,10,11,12,13};
   int espaco[10];//vetor que pega os indices de onde o tempo corresponde ao espaço
   char aux[20];
   char aux2[20];
   char retornoTroca[100];//recebe as duas palavras retornadas pela função troca, ou seja, como resultado da verificação.
   char definitiJunto[100];
   // tam = strlen(str1);
    char original[100];
    char palavra1[50][50];
    char fraseMinuscula[100];//recebe a palavra toda em minuscula para facilitar a busca no dicionario.
    char ptr;
    
    //strTolower(str1,fraseMinuscula);
    //printf("String minuscula => %s\n",fraseMinuscula);
    //strcpy(str1,fraseMinuscula);
    for(i=0,k=0,j=0; i < strlen(str1);i++){
            if(str1[i]!= ' '){
                palavra1[j][k] = str1[i];
                k++;
            }else{
                espaco[j] = i;
                palavra1[j][i]='\0';
                j++;
                k=0;
            }
            palavra1[j][k]='\0';
    }
    //palavra1[j][k]='\0';
        //printf("Aux2 - 1 => %s\n",palavra1[1]);
            
            for(i=0;i<j;i++){
                if((tempo[espaco[i]+1]-tempo[espaco[i]])<=20){//pega apenas os indices onde há espaços e faz a subtração para verificar se foi digitado dentro do espaço/tempo.
                        strcpy(aux,palavra1[i]);
                        strcpy(aux2,palavra1[i+1]);
                        
                        troca(aux,aux2);
                    
                        pos++;
                }
            }
            if(pos==0){
               
            }
   return 0;
}

int procura(char string1[],char string2[]){
    int i,j,cont=0,cont2=0,tam,tam2,flag = 0,t;
   

    char dicionario[50][50] = {"ab","bba","bbba"};
    
              tam=strlen(dicionario[i]);
              for(i=0;i<strlen(dicionario[i]);i++){
                  if(strcmp(string1,dicionario[i])==0){
                    printf("Esta no dicionario P1 => %s\n",string1);
                    cont =1;
                    break;
                  }
              }
              for(i=0;i<strlen(dicionario[i]);i++){
                  if(strcmp(string2,dicionario[i])==0){
                    printf("Esta no dicionario P2 => %s\n",string2);
                    cont2 = 2;
                    break;
                  }
              }
              if(cont==0&&cont2==0){
                    t=0;
              }else if((cont+cont2)==3){
                  t = 1;
              }
              return t;
}

void troca(char string1[],char string2[]){
    char aux1[50], aux2[50],conserva1[50],conserva2[50];
    char caracter[2],apaga[20];
    int tam,i,j,k;
    
    
    strcpy(conserva1,string1);
    strcpy(conserva2,string2);
    //char lixo = getchar();
    
     for(i=1,j=0; i < strlen(string2);i++){//passa a string2 para uma string auxiliar mas sem a letra da primeira posição
            if(string2[i]!= '\0'){
                apaga[j] = string2[i];
                j++;
            }
    }
       
        apaga[i] ='\0';
        
        caracter[0] = string2[0];
        strcpy(string2,apaga);
        strcpy(aux1,string1);
        strcat(aux1,caracter);
        strcpy(string1,aux1);
       tam = procura(string1,string2);
       if(tam==0){
           strcpy(string1,conserva1);
           strcpy(string2,conserva2);
           printf("conservou => %s %s\n",string1,string2);
       }else{
        printf("mudou => %s %s",string1,string2);
       }
       juntarDuas(string1,string2);
    
    
}

void juntarDuas(char string1[],char string2[]){

     printf(" => %s %s\n",string1,string2);
     char stand[50];

     if(strcmp(string1,compara1)!=0&&strcmp(string2,compara2)!=0){
         strcat(final,string1);
         strcat(final,string2);
        strcpy(compara1,string1);
        strcpy(stand,string2);
        strcpy(compara2,string2);
     }else if()
     
}

char *strTolower(const char *src, char *dest)
{
   size_t i = 0;

   for (; src[i]; i++)
dest[i] = tolower(src[i]);

   dest[i] = tolower(src[i]);

   return dest;
}
/* 1 apenas a primeira esta no dicionario
2 as duas estão no dicionario
> 2 nenhuma das duas está no dicionario*/