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
    void carregaDados();
    int contaTab(std::string& s);
    int contaEsp(std::string& s );


public:
   Leitor_Arquivo(std::string nomeArquivo);
    void criaTabelas();
    Tabela** retornaTabelas();
     std::string &ltrim(std::string &s);
     std::string &rtrim(std::string &s);
    std::string &trim(std::string &s);

};


#endif //TRABALHOAED_LEITOR_ARQUIVO_H
