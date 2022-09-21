#include <stdio.h>
#include <stdlib.h>
#include "RB.h"

Tree leaf;

void boot(Tree *tree) {
	*tree = NULL;
	leaf = (Tree) malloc(sizeof(struct No));
	leaf->color = DBLACK;
	leaf->valor = 0;
}

void adjust(Tree *tree, Tree value){
	while(color(value->dad) == RED && color(value) == RED) {
			//caso 1: Cor do tio é vermelha, desce o preto do avô
			if(color(uncle(value)) == RED) {
				uncle(value)->color = BLACK;
				value->dad->color = BLACK;
				value->dad->dad->color = RED;				
				value = value->dad->dad;
				continue;
			} 
			//caso 2: rotação simples direita
			if(is_left_son(value) && is_left_son(value->dad)) {
					rotacao_simples_direita(tree, value->dad->dad);
					value->dad->color = BLACK;
					value->dad->right->color = RED;
					continue;
			}
			//caso 2: rotação simples esquerda
			if(!is_left_son(value) && !is_left_son(value->dad)) {
					rotacao_simples_esquerda(tree, value->dad->dad);
					value->dad->color = BLACK;
					value->dad->left->color = RED;
					continue;
			}
			//caso 3: rotação dupla direita
			if(!is_left_son(value) && is_left_son(value->dad)) {
				
					rotacao_simples_esquerda(tree, value->dad);
					rotacao_simples_direita(tree, value->dad);
					value->color = BLACK;
					value->right->color = RED;
					value->left->color = RED;
					continue;
					
			}
			//caso 3: rotação dupla esquerda
			if(is_left_son(value) && !is_left_son(value->dad)) {
				
					rotacao_simples_direita(tree, value->dad);
					rotacao_simples_esquerda(tree, value->dad);
					value->color = BLACK;
					value->right->color = RED;
					value->left->color = RED;
					continue;
					
			}

	}
	(*tree)->color = BLACK;
}

void insert(int valor, Tree *tree) {

	Tree dad, new, position;
	position = *tree;
	dad = NULL;
	while(position != NULL) {
			dad = position;
			if(valor > position->valor) 
					position = position->right;
			else 
					position = position->left;
	}

//Após achar a posição, inicializa o novo elemento
	new = (Tree) malloc(sizeof(struct No));
	new->valor = valor;
	new->left = NULL;
	new->right = NULL;
	new->dad = dad;
	new->color = RED;

//Atualiza a raiz da árvore
	if(is_root(new))	
			*tree = new;
	else {
		if(valor > dad->valor)
			dad->right = new;
		else
			dad->left = new;
	}

//Após inserir, verifica e ajusta a árvore resultante
	adjust(tree, new);
}

void rotacao_simples_direita(Tree *tree, Tree pivot){
	Tree u, t1;
	u = pivot->left;
        t1 = u->right;
	int left_pivot = is_left_son(pivot);
			
//Atualização dos ponteiros
	pivot->left = t1;
        if(t1 != NULL)
		t1->dad = pivot;

	u->right = pivot;    
	u->dad = pivot->dad;
	pivot->dad = u;
    	pivot->color = RED;
	u->color = BLACK;
			
	if(is_root(u))
		*tree = u;
	else {
	if(left_pivot)
		u->dad->left = u;
	else
		u->dad->right = u;
	}
}

void rotacao_simples_esquerda(Tree *tree, Tree pivot) {

	Tree u, t1, t2, t3;
	u = pivot->right;
        t1 = u->left;
	int left_pivot = is_left_son(pivot);
			
//Atualização dos ponteiros
	pivot->right = t1;
        if(t1 != NULL)
		t1->dad = pivot;

	u->left = pivot;
        u->dad = pivot->dad;
	pivot->dad = u;
    	pivot->color = RED;
	u->color = BLACK;
	if(is_root(u))
		*tree = u;
	else {
		if(left_pivot)
			u->dad->left = u;
		else
			u->dad->right = u;
			}
}

//Retorna a cor do nó
enum color color(Tree value) {
	enum color cor;
	if(value == NULL || value->color == BLACK)
		cor = BLACK;
	else
		cor = RED;
	return cor;
}

//Verifica se um nó é a raiz
int is_root(Tree tree){
	return (tree->dad == NULL);
}

//Verifica se é filho esquerdo
int is_left_son(Tree relative) {
	return (relative->dad != NULL && relative == relative->dad->left);
}

