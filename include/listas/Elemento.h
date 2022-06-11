#ifndef GAME_ELEMENTO_H
#define GAME_ELEMENTO_H

namespace Listas {

    template <class TE> class Elemento
    {
    private:
        Elemento<TE>* pProx;
        TE* item;

    public:
        Elemento();
        ~Elemento();
        void setPProx(Elemento<TE>* pProx) { this->pProx = pProx; }
        void setItem(TE* item) { this->item = item; }
        Elemento<TE>* getPProx() { return pProx; }
        TE* getItem() { return item; }
    };

    template<class TE>
    inline Elemento<TE>::Elemento()
    {
        pProx = nullptr;
        item = nullptr;
    }

    template<class TE>
    inline Elemento<TE>::~Elemento()
    {
    }

}

#endif //GAME_ELEMENTO_H
