#include <stdio.h>
#include <stdlib.h>
#include<iostream>
#include<locale.h>
using namespace std;

struct No {
    int valor;
    struct No* esquerda;
    struct No* direita;
};

// exemplos nos slides)
struct No* novoNo(int valor);
struct No* inserir(struct No* raiz, int valor);
void emOrdem(struct No* raiz, int);

// a ser implementado
int altura(struct No* raiz);
int ehABB(struct No* raiz);
struct No* buscaMin(struct No* raiz);
struct No* buscaMax(struct No* raiz);
struct No* fDelete(struct No* raiz, int remover);

int main() {
    struct No* raiz = NULL;
    setlocale(LC_ALL,"");
    // inserções
    raiz = inserir(raiz, 50);
    raiz = inserir(raiz, 30);
    raiz = inserir(raiz, 20);
    raiz = inserir(raiz, 40);
    raiz = inserir(raiz, 45);
    raiz = inserir(raiz, 70);
    raiz = inserir(raiz, 80);
    //raiz = inserir(raiz, 10);
    //raiz = inserir(raiz, 5);
    raiz = inserir(raiz, 60);
    raiz = inserir(raiz, 55);
    raiz = inserir(raiz, 10);
    raiz = inserir(raiz, 90);
    raiz = inserir(raiz, 75);
    raiz = inserir(raiz, 100);
    raiz = inserir(raiz, 120);

    emOrdem(raiz, 0);
    int leftAltura = 0;
    int rightAltura = 0;
    //altura(raiz);
    rightAltura = altura(raiz->direita);
    leftAltura = altura(raiz->esquerda);
    cout<<"Altura esquerda: "<<leftAltura<<endl;
    cout<<"Altura direita: "<<rightAltura<<endl;

    cout<<"Valor mínimo: "<<buscaMin(raiz)->valor<<endl;
    cout<<"Valor máximo: "<<buscaMax(raiz)->valor<<endl;
    //Teste de erro raiz->direita->valor = 20;
    cout<<ehABB(raiz)<<endl;;

    int remover;
    cout<<"Escolha o valor a ser removido: "<<endl;
    cin>>remover;

    fDelete(raiz, remover);

    emOrdem(raiz, 0);

    // implementar mais testes para as novas funcionalidades e a travessia

    return 0;
}

struct No* novoNo(int valor) {
    struct No* no = (struct No*)malloc(sizeof(struct No));
    no->valor = valor;
    no->esquerda = NULL;
    no->direita = NULL;
    return no;
}

struct No* inserir(struct No* raiz, int valor) {

    if(raiz == NULL){
        return novoNo(valor);
    }
    if(valor > raiz->valor){
        raiz->direita = inserir(raiz->direita, valor);
    }
    if(valor < raiz->valor){
        raiz->esquerda = inserir(raiz->esquerda, valor);
    }
    return raiz;

}

void emOrdem(struct No* raiz, int esp) {
    if (raiz != NULL) {
        esp = esp + 5;
        emOrdem(raiz->esquerda, esp);
        for(int i = 0; i<esp;i++){
            cout<<" ";
        }
        cout << raiz->valor << endl;
        emOrdem(raiz->direita, esp);
    }
}

// novas funções
int altura(struct No* raiz) {
    // retorna a altura da árvore ou subárvore dada por raiz
	// a altura de uma árvore vazia é -1 e a altura de uma árvore com apenas um nó é 0
	if(raiz == NULL){
        return 0;
	}else{
        int dirAltura = altura(raiz->direita);
        int esqAltura = altura(raiz->esquerda);
        if(dirAltura>esqAltura){
            return dirAltura +1;
        }else{
            return esqAltura +1;
        }
	}

}

//struct No* remover(struct No* raiz, int valor) {
// essa deixamos para a próxima atividade
//}

int ehABB(struct No* raiz) {
	// verifica se a árvore binária satisfaz as propriedades de uma árvore binária de busca
	// pode ser usado para validar a corretude das operações de inserção e remoção
    if(raiz == NULL){
        return 0;
    }
    if(raiz->esquerda != NULL && raiz->esquerda->valor > raiz->valor){
        cout<<"Árvore não é ABB"<<endl;
        return -1;
    }
    if(raiz->direita != NULL && raiz->direita->valor < raiz->valor){
        cout<<"Árvore não é ABB"<<endl;
    }
    if(ehABB(raiz->esquerda) == -1 || ehABB(raiz->direita) == -1){
        return -1;
    }
    return 0;

}

// as funções abaixo buscam o menor e o maior valor na árvore, respectivamente
struct No* buscaMin(struct No* raiz) {
    if(raiz->esquerda != NULL){
        return buscaMin(raiz->esquerda);
    }
    return raiz;

}

struct No* buscaMax(struct No* raiz) {
    if(raiz->direita != NULL){
        return buscaMax(raiz->direita);
    }
    return raiz;
}

struct No* fDelete(struct No* raiz, int remover){

    if(raiz == NULL){
    return raiz ;
    }

    if(remover < raiz->valor){
    raiz -> esquerda = fDelete(raiz->esquerda, remover) ;
    } else if(remover > raiz->valor) {
    raiz -> direita = fDelete(raiz->direita, remover);
    }else{
        if(raiz->esquerda == NULL){
            struct No* aux = raiz->direita;
            free(raiz);
            return aux;
        }else if(raiz->direita == NULL){
            struct No* aux = raiz->esquerda;
            free(raiz);
            return aux;
        }else{
            struct No* aux = buscaMin(raiz->direita);
            raiz->valor = aux->valor;
            raiz->direita = fDelete(raiz->direita, aux->valor);
        }
        return raiz;
    }

    //system("cls");

};