Tree brother(Tree relative) {
	if(is_left_son(relative))
		return relative->dad->right;
	else
		return relative->dad->left;
}

Tree uncle(Tree relative) {
	return brother(relative->dad);
}

int compare(int valor1, int valor2) {
	if(valor1 > valor2)
		return valor1;
	else
		return valor2;
}
//Descobre a altura
int height(Tree tree) {
	if(tree == NULL) {
		return 0;
	}
	return 1 + compare(height(tree->right), height(tree->left));
}

int maior_valor(Tree tree) {
	if(tree == NULL)
		return -1;
	if(tree->right == NULL)
		return tree->valor;
	else
		return maior_valor(tree->right);
}

int menor_valor(Tree tree) {
	if(tree == NULL)
		return -1;
	if(tree->left == NULL)
		return tree->valor;
	else
		return maior_valor(tree->left);
}

void color_print(Tree tree){

	switch(tree->color)
	{
		case BLACK:
			printf("\x1b[30m[%d]\x1b[0m", tree->valor);
			break;
		case RED:
			printf("\x1b[31m[%d]\x1b[0m", tree->valor);
			break;
		case DBLACK:
			printf("\x1b[32m[%d]\x1b[0m", tree->valor);
			break;
	}
}
//Printar ordenado no formato Pre order.
void preorder(Tree tree){
    if(tree != NULL){
        color_print(tree);
        preorder(tree->left);
        preorder(tree->right);
    }
}

//Printar ordenado no formato In order.
void inorder(Tree tree){
    if(tree != NULL){
        inorder(tree->left);
        color_print(tree);
        inorder(tree->right);
    }
}

//Printar ordenado no formato Pos order.
void posorder(Tree tree){
    if(tree != NULL){
        posorder(tree->left);
        posorder(tree->right);
        color_print(tree);
    }
}

void readjust(Tree *tree, Tree value){
//caso 1	
	if(is_root(value))
		value->color = BLACK;
		return;

//caso 2
	if(color(value->dad) == BLACK && color(brother(value)) == RED && color(brother(value)->right) == BLACK && color(brother(value)->left) == BLACK){
		if(is_left_son(value))
			rotacao_simples_esquerda(tree, value->dad);
		else
			rotacao_simples_direita(tree, value->dad);	
		value->dad->dad->color = BLACK;
		value->dad->color = RED;
                readjust(tree, value);
                return;
	}
//caso 3

	if(color(value->dad) == BLACK && color(brother(value)) == BLACK && color(brother(value)->right) == BLACK && color(brother(value)->left) == BLACK){
		Tree dad = value->dad; 
		dad->color = DBLACK;
		brother(value)->color = RED;
		retira_dblack(tree, value);
		readjust(tree, dad);
		return;
	}	
//caso 4
	if(color(value->dad) == RED && color(brother(value)) == BLACK && color(brother(value)->right) == BLACK && color(brother(value)->left) == BLACK){	
		value->dad->color = BLACK;
		brother(value)->color = RED;
		retira_dblack(tree, value);
		return;
	}
//caso 5
//caso 5a
	if(is_left_son(value) && color(brother(value)) == BLACK && color(brother(value)->right) == BLACK && color(brother(value)->left) == RED){
			 
		Tree dad, vbrother, nephewL, nephewR;
			 
		dad = value->dad;
		vbrother = brother(value);
		nephewR = vbrother->right;
		nephewL = vbrother->left;
			 
	 	dad->right = nephewL;
		nephewL->dad = dad;
		vbrother->left = nephewL->right;
		vbrother->dad = nephewL;
		nephewL->right = vbrother;
		if(vbrother->left != NULL)
			vbrother->left->dad = vbrother;
		vbrother->color = RED;
		nephewL->color = BLACK; 
		readjust(tree, value);
		return;
			
	}	

	//caso 5b
	if(!is_left_son(value) && color(brother(value)) == BLACK && color(brother(value)->right) == RED && color(brother(value)->left) == BLACK) {	
		Tree dad, vbrother, nephewR, nephewL;
			 
		dad = value->dad;
		vbrother = brother(value);
		nephewR = vbrother->right;
		nephewL = vbrother->left; 
		dad->left = nephewR;
		nephewR->dad = dad;
		vbrother->right = nephewR->left;
		vbrother->dad = nephewR;
		nephewR->left = vbrother;
		if(vbrother->right != NULL)
			vbrother->right->dad = vbrother; 
		vbrother->color = RED;
		nephewR->color = BLACK;	
		readjust(tree, value);
		return;
	
}

	//caso 6a
	if(is_left_son(value) && color(brother(value)) == BLACK && color(brother(value)->right) == RED){	
		Tree dad, vbrother, nephewR, nephewL;
			 
		dad = value->dad;
		vbrother = brother(value);
		nephewR = vbrother->right;
		nephewL = vbrother->left;
			 
		dad->right = nephewL;
		if(nephewL != NULL)
			nephewL->dad = dad;
			
		if(!is_root(dad)){
			if(is_left_son(dad))
				dad->dad->left = vbrother;
			else
				dad->dad->right = vbrother;
			}
		
		vbrother->dad = dad->dad;
		dad->dad = vbrother;
		vbrother->left = dad;
			 	 
	     	if(color(dad) == RED)
			vbrother->color = RED;
		nephewR->color = BLACK;
		dad->color = BLACK;
		retira_dblack(tree, value);
		return;
			 
		
	}
//caso 6b
	if(!is_left_son(value) && color(brother(value)) == BLACK && color(brother(value)->left) == RED) {	
		Tree dad, vbrother, nephewR, nephewL;
			 
		dad = value->dad;
		vbrother = brother(value);
		nephewR = vbrother->right;
		nephewL = vbrother->left;
		dad->left = nephewR;
		if(nephewR != NULL)
			nephewR->dad = dad;
			
			if(!is_root(dad)){
				if(is_left_son(dad))
					dad->dad->left = vbrother;
				else
					dad->dad->right = vbrother;
			}
			
		vbrother->dad = dad->dad;
		dad->dad = vbrother;
		vbrother->right = dad;
			 
		if(color(dad) == RED)
			vbrother->color = RED;
		nephewL->color = BLACK;
		dad->color = BLACK;
		retira_dblack(tree, value);
		return;
		
		
	}
}

