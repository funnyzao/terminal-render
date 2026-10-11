#include <stdio.h>
#define ALT 10
#define LAR 20
//TAMANHO DO TERMINAL PADRAO 30X120

void atualizar_estado(int grade[ALT][LAR]);
void renderizar_buffer(int grade[ALT][LAR], int x, int y, int tela[30][120]);
void printar_tela(int tela[30][120]);
void limpar_tela(int tela[30][120]);

int main(){
	int grade[ALT][LAR], x=10, y=10, tela[30][120];
	
	printf("\033[7m");
	limpar_tela(tela);
	atualizar_estado(grade);
	renderizar_buffer(grade, x, y, tela);
	printar_tela(tela);
	printf("\033[0m");
	
	return 0;
}

void atualizar_estado(int grade[ALT][LAR]){
	int i,j;
	for(i=0;i<ALT;i++){
		for(j=0;j<LAR;j++){
			if(i==0||j==0||j==LAR-1||i==ALT-1){
				grade[i][j]=1;
			}
			else{
				grade[i][j]=0;
			}
		}
	}
}

void renderizar_buffer(int grade[ALT][LAR], int x, int y, int tela[30][120]){
    int i, j;

    for(i=0;i<ALT;i++){
        for(j=0;j<LAR;j++){
            int tela_y = y + i;
            int tela_x = x + j;

            if(tela_y < 0 || tela_y >= 30 || tela_x < 0 || tela_x >= 120)
                continue;

            tela[tela_y][tela_x] = grade[i][j];
        }
    }
}

void printar_tela(int tela[30][120]){
	int i, j;
	for(i=0;i<30;i++){
		for(j=0;j<120;j++){
			if(tela[i][j]==1){
				putchar(219);
			}
			else{
				printf(" ");
			}
		}
	}
}

void limpar_tela(int tela[30][120]){
	int i, j;
	for(i=0;i<30;i++){
		for(j=0;j<120;j++){
			tela[i][j]=0;
		}
	}
}
