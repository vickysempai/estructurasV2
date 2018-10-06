#ifndef NODORYN_H
#define NODORYN_H
#include <iostream>
#include <cstddef>
using namespace std;

class nodoRyN{
public:
	nodoRyN(){llave = 0; color = 'R'; izquierdo = NULL; derecho = NULL; padre = NULL;}
	int llave;
	string definicion;
	char color; // r = ROJO   y   n = NEGRO
	nodoRyN *izquierdo;
	nodoRyN *derecho;
	nodoRyN *padre;
};

typedef nodoRyN *nRN;


#endif
