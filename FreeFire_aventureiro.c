#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define MAX_STR_NOME 30
#define MAX_STR_TIPO 20
#define MAX_ITENS 10

/////////////////////////////////////////////////////////// Vetor
typedef struct {
  char name[MAX_STR_NOME];
  char type[MAX_STR_TIPO];
  int quantity;
} DadosItem;

typedef struct {
  DadosItem itens[MAX_ITENS];
  int contador;
}ListaSequencial;

void inicializarListaSequencial(ListaSequencial *lista);
void inserirNaListaSequencial(ListaSequencial *lista);
void removerDaListaSequencial(ListaSequencial *lista);
void listarListaSequencial(ListaSequencial *lista);
void buscaSequencialVetor(ListaSequencial *lista);
void ordenarVetor(ListaSequencial *lista);
void buscaBinariaVetor(ListaSequencial *lista);

////////////////////////////////////////////////////////// Encadeada
typedef struct No{
  DadosItem dado;
  struct No *proximo;
} No;

typedef No* listaEncadeada;

void inicializarListaEncadeada(listaEncadeada *lista);
int contadorDeItensListaEncadeada(listaEncadeada *lista);
void inserirNaListaEncadeada(listaEncadeada *lista);
void removerDaListaEncadeada(listaEncadeada *lista);
void listarListaEncadeada(listaEncadeada *lista);
void buscaSequencialEncadeada(listaEncadeada *lista);

///////////////////////////////////////////////////////// Menus
void menuVetor();
void menuEncadeado();

int main(){
  int opcao;

  do{
    printf("==========================================================\n");
    printf("                 MOCHILAS DE SOBREVIVÊNCIA                \n");
    printf("==========================================================\n");
    printf("1. Mochila de sobrevivência (Vetor)\n");
    printf("2. Mochila de sobrevivência (Encadeada)\n");
    printf("0. Sair\n");
    printf("----------------------------------------------------------\n");
    printf("Escolha uma opção: ");
    scanf("%d", &opcao);
    getchar();  
  
    switch (opcao){
    case 1:
      menuVetor();
      break;
  
    case 2:
      menuEncadeado();
      break;

    case 0:
      printf("saindo\n");
      break;
    
    default:
      printf("Opção invalida\n");
      break;
    }
  } while (opcao != 0);
  
  return 0;
}

//funções da lista sequencial (vetor)
void inicializarListaSequencial(ListaSequencial *lista){
  lista->contador = 0;
}
void inserirNaListaSequencial(ListaSequencial *lista){
  char nome[MAX_STR_NOME];
  char tipo[MAX_STR_TIPO];
  int quantidade;

  if(lista->contador == MAX_ITENS){
    printf("\nErro: Mochila cheia! Não é possível coletar mais itens\n\n");
    printf("\n Pressione Enter para continuar...");
    getchar();
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
void removerDaListaSequencial(ListaSequencial *lista){
  int i, pos = -1;
  char item[MAX_STR_NOME];

  if (lista->contador == 0){
    printf("\nMochila vazia: Não há itens pra serem removidos\n\n");
    printf("Pressione Enter para continuar...");
    getchar();
    return;
  }

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

  printf("\n Pressione Enter para continuar...");
  getchar();
}
void listarListaSequencial(ListaSequencial *lista){
  if (lista->contador == 0){
    printf("\nMochila vazia: você ainda não coletou nenhum item.\n\n");
    printf("Pressione Enter para continuar...");
    getchar();
    return;
  }

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
  
  printf("\n Pressione Enter para continuar...");
  getchar();
}
void buscaSequencialVetor(ListaSequencial *lista){
  int pos = -1;
  int comparacao = 0;
  char item[MAX_STR_NOME];

  printf("Digite o item que deseja buscar: ");
  fgets(item, MAX_STR_NOME, stdin);
  item[strcspn(item, "\n")] = 0;

  for (int i = 0; i < lista->contador; i++){
    comparacao++;
    if (strcmp(lista->itens[i].name, item) == 0){
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
    lista->itens[pos].name, 
    lista->itens[pos].type, 
    lista->itens[pos].quantity);
    printf("---------------------------------------------------\n");
    printf("Busca sequencial realizou %d buscas!\n\n", comparacao);
  }
  printf("\n Pressione Enter para continuar...");
  getchar();

}
void ordenarVetor(ListaSequencial *lista){
  int tamanho = lista->contador;

  for (int j = 0; j < tamanho - 1; j++){
    for (int i = 0; i < tamanho - 1; i++){
      if (strcmp(lista->itens[i].name, lista->itens[i + 1].name) > 0){
        DadosItem temp = lista->itens[i];
        lista->itens[i] = lista->itens[i+1];
        lista->itens[i+1] = temp;
      } 
    } 
  }
  printf("\nMochila ordenada com sucesso para busca binária!\n");
}
void buscaBinariaVetor(ListaSequencial *lista){
  int contadorDeComparacao = 0;
  char item[MAX_STR_NOME];
  int inicio = 0;
  int fim = lista->contador - 1;
  int meio, pos = -1;

  printf("Digite o item que deseja buscar: ");
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
    } else{
      fim = meio - 1;
    }
  }

  if (pos == -1){
    printf("          ---          MOCHILA         ---          \n");
    printf("---------------------------------------------------\n");
    printf("%-20s | %-15s | %-10s \n", "NOME", "TIPO", "QUANTIDADE");
    printf("---------------------------------------------------\n");
    printf("\nErro: Item \"%s\" não encontrado na mochila.\n\n", item);
    printf("---------------------------------------------------\n");
  } else{
    printf("\n          ---          MOCHILA         ---          \n");
    printf("---------------------------------------------------\n");
    printf("%-20s | %-15s | %-10s \n", "NOME", "TIPO", "QUANTIDADE");
    printf("---------------------------------------------------\n");
    printf("%-20s | %-15s | %-10d \n", 
    lista->itens[pos].name, 
    lista->itens[pos].type, 
    lista->itens[pos].quantity);
    printf("---------------------------------------------------\n");
    printf("Busca binária realizou %d buscas!\n\n", contadorDeComparacao);
  }
  printf("\n Pressione Enter para continuar...");
  getchar();
  
}

