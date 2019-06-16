#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 1000000
#define TAM_BRUT 10000
#define TAM_DIC 5000
#define TAM_50 50

typedef struct{ /* PARA CAPTURAR INFORMAÇÕES FORMATADAS CONTIDAS NO ARQUIVO */
    char SENTENCA[2500];
    int VETOR_TEMPO[TAM_50];
    char DICIONARIO[TAM_DIC];
} DADOS;

DADOS dados[TAM_50];

/* PROTÓTIPOS */
int procura(char string1[], char string2[], int instancia);
void correcao_troca(char string1[],char string2[], int instancia, int space);
void tratamento();
void separa_palavras_instancia( int instancia);
void formatacao_final(char string1[], char string2[], int instancia);
int igual(char P1[], char P2[]);
int separaMarizSentenca(int instancia, int tamSentenca);
void separaMatrizDicionario(int instancia, int tamDicionario);
int quantidadeLinhasArquivo();
void export();

/* VARIAVEIS GLOBAIS */
int posicao = 0;
int linha_matriz_sentenca = 0;

/* MATRIZ SENTENCA */
char separacao_palavras_sentenca[TAM_50][TAM_50]; //pega as palvras da SENTENÇA separadas

/* MATRIZ DO DICIONARIO */
char separacao_palavras_dicionario[TAM_50][TAM_50]; //pega as palvras do DICIONARIO separadas.

int espaco[TAM_50], space[TAM_50];//vetor para pegar indices dos espaços

/* PRINCIPAL */
int main(int argc, char const *argv[]){
    
    tratamento(dados);//Tratamento de dados brutos contido no arquivo para struct(dados formatados).
    for(int i = 0; i < 8; i++){// CADA INDICIE CORRESPONDE A UMA INSTANCIA DO ARQUIVO.
        separa_palavras_instancia(i);
        posicao = 0;
        export();
    }

    return 0;
}

