#include "Lista.h"
#include "Tabela.h"
#include "Leitor_Arquivo.h"
#include "Banco.h"
#include "timer.h"

bool menu(Banco* banco,Tabela ** tab);
void buscaTodosRegistros(Banco *bd, Tabela **tab);
void buscaIndividual(Banco *bd);
void inserirTabela(Banco *bd);
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

    while(menu(bd,tab));

      return 0;
}


bool menu(Banco *bd,Tabela **tab)
{
    int flag = 0;
    std::cout<<"1 - Buscar um unico registro "<<std::endl;
    std::cout<<"2 - Buscar Todos registros"<<std::endl;
    std::cout<<"3 - Inserir Nova Tabela"<<std::endl;
    std::cout<<"0 - Sair"<<std::endl;

    std::cin>>flag;
    switch(flag)
    {
        case 1:
            buscaIndividual(bd);
            break;
        case 2:
            buscaTodosRegistros(bd,tab);
            break;
        case 3:
            inserirTabela(bd);
            break;
        case 0:
            return false;
        default:
            break;
    }

    return true;

}
void buscaTodosRegistros(Banco *bd, Tabela **tab)
{
    double inicio = 0,fim = 0;
    std::string nome, chave;
    int indColisao = 0;
    Lista * lColisao;
    int k;
    GET_TIME(inicio);
    for(int i = 0; i<bd->retornarQtdTabelas();i++)
    {
        nome = tab[i]->retornaNomeTabela();
        Lista **l = tab[i]->retornaColunas();
        k = 0;
        while(k != tab[i]->retornaTamanhoTabela())
        {
            if(l[k] != NULL)
            {
                chave = l[k]->retornaID();
                Lista * l12 = bd->retornarTabela(nome)->retornaLinha(chave);
              //  if(l12 != NULL)
                //    l12->imprimeCampos();
                lColisao = l[k];
                while(indColisao < l[k]->retornaQTDColisao() )
                {
                    chave = lColisao->retornaID();
                    bd->retornarTabela(nome)->retornaLinha(chave);
                    lColisao = lColisao->retornaProximo();
                    //lColisao->imprimeCampos();
                    indColisao++;
                }
                indColisao = 0;
            } k++;
        }
    }
    GET_TIME(fim);
    std::cout<<"Tempo para buscar todos registros "<<(fim-inicio)<<"s\n\n"<<std::endl;

}
void buscaIndividual(Banco *bd)
{

    double ini = 0, fim = 0;
    std::string chave;
    std::string nomeTabela;
    std::cout<<"Digite o nome da tabela"<<std::endl;
    std::cin>>nomeTabela;
    std::cout<<"Digite a chave primaria (caso seja composta, nao adicione espaco)"<<std::endl;
    std::cin>>chave;

    GET_TIME(ini);
    Tabela * t = bd->retornarTabela(nomeTabela);

    if( t== NULL)
        std::cout<<"Tabela "<<nomeTabela<<" nao encontrada"<<std::endl;
    else
    {
        Lista * l = t->retornaLinha(chave);
        if(l == NULL)
            std::cout<<"Impossivel encontrar registro com chave primaria "<<chave<<std::endl;
        else
        {
            t->imprimir();
            l->imprimeCampos();
        }

    }
    GET_TIME(fim);
    std::cout<<"Tempo de busca: "<<fim-ini<<"ms"<<std::endl;
}
void inserirTabela(Banco *bd)
{
    std::string nomeTabela, id, *campos, *valColuna;
    Tabela *t;
    Lista *l = new Lista();
    int qtdColunas = 0;
    std::cout<<"Digite o nome da Tabela"<<std::endl;
    std::cin>>nomeTabela;
    std::cout<<"Digite a quantidade de colunas da tabela"<<std::endl;
    std::cin>>qtdColunas;


    qtdColunas = 2;
    campos = new std::string[qtdColunas];
    valColuna = new std::string[qtdColunas];
    for(int  i = 0; i<qtdColunas; i++) {
        std::cout << "Digite o nome das colunas e o valor da tabela" << std::endl;
        std::cin >> campos[i];
        std::cin>>valColuna[i];
        l->inserir(campos[i],valColuna[i]);
    }
    std::cout<<"Digite o id\n";
    std::cin>>id;

    t = new Tabela(100);
    l->defineID(id);
    t->defineNomeTabela(nomeTabela);
    t->defineCampos(campos,qtdColunas);
    t->inserirCampos(l);
    bd->insereNovaTabela(t);
}

