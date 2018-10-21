#ifndef LISTADC_H
#define LISTADC_H

#include <iostream>
#include <string>
#include <cstddef>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <stdio.h>
#include <cstring>
#include "nodo.h"
using namespace std;
typedef nodo *pnodoDC;
class listaDC {
public:
	listaDC() { primero = actual = NULL; }
	
	void InsertarInicio(string v);
	void InsertarFinal(string v);
	void InsertarPos (string v, int pos);
	void EliminarInicio();
	void EliminarFinal();
	void EliminarPos(int pos);
	bool ListaVacia() { return primero == NULL; } 
	void Imprimir();
	void Borrar(int v);
	void Mostrar();
	void Siguiente();
	void Primero();
	void Ultimo();
	void BorrarFinal();
	void BorrarInicio();
	void borrarPosicion(int pos);
	int largoLista();
	void agregarArbol(ArbolB *b,avlTree *a);
	
	pnodoDC primero;
	pnodoDC actual;
};
#endif
