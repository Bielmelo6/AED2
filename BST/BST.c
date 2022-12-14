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

//Descobrir altura da árvore
int height(Tree tree) {
	if(tree == NULL) {
		return 0;
	}
	return 1 + compare(height(tree->right), height(tree->left));

//Descobrir maior valor da árvore.
Tree maior_valor(Tree tree){
    Tree higher = tree;
    while(higher->right != NULL){
        higher = higher->right;
    }
    return higher;
}

//Remoção de itens da árvore BST.
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
            return NULL;
        }
        //caso 3: Sem o filho da direita:
        if(tree->left != NULL && tree->right == NULL){
            Tree temp = tree->left;
            free(tree);
            return temp;
        }
        //caso 4: Sem o filho da esquerda:
        if(tree->left == NULL && tree->right != NULL){
            Tree temp = tree->right;
            free(tree);
            return temp;
        }
        //caso 5: Com os dois filhos:
        if(tree->left != NULL && tree->right != NULL){
            Tree higher = maior_valor(tree->left);
            tree->valor = higher->valor;
            tree->left = remover(tree->left, higher->valor);
            return tree;
        }
    }
    if(del < tree->valor)
        tree->left = remover(tree->left, del);

    else
        tree->right = remover(tree->right, del);
    return tree;
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
    
int main(){
    
    Tree teste = NULL;
    Tree higher = NULL;
    
    while(1){
        int opcao;
        scanf("%d", &opcao);
        int usuario;
        int removivel;
        switch(opcao)
        {
        	case 1:
            		scanf("%d", &usuario);
            		printf("%d", usuario);
            		teste = insert(teste, usuario);
            		break;
        	case 2:
        		scanf("%d", &removivel);
            		teste = remover(teste, removivel);
            		break;
        	case 3:
        		printf("ALTURA: %d\n", height(teste));
        		break;
        	case 4:
            		printf("\nPRE ORDER:\n");
            		preorder(teste);
            		break;
        	case 99:
            		exit(0);
        }
    }
    return 0;
}
