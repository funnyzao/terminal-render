#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>

#define DEFAULT 0
#define JUSTA 1
#define BORDA 2

typedef struct{
	char *opcoes[10];
	int numOpcoes;
}Opcoes;

typedef struct{
	int grade[30][30];
	int cor;
	int alt;
	int larg;
	int x;
	int y;
	int id;
	Opcoes opcoes;
}Janela;

Janela *janela=NULL;
int qtd=0;
Opcoes menu={.opcoes={
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
void criarJanela(int cor, int alt, int larg, int x, int y, int id, Opcoes menuVar){
	int i;
	janela=realloc(janela, (qtd+1)*sizeof(Janela));
	
	janela[qtd].cor=cor;
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

//==========================================================================MAIN========================================================================================

int main(){
	int select;
	
    printf("\033[?25l");
    	//COR, ALT, LARG, X, Y, ID, MENU_ASSOCIADO
    criarJanela(32, 6, 15, 45, 10, 0, menu);
    bufferJanela(0, BORDA);
    desenharJanela(0);
    
    select=selecionarOpcao(0);
    printf("\nVoce escolheu: %d\n", select + 1);
    
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
            printf("\033[0m");
        printf("%s", janela[id].opcoes.opcoes[i]);
        printf("\033[0m");
    }
    fflush(stdout);
}

void desenharJanela(int id){
	int i, j;
	char linha[120];
	
	printf("\033[%im", janela[id].cor);
	for(i=0;i<janela[id].alt;i++){
		printf("\033[%i;%iH", janela[id].y+i, janela[id].x);
		for(j=0;j<janela[id].larg;j++){
			if(janela[id].grade[i][j]!=' '){
				linha[j]=janela[id].grade[i][j];
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
						janela[id].grade[i][j]=219;
					break;
				}
				case JUSTA:{
					if(i==0){
						janela[id].grade[i][j]=220;
					}
					else if(i==janela[id].alt-1){
						janela[id].grade[i][j]=223;
					}
					else{
						janela[id].grade[i][j]=219;
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
			}
		}
	}
}
