#include <stdio.h>
#include <conio.h>

#define KEY_RIGHT 77
#define KEY_LEFT 75
#define KEY_UP 72
#define FLOOR 20
#define CHAR_BODY 219
#define SCREEN 120
#define TRUE 1
#define FALSE 0

typedef struct{
	int x;
	int y;
	int inAir;
	int vel;
}Player;

void printChao();
void input(Player *);
void update(Player *);


int main(){
	Player player={1,FLOOR-1, FALSE, 0};
	
	printf("\033[?25l");
	printChao();								//Printa o chao na tela
	
	while(1){
		printf("\033[%i;%iH%c", player.y, player.x, CHAR_BODY);		//Printa o personagem
		Sleep(70);
		fflush(stdout);
		input(&player);
		update(&player);
		printf("\033[Hy=%i\nx=%i \nvel=%i\ninAir=%i", player.y, player.x, player.vel, player.inAir);
	}
}

void printChao(){
	int i;
	printf("\033[33m");
	for(i=0;i<=SCREEN;i++){
		printf("\033[%i;%iH%c", FLOOR, i, CHAR_BODY);
		fflush(stdout);
	}
	printf("\033[0m");
}

void input(Player *player){
	int ch;
	if(_kbhit()){							//Detecta se uma tecla foi pressionada, sem interromper o programa
		ch=getch();
		if(ch==224||ch==0){
			printf("\033[%i;%iH ", player->y, player->x);			//Limpa o estado anterior do personagem
			fflush(stdout);
			ch=getch();
			if(ch==KEY_LEFT && player->x>1) player->x--;			//Andar para a esquerda
			//if(ch==80) y++;
			if(ch==KEY_RIGHT) player->x++;							//Andar para a direita
			if(ch==72 && player->y>1) player->inAir=TRUE;			//Pular
		}
		//printf("%i", y);
	}
}

void update(Player *player){
	if(player->y<FLOOR-1 && player->inAir==FALSE){			//Verifica colisao com o chao, -1 para ficar acima dele
		printf("\033[%i;%iH ", player->y, player->x);		//Limpa o caractere
		fflush(stdout);
		player->y++;
	}
	if(player->inAir==TRUE){
		if(player->vel==0){
			printf("\033[%i;%iH ", player->y, player->x);
			player->vel=3;
			player->y--;
		}
		else if(player->vel!=0){
			printf("\033[%i;%iH ", player->y, player->x);
			player->y--;
			player->vel--;
			if(player->vel==0){
				player->inAir=FALSE;
			}
		}
	}
}