void tratamento(){
    int x = 0; // Controle dos indicies da sentenca bruta 
    int ordem = 0; // Controla qual tipo de dado sera capturado, senteça, vetor ou dicionario 
    int control = 0;//Controle para idendificar em qual instancia o arquivo se encontra
    int id_1 = 0, id_2 = 0, id_3 = 0; // Indicie valido para salvar os dados na struct

    //  Estas servem para conversao de um char pra um int
    char atom[7];
    int number = 0;
    int count_pos_atom = 0;

    FILE *fPtr;

    if((fPtr = fopen("Entrada.txt", "r")) == NULL){
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

void separa_palavras_instancia( int instancia){
    int i,j,k;
    int result_busca;
    
    int tamSentenca = strlen(dados[instancia].SENTENCA);

    //SEPARA AS PALAVRAS DA SENTENÇA NUMA MATRIZ.
    j = separaMarizSentenca(instancia,tamSentenca);
    char P1[TAM_50];
    char P2[TAM_50];

    // PALAVRAS SEPARADAS EM DUPLAS PARA FAZER PESQUISA INICIAL AO DICIONARIO.
    for(i = 0; i < j ; i++){
        if(((dados[instancia].VETOR_TEMPO[espaco[i]] - dados[instancia].VETOR_TEMPO[espaco[i]+1])* (-1))<= 20){
            separaMarizSentenca(instancia,tamSentenca);
            strcpy(P1, separacao_palavras_sentenca[i]);// PALAVRA 1
            strcpy(P2, separacao_palavras_sentenca[i+1]);// PALAVRA 2
            
            result_busca = procura(P1, P2, instancia);

            if(result_busca == 0){
                correcao_troca(P1, P2, instancia, espaco[i]); // TROCA DAS DUAS PALAVRAS
            }
        }
    }
}
 
void correcao_troca( char string1[],char string2[], int instancia, int space){
    int i,j,k;
    char stringAux[TAM_50];
    char palavra[TAM_50]; //RECEBE AS PALAVRAS CORRIGIDAS 
    char primeiraLetra_str2[2];
    char stringOrigin_1[TAM_50], stringOrigin_2[TAM_50]; //RECEBEM AS PALAVRAS ORIGINAIS 

    strcpy(stringOrigin_1, string1);
    strcpy(stringOrigin_2, string2);

    int n;
    for(n = 0; string1[n] != '\0'; n++);
    string1[n] = string2[0];
    string1[n+1] = '\0';
    //ARMAZENA A STRING2 EM UMA STRING AUXILIAR SEM A LETRA DA PRIMEIRA POSIÇÃO (FOR COMEÇA DO 1 NAO DO 0) 
    
    for(i = 1, j = 0; string2[i] != '\0'; i++){
        string2[i-1] = string2[i];
    }
    string2[i-1] = '\0';
       
    stringAux[i] = '\0';  //ATRIBUIÇÃO DO ESPAÇO A ULTIMA POSIÇÃO DA STRING AUXILIAR     
    primeiraLetra_str2[0] = string2[0]; //SALVA A PRIMEIA LETRA DA STRING2

    char STRING[TAM_50];
    STRING[0] = '\0';
    strcpy(STRING,string1);
    strcat(STRING, " ");
    strcat(STRING,string2);

    int altera = procura(string1, string2, instancia); //SE ENCONTRADAS AS PALAVRAS MODIFICADAS NO DICIONARIO RECEBE 1 CASO NAO RECEBE 0  
    int tamSentenca = strlen(dados[instancia].SENTENCA);
    
    int tamStr2 = strlen(string2);
    if(tamStr2 == 0){//RESTRIÇÃO PARA NAO PERMITIR UMA P2 DE TAMANHO 0.
        altera = 0;
    }
    
    if(altera == 1){

        separaMarizSentenca(instancia,tamSentenca);        
        int prox = 0;
        for(int i = 0; i < strlen(STRING); i++){
            dados[instancia].SENTENCA[posicao] = STRING[i];
            if(STRING[i] == ' '){
                prox = posicao +1;
            }     
            posicao++;
        }
        
        posicao = prox;// SALVA A POSIÇÃO DO ESPAÇO PARA TESTAR A PROXIMA DUPLA.

    } else {
        separaMarizSentenca(instancia,tamSentenca);
        int inicio = strlen(stringOrigin_1);
        posicao = inicio +1;
    }
}

int procura(char string1[],char string2[], int instancia){

    int tamDicionario = strlen(dados[instancia].DICIONARIO);
    separaMatrizDicionario(instancia,tamDicionario);

    int count_1;
    for(int i = 0; i < tamDicionario; i++){
        count_1 = igual(string1, separacao_palavras_dicionario[i]);
        if(count_1 == 1){
            break;
        }
    }

    int count_2;
    for(int i = 0; i < tamDicionario; i++){
        count_2 = igual(string2, separacao_palavras_dicionario[i]);
        if(count_2 == 1){
            break;
        }
    }
    
    if(count_1 == 0 || count_2 == 0){
        return 0;
    } else {
        if(count_1 == 1 && count_2 == 1){
            return 1;
        }
    }
    
    return -1;
}

int igual(char P1[], char P2[]){

    if((strlen(P1)) != strlen(P2)){
        return 0;
    }

    for(int x = 0; P2[x] != '\0'; x++){
        if(P1[x] != P2[x] && P1[x] != P2[x]-32){
            return 0;
        }
    }
    return 1;
}

void separaMatrizDicionario(int instancia, int tamDicionario){
    int i,j,k;
    //SEPARA AS PALAVRAS DO DICIONARIO NUMA MATRIZ.
    for(i = 0, k = 0, j = 0; i < strlen(dados[instancia].DICIONARIO)-1; i++){
        if(dados[instancia].DICIONARIO[i] != ' '){
            separacao_palavras_dicionario[j][k] = dados[instancia].DICIONARIO[i];
            k++;
        }else{
            espaco[j] = i;
            separacao_palavras_dicionario[j][i] = '\0';
            j++;
            k = 0;
        }
        separacao_palavras_dicionario[j][k] = '\0';
    }
}

int separaMarizSentenca(int instancia, int tamSentenca){
  //  printf("Separa Matriz Sentenca {%s}\n", dados[instancia].SENTENCA);
    int i, j, k;
    for(i = 0, k = 0, j = 0; i < tamSentenca; i++){
        if(dados[instancia].SENTENCA[i] != ' '){
            separacao_palavras_sentenca[j][k] = dados[instancia].SENTENCA[i];
            k++;
        }else{
           espaco[j] = i;
            separacao_palavras_sentenca[j][i] = '\0';
            j++;
            k = 0;
        }
        separacao_palavras_sentenca[j][k] = '\0';
    }

    /* SALVA OS INDICIES DAS POSIÇÕES DO ESPAÇO EM UM VETOR PARA FAZER A SUBTRAÇÃO PARA HABILITAR UMA FUTURA TROCA */
    int space[TAM_50], pos = 0;//salva as posições de todas as intercecções possiveis.
    for(int i = 0; i < tamSentenca; i++){
        if(dados[instancia].SENTENCA[i] == ' '){//Identificado a intersecção entre as duas.
            space[pos] = i;
            pos++;
        }
    }
    return j;
}

int quantidadeLinhasArquivo(){
    FILE *fPtr;
    int qtd_instancias = 0;

    if((fPtr = fopen("Entrada.txt","r")) == NULL){
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
    return qtd_instancias;
}

void export(){
    FILE *fPtr;

    fPtr = fopen("Saida.txt", "w");

    int qtd_linhas_arquivo = quantidadeLinhasArquivo();

    for(int i = 0; i < qtd_linhas_arquivo; i++){
        fprintf(fPtr, "%s\n", dados[i].SENTENCA);
    }
    fclose(fPtr);
}