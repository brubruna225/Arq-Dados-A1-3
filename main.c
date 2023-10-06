#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct sRegistro
{
    int tempo;         // tempo de vida da espécie
    char especie[100]; // nome da espécie
    struct sRegistro *left;
    struct sRegistro *right;
} REGISTRO;

REGISTRO *criarArvore()
{
    return NULL;
}

bool arvoreVazia(REGISTRO *arvore)
{
    return arvore == NULL;
}

void mostrarArvore(REGISTRO *arvore)
{
    printf("<");

    if (!arvoreVazia(arvore))
    {
        printf("%d ", arvore->tempo);
        printf("%s ", arvore->especie);
        mostrarArvore(arvore->left);
        mostrarArvore(arvore->right);
    }

    printf(">");
}

void insereArvore(REGISTRO **arvore, int tempo, char especie[])
{
    if (*arvore == NULL)
    {
        *arvore = (REGISTRO *)malloc(sizeof(REGISTRO));
        (*arvore)->left = NULL;
        (*arvore)->right = NULL;
        strcpy((*arvore)->especie, especie);
        (*arvore)->tempo = tempo;
    }
    else
    {
        if (tempo < (*arvore)->tempo)
        {
            insereArvore(&(*arvore)->left, tempo, especie);
        }
        else if (tempo > (*arvore)->tempo)
        {
            insereArvore(&(*arvore)->right, tempo, especie);
        }
    }
}

bool buscaArvore(REGISTRO *arvore, int tempo)
{
    if (arvoreVazia(arvore))
    {
        return false;
    }
    if (arvore->tempo == tempo)
    {
        return true;
    }
    else if (tempo < arvore->tempo)
    {
        return buscaArvore(arvore->left, tempo);
    }
    else
    {
        return buscaArvore(arvore->right, tempo);
    }
}

REGISTRO *encontrarMin(REGISTRO *arvore)
{
    if (arvore == NULL)
    {
        return NULL;
    }
    while (arvore->left != NULL)
    {
        arvore = arvore->left;
    }
    return arvore;
}

 void apagarNo(REGISTRO **arvore, int tempo)
{
    if (*arvore == NULL)
    {
        printf("Elemento não encontrado\n");
        return;
    }

    if (tempo < (*arvore)->tempo)
    {
        apagarNo(&((*arvore)->left), tempo);
    }
    else if (tempo > (*arvore)->tempo)
    {
        apagarNo(&((*arvore)->right), tempo);
    }
    else
    {
        REGISTRO *temporario;

        // Caso 1: Nó sem ou com apenas um filho
        if ((*arvore)->left == NULL)
        {
            temporario = *arvore;
            *arvore = (*arvore)->right;
            free(temporario);
        }
        else if ((*arvore)->right == NULL)
        {
            temporario = *arvore;
            *arvore = (*arvore)->left;
            free(temporario);
        }
        else
        {
            // Caso 2: Nó com dois filhos, encontrar o nó mínimo na subárvore direita
            temporario = encontrarMin((*arvore)->right);

            // Copiar os valores do nó mínimo para o nó atual
            (*arvore)->tempo = temporario->tempo;
            strcpy((*arvore)->especie, temporario->especie);

            // Apagar o nó mínimo da subárvore direita
            apagarNo(&((*arvore)->right), temporario->tempo);
        }
    }
}


    

int main()
{
    REGISTRO *arvore = criarArvore();

    int opcao, tempo;
    char especie[100];

    do
    {
        printf("Escolha uma opção:\n");
        printf("1. Inserir\n2. Buscar\n3. Excluir\n4. Sair\n");
        scanf("%i", &opcao);

        switch (opcao)
        {

        case 1:
            printf("\nDigite o tempo de vida da espécie:\n");
            scanf("%i", &tempo);
            printf("Digite o nome da espécie:\n");
            scanf("%s", especie);
            insereArvore(&arvore, tempo, especie);
            break;

        case 2:
            printf("Digite o tempo de vida da espécie que você procura:\n");
            scanf("%i", &tempo);
            if (buscaArvore(arvore, tempo))
            {
                printf("Tempo encontrado na árvore!\n");
            }
            else
            {
                printf("Tempo não encontrado na árvore!\n");
            }
            break;

        case 3:
            printf("Digite o tempo de vida da espécie que deseja excluir:\n");
            scanf("%i", &tempo);
            apagarNo(&arvore, tempo);
            break;

        case 4:
            break;

        default:
            printf("Opção inválida!\n");
            break;
        }

    } while (opcao != 4);

    return 0;
}