#ifdef _DEBUG
#undef _DEBUG
#include <Python.h>
#define _DEBUG
#else
#include <Python.h>
#endif
#include "Server.h"
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <iostream>
#include <WS2tcpip.h>

#pragma comment (lib, "ws2_32.lib")

constexpr auto ADMIN = ("1.Insertar producto\n2.Modificar producto\n3.Consultar precio\n4.Consultar descuentos\n5.Consultar productos de un super\n6.Registrar clientes\n7.Reportes\n8.Ver datos\n9.Abrir servidor\nQue desea hacer: ");
constexpr auto VENDEDOR = ("1.Consultar precio\n2.Consultar descuento de un cliente\n3.Consultar productos de un super\n4.Cerrar sesion\nQue desea hacer: ");
constexpr auto NOREGISTRADO = ("1.Consultar precio\n2.Consultar productos\n3.Registrarse\nQue desea hacer: ");
constexpr auto CLIENTE = ("1.Consultar precio\n2.Consultar descuento\n3.Consultar productos\n4.Comprar(carrito)\n5.Ver carrito\n6.Facturacion\n7.Cerrar sesion\nQue desea hacer: ");
constexpr auto FUNCIONARIO = ("1.Consultar precio\n2.Consultar descuento\n3.Consultar productos\n4.Comprar(carrito)\n5.Ver carrito\n6.Facturacion\n7.Descuento extra(5%)\n8.Cerrar sesion\nQue desea hacer: ");
constexpr auto LOGIN = ("Cedula: ");


#define BUFFER_SIZE (4096)

using namespace std;

void messageHandler(Server* listener, int client, string msg);

Server server("127.0.0.1", 54010, messageHandler); //variable del Servidor

