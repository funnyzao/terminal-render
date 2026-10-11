#include <stdio.h>
#include <conio.h>

#define DEFAULT 0
#define JUSTA 1
#define BORDA 2

typedef struct{
	int grade[30][30];
	int cor;
	int alt;
	int larg;
	int x;
	int y;
	int id;
}Janela;

typedef struct{
	char *opcoes[10];
	int numOpcoes;
	int id;
	int x;
	int y;
}Opcoes;

void desenharMenu(int, Opcoes*);
void desenharJanela(Janela*);
int selecionarOpcao(Opcoes*);
void bufferJanela(Janela*, int);


//==========================================================================MAIN========================================================================================

int main(){
	Janela janela0={.alt=5, .larg=15, .cor=32, .x=45, .y=10, .id=1};
	Opcoes menu0={.opcoes={"Iniciar","Configuracoes","Sair"}, .numOpcoes=3, .id=1, .x=janela0.x+1, .y=janela0.y+1};
	
    printf("\033[?25l");
    bufferJanela(&janela0, BORDA);
    desenharJanela(&janela0);
    printf("\nVoce escolheu: %d\n", selecionarOpcao(&menu0) + 1);
    printf("\033[?25h");
    return 0;
}

//============================================================================FUNÇÕES===================================================================================

void desenharMenu(int selecionado, Opcoes *menu0) {
	int i;
	
    for(i=0;i<menu0->numOpcoes;i++){
    	printf("\033[%i;%iH", menu0->y+i, menu0->x);
        if(i==selecionado)
            printf("\033[30;47m"); // texto preto fundo branco
        else
            printf("\033[0m");
        printf("%s", menu0->opcoes[i]);
        printf("\033[0m");
    }
    fflush(stdout);
}

void desenharJanela(Janela *janela){
	int i, j;
	char linha[120];
	
	printf("\033[%im", janela->cor);
	for(i=0;i<janela->alt;i++){
		printf("\033[%i;%iH", janela->y+i, janela->x);
		for(j=0;j<janela->larg;j++){
			if(janela->grade[i][j]!=' '){
				linha[j]=janela->grade[i][j];
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

int selecionarOpcao(Opcoes *menu){
	int selecionado=0;
	while(1) {
        desenharMenu(selecionado, menu);
        int tecla = _getch();
        if(tecla == 224) {
            tecla = _getch();
            if(tecla == 72) 		// seta cima
                selecionado--;
            if(tecla == 80) 		// seta baixo
                selecionado++;
        }
        if(selecionado < 0)
            selecionado = menu->numOpcoes-1;
        if(selecionado > menu->numOpcoes-1)
            selecionado = 0;
        if(tecla == 13) 			// ENTER
            break;
    }
    return selecionado;
}

void bufferJanela(Janela *janela, int tipo){
	int i, j;
	
	for(i=0;i<janela->alt;i++){
		for(j=0;j<janela->larg;j++){
			switch(tipo){
				case DEFAULT:{
						janela->grade[i][j]=219;
					break;
				}
				case JUSTA:{
					if(i==0){
						janela->grade[i][j]=220;
					}
					else if(i==janela->alt-1){
						janela->grade[i][j]=223;
					}
					else{
						janela->grade[i][j]=219;
					}
					break;
				}
				case BORDA:{
					if(i==0 && j==0){																//borda superior esquerda
						janela->grade[i][j]=201;
					}
					else if(i==0 && j==janela->larg-1){												//borda superior direita
						janela->grade[i][j]=187;
					}
					else if(j==0 && i==janela->alt-1){												//borda inferior esquerda
						janela->grade[i][j]=200;
					}
					else if(j==janela->larg-1 && i==janela->alt-1){									//borda inferior direita
						janela->grade[i][j]=188;
					}
					else if(i==0 && j!=janela->larg-1 || i==janela->alt-1 && j!=janela->larg-1){	//borda superior/inferior
						janela->grade[i][j]=205;
					}
					else if(j==0 && i!=0 || j==janela->larg-1){										//bordas laterais
						janela->grade[i][j]=186;
					}
					else{
						janela->grade[i][j]=' ';
					}
					break;
				}
			}
		}
	}
}
