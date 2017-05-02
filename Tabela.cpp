//
// Created by zumbi on 14/04/17.
//

#include "Tabela.h"

Tabela::Tabela(int t)
{

    tamanhoTabela = t;
    colunas = new Lista*[tamanhoTabela];    //Inicializa as váriaveis para a criação do Hashtable
    for(int i = 0; i<tamanhoTabela; i++)
        colunas[i] = NULL;
    qtdCampos = 0;
    qtdPosicoesOcupadas = 0;
    proxima = NULL;
    nomeTabela ="";
    campos = NULL;

}
//retorna a Lista contida na tabela
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

//Define os campos da tabela, bem como a quantidade destes
void Tabela::defineCampos(std::string *s, int tam)
{
    qtdCampos = tam;
    campos  = s;
}

//Insere um novo registro na tabela
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
            colunas[h] = l;   //Inserção no caso em que não há colisão;
            qtdPosicoesOcupadas++;
        }
        else
        {
            Lista *it = colunas[h];
            while(it->retornaProximo() != NULL)  //Colisao tratada via encadeamento
                it = it->retornaProximo();
            it->defineProximo(l);
        }

    }


}
//Funcao utilizada para a re-indexação no caso em que há a necessidade de redimensionar a tabela
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
//Imprime os campos
void Tabela::imprimir()
{
    for(int i = 0; i<qtdCampos; i++)
        std::cout<<campos[i]<<"\t";
    std::cout<<"\n";
}
//Redimensiona a tabela para possibilitar a inserção de novos dados;
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
//Hash da multiplicação faz uso de 2 números primos grandes
int Tabela::hash(std::string s)
{
   long int  h = 3628273133;
    for(int i=0; i<s.size(); i++)
    {
        h += s[i];
        h *= 3367900313;
    }
    return  abs((int)h % tamanhoTabela);

}

std::string* Tabela::retornaCampos() {return campos;}
std::string Tabela::retornaNomeTabela() {return nomeTabela;}
Tabela* Tabela::retornaProximaTabela() { return proxima;}
Lista** Tabela::retornaColunas(){return colunas;}
int Tabela::retornaTamanhoTabela() {return tamanhoTabela;}
void Tabela::defineProximaTabela(Tabela *t) {proxima = t;}
void Tabela::defineNomeTabela(std::string nome) { nomeTabela = nome;}
int Tabela::retornaQtdCampos() {return qtdCampos;}
