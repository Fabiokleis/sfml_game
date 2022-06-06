#ifndef GAME_LISTA_H
#define GAME_LISTA_H
#include "Elemento.h"

using namespace Listas;

namespace Listas {

    template <class TL> class Lista
    {
    private:
        Elemento<TL>* pFirst;
        Elemento<TL>* pLast;
        int len;

    public:
        Lista();
        ~Lista();
        int getLen() { return len; }

        TL* getItem(int posicao) {
            Elemento<TL>* temp = pFirst;
            if(posicao < len){
                if (posicao == 0) {
                    return temp->getItem();
                }
                for (int i = 0; i < posicao; i++) {
                    temp = temp->getPProx();
                    std::cout << "temp->getPProx OK" << std::endl;
                }
                return temp->getItem();
            }
            else{
                std::cout << "Posicao fora da lista" << std::endl;
            }
            return nullptr;
        }
        void push(TL* item) {
            if (this->pFirst == nullptr) {
                pFirst = new Elemento<TL>;
                pFirst->setItem(item);
                pLast = pFirst;
            }
            else {
                Elemento<TL>* temp = new Elemento<TL>;
                temp->setItem(item);
                pLast->setPProx(temp);
                pLast = temp;
            }
            len++;
        }
        void pop(TL* item) {
            Elemento<TL>* temp = pFirst;
            Elemento<TL>* tempAnt = nullptr;
            while (temp->getItem() != item) {
                tempAnt = temp;
                temp = temp->getPProx();
            }
            if (temp == pFirst) {
                pFirst = temp->getPProx();
            }
            else if (temp == pLast) {
                tempAnt->setPProx(nullptr);
                pLast = tempAnt;
            }
            else {
                tempAnt->setPProx(temp->getPProx());
            }
            delete temp;
            len--;
        }

    };

    template<class TL>
    inline Lista<TL>::Lista()
    {
        pFirst = nullptr;
        pLast = nullptr;
        len = 0;
    }

    template<class TL>
    inline Lista<TL>::~Lista()
    {
        pFirst = nullptr;
        pLast = nullptr;
    }

}
#endif //GAME_LISTA_H
