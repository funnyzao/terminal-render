#include <stdio.h>
#define ALT 30
#define LAR 120
#define JANELA_ALT 10
#define JANELA_LAR 30
#define RED 31
#define BLUE 34
#define GREEN 32
#define SOLID 0
#define HOLLOW 1

typedef struct{
	char caracter;
	int cor;
}Pixel;

typedef struct{
	Pixel grade[JANELA_ALT][JANELA_LAR];
	int x;
	int y;
}Janela;

typedef struct{
	Pixel gradeTela[ALT][LAR];
}Tela;

void initScreen(Tela*);
void bufferJanela(Janela*, int, int);
void renderScreen(Janela, Tela*, int*);
void printScreen(Tela*, int);

int main(){
	Janela janela0={.x=5, .y=3}, janela1={.x=35, .y=3}, janela2={.x=65, .y=3};
	Tela pilha[5];
	int topo=0;
	
	printf("\033[?25l");							//Esconde cursor
	
	initScreen(pilha);								//Escrever todos os valores da pilha como 0
	bufferJanela(&janela0, RED, SOLID);				//Armazenar a janela
	bufferJanela(&janela1, BLUE, SOLID);
	bufferJanela(&janela2, GREEN, SOLID);
	renderScreen(janela0, pilha, &topo);				//Renderizar elementos da janela na pilha
	renderScreen(janela1, pilha, &topo);
	renderScreen(janela2, pilha, &topo);
	printScreen(pilha, topo);						//Printa a tela da pilha
	printf("\033[?25h");
	return 0;
}

void initScreen(Tela *pilha){
	int i,j, k;
	for(k=0;k<5;k++){
		for(i=0;i<ALT;i++){
			for(j=0;j<LAR;j++){
				pilha[k].gradeTela[i][j].caracter=0;
				pilha[k].gradeTela[i][j].cor=0;
			}
		}
	}
}
void bufferJanela(Janela *janela, int cor, int estado){
	int i, j;
	switch(estado){
		case SOLID:{
			for(i=0;i<JANELA_ALT;i++){
				for(j=0;j<JANELA_LAR;j++){
					janela->grade[i][j].caracter=219;
					janela->grade[i][j].cor=cor;
				}
			}
			break;
		}
		case HOLLOW:{
			for(i=0;i<JANELA_ALT;i++){
				for(j=0;j<JANELA_LAR;j++){
					if(j==0||j==JANELA_LAR-1){
						janela->grade[i][j].caracter=219;
					}
					else if(i==0){
						janela->grade[i][j].caracter=223;
					}
					else if(i==JANELA_ALT-1){
						janela->grade[i][j].caracter=220;
					}
					janela->grade[i][j].cor=cor;
				}
			}
			break;
		}
	}
	
}
void renderScreen(Janela janela, Tela *pilha, int *topo){ 
	int i, j;
	
	if(*topo>0){
		pilha[*topo]=pilha[*topo-1];
	}
	for(i=0;i<JANELA_ALT;i++){
		for(j=0;j<JANELA_LAR;j++){
			pilha[*topo].gradeTela[janela.y+i][janela.x+j].caracter=janela.grade[i][j].caracter;
			pilha[*topo].gradeTela[janela.y+i][janela.x+j].cor=janela.grade[i][j].cor;
		}
	}
	(*topo)++;
}
void printScreen(Tela pilha[5], int topo){
	int i, j, pos;
	char linha[1000];
	int corAtual= -1;
	
	topo--;
	
	for(i=0;i<ALT;i++){
		for(j=0, pos=0;j<LAR;j++,pos++){
			if(pilha[topo].gradeTela[i][j].caracter!=0){
				if(pilha[topo].gradeTela[i][j].cor!=corAtual){
					corAtual=pilha[topo].gradeTela[i][j].cor;
					sprintf(&linha[pos], "\033[%im", corAtual);
					pos+=5;
				}
				linha[pos]=pilha[topo].gradeTela[i][j].caracter;
			}
			else{
				linha[pos]=' ';
			}
		}
		linha[pos]='\0';
		fputs(linha, stdout);
	}
	printf("\033[0m");	
}
