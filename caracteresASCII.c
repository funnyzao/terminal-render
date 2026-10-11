#include <stdio.h>

int main(){
	int i;
	
	for(i=0;i<=256;i++){
		printf("%3i - %c\n", i, i);
	}
	system("pause");
	return 0;
}
