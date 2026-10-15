#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>

#define ALT_MAX 30
#define LARG_MAX 60

#define DEFAULT 0
#define JUSTA 1
#define BORDA 2
#define BORDA_SIMPLES 3

#define BLACK 30
#define RED 31
#define GREEN 32
#define YELLOW 33
#define BLUE 34
#define PURPLE 35
#define CIAN 36
#define WHITE 37

typedef struct{
	char *opcoes[10];
	int numOpcoes;
}Opcoes;

typedef struct{
	char grade[ALT_MAX][LARG_MAX];
	int cor;
	int corBG;
	int alt;
	int larg;
	int x;
	int y;
	int id;
	Opcoes opcoes;
}Janela;

typedef struct{
	char grade[ALT_MAX][LARG_MAX];
	int cor;
	int alt;
	int larg;
	int x;
	int y;
	int id;
	char *texto;
}JanelaTexto;

Janela *janela=NULL;
int qtd=0;
JanelaTexto *janelaTexto=NULL;

Opcoes start={.opcoes={
			"Iniciar",
			"Configuracoes",
			"Sair",
			"Bonus"},
			.numOpcoes=4
		};

void desenharMenu(int, int);
void desenharJanela(int);
int selecionarOpcao();
void bufferJanela(int, int);
void criarJanela(int, int, int, int, int, int, int, Opcoes);
void criarJanelaTexto(int, int, int, int, int, int);
void bufferJanelaTexto(int, int, char*);
void desenharJanelaTexto(int);

//==========================================================================MAIN========================================================================================

int main(){
	int select;
	
    printf("\033[?25l");
    system("cls");
    
    	//COR, ALT, LARG, X, Y, ID, MENU_ASSOCIADO
    criarJanela(GREEN, BLACK, 6, 15, 10, 10, 0, start);
    bufferJanela(0, BORDA_SIMPLES);
    
    criarJanela(GREEN, GREEN, 6, 15, 35, 10, 1, start);
    bufferJanela(1, DEFAULT);
    
    criarJanela(GREEN, BLACK, 6, 15, 60, 10, 2, start);
    bufferJanela(2, BORDA);
    
    criarJanela(GREEN, BLACK, 6, 15, 85, 10, 3, start);
    bufferJanela(3, JUSTA);
    
    criarJanelaTexto(WHITE, 6, 41, 28, 1, 4);
    bufferJanelaTexto(4, BORDA, "Esse texto e desnecessariamente grande para poder testar a capacidade de escrita dentro das janelas de texto");
    
    desenharJanelaTexto(4);
    
    desenharJanela(0);
    select=selecionarOpcao(0);
    
    //system("cls");
    
    desenharJanela(1);
    select=selecionarOpcao(1);
    
    //system("cls");
    
    desenharJanela(2);
    select=selecionarOpcao(2);
    
    //system("cls");
    
    desenharJanela(3);
    select=selecionarOpcao(3);
    
    system("cls");
    printf("\033[?25h");
    
    free(janela);
    return 0;
}

//============================================================================FUNÇÕES===================================================================================

void desenharMenu(int selecionado, int id) {
	int i;
	
    for(i=0;i<janela[id].opcoes.numOpcoes;i++){
    	printf("\033[%i;%iH", janela[id].y+i+1, janela[id].x+1);
        if(i==selecionado)
            printf("\033[30;47m"); // texto preto fundo branco
        else
            printf("\033[%i;%im", WHITE, janela[id].corBG);
        printf("%s", janela[id].opcoes.opcoes[i]);
        printf("\033[0m");
    }
    fflush(stdout);
}

void desenharJanela(int id){
	int i, j;
	char linha[120];
	
	printf("\033[%i;%im", janela[id].cor, janela[id].corBG);
	for(i=0;i<janela[id].alt;i++){
		printf("\033[%i;%iH", janela[id].y+i, janela[id].x);
		for(j=0;j<janela[id].larg;j++){
			//if(janela[id].grade[i][j]!=' '){
				linha[j]=janela[id].grade[i][j];
			//}
			//else{
			//	linha[j]=' ';
			//}
		}
		linha[j]='\0';
		fputs(linha, stdout);
	}
	printf("\033[0m");
}

