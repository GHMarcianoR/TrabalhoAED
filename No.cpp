//
// Created by zumbi on 14/04/17.
//


#include "No.h"


No::~No() {info =""; nome_Coluna="";prox=NULL; }
No::No() {}
std::string No::getInfo() { return info;}
No* No::getProximo() {return prox;}
std::string No::getNomeColuna(){return nome_Coluna;}
void No::setInfo(std::string inf) { info = inf;}
void No::setProximo(No *p) {prox = p;}
void No::setNomeColuna(std::string s) {nome_Coluna = s;}

