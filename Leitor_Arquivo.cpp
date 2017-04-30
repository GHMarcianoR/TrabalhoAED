//
// Created by zumbi on 18/04/17.
//

#include "Leitor_Arquivo.h"
#include <stdlib.h>

Leitor_Arquivo::Leitor_Arquivo(std::string nomeArquivo)
{

    arquivo.open(nomeArquivo, std::fstream::in);
    if(!arquivo.good())
    {
        std::cout<<"Erro durante a leitura do arquivo"<<std::endl;
        exit(-1);

    }
    tabela = new Tabela*[10];

}
int Leitor_Arquivo::contaTab(std::string &s)
{
    int cont = 0;
    for(int i = 0; i<s.size(); i++)
        if(s[i] == '\t')
            cont++;
    return cont;

}
int Leitor_Arquivo::contaEsp(std::string &s)
{
    int cont = 0;
    for(int i = 0; i<s.size(); i++)
        if(s[i] == ' ')
            cont++;
    return cont;

}
void Leitor_Arquivo::criaTabelas()
{
      int contTabela = 0;
      int ind = 0;
      int indStr = 0;
      std::string linha;
      std::string l1;

      while(!arquivo.eof() && contTabela != 10)
      {
            getline(arquivo,linha);
            std::string *str = new std::string[contaEsp(linha)];
            std::string nomeCampos ="";
            for(int i = 0; i<linha.size(); i++)
            {
                if(linha[i] == ' ')
                {
                    str[indStr] = linha.substr(ind, i-ind);
                    indStr++;
                    ind = i;
                }
            }
          ind = 0;
          indStr = 0;
           if(linha.find("CREATE TABLE") != std::string::npos)
           {
               tabela[contTabela] = new Tabela(20000);
               tabela[contTabela]->defineNomeTabela(trim(str[2]));
           }
          else if(linha.find("    ") != std::string::npos)
                  l1 +=str[4]+" "; //Armazena os nomes dos campos das tabelas em questão
          else if(linha.find(");") != std::string::npos)
          {

              std::string *nomeCampo = new std::string[contaEsp(l1)];
              for(int i =0; i<l1.size(); i++)
              {
                  if(l1[i] == ' ')
                  {
                      nomeCampo[indStr] = l1.substr(ind+1, i-ind);
                      if(!nomeCampo[indStr].empty() && nomeCampo[indStr] != " ")
                      {
                         indStr++;
                          ind = i;
                      }
                  }
              }
              tabela[contTabela]->defineCampos(nomeCampo,indStr);
              ind = 0;
              indStr = 0;
              l1.clear();
              contTabela++;



          }
      }
    carregaDados();
}
void Leitor_Arquivo::carregaDados()
{
    int contaTabela = 0;
    std::string linha;
    Tabela* tab;
    std::string* campos;
    int indStr = 0, ind  = 1;

    while(!arquivo.eof() && contaTabela < 11)
    {
        getline(arquivo,linha);
        linha+="\n";
        if(linha.find("FROM stdin") != std::string::npos)
        {
            tab = tabela[contaTabela];
            contaTabela++;
            campos = tab->retornaCampos();
            std::cout<<"Tabela: "<<contaTabela<<" "<<tab->retornaNomeTabela() <<std::endl;
        }
        else
        {
            Lista* l  = new Lista();
            for(int i = 0; i<linha.size(); i++)
            {
                if(linha[i] == '\t' ||linha[i]=='\n')
                {

                    std::string inf = linha.substr(ind,i-ind);
                   if(!inf.empty())
                   {
                       if(indStr != tab->retornaQtdCampos())
                       {
                           l->inserir(campos[indStr],inf);
                           if(indStr == 0)
                               l->defineID(trim(inf));
                           indStr++;
                       }
                   }
                    inf.clear();
                    ind = i;

                }
            }
            indStr = 0;
            ind = 0;
          if(l->retornaTamanho() > 0)
            tab->inserirCampos(l);

        }

    }


}
 std::string &Leitor_Arquivo::rtrim(std::string &s)
{
    s.erase(std::find_if(s.rbegin(), s.rend(),
                         std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
    return s;
}
std::string& Leitor_Arquivo::ltrim(std::string &s)
{
    s.erase(s.begin(), std::find_if(s.begin(), s.end(),
                                    std::not1(std::ptr_fun<int, int>(std::isspace))));
    return s;
}
 std::string& Leitor_Arquivo::trim(std::string &s) {
    return ltrim(rtrim(s));
}
Tabela** Leitor_Arquivo::retornaTabelas() {return tabela;}


