#include <stdio.h>
#include <conio.h>

void desenharMenu(int selecionado) {
	int i;
	
    printf("\033[2J");
    printf("\033[H");

    char *opcoes[3] = {
        "Iniciar",
        "Configuracoes",
        "Sair"
    };

    for(i = 0; i < 3; i++) {

        if(i == selecionado)
            printf("\033[30;47m"); // texto preto fundo branco
        else
            printf("\033[0m");

        printf("  %s\n", opcoes[i]);
    }

    printf("\033[0m");
}

int main() {

    printf("\033[?25l");

    int selecionado = 0;

    while(1) {

        desenharMenu(selecionado);

        int tecla = _getch();

        if(tecla == 224) {

            tecla = _getch();

            if(tecla == 72) // seta cima
                selecionado--;

            if(tecla == 80) // seta baixo
                selecionado++;
        }

        if(selecionado < 0)
            selecionado = 2;

        if(selecionado > 2)
            selecionado = 0;

        if(tecla == 13) // ENTER
            break;
    }

    printf("\nVoce escolheu: %d\n", selecionado + 1);

}
