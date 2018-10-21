#include "listaCarrito.h"
#include <fstream>
#include <sstream>
#include <vector>

listaC::~listaC() {
	pnodoC aux;

	while (primero) {
		aux = primero;
		primero = primero->siguiente;
		//delete aux;
	}
	actual = NULL;
}

int listaC::largoLista() {
	int cont = 0;

	pnodoC aux;
	aux = primero;
	if (ListaVacia()) {
		return cont;
	}
	else {
		while (aux != NULL) {
			aux = aux->siguiente;
			cont++;
		}
		return cont;
	}

}

void listaC::InsertarInicio(string pNombre, int pCant, float pPrecio)
{
	if (ListaVacia())
		primero = new nodoC(pNombre, pCant, pPrecio);
	else
		primero = new nodoC(pNombre, pCant, pPrecio ,primero);
}

void listaC::InsertarFinal(string pNombre, int pCant, float pPrecio)
{
	if (ListaVacia())
		primero = new nodoC(pNombre, pCant, pPrecio);
	else
	{
		pnodoC aux = primero;
		while (aux->siguiente != NULL)
			aux = aux->siguiente;
		aux->siguiente = new nodoC(pNombre, pCant, pPrecio);
	}
}


void listaC::InsertarPos(string pNombre, int pCant, float pPrecio, int pos)
{
	if (ListaVacia())
		primero = new nodoC(pNombre, pCant, pPrecio);
	else {
		if (pos <= 1) {
			pnodoC nuevo = new nodoC(pNombre, pCant, pPrecio);
			nuevo->siguiente = primero;
			primero = nuevo;
		}
		else {
			pnodoC aux = primero;
			int i = 2;
			while ((i != pos) && (aux->siguiente != NULL)) {
				i++;
				aux = aux->siguiente;
			}
			pnodoC nuevo = new nodoC(pNombre, pCant, pPrecio);
			nuevo->siguiente = aux->siguiente;
			aux->siguiente = nuevo;

		}
	}
}

void listaC::BorrarFinal()
{
	if (ListaVacia()) {
		cout << "No hay elementos en la lista:" << endl;

	}
	else {
		if (primero->siguiente == NULL) {
			primero = NULL;
		}
		else {

			pnodoC aux = primero;
			while (aux->siguiente->siguiente != NULL) {
				aux = aux->siguiente;

			}

			pnodoC temp = aux->siguiente;
			aux->siguiente = NULL;


			delete temp;
		}
	}
}

void listaC::BorrarInicio()
{
	if (ListaVacia()) {
		cout << "No hay elementos en la lista:" << endl;

	}
	else {
		if (primero->siguiente == NULL) {
			primero = NULL;
		}
		else {

			pnodoC aux = primero;
			primero = primero->siguiente;
			delete aux;
		}
	}
}



void listaC::borrarPosicion(int pos) {
	if (ListaVacia()) {
		cout << "Lista vacia" << endl;
	}
	else {
		if ((pos > largoLista()) || (pos < 0)) {
			cout << "Error en posicion" << endl;
		}
		else {
			if (pos == 1) {
				primero = primero->siguiente;
			}
			else {
				int cont = 2;
				pnodoC aux = primero;
				while (cont < pos) {
					aux = aux->siguiente;
					cont++;
				}
				aux->siguiente = aux->siguiente->siguiente;
			}
		}
	}

}


string listaC::Mostrar()
{
	string msg = "";
	nodoC *aux;

	aux = primero;
	while (aux) {
		msg += aux->nombre + ";" + to_string(aux->cantidad) + ";" + to_string(aux->precio) + "-> ";
		aux = aux->siguiente;
	}
	return msg;
}

void listaC::Siguiente()
{
	if (actual) actual = actual->siguiente;
}

pnodoC listaC::Primero()
{
	return primero;
}

void listaC::Ultimo()
{
	actual = primero;
	if (!ListaVacia())
		while (actual->siguiente) Siguiente();
}

float listaC::calcularTotal() {
	float total = 0;
	pnodoC aux = primero;
	while (aux != NULL) {
		float totalIndividual = aux->precio * (float)aux->cantidad;
		total += totalIndividual;
		aux = aux->siguiente;
	}
	return total;
}

void listaC::facturar(string cedula,string telefono,int numFactura,int descuento,string nombre) {
	pnodoC aux = primero;
	ofstream outputFile;
	float pDescuento = ((float)descuento / 100);
	cout << endl;

	outputFile.open("facturas/Factura" + nombre + to_string(numFactura) + ".txt");
	outputFile << "Consecutivo factura: " << numFactura << endl;
	outputFile << endl;
	outputFile << "Cedula: " << cedula << endl;
	outputFile << "Nombre: " << nombre << endl;
	outputFile << "Telefono: " << telefono << endl;
	outputFile << "Codigo super: " << codSuper << endl;
	outputFile << endl;
	outputFile << "Producto | Cantidad | Precio ud. | Total" << endl;
	while (aux != NULL) {
		float total = ((float)aux->cantidad)*(aux->precio);
		outputFile << aux->nombre << " | " << aux->cantidad << " | " << aux->precio << " | " << total << endl;
		aux = aux->siguiente;
	}
	outputFile << endl;
	outputFile << "Subtotal: " << calcularTotal() << endl;
	outputFile << "Descuento: " << descuento << endl;
	outputFile << "Total: " << (calcularTotal() - (calcularTotal()*pDescuento)) << endl;
	outputFile.close();
}