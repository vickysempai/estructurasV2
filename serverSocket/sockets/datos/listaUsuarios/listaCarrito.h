#ifndef LISTACARRITO_H
#define LISTACARRITO_H

#include <iostream>
#include <string>
#include "nodoCarrito.h"

class listaC {
	public:
		listaC() { primero = actual = NULL; }
		~listaC();

	void InsertarInicio(string pNombre, int pCant, float pPrecio);
	void InsertarFinal(string pNombre, int pCant, float pPrecio);
	void InsertarPos(string pNombre, int pCant, float pPrecio, int pos);
	bool ListaVacia() { return primero == NULL; }
	string Mostrar();
	void Siguiente();
	pnodoC Primero();
	void Ultimo();
	void BorrarFinal();
	void BorrarInicio();
	void borrarPosicion(int pos);
	int largoLista();
	float calcularTotal();
	void facturar(string cedula,string telefono,int numFactura,int descuento,string nombre);

	void setCodSuper(string pCodSuper) {
		codSuper = pCodSuper;
	}

	string codSuper = "";

	private:
		pnodoC primero;
		pnodoC actual;
};

#endif