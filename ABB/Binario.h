
#ifndef _BINARIO_H
#define	_BINARIO_H
#include "NodoBinario.h"
#include "Pila.cpp"

using namespace std;

class Binario{
public:
    pNodoBinario raiz;

    Binario():raiz(NULL){}

    void InsertaNodo(string cod,string name);
    void PreordenI();
    void InordenI();
    void PostordenI();
    bool buscar(string cod);
};



#endif	/* _BINARIO_H */