void retira_dblack(Tree *tree, Tree value) {
			if(value == leaf){
				if(is_left_son(value))
					value->dad->left = NULL;
				else
					value->dad->right = NULL;
			}
			else
				value->color = BLACK;
}

void remover(int valor, Tree *tree){
	Tree position;
	position = *tree;

	while(position != NULL) {
		if(valor == position->valor){
//não possui filhos
			if(position->left == NULL && position->right == NULL) {
//Remover raiz sem filhos					
				if(is_root(position)) {
					*tree = NULL;
					break;
				}
//Remover elemento que não possui filhos e não é raiz
//Se for vermelho, apenas remove atualizando o ponteiro
				if(position->color == RED) {
					if(is_left_son(position))
						position->dad->left = NULL;
					else
						position->dad->right = NULL;
						break;
				}else{
//Se for preto, substitui pelo duplo preto e depois ajusta a árvore
					leaf->dad = position->dad;
					if(is_left_son(position))
						position->dad->left = leaf;
					else
						position->dad->right = leaf;
					readjust(tree, leaf);
					break;
					}
				}
//possui apenas um filho (direito)
				if(position->left == NULL) {
					position->right->color = BLACK;
					if(is_root(position)) {
						*tree = position->right;
				        }else{
					if(is_left_son(position))
						position->dad->left = position->right;
					else 
						position->dad->right = position->right;
					}
					break;
				}
//possui apenas um filho (esquerdo)
				if(position->right == NULL) {
					position->left->color = BLACK;
					if(is_root(position)) {
						*tree = position->left;
					}else{
						if(is_left_son(position)) {
							position->dad->left = position->left;
						}else{
							position->dad->right = position->left;
						}
					}
					break;
				}
//possui dois filhos 
				position->valor = maior_valor(position->left);
				remover(position->valor, &(position->left));
		}	
		if(valor > position->valor) 
				position = position->right;
		else 
				position = position->left;
	}
}

int main(){

    Tree teste;
    boot(&teste);
    
    while(1){
	int opcao;
        scanf("%d", &opcao);
        int usuario;
        int removivel;
        switch(opcao)
        {
        	case 1:
            		scanf("%d", &usuario);
            		insert(usuario, &teste);
            		break;
        	case 2:
            		scanf("%d", &removivel);
            		remover(removivel, &teste);
            		break;
        	case 10:
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

