//
// Created by Gerson H Marciano R on 14/04/17.
//

#ifndef TRABALHOAED_LISTA_H
#define TRABALHOAED_LISTA_H


#include "No.h"
#include <iostream>
class Lista {
    No* primeiro;
    No* ultimo;
    std::string id;
    Lista *prox;
    int tamanho;

public:
    Lista();
    ~Lista();
    std::string retornaID();
    Lista* retornaProximo();
    int retornaTamanho();

    void inserir(std::string nomeColuna, std::string val);
    void imprimeCampos();
    void imprime();
    void defineID(std::string id);
    void defineProximo(Lista *p);




};


#endif //TRABALHOAED_LISTA_H