void messageHandler(Server* listener, int client, string msg) {
	char buf[BUFFER_SIZE];
	ZeroMemory(buf, BUFFER_SIZE);
	if (listener->tipoUsuario == 4) { // Respuestas del login
		if (msg != "0" && msg != "2" && msg != "3") {
			listener->Send(client, "Tipo invalido\nTipo:");
			return;
		}
		listener->Send(client, LOGIN);
		recv(client, buf, 4096, 0); // Recibir cedula del cliente
		string cedula = buf;
		if (server.login(cedula, msg)) {
			if (msg == "0") {
				listener->Send(client, CLIENTE);
				listener->tipoUsuario = 0;
			}
			else if (msg == "2") {
				listener->Send(client, VENDEDOR);
				listener->tipoUsuario = 2;
			}
			else if (msg == "3") {
				listener->Send(client, FUNCIONARIO);
				listener->tipoUsuario = 3;
			}
			else {
				listener->Send(client, "Respuesta invalida");
			}
		}
		else if (msg == "0") {
			listener->Send(client, NOREGISTRADO);
			listener->tipoUsuario = 5;
		}
		else
			listener->Send(client, "Usuario no encontrado\nTipo:");
	}
	else if (listener->tipoUsuario == 0) { // Respuestas del cliente
		if (msg == "1") { // Consultar precio
			listener->Send(client, "Codigo del super: ");
			recv(client, buf, 4096, 0); // Recibir codigos del cliente
			string codSuper = buf;
			listener->Send(client, "Codigo del producto: ");
			recv(client, buf, 4096, 0);
			string codigo = buf;
			listener->Send(client, server.consultarPrecio(codSuper,codigo)+"\n\n"+CLIENTE); // Enviarle el precio
		}
		else if (msg == "2") { // consultarDescuento
			listener->Send(client,server.consultarDescuento(server.cedulaUser)); // Enviarle el descuento
		}
		else if (msg == "3") { // consultarProductos
			listener->Send(client, "Codigo del super: ");
			recv(client, buf, 4096, 0); // Recibir codigo del cliente
			string codSuper = buf;
			listener->Send(client, "Productos: "+server.consultarProductos(codSuper) + "\n\n" + CLIENTE); // Enviarle la lista de productos
		}
		else if (msg == "4") { // comprar
			listener->Send(client, "Codigo del super: ");
			recv(client, buf, 4096, 0); // Recibir codigo del cliente
			string codSuper = buf;
			if (server.supers.buscar(codSuper) == NULL) {
				listener->Send(client,"Super no encontrado");
				return;
			}
			listener->Send(client, "Codigo del producto: ");
			recv(client, buf, 4096, 0);
			string codigo = buf;
			if (server.supers.buscar(codSuper)->inventario->buscar(codigo) == NULL) {
				listener->Send(client, "Producto no encotrado");
				return;
			}
			listener->Send(client, "Cantidad: ");
			recv(client, buf, 4096, 0);
			int cant = stoi(buf);
			NodoAA *prod = server.supers.buscar(codSuper)->inventario->buscar(codigo);
			if (prod->cantidad == 0) {
				listener->Send(client, "Ya no quedan");
				return;
			}
			while (prod->cantidad < cant) {
				listener->Send(client, "Solo hay " + to_string(prod->cantidad)+"\nCuantos quiere?");
				recv(client, buf, 4096, 0);
				cant = stoi(buf);
			}
			prod->cantidad -= cant;
			listener->Send(client, server.comprar(codSuper, prod->nombre, cant, prod->precioU) + "\n\n" + CLIENTE);
		}
		else if (msg == "5") { // verCarrito
			string carrito = server.verCarrito();
			if (carrito == "") {
				listener->Send(client, "El carrito esta vacio");
			}
			else {
				listener->Send(client, "Carrito: " + carrito + "\n\n" + CLIENTE);
			}
		}
		else if (msg == "6") { // facturar
			server.facturar();
			listener->Send(client, "Factura lista");
		}
		else if (msg == "7") { // Cerrar sesion
			listener->Send(client, "Tipo: ");
			listener->tipoUsuario = 4;
		}
		else {
			listener->Send(client, "Respuesta invalida");
		}
	}
	else if (listener->tipoUsuario == 2) { // Respuestas del vendedor
		if (msg == "1") { // Consultar precio
			listener->Send(client, "Codigo del super: ");
			recv(client, buf, 4096, 0); // Recibir codigos del cliente
			string codSuper = buf;
			listener->Send(client, "Codigo del producto: ");
			recv(client, buf, 4096, 0);
			string codigo = buf;
			listener->Send(client, server.consultarPrecio(codSuper, codigo) + "\n\n" + VENDEDOR); // Enviarle el precio
		}
		else if (msg == "2") {// consultarDescuento
			listener->Send(client, "Cedula: ");
			recv(client, buf, 4096, 0); // Recibir cedula del cliente
			string cedula = buf;
			listener->Send(client, server.consultarDescuento(cedula) + "\n\n" + VENDEDOR); // Enviarle el descuento
		}
		else if (msg == "3") { // Consultar productos
			listener->Send(client, "Codigo del super: ");
			recv(client, buf, 4096, 0); // Recibir codigo del cliente
			string codSuper = buf;
			listener->Send(client, "Productos: " + server.consultarProductos(codSuper) + "\n\n" + VENDEDOR); // Enviarle la lista de productos
		}
		else if (msg == "4") {
			listener->Send(client, "Tipo: ");
			listener->tipoUsuario = 4;
		}
		else {
			listener->Send(client, "Respuesta invalida");
		}
	}
	else if (listener->tipoUsuario == 5) { // Respuestas del cliente no registrado
		if (msg == "1") {// Consultar precio
			listener->Send(client, "Codigo del super: ");
			recv(client, buf, 4096, 0); // Recibir codigos del cliente
			string codSuper = buf;
			listener->Send(client, "Codigo del producto: ");
			recv(client, buf, 4096, 0);
			string codigo = buf;
			listener->Send(client, server.consultarPrecio(codSuper, codigo) + "\n\n" + NOREGISTRADO); // Enviarle el precio
			}
		else if (msg == "2") { // Consultar productos
			listener->Send(client, "Codigo del super: ");
			recv(client, buf, 4096, 0); // Recibir codigo del cliente
			string codSuper = buf;
			listener->Send(client, "Productos: " + server.consultarProductos(codSuper) + "\n\n" + NOREGISTRADO); // Enviarle la lista de productos
		}
		else if (msg == "3") { //registrarse
			listener->Send(client, "Codigo de ciudad: ");
			recv(client, buf, 4096, 0); 
			string codCiudad = buf;
			listener->Send(client, "Cedula: ");
			recv(client, buf, 4096, 0);
			string cedula = buf;
			listener->Send(client, "Nombre: ");
			recv(client, buf, 4096, 0);
			string nombre = buf;
			listener->Send(client, "Telefono: ");
			recv(client, buf, 4096, 0);
			string telefono = buf;
			listener->Send(client, server.registrarse(codCiudad,cedula,nombre,telefono) + "\n\n" + NOREGISTRADO); 
		}
		else {
			listener->Send(client, "Respuesta invalida");
		}
	}
	else {  // Respuestas del funcionario
		if (msg == "1") { // Consultar precio
			listener->Send(client, "Codigo del super: ");
			recv(client, buf, 4096, 0); // Recibir codigos del cliente
			string codSuper = buf;
			listener->Send(client, "Codigo del producto: ");
			recv(client, buf, 4096, 0);
			string codigo = buf;
			listener->Send(client, server.consultarPrecio(codSuper, codigo) + "\n\n" + FUNCIONARIO); // Enviarle el precio
		}
		else if (msg == "2") { // consultarDescuento
			listener->Send(client, server.consultarDescuento(server.cedulaUser) + "\n\n" + FUNCIONARIO); // Enviarle el descuento
		}
		else if (msg == "3") { // Consultar productos
			listener->Send(client, "Codigo del super: ");
			recv(client, buf, 4096, 0); // Recibir codigo del cliente
			string codSuper = buf;
			listener->Send(client, server.consultarProductos(codSuper) + "\n\n" + FUNCIONARIO); // Enviarle la lista de productos
		}
		else if (msg == "4") { // comprar
			listener->Send(client, "Codigo del super: ");
			recv(client, buf, 4096, 0); // Recibir codigo del cliente
			string codSuper = buf;
			if (server.supers.buscar(codSuper) == NULL) {
				listener->Send(client, "Super no encontrado");
				return;
			}
			listener->Send(client, "Codigo del producto: ");
			recv(client, buf, 4096, 0);
			string codigo = buf;
			if (server.supers.buscar(codSuper)->inventario->buscar(codigo) == NULL) {
				listener->Send(client, "Producto no encotrado");
				return;
			}
			listener->Send(client, "Cantidad: ");
			recv(client, buf, 4096, 0);
			int cant = stoi(buf);
			NodoAA *prod = server.supers.buscar(codSuper)->inventario->buscar(codigo);
			if (prod->cantidad == 0) {
				listener->Send(client, "Ya no quedan");
				return;
			}
			while (prod->cantidad < cant) {
				listener->Send(client, "Solo hay " + to_string(prod->cantidad) + "\nCuantos quiere?");
				recv(client, buf, 4096, 0);
				cant = stoi(buf);
			}
			prod->cantidad -= cant;
			listener->Send(client, server.comprar(codSuper, prod->nombre, cant, prod->precioU) + "\n\n" + FUNCIONARIO);
		}
		else if (msg == "5") { // verCarrito
			string carrito = server.verCarrito();
			if (carrito == "") {
				listener->Send(client, "El carrito esta vacio");
			}
			else {
				listener->Send(client, "Carrito: "+carrito + "\n\n" + FUNCIONARIO);
			}
		}
		else if (msg == "6") { // facturar
			server.facturar();
			listener->Send(client, "Factura lista");
		}
		else if (msg == "7") { // descuentoExtra
			server.descuentoExtra();
			listener->Send(client, "Descuento extra aplicado");
		}
		else if (msg == "8") { // Cerrar sesion
			listener->Send(client, "Tipo: ");
			listener->tipoUsuario = 4;
		}
		else {
			listener->Send(client, "Respuesta invalida");
		}
	}
}

