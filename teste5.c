#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX 1000000
#define TAM_BRUT 10000
#define TAM_DIC 5000
#define TAM_50 50

typedef struct{ /* PARA CAPTURAR INFORMAÇÕES FORMATADAS CONTIDAS NO ARQUIVO */
    char SENTENCA[TAM_50];
    int VETOR_TEMPO[TAM_50];
    char DICIONARIO[TAM_DIC];
} DADOS;




/* PROTÓTIPOS */
int procura(DADOS dados[], char string1[], char string2[], int instancia);
int correcao_troca(DADOS dados[], char string1[],char string2[], int instancia, int dupla);
int quantidadeLinhasArquivo();
void tratamento(DADOS dados[]);
void separa_palavras_instancia(DADOS dados[], int instancia);
void formatacao_final(DADOS dados[], char string1[], char string2[], int instancia);
void print_frase(char frase[], int instancia);

int minuscula(DADOS dados[], char string1[],char string2[], int instancia);

/* PRINCIPAL */
int main(int argc, char const *argv[]){

    int qtd_instancias_arquivo = quantidadeLinhasArquivo();//Conta quantas linhas o arquivo tem.
    
    DADOS dados[qtd_instancias_arquivo];//Dados do arquivo de entrada ja formatados.
    
    tratamento(dados);//Tratamento de dados brutos contido no arquivo para struct(dados formatados).

    int i = 5;
    //int x = 5;
    //for(int i = 0; i < qtd_instancias_arquivo; i++){// CADA INDICIE CORRESPONDE A UMA INSTANCIA DO ARQUIVO.
        separa_palavras_instancia(dados, i);
    //}

    return 0;
}

void tratamento(DADOS dados[]){
    int x = 0; // Controle dos indicies da sentenca bruta 
    int ordem = 0; // Controla qual tipo de dado sera capturado, senteça, vetor ou dicionario 
    int control = 0;//Controle para idendificar em qual instancia o arquivo se encontra
    int id_1 = 0, id_2 = 0, id_3 = 0; // Indicie valido para salvar os dados na struct

    //  Estas servem para conversao de um char pra um int
    char atom[7];
    int number = 0;
    int count_pos_atom = 0;

    FILE *fPtr;

    if((fPtr = fopen("entrada.txt", "r")) == NULL){
        printf("\n Erro na abertura do arquivo!");
        exit(1);
    } else {
        while(!feof(fPtr)){
            char sentenca_bruta[TAM_BRUT];
            fgets(sentenca_bruta, TAM_BRUT, fPtr);

            while(sentenca_bruta[x] != '\0'){
                //CONDIÇÃO DE TRATAMENTO DA SENTENÇA
                if(ordem == 0){
                    if(sentenca_bruta[x] == ','){
                        ordem = 1;
                        ++x;
                    } else {
                        if(sentenca_bruta[x] != '"'){
                            dados[control].SENTENCA[id_1] = sentenca_bruta[x];
                            id_1++; // incremento da variavel sentença da struct.
                        }
                    }
                }
                
                //CONDIÇÃO DE TRATAMENTO DO VETOR DO TEMPO
                if(ordem == 1){
                    if((sentenca_bruta[x] != ' ') && (sentenca_bruta[x] != '{') && (sentenca_bruta[x] != '}')){
                        if(sentenca_bruta[x] == '"'){
                            ordem = 2;
                            ++x;
                        } else {
                            if(sentenca_bruta[x] != ','){
                                atom[count_pos_atom] = sentenca_bruta[x];
                                count_pos_atom++;
                            }

                            if(sentenca_bruta[x] == ',' && sentenca_bruta[x] != ' '){//Quando identificada uma , e mostado o numero e atribuido a struct.
                                atom[count_pos_atom] = '\0';
                                number = atoi(atom);
                                dados[control].VETOR_TEMPO[id_2] = number;
                                count_pos_atom = 0;
                                id_2++;
                            }
                        }
                    }
                }
                
                //CONDIÇÃO DE TRATAMENTO DO DICIONARIO
                if(ordem == 2){
                    if(sentenca_bruta[x] == '}'){// Condição de parada
                        dados[control].DICIONARIO[id_3] = '\0';
                    } else {
                        if(sentenca_bruta[x] == ','){
                            dados[control].DICIONARIO[id_3] = ' ';
                            id_3++;
                        } else if(sentenca_bruta[x] != '"'){
                            dados[control].DICIONARIO[id_3] = sentenca_bruta[x];
                            id_3++;
                        }
                    }
                }
                x++;
            }
            x = 0;
            id_1 = 0;
            id_2 = 0;
            id_3 = 0;
            ordem = 0;  // INICIALIZANDO COM 0 PARA FILTRAR UMA NOV INSTANCIA.
            control++; // INCREMENTO DA LINHA OU NOVA SENTENÇA NO ARQUIVO.
        }
        fclose(fPtr);
    }
}

