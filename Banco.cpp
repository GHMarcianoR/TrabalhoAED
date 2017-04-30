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
    qtdPosicoesOcupadas = 0;
}
int Banco::hash(std::string str)
{
    return abs((int) hs(str) % qtdTabelas);
}
void Banco::insereNovaTabela(Tabela *t)
{
   if(t != NULL)
   {
       int p = hash(t->retornaNomeTabela());
       if(qtdPosicoesOcupadas > qtdTabelas)
       {
           redimensiona();
       }
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
Tabela* Banco::getTabela(std::string nome)
{
    int h = hash(nome);
     if(tabela[h] != NULL && tabela[h]->retornaNomeTabela() == nome)
         return tabela[h];
    else
     {
         Tabela* t = tabela[h];
         while(t->retornaNomeTabela() != nome)
             t = t->retornaProximaTabela();
        return t;
     }

}
void Banco::redimensiona()
{
    int novoT = qtdTabelas*2;
    Tabela** t = tabela;

    delete [] tabela;

    tabela = new Tabela*[novoT];

    for(int i = 0; i<novoT; i++)
        tabela[i]= NULL;
    for(int i = 0; i<qtdTabelas; i++)
        tabela[i] = t[i];

    qtdPosicoesOcupadas = qtdTabelas;
    qtdTabelas = novoT;

}