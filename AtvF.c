#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// Estrutura para armazenar os registros dos veículos
struct Veiculo {
    char proprietario[50];
    char combustivel[20];
    char modelo[50];
    char cor[20];
    char numChassi[20];
    int ano;
    char placa[8];
    struct Veiculo *prox;
};


// Função para listar proprietários de carros do ano de 2010 ou posterior e movidos a diesel
void listarDiesel2010(struct Veiculo *inicio) {
    struct Veiculo *ptr = inicio;


    printf("\nProprietários de carros do ano 2010 ou posterior movidos a diesel:\n");
    while (ptr != NULL) {
        if (ptr->ano >= 2010 && strcmp(ptr->combustivel, "diesel") == 0) {
            printf("Proprietário: %s\n", ptr->proprietario);
        }
        ptr = ptr->prox;
    }
}


// Função para listar placas que atendem a condição específica e seus respectivos proprietários
void listarPlacasJ(struct Veiculo *inicio) {
    struct Veiculo *ptr = inicio;


    printf("\nPlacas que começam com J e terminam com 0, 2, 4 ou 7 e seus respectivos proprietários:\n");
    while (ptr != NULL) {
        if (ptr->placa[0] == 'J' && (ptr->placa[6] == '0' || ptr->placa[6] == '2' || ptr->placa[6] == '4' || ptr->placa[6] == '7')) {
            printf("Placa: %s\t Proprietário: %s\n", ptr->placa, ptr->proprietario);
        }
        ptr = ptr->prox;
    }
}


// Função auxiliar para calcular a soma dos valores numéricos de uma placa
int somaValoresNumericos(char *placa) {
    int soma = 0;
    for (int i = 3; i < 7; i++) {
        soma += (placa[i] - '0');
    }
    return soma;
}


// Função para listar modelo e cor dos veículos com condições específicas na placa
void listarModeloCor(struct Veiculo *inicio) {
    struct Veiculo *ptr = inicio;


    printf("\nModelo e cor dos veículos com placas que possuem como segunda letra uma vogal e cuja soma dos valores numéricos é par:\n");
    while (ptr != NULL) {
        if ((ptr->placa[1] == 'A' || ptr->placa[1] == 'E' || ptr->placa[1] == 'I' || ptr->placa[1] == 'O' || ptr->placa[1] == 'U') &&
            somaValoresNumericos(ptr->placa) % 2 == 0) {
            printf("Modelo: %s\t Cor: %s\n", ptr->modelo, ptr->cor);
        }
        ptr = ptr->prox;
    }
}


// Função para trocar o proprietário com base no número do chassi para carros com placas sem dígito zero
void trocarProprietario(struct Veiculo *inicio, char *chassi, char *novoProprietario) {
    struct Veiculo *ptr = inicio;


    while (ptr != NULL) {
        int zeroEncontrado = 0;
        for (int i = 0; i < strlen(ptr->placa); i++) {
            if (ptr->placa[i] == '0') {
                zeroEncontrado = 1;
                break;
            }
        }
        if (!zeroEncontrado && strcmp(ptr->numChassi, chassi) == 0) {
            strcpy(ptr->proprietario, novoProprietario);
            printf("Proprietário do veículo com chassi %s atualizado para: %s\n", chassi, novoProprietario);
            return;
        }
        ptr = ptr->prox;
    }
    printf("Nenhum veículo encontrado com as condições especificadas.\n");
}


// Função para inserir um veículo no início da lista encadeada
void inserirVeiculo(struct Veiculo **inicio, struct Veiculo novoVeiculo) {
    struct Veiculo *novoNo = (struct Veiculo *)malloc(sizeof(struct Veiculo));
    *novoNo = novoVeiculo;
    novoNo->prox = *inicio;
    *inicio = novoNo;
}


int main() {
    struct Veiculo *inicio = NULL;


    // Exemplo de inserção de veículos na lista
    struct Veiculo carro1 = {"Proprietario1", "diesel", "Modelo1", "Cor1", "Chassi1", 2010, "JAB1234"};
    struct Veiculo carro2 = {"Proprietario2", "gasolina", "Modelo2", "Cor2", "Chassi2", 2015, "JZZ0247"};
    struct Veiculo carro3 = {"Proprietario3", "diesel", "Modelo3", "Cor3", "Chassi3", 2012, "KIA1010"};


    inserirVeiculo(&inicio, carro1);
    inserirVeiculo(&inicio, carro2);
    inserirVeiculo(&inicio, carro3);


    listarDiesel2010(inicio);
    listarPlacasJ(inicio);
    listarModeloCor(inicio);
    trocarProprietario(inicio, "Chassi2", "NovoProprietario");


    return 0;
}


