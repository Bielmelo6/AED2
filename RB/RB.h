#ifndef RB_H
#define RB_H

enum color{RED, BLACK, DBLACK};

typedef struct No{
	int valor;
	enum color color;
	struct No *left, *right, *dad;
} No;

typedef No* Tree;

void boot(Tree *tree);
void insert(int valor, Tree *tree);
void remover(int valor,Tree *tree);
int height(Tree tree);
int compare(int valor1, int valor2);
int maior_valor(Tree tree);
int menor_valor(Tree tree);
void color_print(Tree tree);
void preorder(Tree tree);
void posorder(Tree tree);
void inorder(Tree tree);
enum color color(Tree value);
void adjust(Tree *tree, Tree value);
void readjust(Tree *tree, Tree value);
void rotacao_simples_direita(Tree *tree, Tree pivot);
void rotacao_simples_esquerda(Tree *tree, Tree pivot);
int is_root(Tree tree);
int is_left_son(Tree relative);
Tree brother(Tree relative);
Tree uncle(Tree relative);
void retira_dblack(Tree *tree, Tree value);


#endif
