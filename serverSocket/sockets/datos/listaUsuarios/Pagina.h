#ifndef PAGINA_H
#define PAGINA_H
#include <cstddef>
#include <string>
#include "nodoUsuario.h"

using namespace std;

typedef nodoUsuario tipoClave;
class Pagina;

typedef Pagina * PPagina;

class Pagina
{
protected:
	tipoClave *claves; // puntero array de claves variables
	PPagina *ramas; // puntero array de punteros a p�ginas variable
	int cuenta; // n�mero de claves que almacena la p�gina
private:
	int m; //m�ximo n�mero de claves que puede almacenar la p�gina
public:
	// crea una p�gina vac�a de un cierto orden dado
	Pagina (int orden)
	{
		m = orden;
		claves = new nodoUsuario[orden];
		ramas = new PPagina[orden];
		for (int k = 0; k <= orden; k++)
			ramas[k] = NULL;
	}
		// decide si un nodo est� lleno
		bool nodoLLeno()
	{
		return (cuenta == m - 1);
	}
	// decide si una p�gina tiene menos de la mitad de claves
	bool nodoSemiVacio()
	{
		return (cuenta < m / 2);
	}
	
	// obtener la clave que ocupa la posici�n i en el array de claves
	tipoClave Oclave(int i){ return claves[i];}

	nodoUsuario* obtenerClave(int i){return &claves[i];}
	
	// cambiar la clave que ocupa la posici�n i en el array de claves
	void Pclave(int i, tipoClave clave){ claves[i] = clave;}
	
	// obtener la rama que ocupa la posici�n i en el array de ramas
	Pagina* Orama(int i){ return ramas[i];}
	
	// cambiar la rama que ocupa la posici�n i en el array de ramas
	void Prama(int i, Pagina * p) { ramas[i] = p;}
	
	// obtener el valor de cuenta
	int Ocuenta(){ return cuenta;}
	
	// cambiar el valor de cuenta
	void Pcuenta( int valor) { cuenta = valor;}
};
#endif

