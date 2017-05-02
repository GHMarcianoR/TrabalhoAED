//
// Created by zumbi on 14/04/17.
//

#ifndef TRABALHOAED_TABELA_H
#define TRABALHOAED_TABELA_H


#include "Lista.h"

class Tabela {


    Lista** colunas;
    std::string nomeTabela;
    std::string* campos;
    Tabela *proxima;
    int tamanhoTabela;
    int qtdPosicoesOcupadas;
    int qtdCampos;

    int hash(std::string str);
    void redimensiona();
    void inserirCamposRedimensiona(Lista *l);
public:
    Tabela(int t);
    Tabela* retornaProximaTabela();
    Lista* retornaLinha(std::string str);
    std::string retornaNomeTabela();
     std::string* retornaCampos();
    int retornaQtdCampos();
    Lista** retornaColunas();


    void defineProximaTabela(Tabela *t);
    void defineNomeTabela(std::string nome);
    void inserirCampos(Lista * l);
    void estatisticas();
    void imprimir();
    void defineCampos(std::string *s, int tam);
};


#endif //TRABALHOAED_TABELA_H