Server::Server(std::string ipAddr, int port, MessageReceivedHandler handler) {
	my_ip = ipAddr;
	my_port = port;
	message = handler;
}

Server::~Server() {
	Cleanup();
}

void Server::agregarArboles() {
	for (int i = 0; i < 4; i++) {
		usuarios.InsertarFinal(to_string(i));
	}
	usuarios.agregarArbol(&users,&funcionarios);
}

// Enviar mensaje a un cliente
void Server::Send(int clientSocket, std::string msg) {
	send(clientSocket, msg.c_str(), msg.size() + 1, 0);
}
// Inicializar winsock
bool Server::Init() {
	WSAData data;
	WORD ver = MAKEWORD(2, 2);

	int wsInit = WSAStartup(ver, &data);
	// TODO: agarrar error

	return wsInit == 0;
}
// Ciclo principal
void Server::Run() {
	char buf[BUFFER_SIZE];
	string input;

	//while (true) {
		SOCKET listening = CreateSocket();
		if (listening == INVALID_SOCKET) {
			//break;
			return;
		}

		SOCKET client = WaitForConnection(listening);
		if (client != INVALID_SOCKET) {
			closesocket(listening);

			int bytesReceived = 0;
			do {
				ZeroMemory(buf, BUFFER_SIZE);

				bytesReceived = recv(client, buf, 4096, 0);
				if (bytesReceived > 0) {
					if (message != NULL) {
						message(this, client, std::string(buf, 0, bytesReceived));
						cout << "CLIENT> " << string(buf, 0, bytesReceived) << endl;
					}
				}
			} while (bytesReceived > 0);
			closesocket(client);
			tipoUsuario = 4;
			cout << "Cliente desconectado" << endl;
		}
	//}
}
// Limpiar winsock
void Server::Cleanup() {
	WSACleanup();
}

