#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_ITENS 10
#define MAX_STR_NOME 30
#define MAX_STR_TIPO 20

typedef struct {
    char name[MAX_STR_NOME];
    char type[MAX_STR_TIPO];
    int quantity;
} DadosItem;

typedef struct {
    DadosItem itens[MAX_ITENS];
    int contador;
}ListaEstatica;

void inicializarLista(ListaEstatica *lista){
    lista->contador = 0;
}

void adicionarItem(ListaEstatica *lista){
    char nome[MAX_STR_NOME];
    char tipo[MAX_STR_TIPO];
    int quantidade;

    if(lista->contador == MAX_ITENS){
        printf("Erro: Mochila cheia! Não é possível coletar mais itens");
        return;
    }

    printf("\nNome do item: ");
    fgets(nome, MAX_STR_NOME, stdin);
    nome[strcspn(nome, "\n")] = 0;

    printf("Tipo do item (arma, munição, cura, etc.): ");
    fgets(tipo, MAX_STR_NOME, stdin);
    tipo[strcspn(tipo, "\n")] = 0;

    printf("Quantidade: ");
    scanf("%d", &lista->itens[lista->contador].quantity);
    getchar();

    strcpy(lista->itens[lista->contador].name, nome);
    strcpy(lista->itens[lista->contador].type, tipo);

    lista->contador++;
    printf("\nItem \"%s\" adicionado a mochila. \n\n", nome);
    printf("          --- ITENS NA MOCHILA (%d/10) ---          \n", lista->contador);
    printf("---------------------------------------------------\n");
    printf("%-20s | %-15s | %-10s ", "NOME", "TIPO", "QUANTIDADE");
    printf("\n---------------------------------------------------\n");
    printf("%-20s | %-15s | %-10d ", lista->itens[lista->contador-1].name, lista->itens[lista->contador-1].type, lista->itens[lista->contador-1].quantity);
    printf("\n---------------------------------------------------\n\n");
    printf("\n Pressione Enter para continuar...");
    getchar();
}

void listarItens(ListaEstatica *lista){
    if (lista->contador == 0){
        printf("\nMochila vazia: você ainda não coletou nenhum item.\n\n");
        printf("Pressione Enter para continuar...");
        getchar();
        return;
    } else{
        printf("          --- ITENS NA MOCHILA (%d/10) ---          \n", lista->contador);
        printf("---------------------------------------------------\n");
        printf("%-20s | %-15s | %-10s \n", "NOME", "TIPO", "QUANTIDADE");
        printf("---------------------------------------------------\n");

        for (int i = 0; i < lista->contador; i++){
            printf("%-20s | %-15s | %-10d \n", 
                lista->itens[i].name, 
                lista->itens[i].type, 
                lista->itens[i].quantity);
        }
        printf("---------------------------------------------------\n");
    }
    
    printf("\n Pressione Enter para continuar...");
    getchar();
}

void removerItem(ListaEstatica *lista){
    int i, pos = -1;
    char item[MAX_STR_NOME];

    if (lista->contador == 0){
        printf("\nMochila vazia: Não há itens pra serem removidos\n\n");
        printf("Pressione Enter para continuar...");
        getchar();
        return;
    } else{
        printf("Digite o item voce desejar remover: ");
        fgets(item, MAX_STR_NOME, stdin);
        item[strcspn(item, "\n")] = 0;

        for (i = 0; i < lista->contador; i++){
            if (strcmp(lista->itens[i].name, item) == 0) {
                pos = i;
                break;
            }   
        }
        if (pos == -1){
            printf("Erro: Texto \"%s\" não encontrado na lista.\n", item);
            return;
        }

        for (i = pos; i < lista->contador - 1; i++){
            lista->itens[i] = lista->itens[i + 1];
        }
        lista->contador--;
        printf("\nItem \"%s\" removido da mochila.\n\n", item);
    }
    printf("\n Pressione Enter para continuar...");
    getchar();
}

void buscandoItem(ListaEstatica *lista){
    int i, pos = -1;
    char item[MAX_STR_NOME];

    if (lista->contador == 0){
        printf("\nMochila vazia: Impossível buscar por quaisquer itens!\n\n");
        printf("Pressione Enter para continuar...");
        getchar();
        return;
    } else{
        printf("Digite o item que deseja buscar: ");
        fgets(item, MAX_STR_NOME, stdin);
        item[strcspn(item, "\n")] = 0;

        for (i = 0; i < lista->contador; i++){
            if(strcmp(lista->itens[i].name, item) == 0){
                pos = i;
                break;
            } 
        }
        if (pos == -1){
            printf("          ---          MOCHILA         ---          \n");
            printf("---------------------------------------------------\n");
            printf("%-20s | %-15s | %-10s \n", "NOME", "TIPO", "QUANTIDADE");
            printf("---------------------------------------------------\n");
            printf("\nErro: Item \"%s\" não encontrado na mochila.\n\n", item);
            printf("---------------------------------------------------\n");
            return;
        } else{
            printf("\n          ---          MOCHILA         ---          \n");
            printf("---------------------------------------------------\n");
            printf("%-20s | %-15s | %-10s \n", "NOME", "TIPO", "QUANTIDADE");
            printf("---------------------------------------------------\n");
            printf("%-20s | %-15s | %-10d \n", 
            lista->itens[i].name, 
            lista->itens[i].type, 
            lista->itens[i].quantity);
            printf("---------------------------------------------------\n");
        }

        printf("\n Pressione Enter para continuar...");
        getchar();
    }
    
}

int main() {
    int opcao;
    ListaEstatica lista;
    inicializarLista(&lista);

    do{
        printf("==========================================================\n");
        printf("        MOCHILA DE SOBREVIVÊNCIA - CÓDIGO DA ILHA         \n");
        printf("==========================================================\n");
        printf("Itens da mochila: %d/10\n\n", lista.contador);
        printf("1. Adicionar Item (Loot)\n");
        printf("2. Remover Item\n");
        printf("3. Listar itens na mochila\n");
        printf("4. Buscar item\n");
        printf("0. Sair\n");
        printf("----------------------------------------------------------\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        getchar();

        switch (opcao){
        case 1:
            adicionarItem(&lista);
            break;
        case 2:
            removerItem(&lista);
            break;
        case 3:
            listarItens(&lista);
            break;
        case 4:
            buscandoItem(&lista);
            break;
        case 0:
            printf("Saindo do programa...\n");
            break;
        default:
            printf("Opção invalida\n");
        }

    } while (opcao != 0 );
    
    return 0;
}

