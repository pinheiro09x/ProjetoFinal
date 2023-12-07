#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char proprietario[50];
    char combustivel[20];
    char modelo[50];
    char cor[20];
    char chassi[20];
    int ano;
    char placa[10];
} Veiculo;

typedef struct No {
    Veiculo veiculo;
    struct No* proximo;
} No;

void inicializarLista(No** lista) {
    *lista = NULL;
}

void adicionarVeiculo(No** lista, Veiculo novoVeiculo) {
    No* novoNo = (No*)malloc(sizeof(No));
    novoNo->veiculo = novoVeiculo;
    novoNo->proximo = *lista;
    *lista = novoNo;
}

void listarDiesel2010ouPosterior(No* lista) {
    printf("\nProprietarios de carros de 2010 ou posterior movidos a diesel:\n");
    while (lista != NULL) {
        if (lista->veiculo.ano >= 2010 && strcmp(lista->veiculo.combustivel, "diesel") == 0) {
            printf("%s\n", lista->veiculo.proprietario);
        }
        lista = lista->proximo;
    }
}

void listarPlacasJ(No* lista) {
    printf("\nPlacas começando com 'J' e terminando com 0, 2, 4 ou 7 e seus respectivos proprietarios:\n");
    while (lista != NULL) {
        if (lista->veiculo.placa[0] == 'J' &&
            (lista->veiculo.placa[6] == '0' || lista->veiculo.placa[6] == '2' ||
             lista->veiculo.placa[6] == '4' || lista->veiculo.placa[6] == '7')) {
            printf("Placa: %s, Proprietario: %s\n", lista->veiculo.placa, lista->veiculo.proprietario);
        }
        lista = lista->proximo;
    }
}

void listarModeloCorVogal(No* lista) {
    printf("\nModelo e cor de veiculos com placas de segunda letra vogal e soma dos valores numericos par:\n");
    while (lista != NULL) {
        if (strchr("aeiouAEIOU", lista->veiculo.placa[1]) != NULL) {
            int somaNumeros = atoi(lista->veiculo.placa + 3) + atoi(lista->veiculo.placa + 4) +
                              atoi(lista->veiculo.placa + 5) + atoi(lista->veiculo.placa + 6);
            if (somaNumeros % 2 == 0) {
                printf("Modelo: %s, Cor: %s\n", lista->veiculo.modelo, lista->veiculo.cor);
            }
        }
        lista = lista->proximo;
    }
}

void listarVeiculo(Veiculo veiculo) {
    printf("\nVeiculo:\n");
    printf("Proprietario: %s\n", veiculo.proprietario);
    printf("Combustivel: %s\n", veiculo.combustivel);
    printf("Modelo: %s\n", veiculo.modelo);
    printf("Cor: %s\n", veiculo.cor);
    printf("Chassi: %s\n", veiculo.chassi);
    printf("Ano: %d\n", veiculo.ano);
    printf("Placa: %s\n", veiculo.placa);
}

void trocarProprietario(No** lista, char chassi[20], char novoProprietario[50]) {
    No* atual = *lista;

    while (atual != NULL) {
        // Verifica se o chassi atual começa com o chassi fornecido e se não possui dígito zero na placa
        if (strncmp(atual->veiculo.chassi, chassi, strlen(chassi)) == 0 &&
            strchr(atual->veiculo.placa, '0') == NULL) {
            strcpy(atual->veiculo.proprietario, novoProprietario);
            printf("\nProprietario trocado com sucesso.\n");

            // Listar veículo atualizado
            listarVeiculo(atual->veiculo);
            return;
        }
        atual = atual->proximo;
    }

    printf("\nVeiculo nao encontrado ou placa contem digito 0.\n");
}

void liberarLista(No** lista) {
    No* atual = *lista;
    while (atual != NULL) {
        No* proximo = atual->proximo;
        free(atual);
        atual = proximo;
    }
    *lista = NULL;
}

int main() {
    No* lista;
    Veiculo veiculo;

    inicializarLista(&lista);

    int quantidadeVeiculos;
    printf("Quantidade de veiculos a serem adicionados: ");
    scanf("%d", &quantidadeVeiculos);

    for (int i = 0; i < quantidadeVeiculos; ++i) {
        printf("\nVeiculo %d:\n", i + 1);

        printf("Proprietario: ");
        scanf(" %[^\n]s", veiculo.proprietario);

        printf("Combustivel (alcool/diesel/gasolina): ");
        scanf(" %[^\n]s", veiculo.combustivel);

        printf("Modelo: ");
        scanf(" %[^\n]s", veiculo.modelo);

        printf("Cor: ");
        scanf(" %[^\n]s", veiculo.cor);

        printf("Chassi: ");
        scanf(" %[^\n]s", veiculo.chassi);

        printf("Ano: ");
        scanf("%d", &veiculo.ano);

        printf("Placa: ");
        scanf(" %[^\n]s", veiculo.placa);

        adicionarVeiculo(&lista, veiculo);
    }

    listarDiesel2010ouPosterior(lista);
    listarPlacasJ(lista);
    listarModeloCorVogal(lista);

    char chassiTroca[20], novoProprietario[50];
    printf("\nInforme o chassi do veiculo a ter o proprietario trocado: ");
    scanf(" %[^\n]s", chassiTroca);

    printf("Informe o novo proprietario: ");
    scanf(" %[^\n]s", novoProprietario);

    trocarProprietario(&lista, chassiTroca, novoProprietario);

    liberarLista(&lista);

    return 0;
}