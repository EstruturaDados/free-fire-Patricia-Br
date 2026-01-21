#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h> //sleep()

#define MAX_STR_NOME 30
#define MAX_STR_TIPO 20
#define MAX_ITENS 20

typedef struct {
  char name[MAX_STR_NOME];
  char type[MAX_STR_TIPO];
  int quantity;
  int priority;
} DadosItem;

typedef struct{
  DadosItem itens[MAX_ITENS];
  int contador;
}listaSequencial;

// funçao de inicialização da lista
void inicializarLista(listaSequencial *lista){
  lista->contador = 0;
}

// função que adiciona componentes a lista
void adicionarComponente(listaSequencial *lista){
  char nome[MAX_STR_NOME];
  char tipo[MAX_STR_TIPO];
  int quantidade;
  int prioridade;

  if (lista->contador == MAX_ITENS){
    printf("\nErro: Mochila cheia! Não é possível adicionar mais componentes\n\n");
    printf("\n Pressione Enter para continuar...");
    getchar();
  }

  printf("\nNome: ");
  fgets(nome, MAX_STR_NOME, stdin);
  nome[strcspn(nome, "\n")] = 0;

  printf("Tipo (Estrutural, Eletronico, Energia): ");
  fgets(tipo, MAX_STR_NOME, stdin);
  tipo[strcspn(tipo, "\n")] = 0;

  printf("Quantidade: ");
  scanf("%d", &lista->itens[lista->contador].quantity);
  getchar();

  printf("Prioridade de montagem (1-5): ");
  scanf("%d", &lista->itens[lista->contador].priority);
  getchar();

  strcpy(lista->itens[lista->contador].name, nome);
  strcpy(lista->itens[lista->contador].type, tipo);
  
  lista->contador++;
  
  printf("\nComponente \"%s\" adicionado a mochila. \n\n", nome);
  printf("                   --- INVENTARIO ATUAL (%d/10) ---                  \n", lista->contador);
  printf("---------------------------------------------------------------------\n");
  printf("%-20s | %-15s | %-15s | %-15s\n", "NOME", "TIPO", "QUANTIDADE", "PRIORIDADE");
  printf("---------------------------------------------------------------------\n");
  printf("%-20s | %-15s | %-15d | %-15d", lista->itens[lista->contador-1].name, lista->itens[lista->contador-1].type, lista->itens[lista->contador-1].quantity, lista->itens[lista->contador-1].priority);
  printf("\n---------------------------------------------------------------------\n\n");
  printf("\n Pressione Enter para continuar...");
  getchar();
}

// função que apaga componentes 
void descartarComponente(listaSequencial *lista){
  int i, pos = -1;
  char item[MAX_STR_NOME];

  if (lista->contador == 0){
    printf("\nMochila vazia: Não há componentes pra serem removidos\n\n");
    printf("Pressione Enter para continuar...");
    getchar();
    return;
  }

  printf("Digite o componente que voce deseja remover: ");
  fgets(item, MAX_STR_NOME, stdin);
  item[strcspn(item, "\n")] = 0;

  for (i = 0; i < lista->contador; i++){
    if (strcmp(lista->itens[i].name, item) == 0) {
      pos = i;
      break;
    }   
  }
  if (pos == -1){
    printf("Erro: Componente \"%s\" não encontrado na lista.\n", item);
    return;
  }

  for (i = pos; i < lista->contador - 1; i++){
    lista->itens[i] = lista->itens[i + 1];
  }
  lista->contador--;
  printf("\nComponentes \"%s\" removido da mochila.\n\n", item);

  printf("\n Pressione Enter para continuar...");
  getchar();
}

// função que lista todos os componentes para visualização
void listarComponentes(listaSequencial *lista){
  if (lista->contador == 0){
    printf("\nMochila vazia: Você ainda não coletou nenhum item\n\n");
    printf("Pressione Enter para continuar...");
    getchar();
    return;
  }

  printf("\n                   --- INVENTARIO ATUAL (%d/10) ---                  \n", lista->contador);
  printf("---------------------------------------------------------------------\n");
  printf("%-20s | %-15s | %-15s | %-15s\n", "NOME", "TIPO", "QUANTIDADE", "PRIORIDADE");
  printf("---------------------------------------------------------------------\n");
  for (int i = 0; i < lista->contador; i++){
    printf("%-20s | %-15s | %-15d | %-15d\n",
      lista->itens[i].name,
      lista->itens[i].type,
      lista->itens[i].quantity,
      lista->itens[i].priority);
  }
  printf("---------------------------------------------------------------------\n");
  printf("\nPressione Enter para continuar...");
  getchar();
}


