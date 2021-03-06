//
// Created by zumbi on 19/04/17.
//

#include "Banco.h"

Banco::Banco(int tamanho)
{
    qtdTabelas = tamanho;
    tabela = new Tabela*[qtdTabelas];
    for(int i =0; i<qtdTabelas; i++)
        tabela[i] = NULL;
    qtdPosicoesOcupadas = 0;   //Inicializa as váriaveis utilizadas para criação do hashtable
}
int Banco::hash(std::string str)
{
    long int  hashedValue = 3628273133;
    for(int i=0; i<str.size(); i++)
    {
        hashedValue += str[i];
        hashedValue *= 3367900313;    //Funcao de hash de multiplicação faz uso de 2 números primos grandes;
    }
    return  abs((int)hashedValue % qtdTabelas);


}

//Insere uma nova tabela no hashtable do banco
void Banco::insereNovaTabela(Tabela *t)
{
   if(t != NULL)
   {
       int p = hash(t->retornaNomeTabela());
       if(qtdPosicoesOcupadas > qtdTabelas)
       {
           redimensiona();   //redimensiona a tabela para inserção de novos elementos;
       }
       if(tabela[p]==NULL)
       {
           tabela[p] = t;
           qtdPosicoesOcupadas++;
       }
       else
       {
           Tabela* it =tabela[p];
           while(it->retornaProximaTabela() != NULL) //Colisão tratado por encadeamento
               it = it->retornaProximaTabela();
           it->defineProximaTabela(t);
       }

   }


}
//Funcao utilizada para re-indexação dos dados na hora do redimensionamento
void Banco::insereNovaTabelaRedimensiona(Tabela *t)
{
    if(t != NULL)
    {
        int p = hash(t->retornaNomeTabela());
         if(tabela[p]==NULL)
        {
            tabela[p] = t;
            qtdPosicoesOcupadas++;
        }
        else
        {
            Tabela* it =tabela[p];
            while(it->retornaProximaTabela() != NULL)
                it = it->retornaProximaTabela();
            it->defineProximaTabela(t);
        }

    }
}
Tabela **Banco::retornaTabela(){return tabela ;}

Tabela* Banco::retornarTabela(std::string nome)
{
    int h = hash(nome);
     if(tabela[h] != NULL && tabela[h]->retornaNomeTabela() == nome)
         return tabela[h];
    else
     {
         Tabela* t = tabela[h];
         if(t!= NULL)
         while(t->retornaNomeTabela() != nome)
             t = t->retornaProximaTabela();
        return t;
     }

}
//redimensiona o tamanho da tabela para a inserção de novos dados;
void Banco::redimensiona()
{
    int novoT = qtdTabelas*2;
    Tabela** t = tabela;

    tabela = new Tabela*[novoT];

    for(int i = 0; i<novoT; i++)
        tabela[i]= NULL;

    for(int i = 0; i<qtdTabelas; i++)
        if(t[i] != NULL)
            insereNovaTabelaRedimensiona(t[i]);

    qtdTabelas = novoT;

}
int Banco::retornarQtdTabelas() {return qtdTabelas;}