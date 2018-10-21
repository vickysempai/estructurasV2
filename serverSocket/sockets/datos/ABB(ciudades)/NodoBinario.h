#ifndef _NODOBINARIO_H
#define	_NODOBINARIO_H
#include <iostream>
#include <string>

using namespace std;


class NodoBinario {
   public:

    NodoBinario(string cod,string name, NodoBinario *der = NULL, NodoBinario *izq = NULL, NodoBinario *sig=NULL, NodoBinario *ant=NULL):
        Hizq(izq), Hder(der), codigo(cod),nombre(name), siguiente(sig), anterior(ant), FB(0) {}


    string codigo,nombre;
    int FB;
    NodoBinario *Hizq, *Hder, *siguiente, *anterior;

    friend class Pila;
    friend class Binario;

    void InsertaBinario(string cod,string name);
};

typedef NodoBinario *pnodo;
typedef NodoBinario *pNodoBinario;

void PreordenR(NodoBinario* R);
void InordenR(NodoBinario* R);
void PostordenR(NodoBinario* R);
#endif	

