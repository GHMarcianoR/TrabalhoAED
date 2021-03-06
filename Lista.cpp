//
// Created by zumbi on 14/04/17.
//

#include "Lista.h"
//Inicializa as váriaveis para a criação da lista encadeada
Lista::Lista(){ primeiro = ultimo = NULL; tamanho =0; prox = NULL; id = "";}
Lista::~Lista()
{
    No* p = primeiro;
    while(p != NULL)
    {
        No* i = p->getProximo();
        delete p;
        p = i;

    }
}
//insere novo elemento na lista;
void Lista::inserir(std::string nomeColuna, std::string val)
{
    No *p = new No();
    p->setNomeColuna(nomeColuna);
    p->setInfo(val);
    p->setProximo(NULL);

    if(primeiro == NULL)
    {
        primeiro = p;
        ultimo = p;
    }
    else if(primeiro == ultimo)
    {
        ultimo = p;
        primeiro->setProximo(ultimo);
    }
    else
    {

        ultimo->setProximo(p);
        ultimo = p;
    }
    tamanho++;
}
void Lista::imprime()
{
    std::cout<<"id: "<<this->id<<std::endl;
    for(No * p = primeiro; p != NULL; p = p->getProximo())
        std::cout<<p->getNomeColuna()<<" ";

    std::cout<<std::endl;
}
void Lista::imprimeCampos()
{
    if(primeiro != NULL)
    {
        No * p = primeiro;
        while(p != NULL)
        {
            if(p->getInfo()== "\t")
                std::cout<<"NULL ";
            else
                std::cout<<p->getInfo()<<"\t";
            p = p->getProximo();
        }
        std::cout<<std::endl;
    }
}
void Lista::defineID(std::string id)
{
    this->id = id;

}
void Lista::defineProximo(Lista *p)
{
    prox = p;
    contColisao++;;
}
Lista* Lista::retornaProximo()
{
    return prox;
}
std::string Lista::retornaID()
{
    return id;
}
int Lista::retornaTamanho() {return tamanho;}
int Lista::retornaQTDColisao() {return contColisao;}