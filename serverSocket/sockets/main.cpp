#include <iostream>
#include "Server.h"

constexpr auto LOGIN = ("Bienvenido al super\nQue tipo de usuario es(0-1-2-3): ");
constexpr auto VENDEDOR = ("1.Consultar precio\n2.Consultar descuento de un cliente\n3.Consultar productos de un super\n4.Cerrar sesion\nQue desea hacer: ");
constexpr auto CLIENTE = ("1.Consultar precio\n2.Consultar descuento\n3.Consultar productos\n4.Comprar(carrito)\n5.Ver carrito\n6.Facturacion\n7.Cerrar sesion\nQue desea hacer: ");
constexpr auto FUNCIONARIO = ("1.Consultar precio\n2.Consultar descuento\n3.Consultar productos\n4.Comprar(carrito)\n5.Ver carrito\n6.Facturacion\n7.Descuento extra(5%)\n8.Cerrar sesion\nQue desea hacer: ");

#include <string>
#pragma comment (lib, "ws2_32.lib")

using namespace std;