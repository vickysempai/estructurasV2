#ifndef NODORYN_H
#define NODORYN_H
#include <iostream>
#include <cstddef>
#include "../AA(inventario)/ArbolAA.cpp"
using namespace std;

class nodoRyN{
public:
	nodoRyN(string ciudad, string codigo, string pNombre) {codCiudad = ciudad;codSuper = codigo;nombre = pNombre; color = 'R';cantidadSuper = 0; izquierdo = NULL; derecho = NULL; padre = NULL; }
	string codCiudad,codSuper,nombre;
	char color; //v  r = ROJO   y   n = NEGRO
	int cantidadSuper=0;
	nodoRyN *izquierdo;
	nodoRyN *derecho;
	nodoRyN *padre;
	ArbolAA* inventario = new ArbolAA;
};

typedef nodoRyN *nRN;


#endif