SOCKET Server::CreateSocket() {
	SOCKET listening = socket(AF_INET, SOCK_STREAM, 0);
	if (listening != INVALID_SOCKET) {
		sockaddr_in hint;
		hint.sin_family = AF_INET;
		hint.sin_port = htons(my_port);
		inet_pton(AF_INET, my_ip.c_str(), &hint.sin_addr);

		int bindOk = bind(listening, (sockaddr*)&hint, sizeof(hint));
		if (bindOk != SOCKET_ERROR) {
			int listenOk = listen(listening, SOMAXCONN);
			if (listenOk == SOCKET_ERROR) {
				return -1;
			}
		}
		else {
			return -1;
		}
	}
	return listening;
}

SOCKET Server::WaitForConnection(SOCKET listening) {
	sockaddr_in client;
	int clientSize = sizeof(client);
	cout << "Esperando cliente..." << endl;
	SOCKET clientSocket = accept(listening, (sockaddr*)&client, &clientSize);
	if (clientSocket == INVALID_SOCKET) {
		cerr << "No se pudo conectar el cliente" << endl;
	}

	char host[NI_MAXHOST];    // Nombre del cliente
	char service[NI_MAXSERV]; // Puerto del cliente

	ZeroMemory(host, NI_MAXHOST);
	ZeroMemory(service, NI_MAXSERV);

	if (getnameinfo((sockaddr*)&client, clientSize, host, NI_MAXHOST, service, NI_MAXSERV, 0) == 0) {
		cout << host << " conectado en el puerto " << service << endl;
	}
	else {
		inet_ntop(AF_INET, &client.sin_addr, host, NI_MAXHOST);
		cout << host << " conectado en el puerto " << ntohs(client.sin_port) << endl;
	}
	return clientSocket;
}

// metodos de los clientes
string Server::consultarPrecio(string codSuper,string codProducto) {
	if (supers.buscar(codSuper) == NULL) {
		return "Super no encontrado";
	}
	else if (supers.buscar(codSuper)->inventario->buscar(codProducto) == NULL) {
		return "Producto no encontrado";
	}
	else {
		NodoAA *prod = supers.buscar(codSuper)->inventario->buscar(codProducto);
		return "Precio de " + prod->nombre + ": " + to_string(prod->precioU);
	}
}

string Server::consultarProductos(string codSuper) {
	if (supers.buscar(codSuper) == NULL) {
		return "Super no encontrado";
	}
	else {
		string msg="";
		supers.buscar(codSuper)->inventario->toString(supers.buscar(codSuper)->inventario->raiz,msg);
		return "Productos: " + msg;

	}
}

string Server::consultarDescuento(string cedula) {
	int n = 0;
	Pagina *p = users.buscar(cedula, n);
	if (p != NULL) {
		nodoUsuario *user = p->obtenerClave(n);
		return "Descuento de " + user->nombre + ": " + to_string(user->descuento) + "%";
	}
	else {
		avl_node *user = funcionarios.obtenerUsuario(cedula);
		if (user != NULL) {
			return "Descuento de " + user->nombre + ": " + to_string(user->descuento) + "%";
		}
		else {
			return "Cliente no encontrado";
		}
	}
}

void Server::descuentoExtra() {
	avl_node *user = funcionarios.obtenerUsuario(server.cedulaUser);
	user->descuento += 10;
}

string Server::comprar(string codSuper,string nombre,int cant,float precio) {
	nodoRyN* super = server.supers.buscar(codSuper);
	if (tipoUsuario == 0) {
		int n;
		Pagina *p = users.buscar(server.cedulaUser, n);
		nodoUsuario *user = p->obtenerClave(n);
		if (user->carrito.codSuper == "")
			user->carrito.setCodSuper(codSuper);
		else if (user->carrito.codSuper != codSuper)
			return "Ese producto esta en otro super al que esta comprando";
		user->carrito.InsertarFinal(nombre, cant, precio);
		super->cantidadSuper++;
		return "Compra realizada con exito";
	}
	else {
		avl_node *user = funcionarios.obtenerUsuario(server.cedulaUser);
		user->carrito.InsertarFinal(nombre, cant, precio);
		super->cantidadSuper++;
		return "Compra realizada con exito";
	}
}

