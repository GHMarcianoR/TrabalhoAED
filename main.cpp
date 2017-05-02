#include "Lista.h"
#include "Tabela.h"
#include "Leitor_Arquivo.h"
#include "Banco.h"
#include "timer.h"

bool menu(Banco* banco);
void buscaTodosRegistros(Banco *bd, Tabela **tab);
int main() {

    Leitor_Arquivo* arq;
    Tabela** tab;
    double inicio = 0, fim = 0;

    GET_TIME(inicio);
    arq = new Leitor_Arquivo("usda.sql");
    arq->coletaDados();
    tab = arq->retornaTabelas();

    Banco* bd = new Banco(arq->retornarQtdTabelas());
    for(int i = 0; i<bd->retornarQtdTabelas(); i++)
         bd->insereNovaTabela(tab[i]);
    GET_TIME(fim);
    std::cout<<"Tempo decorrido para carregar os dados "<<(fim-inicio)<<"s\n\n"<<std::endl;

    buscaTodosRegistros(bd,tab);
    while(menu(bd));

    return 0;
}


bool menu(Banco *banco)
{
    std::string nomeTabela,chave;
    bool flag = 1;
    double ini = 0, fim = 0;
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
        //else
     //     l->imprimeCampos();

    }
    GET_TIME(fim);
    std::cout<<"Tempo de busca: "<<fim-ini<<"ms"<<std::endl;
    std::cout<<"\nDigite 0 para sair\n1 para continuar"<<std::endl;
    std::cin>>flag;

    return flag;

}
void buscaTodosRegistros(Banco *bd, Tabela **tab)
{
    double inicio = 0,fim = 0;
    std::string chave;
    std::string nome;
    Tabela * t = NULL;
    Lista* l1 = NULL;
    GET_TIME(inicio);
    for(int i = 0; i<bd->retornarQtdTabelas();i++)
    {
        nome = tab[i]->retornaNomeTabela();
        Lista **l = tab[i]->retornaColunas();
        int k = 0;
        while(k != tab[i]->retornaTamanhoTabela())
        {
            if(l[k] != NULL)
            {
                chave = l[k]->retornaID();
                t = bd->retornarTabela(nome);
                if(t!= NULL)
                    l1 = t->retornaLinha(chave);
               /* if(l1!= NULL)
                    l1->imprimeCampos();*/
                for(l[k] = l[k]->retornaProximo();l[k] != NULL; l[k] = l[k]->retornaProximo())
                {
                    chave = l[k]->retornaID();
                    t = bd->retornarTabela(nome);
                    if(t!= NULL)
                        l1 = t->retornaLinha(chave);
                    /*if(l1!= NULL)
                        l1->imprimeCampos();*/
                }
            } k++;
        }
    }
    GET_TIME(fim);
    std::cout<<"Tempo para buscar todos registros "<<(fim-inicio)<<"s\n\n"<<std::endl;



}


