#pragma once


#include "datos/cargarDatos.h"
#include "datos/listaSimple.h"

#include <string>
#include <WS2tcpip.h>
#pragma comment (lib, "ws2_32.lib")

class Server;

typedef void(*MessageReceivedHandler)(Server* listener, int socketId, std::string msg);

class Server {
public:

	Server(std::string ipAddr, int port, MessageReceivedHandler handler);

	~Server();
	void web_scrapping();
	void agregarArboles();
	void guardarModificado(string productoModificado);
	void guardarInsertado(string productoInsertado);
	// Metodos para los clientes del servidor
	bool login(std::string cedula, string tipo);
	std::string consultarPrecio(std::string codSuper,std::string codProducto);
	std::string consultarDescuento(std::string cedula);
	std::string consultarProductos(std::string codSuper);
	std::string comprar(string codSuper,string nombre, int cant, float precio);
	std::string verCarrito();
	void facturar();
	void descuentoExtra();
	std::string registrarse(std::string codCiudad, std::string cedula,std::string nombre, std::string telefono);
	
	// Metodos para el admin
	void insertarProducto();
	void modificarProducto();
	void consultarPrecioAdmin();
	void consultarProductosAdmin();
	void consultarDescuentosAdmin();
	void registrarCliente();
	void reportes();
	void verDatos();
	void abrirServidor();

	void cargarDatos();
	void menuAdmin();

	// Metodos para levantar el servidor
	void Send(int clientSocket, std::string msg);
	bool Init();
	void Run();
	void Cleanup();

	int tipoUsuario = 4;
	string cedulaUser;
	
	// Arboles
	Binario ciudades;
	RyN supers;
	listaDC usuarios;
	ArbolB users;
	avlTree funcionarios;
	string ultimoModificado;
	string ultimoInsertado;
private:
	SOCKET CreateSocket();
	SOCKET WaitForConnection(SOCKET listening);
	std::string my_ip;
	int my_port;
	MessageReceivedHandler message;
	lista colaUsuarios;


};