string Server::verCarrito() {
	if (tipoUsuario == 0) {
		int n;
		Pagina *p = users.buscar(server.cedulaUser, n);
		nodoUsuario *user = p->obtenerClave(n);
		return user->carrito.Mostrar();
	}
	else {
		avl_node *user = funcionarios.obtenerUsuario(server.cedulaUser);
		return user->carrito.Mostrar();
	}
}

void Server::facturar() {
	if (tipoUsuario == 0) {
		int n;
		Pagina *p = users.buscar(server.cedulaUser, n);
		nodoUsuario *user = p->obtenerClave(n);
		user->facturas++;
		int nFacturas = user->facturas;
		int suma = 0;
		while (nFacturas != 0) {
			suma += (nFacturas % 10);
			nFacturas /= 10;
		}
		if (suma != 0 && suma % 3 == 0) {
			user->descuento += 1;
		}
		user->carrito.facturar(user->cedula, user->telefono, user->facturas, user->descuento, user->nombre);
		listaC nCarrito;
		user->carrito = nCarrito;
	}
	else {
		avl_node *user = funcionarios.obtenerUsuario(server.cedulaUser);
		user->facturas++;
		int nFacturas = user->facturas;
		int suma = 0;
		while (nFacturas != 0) {
			suma += (nFacturas % 10);
			nFacturas /= 10;
		}
		if (suma != 0 && suma % 3 == 0) {
			user->descuento += 1;
		}
		user->carrito.facturar(user->cedula, user->telefono, user->facturas, user->descuento, user->nombre);
		listaC nCarrito;
		user->carrito = nCarrito;
	}
}

string Server::registrarse(string codCiudad,string cedula,string nombre,string telefono) {
	if (server.ciudades.buscar(codCiudad) ==  NULL) {
		return "Ciudad no encontrada";
	}
	int n;
	if (server.users.buscar(cedula, n) != NULL) {
		return "Ya existe un cliente con esa cedula";
	}
	else if (server.colaUsuarios.buscar(cedula)) {
		return "Ya hay un usuario con esa cedula a la espera";
	}
	else {
		server.colaUsuarios.InsertarFinal(codCiudad, cedula, nombre, telefono, "0");
		return "Usuario añadido a la cola de espera";
	}
}


// metodos del admin
void Server::cargarDatos() {
	server.agregarArboles();
	ciudades = leerCiudades("datos/archivos_txt/Ciudad.txt");
	leerArchivo(supers, ciudades, "datos/archivos_txt/supermercado.txt", 0);
	leerArchivo(supers, ciudades, "datos/archivos_txt/Inventariodatos.txt", 1);
	leerUsuarios("datos/archivos_txt/Usuarios.txt", &funcionarios, &users);
	cout << endl;
}

void Server::insertarProducto() {
	string codSuper, codigo, nombre, cantidad, precio;
	cout << "Codigo del super: ";
	getline(cin, codSuper);
	if ((supers.buscar(codSuper) == NULL)) {
		cout << "Super no encontrado" << endl;
		return;
	}
	cout << "Codigo del producto: ";
	getline(cin, codigo);
	if (((supers.buscar(codSuper)->inventario->buscar(codigo))) != NULL) {
		cout << "Ya existe un producto con ese codigo" << endl;
		return;
	}
	cout << "Nombre: ";
	getline(cin, nombre);
	cout << "Cantidad: ";
	getline(cin, cantidad);
	cout << "Precio unitario: ";
	getline(cin, precio);
	
	supers.insertarProducto(codSuper, codigo, nombre, stoi(cantidad), stof(precio));
	guardarInsertado(nombre);
	return;
}

void Server::modificarProducto() {
	string codSuper, codigo;
	cout << "Codigo del super: ";
	cin >> codSuper;
	if ((supers.buscar(codSuper) == NULL)) {
		cout << "Super no encontrado" << endl;
		return;
	}
	cout << "Codigo del producto: ";
	cin >> codigo;
	
	if (((supers.buscar(codSuper)->inventario->buscar(codigo))) != NULL) {
		string respuesta;
		cout << "Que desea modificar?" << endl;
		cout << "1.Codigo de super" << endl;
		cout << "2.Codigo del producto" << endl;
		cout << "3.Nombre" << endl;
		cout << "4.Cantidad" << endl;
		cout << "5.Precio" << endl;
		cout << "Inserte el numero de lo que quiere modificar: ";
		cin >> respuesta;

		string cambio;
		cout << "Cual es el cambio? ";
		cin >> cambio;
		NodoAA *producto = (supers.buscar(codSuper)->inventario->buscar(codigo));
		if (respuesta == "1" && (supers.buscar(cambio) == NULL)) {
			cout << "Super no encontrado" << endl;
			return;
		}
		if (respuesta == "2" && (supers.buscar(codSuper)->inventario->buscar(cambio) != NULL)) {
			cout << "Ya existe un producto con ese codigo" << endl;
			return;
		}
		guardarModificado(producto->nombre);
		switch (stoi(respuesta)) {
		case 1:
			producto->codSuper = cambio;
			break;
		case 2:
			producto->codProducto = cambio;
			break;
		case 3:
			producto->nombre = cambio;
			break;
		case 4:
			producto->cantidad = stoi(cambio);
			break;
		case 5:
			producto->precioU = stof(cambio);
			break;
		default:
			cout << "Respuesta invalida" << endl;
			break;
		}
	}
	else {
		cout << "Producto no encontrado" << endl;
	}
}

