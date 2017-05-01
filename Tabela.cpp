//
// Created by zumbi on 14/04/17.
//

#include "Tabela.h"

Tabela::Tabela(int t)
{

    tamanhoTabela = t;
    colunas = new Lista*[tamanhoTabela];
    for(int i = 0; i<tamanhoTabela; i++)
        colunas[i] = NULL;
    qtdCampos = 0;
    qtdPosicoesOcupadas = 0;
    proxima = NULL;
    nomeTabela ="";
    campos = NULL;


}

Lista*  Tabela::retornaLinha(std::string str)
{
    int h = hash(str);
    if(colunas[h] != NULL && colunas[h]->retornaID() == str)
        return colunas[h];
    else
    {
        Lista *l = colunas[h];
        while(l != NULL && l->retornaID() != str)
            l = l->retornaProximo();
        return l;
    }
    return NULL;
}
void Tabela::defineCampos(std::string *s, int tam)
{
    qtdCampos = tam;
    campos  = s;
}


void Tabela::inserirCampos(Lista *l)
{
    if(l != NULL)
    {
        int h = hash(l->retornaID());
        if(qtdPosicoesOcupadas >= tamanhoTabela)
        {
            redimensiona();
        }
        if(colunas[h] == NULL)
        {
            colunas[h] = l;
            qtdPosicoesOcupadas++;
        }
        else
        {
            Lista *it = colunas[h];
            while(it->retornaProximo() != NULL)
                it = it->retornaProximo();
            it->defineProximo(l);
        }

    }


}
void Tabela::inserirCamposRedimensiona(Lista *l)
{
    if(l != NULL)
    {
        int h = hash(l->retornaID());
        if (colunas[h] == NULL) {
            colunas[h] = l;
            qtdPosicoesOcupadas++;
        } else {
            Lista *it = colunas[h];
            while (it->retornaProximo() != NULL)
                it = it->retornaProximo();
            it->defineProximo(l);
        }
    }
}
void Tabela::imprimir()
{
    for(int i = 0; i<qtdCampos; i++)
        std::cout<<campos[i]<<"\t";
    std::cout<<"\n";
}
void Tabela::redimensiona()
{
    int novoT = tamanhoTabela*2;
    Lista** col = colunas;

    colunas = new Lista*[novoT];

    for(int i = 0; i<novoT; i++)
        colunas[i]= NULL;

    for(int i = 0; i<tamanhoTabela; ++i)
        if (col[i] != NULL)
              inserirCamposRedimensiona(col[i]);




    tamanhoTabela = novoT;

}

int Tabela::hash(std::string s)
{
   long int  hashedValue = 3628273133;
    for(int i=0; i<s.size(); i++)
    {
        hashedValue += s[i];
        hashedValue *= 3367900313;
    }
    return  abs((int)hashedValue % tamanhoTabela);

}

int Tabela::retornaQtdCampos() {return qtdCampos;}
std::string* Tabela::retornaCampos() {return campos;}
void Tabela::defineProximaTabela(Tabela *t) {proxima = t;}
void Tabela::defineNomeTabela(std::string nome) { nomeTabela = nome;}
Tabela* Tabela::retornaProximaTabela() { return proxima;}
std::string Tabela::retornaNomeTabela() {return nomeTabela;}