// função que organiza os nomes dos componentes por ordem alfabetica
void bubbleSortNome(listaSequencial *lista, int *status){
  clock_t inicio;
  inicio = clock();
  int tamanho = lista->contador;
  int contador = 0;

  for (int i = 0; i < tamanho - 1; i++){
    for (int j = 0; j < tamanho - 1; j++){
      
      contador++;
      if (strcmp(lista->itens[j].name, lista->itens[j+1].name) > 0){
        DadosItem temp = lista->itens[j];
        lista->itens[j] = lista->itens[j + 1];
        lista->itens[j + 1] = temp;
      }
    }
  }
  inicio = clock() - inicio;
  double tempo_execucao = ((double)inicio) / CLOCKS_PER_SEC;
  printf("\nSucesso: componentes organizados por nome\n");
  printf("Foi realizado \"%d\" comparações\n", contador);
  printf("Tempo de execução: %f segundos\n", tempo_execucao);
  *status = 1;
  printf("\n Pressione Enter para continuar...");
  getchar();
}
// função que organiza os tipos dos componentes por ordem alfabetica
void insertionSortTipo(listaSequencial *lista){
  clock_t inicio;
  inicio = clock();
  int tamanho = lista->contador;
  int contador = 0;

  for (int i = 1; i < tamanho; i++){
    DadosItem chave = lista->itens[i];
    int j = i - 1;

    while (j >= 0 && strcmp(lista->itens[j].type, chave.type) > 0){
      contador++;
      lista->itens[j+1] = lista->itens[j];
      j--;
    }

    lista->itens[j+1] = chave;
    
  }
  
  inicio = clock() - inicio;
  double tempo_execucao = ((double)inicio) / CLOCKS_PER_SEC;
  printf("\nSucesso: componentes organizados por tipo\n");
  printf("Foi realizado \"%d\" comparações\n", contador);
  printf("Tempo de execução: %f segundos\n", tempo_execucao);
  printf("\n Pressione Enter para continuar...");
  getchar();
}
// função que organiza os componentes por ordem crescente de prioridade
void selectionSortPrioridade(listaSequencial *lista){
  clock_t inicio;
  inicio = clock();
  int tamanho = lista->contador;
  int contador = 0;

  for (int i = 0; i < tamanho - 1; i++){

    int indice_min = i;

    for (int j = i; j < tamanho; j++){
      contador++;
      if (lista->itens[j].priority < lista->itens[indice_min].priority){
        indice_min = j;

      }
    }

    if (indice_min != i) {
      DadosItem temp = lista->itens[i];
      lista->itens[i] = lista->itens[indice_min];
      lista->itens[indice_min] = temp;
    }
  }

  inicio = clock() - inicio;
  double tempo_execucao = ((double)inicio) / CLOCKS_PER_SEC;
  printf("\nSucesso: componentes organizados por prioridade\n");
  printf("Foi realizado \"%d\" comparações\n", contador);
  printf("Tempo de execução: %f segundos\n", tempo_execucao);
  printf("\n Pressione Enter para continuar...");
  getchar();
}
//função que guia o usuario para a escolha da forma de organização desejada
void organizarComponentes(listaSequencial *lista, int *status){
  int opcao;
  
  printf("\n------ ESTRATEGIA DE ORGANIZAÇÃO ------\n");
  printf("Como deseja ordenar os componentes?\n");
  printf("1. Por Nome (Ordem Alfabetica)\n");
  printf("2. Por Tipo\n");
  printf("3. Por Prioridade de Montagem\n");
  printf("0. Cancelar\n");
  printf("Escolha o criterio: ");
  scanf("%d", &opcao);
  getchar(); 

  switch (opcao){
  case 1:
    bubbleSortNome(lista, status);
    break;
  case 2:
    insertionSortTipo(lista);
    *status = 0;
    break;
  case 3:
    selectionSortPrioridade(lista);
    *status = 0;
    break;
  case 0:
    printf("Cancelando organização\n");
    break;
  
  default:
    break;
  }
}
void buscaBinaria(listaSequencial *lista, int *status){
  if (lista->contador == 0){
    printf("\nMochila vazia: Impossível buscar por quaisquer itens!\n\n");
    printf("Pressione Enter para continuar...");
    getchar();
    return;
  }

  if (*status == 0){
    printf("\nALERTA: A busca binaria requer que a mochila esteja ordenada por NOME.\n");
    printf("Use a opção 4 para organizar a mochila primeiro caso esteja organizada por NOME\n");
    printf("\nPressione Enter para continuar...");
    getchar();  
    return;
  }

  int contadorDeComparacao = 0;
  char item[MAX_STR_NOME];
  int inicio = 0;
  int fim = lista->contador - 1;
  int meio, pos = -1;
  clock_t inicio_relogio;
  inicio_relogio = clock();
  
  printf("Digite o componente que deseja buscar: ");
  fgets(item, MAX_STR_NOME, stdin);
  item[strcspn(item, "\n")] = 0;

  while (inicio <= fim){
    contadorDeComparacao++;
    meio = inicio + (fim - inicio) / 2;
    int comparacao = strcmp(lista->itens[meio].name, item);

    if (comparacao == 0){
      pos = meio;
      break;
    } else if(comparacao < 0){
      inicio = meio + 1;
    }else{
      fim = meio - 1;
    }
  }
  
  if (pos == -1){
    printf("\n                    --- BUSCA DE COMPONENTES ---                   \n", lista->contador);
    printf("---------------------------------------------------------------------\n");
    printf("%-20s | %-15s | %-15s | %-15s\n", "NOME", "TIPO", "QUANTIDADE", "PRIORIDADE");
    printf("---------------------------------------------------------------------\n");
    printf("\nErro: Item \"%s\" não encontrado na mochila.\n\n", item);
    printf("---------------------------------------------------------------------\n");
  } else{
    printf("\n                    --- BUSCA DE COMPONENTES ---                   \n", lista->contador);
    printf("---------------------------------------------------------------------\n");
    printf("%-20s | %-15s | %-15s | %-15s\n", "NOME", "TIPO", "QUANTIDADE", "PRIORIDADE");
    printf("---------------------------------------------------------------------\n");
    printf("%-20s | %-15s | %-15d | %-15d\n",
      lista->itens[pos].name,
      lista->itens[pos].type,
      lista->itens[pos].quantity,
      lista->itens[pos].priority);
    printf("---------------------------------------------------------------------\n");
    inicio_relogio = clock() - inicio_relogio;
    double tempo_execucao = ((double)inicio_relogio) / CLOCKS_PER_SEC;
    printf("Busca binária realizou %d buscas!\n", contadorDeComparacao);
    printf("Tempo de execução: %f segundos\n", tempo_execucao);

  }
  
  printf("\nPressione Enter para continuar...");
  getchar();

}