void Server::consultarPrecioAdmin() {
	string codSuper,codigo;
	cout << "Codigo del super: ";
	cin >> codSuper;
	if (supers.buscar(codSuper) == NULL) {
		cout << "Super no encontrado" << endl;
		return;
	}
	cout << "Codigo del producto: ";
	cin >> codigo;
	if (supers.buscar(codSuper)->inventario->buscar(codigo) == NULL) {
		cout << "Producto no encontrado" << endl;
	}
	else {
		NodoAA *prod = supers.buscar(codSuper)->inventario->buscar(codigo);
		cout << "Precio de " << prod->nombre << ": " << prod->precioU << endl;
	}
}

void Server::consultarProductosAdmin() {
	string codSuper;
	cout << "Codigo del super: ";
	cin >> codSuper;
	if (supers.buscar(codSuper) == NULL) {
		cout << "Super no encontrado" << endl;
		return;
	}
	else {
		cout << "Productos: ";
		supers.buscar(codSuper)->inventario->mostrar(supers.buscar(codSuper)->inventario->raiz);
		cout << endl;
	}
}

void Server::verDatos() { //incompleta
	cout << "CIUDADES: ";
	ciudades.PostordenI();
	cout << endl;
	cout << endl;
	cout << "SUPERS (con sus inventarios): ";
	supers.mostrar(supers.primeroRN);
	cout << "USUARIOS: ";
	users.inOrden(users.raiz);
	funcionarios.inorder(funcionarios.root);
	cout << endl;
}

bool Server::login(string cedula, string tipo) {
	if (tipo == "3") {
		avl_node *user = funcionarios.obtenerUsuario(cedula);
		if (user != NULL && user->cedula == cedula) {
			server.cedulaUser = user->cedula;
			return true;
		}
		return false;
	}
	else {
		int n = 0;
		Pagina *p = users.buscar(cedula, n);
		if (p != NULL) {
			nodoUsuario *user = p->obtenerClave(n);
			if (user->cedula == cedula && user->tipo == tipo) {
				server.cedulaUser = user->cedula;
				return true;
			}
		}
		return false;
	}
}

void Server::consultarDescuentosAdmin() {
	string cedula;
	cout << "Cedula: ";
	cin >> cedula;
	int n = 0;
	Pagina *p = users.buscar(cedula, n);
	if (p != NULL) {
		nodoUsuario *user = p->obtenerClave(n);
		cout << "Descuento de " << user->nombre << ": " << user->descuento << "%" << endl;
	}
	else {
		avl_node *user = funcionarios.obtenerUsuario(cedula);
		if (user != NULL) {
			cout << "Descuento de " << user->nombre << ": " << user->descuento << "%" << endl;
		}
		else {
			cout << "Cliente no encontrado" << endl;
		}
	}
}

void Server::registrarCliente() {
	if (colaUsuarios.ListaVacia()) {
		cout << "No hay usuarios en la cola de espera" << endl;
	}
	else {
		colaUsuarios.Mostrar();
		string cedula;
		cout << "Cual usuario desea registrar (cedula): ";
		cin >> cedula;
		while (!colaUsuarios.buscar(cedula)) {
			cout << "Cedula no encontrada" << endl;
			cout << "Cual usuario desea registrar (cedula): ";
			cin >> cedula;
		}
		pnodoL usuario = server.colaUsuarios.buscarNodo(cedula);
		nodoUsuario nuevo(usuario->codCiudad, usuario->cedula, usuario->nombre, usuario->telefono, "0");
		server.users.insertar(nuevo);

		server.colaUsuarios.borrarPosicion(server.colaUsuarios.buscarPosicion(cedula));
	}
}

