#include <stdio.h>
#define MV_CURSOR "\033[2;1H"
#define HIDE_CURSOR "\033[?25l"

int main(){
	int i;
	
	printf(HIDE_CURSOR"Loading...\n");
	
	for(i=0;i<=100;i++){
		printf(MV_CURSOR"%i%%\n",i);
		Sleep(50);
		
		if(_kbhit()) {
            _getch();
            printf("Loading interrompido ;-;");
            break; 
		}
	}
	
	return 0;
}