int quantidadeLinhasArquivo(){
    FILE *fPtr;
    int qtd_instancias = 0;

    if((fPtr = fopen("entrada.txt","r")) == NULL){
        exit(1);
    } else {
        char caractere_linha;
        while(fread (&caractere_linha, sizeof(char), 1, fPtr)){
            if(caractere_linha == '\n'){
                qtd_instancias++;
            }
        }
        fclose(fPtr);
    }
    return qtd_instancias +1;
}

void separa_palavras_instancia(DADOS dados[], int instancia){
    int i,j,k;
    char separacao_palavras[TAM_50][TAM_50]; //pega as palvras da SENTENÇA separadas.
    int espaco[TAM_50];//vetor para pegar indices dos espaços
    
    int tamSentenca = strlen(dados[instancia].SENTENCA);

    //SEPARA AS PALAVRAS DA SENTENÇA NUMA MATRIZ.
    for(i = 0, k = 0, j = 0; i < tamSentenca; i++){
        if(dados[instancia].SENTENCA[i] != ' '){
            separacao_palavras[j][k] = dados[instancia].SENTENCA[i];
            k++;
        }else{
            espaco[j] = i;
            separacao_palavras[j][i] = '\0';
            j++;
            k = 0;
        }
        //separacao_palavras[j][k] = '\0';
    }
separacao_palavras[j][k] = '\0';
    int buffer_pos = 1;

    int dupla = 0;// SALVA QUANTIDADE DE DUPLAS DE PALAVRAS QUE FORAM PROCESSADAS 
    char P1[TAM_50], P2[TAM_50];
    for(i = 0; i <= 5; i++){
    // SELECIONA OS INDICIES ONDE HÁ ESPAÇOS E SUBTRAI PARA VERIFICAR SE FOI DIGITADO DENTRO DO (ESPAÇO/TEMPO)
        if((dados[instancia].VETOR_TEMPO[espaco[i]+1] - dados[instancia].VETOR_TEMPO[espaco[i]]) <= 20){
            
                strcpy(P1, separacao_palavras[i]);// PALAVRA 1
                strcpy(P2, separacao_palavras[i+1]);// PALAVRA 2
                
                correcao_troca(dados, P1, P2, instancia, dupla); // TROCA DAS DUAS PALAVRAS
            
            dupla++;
        }
    }
}
 
