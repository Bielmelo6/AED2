#include <stdio.h>
#include <stdlib.h>
#include "AVL.h"

Tree insert(Tree tree, int valor, int *cresceu) {
	//Inserir na árvore vazia.
	if(tree == NULL){
		Tree new = (Tree)malloc(sizeof(struct No));
		new->valor = valor;
		new->left = NULL;
		new->right = NULL;
		new->fb = 0;
	  	*cresceu = 1; 
		return new;
	}
	//Inserir a esquerda;
	if(valor > tree->valor) {
		tree->right = insert(tree->right, valor, cresceu);
        	if(*cresceu) {
			switch(tree->fb) {
				case 0:
					tree->fb = 1;
                	    		*cresceu = 1;
					break;
				case -1:
					tree->fb = 0;
					*cresceu = 0;
					break;
				case 1:
					*cresceu = 0;
					return rotation(tree);
				}
			}
	
	} 	
	//Inserir a direita;
	else{
		tree->left = insert(tree->left, valor, cresceu);
		if(*cresceu){
			switch(tree->fb) {
				case 0:
					tree->fb = -1;
                    			*cresceu = 1;
					break;
			    	case -1:
					*cresceu = 0;
					return rotation(tree);
				case 1:
					*cresceu = 0;
                    			tree->fb = 0;
                    break;
			}
		}
	}
	return tree;
	
}

Tree rotation(Tree tree) {
	if(tree->fb > 0) {
		switch(tree->right->fb) {
			case 0:
			case 1:
				return rotacao_simples_esquerda(tree);
			case -1:
				return rotacao_dupla_esquerda(tree);					
			} 
	} else {
		switch(tree->left->fb) {
			case 0:
			case -1:
				return rotacao_simples_direita(tree);
			case 1:
				return rotacao_dupla_direita(tree);					
			} 
	}
}

//Remoção de itens da árvore AVL.
Tree remover(Tree tree, int valor, int *diminuiu){
	//caso 1: Árvore vazia
	if(tree == NULL) 
		return NULL;
	
	if(tree->valor == valor) {	
		*diminuiu = 1;
		if(tree->left == NULL) {
			return tree->right;
		}
		if(tree->right == NULL) {
			return tree->left;
		}
		tree->valor = maior_valor(tree->left);
		tree->left = remover(tree->left, tree->valor, diminuiu);
		if(*diminuiu){
				switch(tree->fb){
					case 0:
						tree->fb = 1;
						*diminuiu = 0;
						break;
					case -1:
						*diminuiu = 1;
						tree->fb = 0;
						break;
					case 1:
						*diminuiu = 1;
						return rotation(tree);
				}
		}
		return tree;
	}	
	
	if(valor > tree->valor) {
			tree->right = remover(tree->right, valor, diminuiu);
			if(*diminuiu) {
				switch(tree->fb){
					case 0:
						tree->fb = -1;
						*diminuiu = 0;
						break;
					case -1:
						*diminuiu = 1;
						return rotation(tree);
					case 1:
						 tree->fb = 0;
						*diminuiu = 1;
						break;
				}
		}
	}else{
			tree->left = remover(tree->left, valor, diminuiu);
			if(*diminuiu){
				switch(tree->fb) {
					case 0:
						tree->fb = 1;
						*diminuiu = 0;
						break;
					case -1:
						tree->fb=0;
						*diminuiu = 1;
						break;
					case 1:
						*diminuiu = 1;
						return rotation(tree);
				}
		}
	}
	return tree; 
}


Tree rotacao_simples_esquerda(Tree tree) {

	Tree p, u, t1, t2, t3;
 
    	p = tree;
	u = p->right;
    	t1 = p->left;
//Não sofrem alterações. 
    	t2 = u->left;
    	t3 = u->right;

//Atualização dos ponteiros.
	p->right = t2;
	u->left = p;
    
//Atualização dos fator de balanço.
	if(u->fb == 1) {
		p->fb = 0;
		u->fb = 0;
	} else {
		p->fb = 1;
		u->fb = -1;
	}	
    
	return u;
}

Tree rotacao_dupla_esquerda(Tree tree) {
	Tree p, u, v, t1, t2, t3;
	p = tree;
	u = p->right;
	v = u->left;
	
//Atualização de ponteiros.
	p->right = v->left;
	v->left = p;
	u->left = v->right;
	v->right = u;
	
//Atualização do fator de balanço.
	if (v->fb == 1){
		p->fb = -1;
		v->fb = 0;
	}
	else
		p->fb = 0;
	if(v->fb == -1){
		u->fb = 1;
		v->fb = 0;
	}
	else
		u->fb = 0;
			
		
	return v;
}

Tree rotacao_simples_direita(Tree tree) {

	Tree p, u, t1, t2, t3;
	
	p = tree;
	u = p->left;
	t2 = u->right;
//Não sofrem alterações.
	t1 = u->left;
	t3 = p->right;
	
//Atualização dos ponteiros.
	p->left = t2;
	u->right = p;

//Atualização do fator de balanço.
	if(u->fb == -1) {
		p->fb = 0;
		u->fb = 0;
	} else {
		p->fb = -1;
		u->fb = 1;
	}	
    
	return u;
}

Tree rotacao_dupla_direita(Tree tree) {

	Tree p, u, v, t1, t2, t3;
	p = tree;
	u = p->left;
	v = u->right;
	
//Atualização dos ponteiros.	
	p->left = v->right;
	v->right = p;
	u->right = v->left;
	v->left = u;
	
//Atualização do fator de balanço.
	if (v->fb == -1){
		p->fb = 1;
		v->fb = 0;
	}
	else{
		p->fb = 0;
	}
	if(v->fb == 1){
		u->fb = -1;
		v->fb = 0;
	}
	
	else{
		u->fb = 0;
	}
	
	return v;
}

int compare(int valor1, int valor2) {
	if(valor1 > valor2)
		return valor1;
	else
		return valor2;
}

//Descobrir altura da árvore
int height(Tree tree) {
	if(tree == NULL) {
		return 0;
	}
	return 1 + compare(height(tree->right), height(tree->left));
}

int maior_valor(Tree tree) {
	if(tree == NULL)
			return 0;
	if(tree->right == NULL)
			return tree->valor;
	else
			return maior_valor(tree->right);
}

int menor_valor(Tree tree) {
	if(tree == NULL)
			return 0;
	if(tree->left == NULL)
			return tree->valor;
	else
			return maior_valor(tree->left);
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

int main(){
    
    Tree teste = NULL;
    Tree higher = NULL;
    int parametro;
    
    while(1){
        int opcao;
        scanf("%d", &opcao);
        int usuario;
        int removivel;
        switch(opcao)
        {
        case 1:
            scanf("%d", &usuario);
            teste = insert(teste, usuario, &parametro);
            break;
        case 2:
            scanf("%d", &removivel);
            teste = remover(teste, removivel, &parametro);
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
