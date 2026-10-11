#include <stdio.h>
#define TAM 50

int main(){
	int i, j;
	
	printf("\033[?25lLoading\n");
	printf("[\033[2;%iH]", TAM);
	
	for(i=2,j=0;i<TAM;i++,j++){
		Sleep(50);
		printf("\033[32m\033[2;%iH%c", i, 219);
		
		/*if(j==3){
			printf("\033[1;11H\b\b\b   ");
			printf("\033[1;8H   ");
			printf("\033[H\033[2KLoading\n");
			j=-1;
		}
		else{
			printf("\033[1;%iH.", (j+8));
		}*/
	}
	printf("\033[0m");
	
	return 0;
}