// funçoes da lista encadeada
void inicializarListaEncadeada(listaEncadeada *lista){
  *lista = NULL;
}
int contadorDeItensListaEncadeada(listaEncadeada *lista){
  int total = 0;
  No *atual = *lista;

  while (atual != NULL){
    total++;
    atual = atual->proximo;
  }
  
  return total;
}
void inserirNaListaEncadeada(listaEncadeada *lista){
  No* novoNo = (No*) malloc(sizeof(No));

  if (contadorDeItensListaEncadeada(lista) == MAX_ITENS){
    printf("Erro: Mochila cheia! Não é possível coletar mais itens\n");
    printf("\n Pressione Enter para continuar...");
    getchar();
    return;
  }
  
  if (novoNo == NULL){
    printf("erro: falha na alocação de memoria para o no.\n");
    return;
  }

  printf("\nNome do item: ");
  fgets(novoNo->dado.name, MAX_STR_NOME, stdin);
  novoNo->dado.name[strcspn(novoNo->dado.name, "\n")] = 0;

  printf("Tipo do item (arma, munição, cura, etc.): ");
  fgets(novoNo->dado.type, MAX_STR_NOME, stdin);
  novoNo->dado.type[strcspn(novoNo->dado.type, "\n")] = 0;

  printf("Quantidade: ");
  scanf("%d", &novoNo->dado.quantity);
  getchar();
  
  novoNo->proximo = *lista;
  *lista = novoNo;

  printf("\nItem \"%s\" adicionado a mochila. \n", novoNo->dado.name);
  printf("\n Pressione Enter para continuar...");
  getchar();
}
void removerDaListaEncadeada(listaEncadeada *lista){
  No *atual = *lista;
  No *anterior = NULL;
  char busca[MAX_STR_NOME];
  
  if (*lista == NULL){
    printf("\nMochila vazia: Não há itens pra serem removidos\n\n");
      printf("Pressione Enter para continuar...");
      getchar();
      return;
  }

  printf("Digite o item que deseja remover: ");
  fgets(busca, MAX_STR_NOME, stdin);
  busca[strcspn(busca, "\n")] = 0;

  while (atual != NULL && strcmp(atual->dado.name, busca) != 0){
    anterior = atual;
    atual = atual->proximo;
  }

  if (atual == NULL){
    printf("erro: item \"%s\" não encontrado na mochila\n", busca);
    return;
  }
  
  if(anterior == NULL){
    *lista = atual->proximo;
  }else{
    anterior->proximo = atual->proximo;
  }

  free(atual);
  printf("\nItem \"%s\" removido da mochila\n\n", busca);
  printf("Pressione Enter para continuar...");
  getchar();
}
void listarListaEncadeada(listaEncadeada *lista){
  No *temp = *lista;
  if(temp == NULL){
    printf("\nMochila vazia: você ainda não coletou nenhum item.\n\n");
    printf("Pressione Enter para continuar...");
    getchar();
    return;
  }

  printf("          --- ITENS NA MOCHILA (%d/10) ---          \n", contadorDeItensListaEncadeada(lista));
  printf("---------------------------------------------------\n");
  printf("%-20s | %-15s | %-10s \n", "NOME", "TIPO", "QUANTIDADE");
  printf("---------------------------------------------------\n");
  while (temp != NULL){
    printf("%-20s | %-15s | %-10d \n", 
      temp->dado.name,
      temp->dado.type,
      temp->dado.quantity);
    
    temp = temp->proximo;
  }
  printf("---------------------------------------------------\n");
  printf("\n Pressione Enter para continuar...");
  getchar();
  
}
void buscaSequencialEncadeada(listaEncadeada *lista){
  int contadorComparacao = 0;
  No *atual = *lista;
  char busca[MAX_STR_NOME];

  if (*lista == NULL){
    printf("\nMochila vazia: Impossível buscar por quaisquer itens!\n\n");
    printf("Pressione Enter para continuar...");
    getchar();
    return;
  }

  printf("Digite o item que deseja buscar: ");
  fgets(busca, MAX_STR_NOME, stdin);
  busca[strcspn(busca, "\n")] = 0;

  while (atual != NULL){
    contadorComparacao++;
    if (strcmp(atual->dado.name, busca) != 0){
      break;
    }
    
    atual = atual->proximo;
  }

  if (atual == NULL){
    printf("                   --- MOCHILA ---                 \n");
    printf("---------------------------------------------------\n");
    printf("%-20s | %-15s | %-10s \n", "NOME", "TIPO", "QUANTIDADE");
    printf("---------------------------------------------------\n");
    printf("erro: item \"%s\" não encontrado na mochila\n", busca);
    printf("---------------------------------------------------\n");
  } else{
    printf("                   --- MOCHILA ---                 \n");
    printf("---------------------------------------------------\n");
    printf("%-20s | %-15s | %-10s \n", "NOME", "TIPO", "QUANTIDADE");
    printf("---------------------------------------------------\n");
    printf("%-20s | %-15s | %-10d \n", 
      atual->dado.name,
      atual->dado.type,
      atual->dado.quantity);
    printf("---------------------------------------------------\n");
    printf("Busca sequencial realizou %d buscas.\n\n", contadorComparacao);
  }

  printf("\n Pressione Enter para continuar...");
  getchar();
}