int selecionarOpcao(int id){
	int selecionado=0;
	while(1) {
        desenharMenu(selecionado, id);
        int tecla = _getch();
        if(tecla == 224) {
            tecla = _getch();
            if(tecla == 72) 		// seta cima
                selecionado--;
            if(tecla == 80) 		// seta baixo
                selecionado++;
        }
        if(selecionado < 0)
            selecionado = janela[id].opcoes.numOpcoes-1;
        if(selecionado > janela[id].opcoes.numOpcoes-1)
            selecionado = 0;
        if(tecla == 13) 			// ENTER
            break;
    }
    return selecionado;
}

void bufferJanela(int id, int tipo){
	int i, j;
	
	for(i=0;i<janela[id].alt;i++){
		for(j=0;j<janela[id].larg;j++){
			switch(tipo){
				case DEFAULT:{
						janela[id].grade[i][j]=' ';
					break;
				}
				case JUSTA:{
					if(i==0){
						janela[id].grade[i][j]=220;
					}
					else if(i==janela[id].alt-1){
						janela[id].grade[i][j]=223;
					}
					else if(j==0 || j==janela[id].larg-1){
						janela[id].grade[i][j]=219;
					}
					else{
						janela[id].grade[i][j]=' ';
					}
					break;
				}
				case BORDA:{
					if(i==0 && j==0){																//borda superior esquerda
						janela[id].grade[i][j]=201;
					}
					else if(i==0 && j==janela[id].larg-1){												//borda superior direita
						janela[id].grade[i][j]=187;
					}
					else if(j==0 && i==janela[id].alt-1){												//borda inferior esquerda
						janela[id].grade[i][j]=200;
					}
					else if(j==janela[id].larg-1 && i==janela[id].alt-1){									//borda inferior direita
						janela[id].grade[i][j]=188;
					}
					else if(i==0 && j!=janela[id].larg-1 || i==janela[id].alt-1 && j!=janela[id].larg-1){	//borda superior/inferior
						janela[id].grade[i][j]=205;
					}
					else if(j==0 && i!=0 || j==janela[id].larg-1){										//bordas laterais
						janela[id].grade[i][j]=186;
					}
					else{
						janela[id].grade[i][j]=' ';
					}
					break;
				}
				case BORDA_SIMPLES:{
					if(i==0 && j==0){																//borda superior esquerda
						janela[id].grade[i][j]=218;
					}
					else if(i==0 && j==janela[id].larg-1){												//borda superior direita
						janela[id].grade[i][j]=191;
					}
					else if(j==0 && i==janela[id].alt-1){												//borda inferior esquerda
						janela[id].grade[i][j]=192;
					}
					else if(j==janela[id].larg-1 && i==janela[id].alt-1){									//borda inferior direita
						janela[id].grade[i][j]=217;
					}
					else if(i==0 && j!=janela[id].larg-1 || i==janela[id].alt-1 && j!=janela[id].larg-1){	//borda superior/inferior
						janela[id].grade[i][j]=196;
					}
					else if(j==0 && i!=0 || j==janela[id].larg-1){										//bordas laterais
						janela[id].grade[i][j]=179;
					}
					else{
						janela[id].grade[i][j]=' ';
					}
					break;
				}
			}
		}
	}
}

void criarJanela(int cor, int corBG, int alt, int larg, int x, int y, int id, Opcoes menuVar){
	int i;
	
	if(alt>ALT_MAX || larg>LARG_MAX){
		printf("Erro: tamanho de janela %i muito grande", id);
		exit(1);
	}
	janela=realloc(janela, (qtd+1)*sizeof(Janela));
	
	janela[qtd].cor=cor;
	janela[qtd].corBG=corBG+10;
	janela[qtd].alt=alt;
	janela[qtd].larg=larg;
	janela[qtd].x=x;
	janela[qtd].y=y;
	janela[qtd].id=id;
	janela[qtd].opcoes.numOpcoes=menuVar.numOpcoes;
	for(i=0;i<menuVar.numOpcoes;i++){
		janela[qtd].opcoes.opcoes[i] = menuVar.opcoes[i];
		//strcpy(janela[qtd].opcoes.opcoes[i], menuVar.opcoes[i]);
	}
	qtd++;
}

