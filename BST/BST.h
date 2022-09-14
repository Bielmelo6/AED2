#ifndef BST_H
#define BST_H

typedef struct No{
    int valor;
    int size;
    struct No *left, *right;
} No;

typedef No* Tree;

Tree insert(Tree raiz, int ins);
Tree remover(Tree raiz, int del);
Tree maior_valor(Tree tree);
int height(Tree tree);
void preorder(Tree tree);
void inorder(Tree tree);
void posorder(Tree tree);
int mediana(Tree tree);
int soma(Tree tree);

#endif