int correcao_troca(DADOS dados[], char string1[],char string2[], int instancia, int dupla){
    int i,j,k,tam;
    char stringAux[TAM_50];
    char palavra[TAM_50]; //RECEBE AS PALAVRAS CORRIGIDAS 
    char primeiraLetra_str2[1];
    char stringOrigin_1[TAM_50], stringOrigin_2[TAM_50]; //RECEBEM AS PALAVRAS ORIGINAIS 

    strcpy(stringOrigin_1, string1);
    strcpy(stringOrigin_2, string2);
    memset(&primeiraLetra_str2, '\0', sizeof(char)*1);
    
    //ARMAZENA A STRING2 EM UMA STRING AUXILIAR SEM A LETRA DA PRIMEIRA POSIÇÃO (FOR COMEÇA DO 1 NAO DO 0) 
    for(i = 1, j = 0; i < strlen(string2); i++){
        if(string2[i] != '\0'){
            stringAux[j] = string2[i];
            j++;
        }
    }
       
    stringAux[j] = '\0';  //ATRIBUIÇÃO DO ESPAÇO A ULTIMA POSIÇÃO DA STRING AUXILIAR     
    primeiraLetra_str2[strlen(primeiraLetra_str2)] = string2[0]; //SALVA A PRIMEIA LETRA DA STRING2
    strcpy(string2, stringAux);
    strcpy(palavra, string1);
    strncat(palavra, primeiraLetra_str2,1);
    strcpy(string1, palavra);
    int altera = minuscula(dados, string1, string2, instancia); //SE ENCONTRADAS AS PALAVRAS MODIFICADAS NO DICIONARIO RECEBE 1 CASO NAO RECEBE 0 
    
    if(altera == 1){
        printf("\n String1 = %s, string2 = %s\n", string1, string2);
        printf("\n Correcao aplicada!");
      //formatacao_final(dados,string1, string2, dupla);
    } else if(altera == 0){
        strcpy(string1, stringOrigin_1);
        strcpy(string2, stringOrigin_2);
        
        //formatacao_final(dados,string1, string2, dupla);
    }
        //formatacao_final(dados,string1, string2, dupla);
    

    return altera;
}
int minuscula(DADOS dados[], char string1[],char string2[], int instancia){
    int i,altera;
    char aux1[50],aux2[50];
   // printf("\n%s",string1);
     strcpy(aux1,string1);
     strcpy(aux2,string2);

    for(i=0;aux1[i]!='\0';i++){
        if(isupper(aux1[i])){
            aux1[i] = tolower(aux1[i]);
        }
    }
   aux1[i]='\0';
    for(i=0;aux2[i]!='\0';i++){
        if(isupper(aux2[i])){
            aux2[i] = tolower(aux2[i]);
        }
    }
    aux2[i]='\0';
    //printf("\n%s %s\n",aux1,aux2);
       altera = procura(dados, aux1, aux2, instancia);
       return altera;
}
int procura(DADOS dados[], char string1[],char string2[], int instancia){
    int i,j,k;
    int count_1 = 0;
int count_2 = 0;
    char separacao_palavras_dicionario[TAM_50][TAM_50]; //pega as palvras da SENTENÇA separadas.
    int espaco[TAM_50];//vetor para pegar indices dos espaços
    //printf("\nX %s\n",string1);
    int tamDicionario = strlen(dados[instancia].DICIONARIO);
    //SEPARA AS PALAVRAS DO DICIONARIO NUMA MATRIZ.
    printf("\n Procura por \nString1 = %s\nstring2 = %s\n", string1, string2);
    //printf("String 1 => %s\n",string1);
    //printf("String 2 => %s\n",string2);
    for(i = 0, k = 0, j = 0; i < tamDicionario; i++){
        if(dados[instancia].DICIONARIO[i] != ' '){
            separacao_palavras_dicionario[j][k] = dados[instancia].DICIONARIO[i];
            k++;
        }else{
            espaco[j] = i;
            separacao_palavras_dicionario[j][i]='\0';
            j++;
            k = 0;
        }
        separacao_palavras_dicionario[j][k] = '\0';
    }
    
    
    for(i = 0; i < k; i++){
        if(strcmp(string1, separacao_palavras_dicionario[i]) == 0){
            printf("Procurando %s\n",string1);
            count_1 = 1;
            break;
        }
        
    }

    for(i = 0; i < k;i++){
        if(strcmp(string2, separacao_palavras_dicionario[i]) == 0){
            count_2 = 2;
            break;
        }
    }

    int result;
    if(count_1 == 0 && count_2 == 0){
        result = 0;
    }else if((count_1 + count_2) == 3){
        result = 1;
    }

    return result;
}

void formatacao_final(DADOS dados[],char string1[], char string2[], int instancia){

    
    //printf("%d\n",count_1);
    /* char sentenca[TAM_50];
    char sentenca2[20][50];
    int i;
    if(count_1 == 0 && count_2 == 0){
        strcpy(sentenca2[instancia],string1);
    }else if((count_1 + count_2) == 3&&instancia!=0){
        strcpy(sentenca2[instancia],string1);
        strcpy(sentenca2[instancia+1],string2);
    }else if((count_1 + count_2) == 3&&instancia==0){
            strcpy(sentenca2[instancia],string1);
            strcpy(sentenca2[instancia+1],string2);
    }else{
        strcpy(sentenca2[instancia],string1);
    }

    */
    
    //printf("\nSentenca %d = %s", instancia, sentenca);

    //print_frase(sentenca, instancia);
    
    
}

void print_frase(char frase[], int instancia){
    printf("\nSentenca %d = %s", instancia, frase);
}