// funções dos menus
void menuVetor(){
  int opcao;
  int busca;
  ListaSequencial lista;
  inicializarListaSequencial(&lista);

  do{
    printf("==========================================================\n");
    printf("             MOCHILA DE SOBREVIVÊNCIA - VETOR             \n");
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
      inserirNaListaSequencial(&lista);
      break;
    case 2:
      removerDaListaSequencial(&lista);
      break;
    case 3:
      listarListaSequencial(&lista);
      break;
    case 4:
      if (lista.contador == 0){
        printf("\nMochila vazia: Impossível buscar por quaisquer itens!\n\n");
        printf("Pressione Enter para continuar...");
        getchar();
        break;
      }
      
      printf("1. Busca Sequencial\n");
      printf("2. Busca Binária\n");
      printf("Como gostaria de realizar sua busca: ");
      scanf("%d", &busca);
      getchar();

      switch (busca){
      case 1:
        buscaSequencialVetor(&lista); 
        break;
      case 2:
        ordenarVetor(&lista);
        buscaBinariaVetor(&lista); 
        break;
      
      default:
        printf("Opção invalida");
        break;
      }
      
      break;
    case 0:
        printf("Saindo do programa...\n");
        break;
    default:
        printf("Opção invalida\n");
    }

  } while (opcao != 0 );
}
void menuEncadeado(){
  listaEncadeada lista;
  inicializarListaEncadeada(&lista);

  int opcao;
  
  do{
    printf("===========================================================\n");
    printf("            MOCHILA DE SOBREVIVÊNCIA - ENCADEADO           \n");
    printf("===========================================================\n");
    printf("Itens da mochila: %d/10\n\n", contadorDeItensListaEncadeada(&lista));
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
      inserirNaListaEncadeada(&lista);
      break;
    case 2:
      removerDaListaEncadeada(&lista);
      break;
    case 3:
      listarListaEncadeada(&lista);
      break;
    case 4:
      buscaSequencialEncadeada(&lista);
      break;
    case 0:
        printf("Saindo do programa...\n");
        break;
    default:
        printf("Opção invalida\n");
    }

  } while (opcao != 0);
}