void menuAdmin() {
	cout << ADMIN << endl;
	string msg;
	cout << "> ";
	cin >> msg;
	if (msg == "1") {
		server.insertarProducto();
	}
	else if (msg == "2") {
		server.modificarProducto();
	}
	else if (msg == "3") {
		server.consultarPrecioAdmin();
	}
	else if (msg == "4") {
		server.consultarDescuentosAdmin();
	}
	else if (msg == "5") {
		server.consultarProductosAdmin();
	}
	else if (msg == "6") {
		server.registrarCliente();
	}
	else if (msg == "7") {
		server.reportes();
	}
	else if (msg == "8") {
		server.verDatos();
	}
	else if (msg == "9") {
		cout << endl;
		if (server.Init()) {
			server.Run();
		}
	}
	else {
		cout << "Respuesta invalida" << endl;
	}
	cout << endl;
	menuAdmin();
}
void Server::web_scrapping() {

	// Para concatenar el url con el producto que se quiere buscar
	string producto = "victor\"";
	string link = "url = \"https:/\/www.ebay.com/sch/";

	string string_final = link + producto;
	const char* url_final = string_final.c_str();

	cout << url_final << endl;
	//////////////////////////////////////////////////////////////

	/////////////////////////////////////////////////////////////

	int numero = 2;
	string num_string = to_string(numero);
	string codigo = "for i in range(0," + num_string;
	string resto_codigo = codigo + "): informacion =informacion + (soup.findAll(\"img\",\"s - item__image - img\")[i]).get(\"alt\") +\";\"+ (soup.find_all(\"span\", \"ITALIC\")[i].text).replace(\" \", \"\") +\";\"+ (soup.findAll(\"img\", \"s-item__image-img\")[i]).get('src')+ \";\" + \"\\n\"";
	const char* codigo_for = resto_codigo.c_str();

	///////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////
	//Interprete Python

	Py_Initialize();

	PyRun_SimpleString("import requests");
	PyRun_SimpleString("from bs4 import BeautifulSoup");

	PyRun_SimpleString(url_final);
	PyRun_SimpleString("pagina = requests.get(url)");

	PyRun_SimpleString("soup = BeautifulSoup(pagina.content, 'html.parser')");
	PyRun_SimpleString("informacion = \"\"");

	PyRun_SimpleString("archivo = open(\"datos.txt\",\"w\", encoding='utf-8')");
	PyRun_SimpleString(codigo_for);


	PyRun_SimpleString("archivo.write(informacion)");
	PyRun_SimpleString("archivo.close()");


	//PyObject *add_module = PyImport_ImportModule("web_scapping.py");
	//PyObject *result=PyObject_CallMethod(PyImport_ImportModule("web_scapping.py"), "web_scrapping", "mesa");

	Py_Finalize();



}
void Server::guardarModificado(string productoModificado) {
	ofstream archivo;
	archivo.open("UltimoModificado.txt", ios::out);
	archivo << productoModificado << endl;
	archivo.close();
}

void Server::guardarInsertado(string productoInsertado) {
	ofstream archivo;
	archivo.open("UltimoInsertado.txt", ios::out);
	archivo << productoInsertado << endl;
	archivo.close();
}
void ingresar() {
	string cedula;
	cout << "por favor ingrese su cedula " << endl;
	cin >> cedula;
	if (server.login(cedula, "1")) {
		menuAdmin();
	}
	else {
		cout << "favor volver a intentar" << endl;
		ingresar();
	}
}
void buscarMasVisitado(nodoRyN *R, int &k, int &m, string &superk, string &superm) {
	//k es mayor
	//m es menor
	if (R == NULL) {
		return;
	}
	else {
		buscarMasVisitado(R->izquierdo, k, m, superk, superm);
		buscarMasVisitado(R->derecho, k, m, superk, superm);
		if (R->cantidadSuper > k) {
			k = R->cantidadSuper;
			superk = R->nombre;
		}
		if (R->cantidadSuper < m) {
			m = R->cantidadSuper;
			superm = R->nombre;
		}
	}
}

void clientequemascompro(Pagina * r,int h,int &k, int &m, string &superk, string &superm)//h se inicia en 1
{
	int i;
	if (r != NULL)
	{
		clientequemascompro(r->Orama(0), h + 5, k, m, superk, superm);
		for (i = 1; i <= r->Ocuenta() / 2;i++)
		{ // llamadas recursivas a la mitad de los sub�rboles
			clientequemascompro(r->Orama(i), h + 5,k,m,superk,superm);
			//cout << endl;
		}
		// visualizaci�n de las claves de la p�gina apuntada por r
		for (i = 1; i <= r->Ocuenta();i++)
		{
			for (int j = 0; j <= h; j++)
				cout << r->Oclave(i).nombre<< "  compro: "<< r->Oclave(i).vecescompra<<endl;
				if (r->Oclave(i).tipo == "0") {
					if (r->Oclave(i).vecescompra > k) {
						k = r->Oclave(i).vecescompra;
						superk = r->Oclave(i).nombre;
					}
					if (r->Oclave(i).vecescompra < m) {
						m = r->Oclave(i).vecescompra;
						superm = r->Oclave(i).nombre;
					}
				}
			//cout << r->Oclave(i).Ocedula() << endl;
		}
		// llamadas recursivas a la otra mitad de los sub�rboles
		for (i = r->Ocuenta() / 2 + 1; i <= r->Ocuenta();i++)
			clientequemascompro(r->Orama(i), h + 5, k, m, superk, superm);
		cout << endl;
	}
}