void criarJanelaTexto(int cor, int alt, int larg, int x, int y, int id){
	int i;
	
	if(alt>ALT_MAX || larg>LARG_MAX){
		printf("Erro: tamanho de janela %i muito grande", id);
		exit(1);
	}
	janelaTexto=realloc(janelaTexto, (qtd+1)*sizeof(JanelaTexto));
	
	janelaTexto[qtd].cor=cor;
	janelaTexto[qtd].alt=alt;
	janelaTexto[qtd].larg=larg;
	janelaTexto[qtd].x=x;
	janelaTexto[qtd].y=y;
	janelaTexto[qtd].id=id;
	
	qtd++;
}

void bufferJanelaTexto(int id, int tipo, char *texto){
	int i, j, k;
	
	for(i=0;i<janelaTexto[id].alt;i++){
		for(j=0;j<janelaTexto[id].larg;j++){
			switch(tipo){
				case DEFAULT:{
						janelaTexto[id].grade[i][j]=219;
					break;
				}
				case JUSTA:{
					if(i==0){
						janelaTexto[id].grade[i][j]=220;
					}
					else if(i==janela[id].alt-1){
						janelaTexto[id].grade[i][j]=223;
					}
					else{
						janelaTexto[id].grade[i][j]=219;
					}
					break;
				}
				case BORDA:{
					if(i==0 && j==0){																//borda superior esquerda
						janelaTexto[id].grade[i][j]=201;
					}
					else if(i==0 && j==janelaTexto[id].larg-1){												//borda superior direita
						janelaTexto[id].grade[i][j]=187;
					}
					else if(j==0 && i==janelaTexto[id].alt-1){												//borda inferior esquerda
						janelaTexto[id].grade[i][j]=200;
					}
					else if(j==janelaTexto[id].larg-1 && i==janelaTexto[id].alt-1){									//borda inferior direita
						janelaTexto[id].grade[i][j]=188;
					}
					else if(i==0 && j!=janelaTexto[id].larg-1 || i==janelaTexto[id].alt-1 && j!=janelaTexto[id].larg-1){	//borda superior/inferior
						janelaTexto[id].grade[i][j]=205;
					}
					else if(j==0 && i!=0 || j==janelaTexto[id].larg-1){										//bordas laterais
						janelaTexto[id].grade[i][j]=186;
					}
					else{
						janelaTexto[id].grade[i][j]=' ';
					}
					break;
				}
			}
		}
	}
	for(i=1,j=0,k=0;texto[k]!='\0';j++, k++){
		if(j==janelaTexto[id].larg-3){
			i++;
			j=0;
			if(i==janelaTexto[id].alt-1){
				printf("Erro: texto demasiadamente grande para a janela de texto %i", id);
				exit(1);
			}
		}
		janelaTexto[id].grade[i][j+1]=texto[k];
	}
}

void desenharJanelaTexto(int id){
	int i, j;
	char linha[120];
	
	printf("\033[%im", janelaTexto[id].cor);
	for(i=0;i<janelaTexto[id].alt;i++){
		printf("\033[%i;%iH", janelaTexto[id].y+i, janelaTexto[id].x);
		for(j=0;j<janelaTexto[id].larg;j++){
			if(janelaTexto[id].grade[i][j]!=' '){
				linha[j]=janelaTexto[id].grade[i][j];
			}
			else{
				linha[j]=' ';
			}
		}
		linha[j]='\0';
		fputs(linha, stdout);
	}
	printf("\033[0m");
}
