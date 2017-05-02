//
// Created by zumbi on 18/04/17.
//

#include "Leitor_Arquivo.h"

//Inicializa as váriaveis e abre o arquivo para leitura
Leitor_Arquivo::Leitor_Arquivo(std::string nomeArquivo)
{

    this->nomeArquivo = nomeArquivo;
    arquivo.open(this->nomeArquivo, std::fstream::in);
    if(!arquivo.good())
    {
        std::cout<<"Erro durante a leitura do arquivo"<<std::endl;
        exit(-1);

    }
    tabela = new Tabela*[qtdTabelasArquivo];

}

//Funcao para retornar o número de tabs em uma string
int Leitor_Arquivo::contaTab(std::string &s)
{
    int cont = 0;
    for(int i = 0; i<s.size(); i++)
        if(s[i] == '\t')
            cont++;
    return cont;

}

//retorna a quantidade de espacos ' ' em uma string
int Leitor_Arquivo::contaEsp(std::string &s)
{
    int cont = 0;
    for(int i = 0; i<s.size(); i++)
        if(s[i] == ' ')
            cont++;
    return cont;

}

//funcao para criar as tabelas onde os dados serão inseridos
void Leitor_Arquivo::criaTabelas()
{
      int contTabela = 0;
      int ind = 0;
      int indStr = 0;
      std::string linha;
      std::string l1;

      while(!arquivo.eof() && contTabela != qtdTabelasArquivo)
      {
            getline(arquivo,linha);
            std::string *str = new std::string[contaEsp(linha)];
            std::string nomeCampos ="";
            for(int i = 0; i<linha.size(); i++) //Instrução utilizada para coletar informações
            {                                   //das tabelas, como nome, e campos;
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
               tabela[contTabela] = new Tabela(1000);
               tabela[contTabela]->defineNomeTabela(trim(str[2]));
           }
          else if(linha.find("    ") != std::string::npos)
                  l1 +=str[4]+" "; //Armazena os nomes dos campos(juntos) das tabelas em questão
          else if(linha.find(");") != std::string::npos)
          {

              std::string *nomeCampo = new std::string[contaEsp(l1)];
              for(int i =0; i<l1.size(); i++)
              {
                  if(l1[i] == ' ')
                  {
                      nomeCampo[indStr] = l1.substr(ind+1, i-ind);
                      nomeCampo[indStr] = trim(nomeCampo[indStr]); //separa os nomes dos campos

                      if(!nomeCampo[indStr].empty() && nomeCampo[indStr] != " ")
                      {
                         indStr++;
                          ind = i;
                      }
                  }
              }
              tabela[contTabela]->defineCampos(nomeCampo,indStr); //Inicializa as variáveis referentes aos nomes das tabelas
              ind = 0;
              indStr = 0;
              l1.clear();
              contTabela++;
          }
      }

    carregaDados();
}


//Carrega todos os dos arquivos, para suas respectivas tabelas
void Leitor_Arquivo::carregaDados()
{
    int contaTabela = 0;
    std::string linha;
    Tabela* tab;
    std::string* campos, id,tab_atual;
    int indStr = 0, ind  = 0;

    while(!arquivo.eof() && contaTabela < qtdTabelasArquivo+1)
    {
        getline(arquivo,linha);
        linha+="\n";
        if(linha.find("FROM stdin") != std::string::npos) //define a tabela na qual se inserirá os dados
        {
            tab = tabela[contaTabela];
            contaTabela++;
            campos = tab->retornaCampos();
          }
        else if (contaTabela > 0)
        {
            Lista* l  = new Lista();
            for(int i = 0; i<linha.size(); i++)
            {
                if(linha[i] == '\t' ||linha[i]=='\n')
                {
                   std::string inf = linha.substr(ind,i-ind); //coleta a informação sobre um determinado campo
                   inf = trim(inf);
                   if(!inf.empty())
                   {
                       if(indStr != tab->retornaQtdCampos())
                       {
                           l->inserir(campos[indStr],inf); //insere tal informação em uma futura linha da tabela
                          for(int k = 0; k<qtdTabelasArquivo; k++)
                              if(tab_IDs[k].find(tab->retornaNomeTabela()) != std::string::npos)
                              {
                                  if (tab_IDs[k].find(campos[indStr]) != std::string::npos) {   //verifica se a tabela tem chave composta
                                      l->defineID(l->retornaID() + inf);                        //em caso verdadeiro, concate as chaves
                                    break;
                                  }
                              }
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
            tab->inserirCampos(l); //Insere a dita linha na tabela em questão

        }

    }


}
//coleta informações pertinentes sobre as tabelas e suas chaves primárias;
void Leitor_Arquivo::coletaDados()
{
    std::ifstream aux;
    std::string linha,str;
    int ind =0, cont = 0;
    std::string *chavesP;

    aux.open(this->nomeArquivo, std::ios::in);
    if(!aux.good())
    {
        std::cout<<"Erro ao abrir o arquivo"<<std::endl;
        exit(-1);
    }
    while(!aux.eof())
    {

        getline(aux,linha);
        if(linha.find("CREATE TABLE") != std::string::npos) //coleta o número de tabelas presente no arquivo
            qtdTabelasArquivo++;
    }
    aux.close();
    aux.open(this->nomeArquivo, std::ios::in);
    chavesP = new std::string[qtdTabelasArquivo];
    while(!aux.eof())
    {
        getline(aux,linha);

        if(linha.find("PRIMARY KEY") != std::string::npos)
        {

            linha.replace(0,19,"");
            for(int i = 0; i< linha.size(); i++)
            {

               if(linha[i] == ' ')
               {
                   linha.replace(i-5,17,"");
                   linha.replace(linha.size()-2,2,"");
                   linha.replace(linha.find(' ') + 1,1,"");        //Armazena o nome de todoas as chaves primarias
                   chavesP[cont]= linha;                            //tanto atomicas quanto compostas;
                   cont++;
                   break;
               }

            }
            linha.clear();
        }
    }
    aux.close();
   tab_IDs = chavesP;
  criaTabelas();

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
int Leitor_Arquivo::retornarQtdTabelas() {return qtdTabelasArquivo;}

