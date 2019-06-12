#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 1000000
#define TAM_BRUT 10000
#define TAM_50 50

typedef struct{ /* PARA CAPTURAR INFORMAÇÕES FORMATADAS CONTIDAS NO ARQUIVO */
    char SENTENCA[TAM_50];
    int VETOR_TEMPO[TAM_50];
    char DICIONARIO[TAM_50][TAM_50];
} DADOS;

/* PROTÓTIPOS */
int procura(DADOS *dados, char string1[], char string2[]);
int troca(DADOS *dados, char string1[], char string2[]);
int quantidadeLinhasArquivo();
void tratamento(int qtd_instancias);

/* PRINCIPAL */
int main(int argc, char const *argv[]){
    int i, j, k;

    int qtd_instancias_arquivo = quantidadeLinhasArquivo();//Conta quantas linhas o arquivo tem.

    tratamento(qtd_instancias_arquivo);//Tratamento de dados brutos contido no arquivo para struct(dados formatados).
    
    return 0;
}

void tratamento(int qtd_instancias){
    DADOS instancia[qtd_instancias];//Instanciada o vetor de dados formatados.

    int control = 0;//Controle para idendificar em qual instancia o arquivo se encontra
    
    char atom[7];
    int number=0;
    int count_pos_atom =0;

    FILE *fPtr;

    if((fPtr = fopen("entrada.txt", "r")) == NULL){
        exit(1);
    } else {
        while(!feof(fPtr)){
            char sentenca_bruta[TAM_BRUT];
            fgets(sentenca_bruta, TAM_BRUT, fPtr);
            printf("Bruta => %s\n",sentenca_bruta);
            int x = 0; // Controle dos indicies da sentenca bruta
            int id_1 = 0, id_2 = 0, id_3 = 0; // Indicie valido para salvar os dados na struct 
            int ordem = 0; // Controla qual tipo de dado sera capturado, senteça, vetor ou dicionario 
            int linha_dic = 0;// controla as palavras contidas no dicionario para salvar uma em cada linha da matriz da struct de dados 
         do{
                if((ordem == 0) && (sentenca_bruta[x] != '"') && (sentenca_bruta[x] != ',')){
                    if(sentenca_bruta[x] == '{'){// caso encontre { entao ira começar a salvar os valores numericos
                        ++ordem;
                        x++;
                    } else {
                        instancia[control].SENTENCA[id_1] = sentenca_bruta[x];
                        id_1++; // incremento da variavel sentença da struct
                        //x++;
                    }
                } 
                if((ordem == 1) && (sentenca_bruta[x] != '"') && (sentenca_bruta[x] != ' ') && (sentenca_bruta[x] != '}') ){
                    // Ascii 0 = 48, Então, se quisermos o número inteiro de algum char é preciso somente retirarmos 48 de seu valor
                    if(ordem==1 && sentenca_bruta[x] == ','){
                        number = atoi(atom);
                         instancia[control].VETOR_TEMPO[id_2] = number;
                         number = 0;
                         count_pos_atom=0;
                        id_2++;
                    }
                       if(ordem == 1 && sentenca_bruta[x]!= ','){
                            atom[count_pos_atom] = sentenca_bruta[x];
                            count_pos_atom++;
                        }
                        if(ordem==1&&sentenca_bruta[x]=='{'){
                            ordem =2;
                            x++;
                        }   
                }
                if((ordem == 2)){
                    if(sentenca_bruta[x]!=','){
                        if(sentenca_bruta[x]!='{'){
                            if(sentenca_bruta[x]=='"' && sentenca_bruta[x+1]==','){
                                instancia[control].DICIONARIO[linha_dic][id_3] = '\0';
                                linha_dic++;
                                id_3 =0;
                            }else if(sentenca_bruta[x]!='"'&&sentenca_bruta[x]!='}'){
                                instancia[control].DICIONARIO[linha_dic][id_3] = sentenca_bruta[x];
                                id_3++;
                            }
                        } 
                    }
                }
               x++;
               //printf("ordem => %d",ordem);
            } while(sentenca_bruta[x] != '\0');

            int tamSentenca = strlen(instancia[control].SENTENCA);

            control++; // INCREMENTO DA LINHA OU NOVA SENTENÇA NO ARQUIVO 
        }
        fclose(fPtr);
    }
      printf("%s\n",instancia[0].DICIONARIO[2]);       
}

int quantidadeLinhasArquivo(){
    FILE *fPtr;
    int qtd_instancias = 0;

    if((fPtr = fopen("entrada.txt","r")) == NULL){
        exit(1);
    } else {
        char caractere_linha;
        while(fread (&caractere_linha, sizeof(char), 1, fPtr)) {
            if(caractere_linha == '\n'){
                qtd_instancias++;
            }
        }
        fclose(fPtr);
    }
    return qtd_instancias +1;
}

/*
    // SEPARA AS PALAVRAS CONTIDAS NA SENTENÇA EM STRINGS SEPARADAS 
    int space[10];//vetor que pega os indices de onde o tempo corresponde ao espaço
    char string_1[TAM_50][TAM_50];
    for(i = 0, k = 0, j = 0; i < tamSentenca; i++){
        if(instancia[control].SENTENCA[i] != ' '){ 
            string_1[j][k] = instancia[control].SENTENCA[i];
            k++;
        }else{// CASO ONDE É IDENTIFICADO UM ESPAÇO
            space[j] = i;
            string_1[j][i]= '\0';
            j++;
            k = 0;
        }
        string_1[j][k+1] = '\0';
    }
*/