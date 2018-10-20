
#ifndef NODO_H
#define NODO_H

#include "ArbolB.h"
#include "avl.h"
#include <iostream>
using namespace std;

class nodo {
	public:
		nodo(string v)
		{
			valor = v;
			siguiente = NULL;
			anterior =NULL;
		}
		
		nodo(string v, nodo * signodo)
		{
			valor = v;
			siguiente = signodo;
		}

		string valor;
		ArbolB *arbolb;	
		avlTree *arbolavl;
		nodo *siguiente;
		nodo *anterior;
		
		
   friend class listaDC;
};


#endif /* NODO_H */

