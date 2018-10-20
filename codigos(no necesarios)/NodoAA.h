#ifndef NodoAA_H
#define NodoAA_H

#include <cstddef>
using namespace std;

class NodoAA
{
public:
	int cont, nivel, codigo;
	string sinonimo;
	NodoAA *derecha;
	NodoAA *izquierda;
	NodoAA *padre;
	NodoAA *raiz;
};

#endif
