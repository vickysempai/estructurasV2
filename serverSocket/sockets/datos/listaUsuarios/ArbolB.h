#ifndef ARBOLB_H
#define ARBOLB_H

#include <iostream>
#include "Pagina.h"
#include <string>
#include <cstddef>
using namespace std;

class ArbolB
{
protected:
	int orden;
public:
	Pagina *raiz;
	ArbolB()
	{
		orden = 5;
		raiz = NULL;
	};
	ArbolB(int m)
	{
		orden = m;
		raiz = NULL;
	}
	bool arbolBvacio()
	{
		return raiz == NULL;
	}
	Pagina * Oraiz(){ return raiz;}
	void Praiz( Pagina * r){ raiz = r;}
	int Oorden(){ return orden;}
	void Porden(int ord){ orden = ord;}
	void crear() { orden = 4; raiz = NULL;}
	void eliminar(tipoClave cl);
	bool buscarNodo(Pagina* actual, string &cl, int & k);
	Pagina* buscar( string &cl, int &n);
	Pagina* buscar(Pagina* actual, string &cl, int &n);
	void insertar(tipoClave& cl);
	Pagina* insertar(Pagina* raiz, tipoClave& cl);
	bool empujar(Pagina* actual, tipoClave& cl,tipoClave &mediana, Pagina *& nuevo);
	void meterPagina(Pagina* actual, tipoClave& cl,Pagina *ramaDr, int k);
	void dividirNodo(Pagina* actual, tipoClave &mediana, Pagina * &nuevo, int pos);
	void escribir();
	void escribir(Pagina* r, int h);
	void listarCreciente();
	void inOrden(Pagina *r);
	
	
};
		
#endif

