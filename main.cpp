#include "Lista.h"
#include "Tabela.h"
#include "Leitor_Arquivo.h"
#include "Banco.h"


int main() {

    Leitor_Arquivo* arq;
    Tabela** tab;
    arq = new Leitor_Arquivo("usda.sql");
    arq->criaTabelas();
    tab = arq->retornaTabelas();

    Banco* bd = new Banco(20);
    for(int i = 0; i<10; i++)
         bd->insereNovaTabela(tab[i]);


    std::string nomeT = "weight";
    std::string id = "83110";

    bd->getTabela(nomeT)->imprimir();
    bd->getTabela(nomeT)->retornaLinha(id)->imprimeCampos();

    delete arq;
    delete bd;
    return 0;
}


