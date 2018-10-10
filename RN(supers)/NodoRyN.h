#ifndef NODORYN_H
#define NODORYN_H
#include <iostream>
#include <cstddef>
#include "../AA(inventario)/ArbolAA.cpp"
using namespace std;

class nodoRyN{
public:
	nodoRyN(string ciudad,string codigo,string pNombre){codCiudad = ciudad;codSuper = codigo;nombre = pNombre; color = 'R'; izquierdo = NULL; derecho = NULL; padre = NULL;}
	string codCiudad,codSuper,nombre;
	char color; // r = ROJO   y   n = NEGRO
	nodoRyN *izquierdo;
	nodoRyN *derecho;
	nodoRyN *padre;
	ArbolAA* inventario = new ArbolAA;
};

typedef nodoRyN *nRN;


#endif
