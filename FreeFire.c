#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define TAM_MAX 10
#define MAX_STR_LEN 1000

typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
    int prioridade;
} Item;

typedef struct {
    Item mochila[10];
    int contador;
} Inventario;

//Códigos sobre os itens.
void inicializarInventario(Inventario *inv) { // inicializa o inventário
    inv->contador = 0;
}

void adicionarItem(Inventario *inv) { // adiciona um item na mochila
    if(inv->contador == TAM_MAX){
        printf("ERRO: Limite de Itens excedido! Não é possível inserir.\n");
        return;
    }
    
    printf("\n--- Adicionar novo item ---\n");
    printf("Nome do item: ");
    fgets(inv->mochila[inv->contador].nome, MAX_STR_LEN, stdin);
    inv->mochila[inv->contador].nome[strcspn(inv->mochila[inv->contador].nome, "\n")] = '\0';
    
    printf("Tipo do item (Arma, Equipamento, Consumível): ");
    fgets(inv->mochila[inv->contador].tipo, 20, stdin);
    inv->mochila[inv->contador].tipo[strcspn(inv->mochila[inv->contador].tipo, "\n")] = '\0';

    printf("Quantidade do item: ");
    scanf("%d", &inv->mochila[inv->contador].quantidade);
    getchar(); // Limpar o buffer

    if(strcmp(inv->mochila[inv->contador].tipo, "Arma") == 0 || strcmp(inv->mochila[inv->contador].tipo, "arma") == 0) {
        inv->mochila[inv->contador].prioridade = 3; // Prioridade alta
    } else if(strcmp(inv->mochila[inv->contador].tipo, "Equipamento") == 0 || strcmp(inv->mochila[inv->contador].tipo, "equipamento") == 0) {
        inv->mochila[inv->contador].prioridade = 2; // Prioridade média
    } else if(strcmp(inv->mochila[inv->contador].tipo, "Consumivel") == 0 || strcmp(inv->mochila[inv->contador].tipo, "consumivel") == 0) {
        inv->mochila[inv->contador].prioridade = 1; // Prioridade baixa
    } else {
        inv->mochila[inv->contador].prioridade = 4; // Prioridade padrão
    }

    printf("\nItem '%s' adicionado à mochila.\n", inv->mochila[inv->contador].nome);
    getchar();
    inv->contador++;
}

void listarMochila(Inventario *inv) { // lista os itens na mochila
    if (inv->contador == 0) {
        printf("\nA mochila está vazia.\n\n");
        getchar();
        return;
    }

    printf("\n--- Itens na Mochila (%d/10) ---\n", inv->contador);
    printf("--------------------------------------------------------------------\n");
    printf("NOME                 | TIPO         | QUANTIDADE         |PRIORIDADE\n");
    printf("--------------------------------------------------------------------\n");

    for (int i = 0; i < inv->contador; i++) {
        printf("%-20s | %-12s | %-20d | %d\n", 
               inv->mochila[i].nome, 
               inv->mochila[i].tipo, 
               inv->mochila[i].quantidade, 
               inv->mochila[i].prioridade);             
    }

    printf("--------------------------------------------------------------------\n");
}

void removerItem(Inventario *inv){ // remove um item pelo nome
    int i, pos = -1;
    char item_removido[30];
    
    if(inv->contador == 0) {
        printf("\nA mochila está vazia.\n\n");
        getchar();
        return;
    }

    printf("Digite o nome do item a remover: ");
    fgets(item_removido, 30, stdin);
    item_removido[strcspn(item_removido, "\n")] = '\0'; // remover \n

    for(i = 0; i < inv->contador; i++){
        if(strcmp(inv->mochila[i].nome, item_removido) == 0){
            pos = i;
            break;
        }
    }

    if(pos == -1){
        printf("ERRO: Item \"%s\" não encontrado na mochila.\n", item_removido);
        return;
    }

    for(i = pos; i < inv->contador - 1; i++){
        inv->mochila[i] = inv->mochila[i + 1];
    }

    inv->contador--;
    printf("Item \"%s\" removido com sucesso!\n\n", item_removido);

    listarMochila(inv);
    getchar();
}

