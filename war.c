#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define TAM_STRING 100

// Estrutura
struct war {
    char territorio[TAM_STRING];
    char cor[TAM_STRING];
    int tropa;
};

// Limpar buffer
void limparBufferEntrada() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Dado (1 a 6)
int valorDado() {
    return (rand() % 6) + 1;
}

int main() {
    struct war *cadastro;
    int total = 0;
    int qtd = 5; // número de territórios fixo

    srand(time(NULL)); // inicializa rand

    // Aloca memória com calloc
    cadastro = (struct war*) calloc(qtd, sizeof(struct war));
    if (cadastro == NULL) {
        printf("Erro de alocação!\n");
        return 1;
    }

    // Cadastro
    while (total < qtd) {
        printf("\nDigite o nome do território: ");
        fgets(cadastro[total].territorio, TAM_STRING, stdin);
        cadastro[total].territorio[strcspn(cadastro[total].territorio, "\n")] = '\0';

        printf("Digite a cor: ");
        fgets(cadastro[total].cor, TAM_STRING, stdin);
        cadastro[total].cor[strcspn(cadastro[total].cor, "\n")] = '\0';

        printf("Digite a quantidade de tropas: ");
        scanf("%d", &cadastro[total].tropa);
        limparBufferEntrada();

        total++;
    }

    // Mostrando territórios cadastrados
    printf("\n====================================\n");
    printf("--- Territórios cadastrados ---\n");
    for (int i = 0; i < total; i++) {
        printf("%d) Território: %s | Cor: %s | Tropas: %d\n",
               i + 1, cadastro[i].territorio, cadastro[i].cor, cadastro[i].tropa);
    }

    // --- Loop de ataques ---
    printf("\n====================================\n");
    printf("=== FASE DE ATAQUE ===\n");

    while (1) {
        int atacante, defensor;

        printf("\nEscolha o território atacante (1 a %d, ou 0 para sair): ", total);
        scanf("%d", &atacante);
        limparBufferEntrada();

        if (atacante == defensor || atacante < 0 || atacante >= total || defensor < 0 || defensor >= total) {
            printf("Escolha inválida!\n");
            continue; // volta para o próximo ataque
        }

        if (atacante == 0) {
            printf("Saindo do jogo...\n");
            break;
        }

        printf("Escolha o território defensor (1 a %d): ", total);
        scanf("%d", &defensor);
        limparBufferEntrada();

        // Ajusta índices
        atacante--;
        defensor--;

       
        printf("\n--- RESULTADO DA BATALHA ---\n");

        int dadoAtacante = valorDado();
        int dadoDefensor = valorDado();

        printf("O atacante %s rolou um dado e tirou: %d\n", cadastro[atacante].territorio, dadoAtacante);
        printf("O defensor %s rolou um dado e tirou: %d\n", cadastro[defensor].territorio, dadoDefensor);

        if (dadoAtacante > dadoDefensor) {
            printf("\nVITÓRIA DO ATAQUE! O defensor perdeu 1 tropa.\n");
            cadastro[defensor].tropa--;

                if (cadastro[defensor].tropa <= 0) {
                    if (cadastro[atacante].tropa > 1) {
                        printf("CONQUISTA! O território %s foi dominado pelo Exército %s!\n",
                            cadastro[defensor].territorio, cadastro[atacante].cor);

                        // Transfere 1 tropa mínima para o território conquistado
                        strcpy(cadastro[defensor].cor, cadastro[atacante].cor);
                        cadastro[defensor].tropa = 1;
                        cadastro[atacante].tropa--;

                    } else {
                        // Caso especial: atacante só tinha 1 tropa
                        printf("O atacante não possui tropas suficientes para ocupar o território!\n");
                        cadastro[defensor].tropa = 1; // defensor mantém 1 tropa mínima
                    }
                }

        } else {
            printf("\nDEFESA RESISTIU! O atacante perdeu 1 tropa.\n");
            cadastro[atacante].tropa--;
        }

        // Situação final
        printf("\n--- Situação atual ---\n");
        for (int i = 0; i < total; i++) {
            printf("%d) %s (Exército %s, Tropas: %d)\n",
                   i + 1, cadastro[i].territorio, cadastro[i].cor, cadastro[i].tropa);
        }
    }

    free(cadastro);
    return 0;
}