void arbolMasVendido(NodoAA* actual, int &k, int &m, string &superk, string &superm) {
	if (actual != NULL)
	{
		if (actual->masVendido > k) {
			k = actual->masVendido;
			superk = actual->nombre;
		}
		if (actual->masVendido < m) {
			m = actual->masVendido;
			superm = actual->nombre;
		}
		arbolMasVendido(actual->izquierda,k,m,superk,superm);
		arbolMasVendido(actual->derecha, k,m,superk,superm);
	}
}

void promedio(NodoAA* actual, int &k, int &m) {
	if (actual != NULL)
	{
		k += actual->precioU;
		m++;	
		promedio(actual->izquierda, k, m);
		promedio(actual->derecha, k, m);
	}
}

void llamarpromedio(nodoRyN *R, int &k, int &m) {
	//k es mayor
	//m es menor
	if (R == NULL) {
		return;
	}
	else {
		llamarpromedio(R->izquierdo, k, m);
		llamarpromedio(R->derecho, k, m);
		k = 0;
		m = 0;
		promedio(R->inventario->raiz, k, m);
		cout << "el promedio es: ";
		if (m != 0)
			cout << 0 << endl;
		else
			cout << k / m << endl;
	}
}

void MasVendido(nodoRyN *R, int &k, int &m, string &superk, string &superm) {
	//k es mayor
	//m es menor
	if (R == NULL) {
		return;
	}
	else {
		MasVendido(R->izquierdo, k, m, superk, superm);
		MasVendido(R->derecho, k, m, superk, superm);
		if (R->cantidadSuper > k) {
			k = R->cantidadSuper;
			superk = R->nombre;
		}
		if (R->cantidadSuper < m) {
			m = R->cantidadSuper;
			superm = R->nombre;
		}
		superk = R->inventario->raiz->nombre;
		superm = R->inventario->raiz->nombre;
		arbolMasVendido(R->inventario->raiz, k, m, superk, superm);
	}
}

void Server::reportes() {
	ifstream var_archivo;
	string STRING;
	cout << "ultimo modificado"<<endl;
	var_archivo.open("UltimoModificado.txt", ios::in);
	while (!var_archivo.eof()) {
		getline(var_archivo, STRING);//String contiene la linea de texto
		cout << STRING<< endl;
	}
	ifstream archivo;
	string text;

	cout << "ultimo insertado" << endl;
	archivo.open("UltimoInsertado.txt", ios::in);
	while (!archivo.eof()) {
		getline(archivo, text);//String contiene la linea de texto
		cout << text << endl;
	}
	nodoRyN* super = server.supers.primeroRN;
	int k = super->cantidadSuper;
	int m = super->cantidadSuper;
	string superk = super->nombre;
	string superm = super->nombre;
	buscarMasVisitado(super, k, m, superk, superm);
	cout << "super  mas visitado = " << superk << k<<endl;
	cout << "super  menos visitado = " << superm << m << endl;
	superk = super->inventario->raiz->nombre;
	superm = super->inventario->raiz->nombre;
	k = super->cantidadSuper;
	m = super->cantidadSuper;
	MasVendido(super, k, m, superk, superm);
	k = server.users.raiz->Oclave(0).vecescompra;
	m = server.users.raiz->Oclave(0).vecescompra;
	superk = server.users.raiz->Oclave(0).nombre;
	superm = server.users.raiz->Oclave(0).nombre;
	clientequemascompro(server.users.raiz,1,k,m,superk,superm);
	cout << "cliente que mas compro = " << superk << k << endl;
	cout << "cliente que menos compro = " << superm << m << endl;
	k = 0;
	m = 0;
	llamarpromedio(super, k, m);
}

int main() {
	server.cargarDatos();
	//server.comprar("1024", "NES Classic Edition", 2, 1278);
	ingresar();
	cin.get();
	return 0;
}
