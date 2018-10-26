#ifndef NODOUSUARIO_H
#define NODOUSUARIO_H
#include <iostream>
#include <string>
#include <cstddef>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <stdio.h>
#include <cstring>
#include "listaCarrito.h"
using namespace std;

class nodoUsuario{
public:
	nodoUsuario(){NULL;}
	nodoUsuario(string cc,string ced,string nomb,string tel,string tip){codCiudad = cc;cedula = ced;nombre = nomb;telefono = tel;tipo=tip;}
			
	string codCiudad,cedula,nombre,telefono,tipo;
	int facturas = 0;
	int descuento = 5;
	int vecescompra=0;
	listaC carrito;
	
	// obtener codigo de ciudad
	string OcodCiudad(){ return codCiudad;}
	
	// obtener cedula
	string Ocedula(){ return cedula;}
	
	// obtener nombre
	string Onombre(){ return nombre;}
	
	// obtener nombre
	string Otelefono(){ return telefono;}
	
};
#endif /*NODOUSUARIO_H*/