// função principal
int main(){
  listaSequencial lista;
  inicializarLista(&lista);
  int opcao;
  int status = 0;
  
  do{
    printf("===============================================================\n");
    printf("         PLANO DE FUGA - CODIGO DA ILHA (NIVEL MESTRE)         \n");
    printf("===============================================================\n");
    printf("Itens na mochila: %d/20\n", lista.contador); 
    if (status == 0){
      printf("Status da ordenação por Nome: NÃO ORDENADO\n\n"); 
    } else{
      printf("Status da ordenação por Nome: ORDENADO\n\n"); 
    }
    
    printf("1. Adicionar Componente\n");
    printf("2. Descartar Componente\n");
    printf("3. Listar Componentes (Inventario)\n");
    printf("4. Organizar mochila (Ordenar Componentes)\n");
    printf("5. Busca Binaria por Componente-Chave (por nome)\n");
    printf("0. ATIVAR TORRE DE FUGA (Sair)\n");
    printf("----------------------------------------------------------\n");
    printf("Escolha uma opção: ");
    scanf("%d", &opcao);
    getchar();  
  
    switch (opcao){
    case 1:
      adicionarComponente(&lista);
      status = 0;
      break;
  
    case 2:
      descartarComponente(&lista);
      break;
    case 3:
      listarComponentes(&lista);
      break;
    case 4:
      organizarComponentes(&lista, &status);
      break;
    case 5:
      buscaBinaria(&lista, &status);
      break;

    case 0:
      if (lista.contador == 0){
        printf("Buscando itens...\n");

        fflush(stdout);
        Sleep(1000);
        printf(".\n");

        fflush(stdout);
        Sleep(1000);
        printf(".\n");
        
        fflush(stdout);
        Sleep(1000);
        printf(".\n");

        fflush(stdout);
        Sleep(500);
        printf("Nenhum item encontrado.\n");
        fflush(stdout);
        Sleep(800);
        printf("TORRE DE FUGA NÃO FOI ATIVADA, VOCE PERDEU\n");
        break;
      }
      
      printf("Buscando itens...\n");

      fflush(stdout);
      Sleep(1000);
      printf("Componentes encontrados...\n");

      fflush(stdout);
      Sleep(1000);
      printf("Contruindo...\n");
      
      fflush(stdout);
      Sleep(1000);
      printf("Finalizando ajustes...\n");

      fflush(stdout);
      Sleep(1000);
      printf("\nATIVANDO TORRE DE FUGA...\n");

      fflush(stdout);
      Sleep(1500);

      printf("\nSUCESSO: VOCE CONSEGUIU ATIVAR A TORRE E SAIU VITORIOSO\n");
      fflush(stdout);
      Sleep(1000);
      printf("\nsaindo do programa...\n");
      break;
    
    default:
      printf("Opção invalida\n");
      break;
    }
  } while (opcao != 0);
  
  return 0;
}
