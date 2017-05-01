//
// Created by zumbi on 14/04/17.
//

#ifndef TRABALHOAED_NO_H
#define TRABALHOAED_NO_H


#include <string>

class No
{
    std::string info;
    std::string nome_Coluna;
    No *prox;
public:
        No();
        ~No();
        std::string getInfo();
        No* getProximo();
        std::string getNomeColuna();

        void setInfo(std::string inf);
        void setProximo(No *p);
        void setNomeColuna(std::string s);


};
#endif //TRABALHOAED_NO_H
