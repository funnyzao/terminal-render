#include <stdio.h>
#include <conio.h>

int main(){
	while(1){
		printf("ok\n");
		if(_kbhit()){
			printf("%i", _getch());
			break;
		}
	}
}
