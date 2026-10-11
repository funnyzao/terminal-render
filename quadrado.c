#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv){
	int x=20, y=10, i;
	
	if(argc>=2){
		if(argv[1][0]!='-'){
			printf("Parametros nao condizentes");
			return 2;
		}
		
		switch(argv[1][1]){
			case 'r':{
				printf("\033[31m");
				break;
			}
			case 'y':{
				printf("\033[33m");
				break;
			}
			case 'b':{
				printf("\033[34m");
				break;
			}
			case 'g':{
				printf("\033[32m");
				break;
			}
			case 'p':{
				printf("\033[35m");
				break;
			}
			case 'w':{
				printf("\033[37m");
				break;
			}
			case 'c':{
				printf("\033[36m");
				break;
			}
			default:{
				printf("Parametros nao condizentes");
				return 1;
			}
		}
	}
	
	switch(argc){
		case 1:{
			break;
		}
		case 2:{
			break;
		}
		case 3:{
			x=atoi(argv[2]);
			break;
		}
		case 4:{
			x=atoi(argv[2]);
			y=atoi(argv[3]);
			break;
		}
		default:{
			printf("Parametros nao condizentes");
			return 1;
		}
	}
	printf("\033[2J");							//Limpar tela
	//printf("\033[41m");						//Fundo vermelho
	
	printf("\033[1;1H%c",201);					//Printar a borda
	printf("\033[%i;1H%c", y, 200);				//Lateral esquerda
	
	for(i=2;i<x;i++){
		printf("\033[1;%iH%c", i, 205);			//Topo 220 se for quadrado
		printf("\033[%i;%iH%c", y, i, 205);		//Baixo 223 se for quadrado
	}
	
	printf("\033[1;%iH%c", x, 187);				//Printar a borda
	printf("\033[%i;%iH%c", y, x, 188);			//Lateral direita
	
	for(i=2;i<y;i++){
		printf("\033[%i;1H%c", i, 186);			//Esquerda 219 se for quadrado
		printf("\033[%i;%iH%c", i, x, 186);		//Direita 219 se for quadrado
	}
	printf("\033[0m");							//Voltar cor padrao
	puts("");
}
