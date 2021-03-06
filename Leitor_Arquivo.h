//
// Created by zumbi on 18/04/17.
//

#ifndef TRABALHOAED_LEITOR_ARQUIVO_H
#define TRABALHOAED_LEITOR_ARQUIVO_H

#include <fstream>
#include <algorithm>
#include <functional>
#include <cctype>
#include <locale>
#include "Tabela.h"



class Leitor_Arquivo {

    std::ifstream arquivo;
    Tabela** tabela;
    std::string nomeArquivo;
    std::string *tab_IDs;
    int qtdTabelasArquivo;

    int tamTabelasArquivo;
    int contaTab(std::string& s);
    int contaEsp(std::string& s );
    void criaTabelas();
    void carregaDados();

public:
   Leitor_Arquivo(std::string nomeArquivo);

    void coletaDados();
    Tabela** retornaTabelas();
     std::string &ltrim(std::string &s);
     std::string &rtrim(std::string &s);
    std::string &trim(std::string &s);
    int retornarQtdTabelas();

};


#endif //TRABALHOAED_LEITOR_ARQUIVO_H
