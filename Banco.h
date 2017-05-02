//
// Created by zumbi on 19/04/17.
//

#ifndef TRABALHOAED_BANCO_H
#define TRABALHOAED_BANCO_H


#include "Tabela.h"

class Banco {

    Tabela** tabela;
    std::hash<std::string> hs;
    int qtdTabelas;
    int qtdPosicoesOcupadas;
    int hash(std::string str);
    void insereNovaTabelaRedimensiona(Tabela* t);
    void redimensiona();
public:
    Banco(int tamanho);
    void insereNovaTabela(Tabela *t);
    Tabela* retornarTabela(std::string nome);
    int retornarQtdTabelas();


};


#endif //TRABALHOAED_BANCO_H
