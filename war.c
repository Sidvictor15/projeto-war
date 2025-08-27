#include <stdio.h>
#include <stdlib.h>
#include <string.h> // Para strcspn()

// --- Constantes Globais ---
#define MAX_LIVROS 50
#define TAM_STRING 100

// --- Definição da Estrutura ---
struct war {
    char territorio[TAM_STRING];
    char cor[TAM_STRING];
    int tropa;
};

// --- Função para limpar o buffer de entrada ---
void limparBufferEntrada() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// --- Função Principal (main) ---
int main() {
    struct war cadastro[MAX_LIVROS];
    int total = 0;

    while (total < 5) {  // aqui vai cadastrar 6 territórios

        printf("\nDigite o nome do território: ");
        fgets(cadastro[total].territorio, TAM_STRING, stdin);
        cadastro[total].territorio[strcspn(cadastro[total].territorio, "\n")] = '\0';



        printf("Digite a cor: ");
        fgets(cadastro[total].cor, TAM_STRING, stdin);
        cadastro[total].cor[strcspn(cadastro[total].cor, "\n")] = '\0';

        printf("Digite a quantidade de tropas: ");
        scanf("%d", &cadastro[total].tropa);
        limparBufferEntrada(); // limpa enter do buffer

        total++;
    }
     printf("\n====================================\n");
    // Mostrando o que foi cadastrado
    printf("\n--- Territórios cadastrados ---\n");
    for (int i = 0; i < total; i++) {
        printf("%d) Território: %s | Cor: %s | Tropas: %d\n",
               i + 1,
               cadastro[i].territorio,
               cadastro[i].cor,
               cadastro[i].tropa);
    }

    return 0;
}