void buscarItem(Inventario *inv){ // busca um item pelo nome
    char item_buscado[30];
    int encontrado = 0;

    if(inv->contador == 0) {
        printf("\nA mochila está vazia.\n\n");
        getchar();
        return;
    }

    printf("\nDigite o nome do item a buscar: ");
    fgets(item_buscado, 30, stdin);
    item_buscado[strcspn(item_buscado, "\n")] = '\0'; // remover \n

    for(int i = 0; i < inv->contador; i++){ // percorre a mochila procurando o item
        if(strcmp(inv->mochila[i].nome, item_buscado) == 0){
            printf("\nItem encontrado:\n");
            printf("Nome: %s\n", inv->mochila[i].nome);
            printf("Tipo: %s\n", inv->mochila[i].tipo);
            printf("Quantidade: %d\n\n", inv->mochila[i].quantidade);
            encontrado = 1;
            getchar();
            break;
        } 
    }

    if(!encontrado){ // caso não encontre o item     
        printf("\nItem \"%s\" não encontrado na mochila.\n", item_buscado);
        getchar();
    }
}

//Códigos sobre ordenação
void bubbleSort(Inventario *inv, int n) { // ordena por nome usando o método bubble sort
    int i, j;
    Item temp;
    for (i = 0; i < n-1; i++) {
        for (j = 0; j < n-i-1; j++) {
            if (strcmp(inv->mochila[j].nome, inv->mochila[j+1].nome) > 0) {
                temp = inv->mochila[j];
                inv->mochila[j] = inv->mochila[j+1];
                inv->mochila[j+1] = temp;
            }
        }
    }
}

void insertionSort(Inventario *inv, int n) { // ordena por tipo usando o método insertion sort
    int i, j;
    Item chave;
    for (i = 1; i < n; i++) {
        chave = inv->mochila[i];
        j = i - 1;
        while (j >= 0 && strcmp(inv->mochila[j].tipo, chave.tipo) > 0) {
            inv->mochila[j + 1] = inv->mochila[j];
            j = j - 1;
        }
        inv->mochila[j + 1] = chave;
    }
}

void selectionSort(Inventario *inv, int n) { // ordena por prioridade usando o método selection sort
    int i, j, min_idx;
    Item temp;
    for (i = 0; i < n-1; i++) {
        min_idx = i;
        for (j = i+1; j < n; j++) {
            if (inv->mochila[j].prioridade < inv->mochila[min_idx].prioridade) {
                min_idx = j;
            }
        }
        temp = inv->mochila[min_idx];
        inv->mochila[min_idx] = inv->mochila[i];
        inv->mochila[i] = temp;
    }
}

void menuOrdenacao(Inventario *inv) { // menu para escolher o tipo de ordenação
    int opcao;
    
    printf("\n--- Organizar Mochila ---\n");
    printf("1. Ordenar por Nome (A-Z)\n");
    printf("2. Ordenar por Tipo\n");
    printf("3. Ordenar por Prioridade\n");
    printf("0. Voltar ao Menu Principal\n");
    printf("----------------------------\n");
    printf("Escolha uma opção: ");
    scanf("%d", &opcao);
    getchar();

    switch(opcao) {
        case 1:
            bubbleSort(inv, inv->contador);
            printf("Mochila organizada por Nome (A-Z).\n");
            listarMochila(inv);
            getchar();
            break;
        case 2:
            insertionSort(inv, inv->contador);
            printf("Mochila organizada por Tipo.\n");
            listarMochila(inv);
            getchar();
            break;
        case 3:
            selectionSort(inv, inv->contador);
            printf("Mochila organizada por Prioridade.\n");
            listarMochila(inv);
            getchar();
            break;
        case 0:
            return;
        default:
            printf("Opção inválida. Tente novamente.\n");
    }
}

void menuInventario() { // menu principal do inventário
    Inventario inv;
    inicializarInventario(&inv);
    int opcao;

    do{   
        printf("============================\n");
        printf("  MOCHILA DE SOBREVIVENCIA - CODIGO DA ILHA  \n");
        printf("============================\n");
        printf("Itens na mochila: %d/10\n\n", inv.contador);

        printf("1. Adicionar Item (Loot).\n");
        printf("2. Remover Item.\n");
        printf("3. Listar Itens na Mochila.\n");
        printf("4. Buscar Item.\n");
        printf("5. Organizar Mochila.\n");
        printf("0. Sair.\n");

        printf("----------------------------\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        getchar();
        
        switch(opcao) {
            case 1:
                adicionarItem(&inv);
                break;
            case 2:
                removerItem(&inv);
                break;
            case 3:
                listarMochila(&inv);
                getchar();
                break;
            case 4:
                buscarItem(&inv);
                break;
            case 5:
                menuOrdenacao(&inv);
                break;
        } 
    } while(opcao != 0);
}

int main() {
    menuInventario();
    return 0;
}
