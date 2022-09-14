#ifndef AVL_H
#define AVL_H

typedef struct No {
	int valor;
	int fb;
	struct No *left, *right;
} No;

typedef No * Tree;

Tree insert(Tree tree, int valor, int *cresceu);
int height(Tree tree);
int compare(int a, int b);
int maior_valor(Tree tree);
int menor_valor(Tree tree);
void preorder(Tree tree);
void posorder(Tree tree);
void inorder(Tree tree);
Tree rotation(Tree tree);
Tree remover (Tree tree, int valor, int * diminuiu);
Tree rotacao_simples_direita(Tree tree);
Tree rotacao_simples_esquerda(Tree tree);
Tree rotacao_dupla_direita(Tree tree);
Tree rotacao_dupla_esquerda(Tree tree);

#endif
