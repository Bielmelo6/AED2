#include "BST.h"
#include <stdio.h>
#include <stdlib.h>

//Inserir valores na árvore.
Tree insert(Tree raiz, int ins){
    //Inserir na árvore vazia.
    if(raiz == NULL){
        Tree new =  (Tree) malloc (sizeof(No));
        new->valor = ins;
        new->left = NULL;
        new->right = NULL;
        //Descobrir número de elementos na árvore;
        new->size++;
        return new;
    }
    else{
    //Inserir a esquerda;
    if(ins < raiz->valor){
        raiz->left = insert(raiz->left, ins);
        //Descobrir número de elementos na árvore;
        raiz->size++;
    }
    //Inserir a direita;
    else{
        raiz->right = insert(raiz->right, ins);
        //Descobrir número de elementos na árvore;
        raiz->size++;
    }
    }
    return raiz;
}

//Descobrir maior valor da árvore.
Tree maior_valor(Tree tree){
    Tree higher = tree;
    while(higher->right != NULL){
        higher = higher->right;
    }
    return higher;
}

//Remover valor da árvore.
Tree remover(Tree tree, int del){
    //caso 1: Árvore vazia
    if(tree == NULL){
        printf("A árvore não possui esse valor!\n");
        return NULL;
    }
    //Valor igual a raíz:
    if(tree->valor == del){
        //caso 2: Sem filhos:
        if(tree->left == NULL && tree->right == NULL){
            free(tree);
            printf("REMOVIDO!\n");
            return NULL;
        }
        //caso 3: Sem o filho da direita:
        if(tree->left != NULL && tree->right == NULL){
            Tree temp = tree->left;
            free(tree);
            printf("REMOVIDO!\n");
            return temp;
        }
        //caso 4: Sem o filho da esquerda:
        if(tree->left == NULL && tree->right != NULL){
            Tree temp = tree->right;
            free(tree);
            printf("REMOVIDO!\n");
            return temp;
        }
        //caso 5: Com os dois filhos:
        if(tree->left != NULL && tree->right != NULL){
            Tree higher = maior_valor(tree->left);
            tree->valor = higher->valor;
            tree->left = remover(tree->left, higher->valor);
            printf("REMOVIDO!\n");
            return tree;
        }
    }
    if(del < tree->valor)
        tree->left = remover(tree->left, del);

    else
        tree->right = remover(tree->right, del);
    return tree;
}

void boot(Tree* tree) {
    tree = NULL;
}

//Printar ordenado no formato Pre order.
void preorder(Tree tree){
    if(tree != NULL){
        printf("[%d] ", tree->valor);
        preorder(tree->left);
        preorder(tree->right);
    }
}

//Printar ordenado no formato In order.
void inorder(Tree tree){
    if(tree != NULL){
        inorder(tree->left);
        printf("[%d] ", tree->valor);
        inorder(tree->right);
    }
}

//Printar ordenado no formato Pos order.
void posorder(Tree tree){
    if(tree != NULL){
        posorder(tree->left);
        posorder(tree->right);
        printf("[%d] ", tree->valor);
    }
}

//Descobrir o somatório da árvore;
int soma(Tree tree){
    if(tree == NULL)
        return 0;
    else
        return tree->valor + soma(tree->left) + soma(tree->right);
}

/*void ordenar_inorder(Tree tree, int value){
    if(tree != NULL && value != 0){
        ordenar_inorder(tree->left, value-1);
        printf("%d \n", tree->valor);
        ordenar_inorder(tree->right, value-1);
        }
}*/

int mediana(Tree tree){
    int aux;
    if(tree == NULL)
        return 0;
    else{
        printf("Tamanho: %d \n", tree->size);
         //arvore impar
        Tree media = tree;
        if(tree->size%2 == 1){
            aux = (tree->size + 1)/2;
            //ordenar_inorder(media,aux);
            printf("Ímpar: %d\n", media->valor);
        } //arvore par
        else{
            aux = (tree->size)/2;
            //ordenar_inorder(media,aux);
            printf("Par: %d\n ", media->valor);
        }
            
    }
    return aux; 
}
    
int main(){
    
    Tree teste;
    boot(teste);
    Tree higher;
    boot(higher);
    
    while(1){
        printf("Digite o número da ação que você quer executar: ");
        int opcao;
        scanf("%d", &opcao);
        int usuario;
        int removivel;
        switch(opcao)
        {
        case 1:
        printf("Digite o valor que você quer inserir: ");
            scanf("%d", &usuario);
            printf("%d", usuario);
            teste = insert(teste, usuario);
            break;
        case 2:
            printf("PRE ORDER:\n");
            preorder(teste);
            break;
        case 3:
            printf("IN ORDER:\n");
            inorder(teste);
            break;
        case 4:
            printf("POS ORDER:\n");
            posorder(teste);
            break;
        case 5:
            printf("SOMATÓRIO:\n");
            printf("Valor do Somatório: %d\n", soma(teste));
            break;
        case 6:
            printf("Posição da mediana: %d\n", mediana(teste));
            break;
        case 7:
            higher = maior_valor(teste);
            printf("Maior valor: %d\n", higher->valor);
            break;
        case 8:
            printf("Qual valor você deseja remover?");
            scanf("%d", &removivel);
            teste = remover(teste, removivel);
            break;
        case 20:
            exit(0);
        }
    }
    return 0;
}
