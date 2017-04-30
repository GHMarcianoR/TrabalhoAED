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

    void redimensiona();
public:
    Banco(int tamanho);
    void setTabelas(Tabela** t, int tam);
    void insereNovaTabela(Tabela *t);
    Tabela* getTabela(std::string nome);



};


#endif //TRABALHOAED_BANCO_H