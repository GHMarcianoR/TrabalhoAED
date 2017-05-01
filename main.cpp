#include "Lista.h"
#include "Tabela.h"
#include "Leitor_Arquivo.h"
#include "Banco.h"
#include "timer.h"

bool menu(Banco* banco);
int main() {

    Leitor_Arquivo* arq;
    Tabela** tab;
    double inicio, fim;

    GET_TIME(inicio);
    arq = new Leitor_Arquivo("usda.sql");
    arq->coletaDados();
    tab = arq->retornaTabelas();

    Banco* bd = new Banco(20);
    for(int i = 0; i<10; i++)
         bd->insereNovaTabela(tab[i]);
    GET_TIME(fim);
    std::cout<<"Tempo decorrido para carregar os dados "<<fim-inicio<<"ms\n"<<std::endl;
    while(menu(bd));

    return 0;
}
bool menu(Banco *banco)
{
    std::string nomeTabela,chave;
    bool flag = 1;
    double ini, fim;
    std::cout<<"Digite o nome da tabela"<<std::endl;
    std::cin>>nomeTabela;
    std::cout<<"Digite a chave primaria (caso seja composta, nao adicione espaco)"<<std::endl;
    std::cin>>chave;
    GET_TIME(ini);
    Tabela * t = banco->retornarTabela(nomeTabela);
    if( t== NULL)
        std::cout<<"Tabela "<<nomeTabela<<" nao encontrada"<<std::endl;
    else
    {
        Lista * l = t->retornaLinha(chave);
        if(l == NULL)
            std::cout<<"Impossivel encontrar registro com chave primaria "<<chave<<std::endl;
        else
          l->imprimeCampos();

    }
    GET_TIME(fim);
    std::cout<<"Tempo de busca: "<<fim-ini<<"ms"<<std::endl;
    std::cout<<"\nDigite 0 para sair\n1 para continuar"<<std::endl;
    std::cin>>flag;

    return flag;

}


