#include <cstdlib>
#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <stdlib.h>
#include <stdio.h>

using namespace std;

class nodo
{
    public:
        int cont, nivel, codigo;
        string sinonimo;
        nodo *derecha;
        nodo *izquierda;
        nodo *padre;
        nodo *raiz;
}*raiz;

/*
 * Declaracion de clase
 */
class ArbolAA
{
    public:
        int insertar(int cod, string sinn);
        void giro(nodo *);
        bool Vacio(nodo *r){return r == NULL;}
        bool reparto(nodo *);
        void rebalancear(nodo *);
        nodo *insertarAux(nodo *,nodo *);
        nodo *buscar(int c);
        int contnodo(nodo *);
        ArbolAA()
    {
            raiz = NULL;
        }
};


class nodoRyN{
public:
        nodoRyN(){llave = 0; color = 'R'; izquierdo = NULL; derecho = NULL; padre = NULL;}
        int llave;
        string definicion;
        char color; // r = ROJO   y   n = NEGRO
        nodoRyN *izquierdo;
        nodoRyN *derecho;
        nodoRyN *padre;
};

typedef nodoRyN *nRN;

class RyN
{
    public:
        nodoRyN *primeroRN;
        void insercion(int key, string definicion); // para insertar un numero en el arbol
        void solucionarRojoRojo(nodoRyN *node, int h); // para solucionar un hijo rojo en un nodo rojo
        void liberar(nodoRyN *node); // para liberar la memoria cuando desea salir del programa
        void mostrar(nodoRyN * actual,int indent); // muestra el padre e hijos del numero insertado y tambien el color del nodo
        nodoRyN *buscar(int key) // para buscar un numero en el arbol
        {
            nodoRyN *ayudante;
            ayudante = primeroRN;
            if (!ayudante)
                return NULL;
            do
            {
                if (key == ayudante->llave)
                    return ayudante;
                else if (key < ayudante->llave)
                    ayudante = ayudante->izquierdo;
                else if (key > ayudante->llave)
                    ayudante = ayudante->derecho;
            }
            while (ayudante);
                return NULL;
        }

};


class nodoAVL{
public:
    string palabra;
    int codPalabra;
    int FE;
    nodoAVL *izquierdo;
    nodoAVL *derecho;
    nodoAVL *padre;
    nodoRyN *def;
    nodo *sin;
    nodoAVL(string p, int c){
        palabra = p;
        codPalabra = c;
        FE = 0;
        izquierdo = NULL;
        derecho = NULL;
        padre = NULL;
        def = NULL;
        sin = NULL;
    }
    friend class AAVL;
};

typedef nodoAVL *nal;

class AAVL{
public:
    nal raiz;
    nal actual;
    int cont;
    int altura;
    AAVL(){
        raiz = NULL;
        actual  = NULL;
    }
    void Insertar(string p, int c);
    bool Vacio(nal r){return r == NULL;}
    bool esta(int c);
    bool esta(string c);
    bool hoja(nal r){return !r->derecho && !r->izquierdo;}
    nal buscar(int c);
    nal buscar(string p);
    void equilibrar(nal n, string x, bool r);
    void RSI(nal n);
    void RSD(nal n);
    void RDI(nal n);
    void RDD(nal n);
    void InOrden(nal r);
    void PreOrden(nal r);
    void PosOrden(nal r);
};

typedef AAVL *AVL;

class nodoABB{
public:
    string letra;
    int codLetra;
    nodoABB *izquierdo;
    nodoABB *derecho;
    nodoAVL *ArbolAVL;
    nodoABB(string le, int c){
        letra = le;
        codLetra = c;
        izquierdo = NULL;
        derecho = NULL;
        ArbolAVL = NULL;
    }
    void *InsertarNodo(string le, int c);
    friend class ABin;
};

typedef nodoABB *nabb;

class ABin{
public:
    nabb raiz;
    ABin(){raiz = NULL;}
    bool Vacio(){return raiz == NULL;}
    void Insertar(string l, int c);
    bool esta(int c);
    bool esta(string c);
    nabb buscar(int c);
    nabb buscar(string l);
    void InOrden(nabb r);
    void PreOrden(nabb r);
    void PosOrden(nabb r);
};

typedef ABin *ABB;

////////////////////////////////////////////////////////////////////

void RyN::insercion(int key, string def)
{
    int ladohijo;
    nodoRyN *hijo;
    nodoRyN *ayudante;
    int bandera;
    if(primeroRN==NULL)
    {
        primeroRN = new nodoRyN();
        primeroRN->llave = key;
        primeroRN->definicion = def;
        primeroRN->padre = NULL;
        primeroRN->izquierdo = NULL;
        primeroRN->derecho = NULL;
        primeroRN->color = 'N';
    }
    else
    {
        hijo = new nodoRyN();
        hijo->llave = key;
        hijo->definicion = def;
        hijo->padre = NULL;
        hijo->izquierdo = NULL;
        hijo->derecho = NULL;
        hijo->color = 'R';
        ayudante=primeroRN;
        do
        {
            hijo->padre = ayudante, bandera = 1;
            if (key<ayudante->llave)
            {
                if (ayudante->izquierdo)
                    ayudante = ayudante->izquierdo;
                else
                    ayudante->izquierdo = hijo, bandera = 0, ladohijo = 1;
            }
            else
            {
                if (ayudante->derecho)
                    ayudante = ayudante->derecho;
                else
                    ayudante->derecho = hijo, bandera = 0, ladohijo = 2;
            }
        }
        while (bandera == 1);
            if (ayudante->color == 'R')
                solucionarRojoRojo(ayudante, ladohijo);
    }
}

void RyN::solucionarRojoRojo(nodoRyN *node, int h)
{
    int ladohijo;
    nodoRyN *abuelo;
    nodoRyN *tio;
    nodoRyN *ayudante;
    abuelo = node->padre;
    if (abuelo->izquierdo && abuelo->derecho)
    {
        if (node == abuelo->izquierdo)
            tio = abuelo->derecho;
        else
            tio = abuelo->izquierdo;

        if (tio->color =='R')
        {
            tio->color = 'N';
            node->color = 'N';
            if (abuelo != primeroRN)
                abuelo->color = 'R';
            if (abuelo->padre)
            {
                ayudante = abuelo->padre;
                if (ayudante->izquierdo == abuelo)
                    ladohijo = 1;
                else
                    ladohijo = 2;
                if (ayudante->color == 'R')
                    solucionarRojoRojo(ayudante, ladohijo);
            }
            return;
        }
    }
    if (h == 1 && abuelo->izquierdo == node)
    {
        node->color = 'N', abuelo->color = 'R';
        ayudante = node->derecho, node ->derecho = abuelo, node->padre = abuelo->padre;
        abuelo->padre = node, abuelo->izquierdo = ayudante;
        if (ayudante)
            ayudante->padre = abuelo;
        if (node->padre)
        {
            ayudante = node->padre;
            if (ayudante->izquierdo == node->derecho)
                ayudante->izquierdo = node;
            else
                ayudante->derecho = node;
        }
        else
            primeroRN = node;
    }
    else if (h == 2 && abuelo->derecho == node)
    {
        node->color = 'N', abuelo->color = 'R';
        ayudante = node->izquierdo, node->izquierdo = abuelo, node->padre = abuelo->padre;
        abuelo->padre = node, abuelo->derecho = ayudante;
        if (ayudante)
            ayudante->padre = abuelo;
        if (node->padre)
        {
            ayudante = node->padre;
            if (ayudante->izquierdo == node->izquierdo)
                ayudante->izquierdo = node;
            else
                ayudante->derecho = node;
        }
        else
            primeroRN = node;
    }
    else if (h == 2 && abuelo->izquierdo == node)
    {
        tio = node->derecho, ayudante = tio->izquierdo, abuelo->izquierdo = tio;
        tio->padre = abuelo, tio->izquierdo = node, node->padre = tio;
        node->derecho = ayudante;
        if (ayudante)
            ayudante->padre = node;
        solucionarRojoRojo(tio, 1);
    }
    else if (h==1 && (abuelo->derecho = node))
    {
        tio = node->izquierdo, ayudante = tio->derecho, abuelo->derecho = tio;
        tio->padre = abuelo, tio->derecho = node, node->padre = tio;
        node->izquierdo = ayudante;
        if (ayudante)
            ayudante->padre = node;
        solucionarRojoRojo(tio, 2);
    }
}

void RyN::liberar(nodoRyN *node)
{
    if (node)
    {
        if (node->izquierdo)
            liberar(node->izquierdo);
        if (node->derecho)
            liberar(node->derecho);
        delete node;
    }
}


void RyN::mostrar(nodoRyN* actual,int indent)
{
    if (actual != NULL)
    {
        mostrar(actual->derecho, indent + 4);
        if (indent > 0)
            cout << indent << " ";
        cout << actual->llave << "|" <<actual->color << endl;
        mostrar(actual->izquierdo, indent + 4);
    }
}


void *nodoABB::InsertarNodo(string le, int c){
    if(c < codLetra){
        if(izquierdo == NULL){
            izquierdo = new nodoABB(le, c);
        }
        else{
            izquierdo->InsertarNodo(le, c);
        }
    }
    else{
        if(derecho == NULL){
            derecho = new nodoABB(le, c);
        }
        else{
            derecho->InsertarNodo(le, c);
        }
    }
}

void ABin::Insertar(string l, int c){
    if(Vacio()){
        raiz = new nodoABB(l, c);
    }
    else{
        raiz->InsertarNodo(l, c);
    }
}

bool ABin::esta(int c){
    if(Vacio()){
        return false;
    }
    else{
        nabb aux = raiz;
        while(aux != NULL){
            if(aux->codLetra == c){
                return true;
            }
            else if(c > aux->codLetra){
                aux = aux->derecho;
            }
            else if(c < aux->codLetra){
                aux = aux->izquierdo;
            }
        }
        return false;
    }
}
bool ABin::esta(string c){
    if(Vacio()){
        return false;
    }
    else{
        nabb aux = raiz;
        while(aux != NULL){
            if(aux->letra == c){
                return true;
            }
            else if(c > aux->letra){
                aux = aux->derecho;
            }
            else if(c < aux->letra){
                aux = aux->izquierdo;
            }
        }
        return false;
    }
}

nabb ABin::buscar(int c){
    if(Vacio()){
        return NULL;
    }
    else{
        nabb aux = raiz;
        while(aux != NULL){
            if(aux->codLetra == c){
                return aux;
            }
            else if(c > aux->codLetra){
                aux = aux->derecho;
            }
            else if(c < aux->codLetra){
                aux = aux->izquierdo;
            }
        }
        return NULL;
    }
}


nabb ABin::buscar(string l){
    if(Vacio()){
        return NULL;
    }
    else{
        nabb aux = raiz;
        while(aux != NULL){
            if(aux->letra == l){
                return aux;
            }
            else /*if(l > aux->letra)*/{
                aux = aux->derecho;
            }
            /*else if(l < aux->letra){
                aux = aux->izquierdo;
            }*/
        }
        return NULL;
    }
}

void ABin::PreOrden(nabb r){
    if(r == NULL){
        return;
    }
    else{
        cout << r->codLetra << "-> " << r->letra;
        PreOrden(r->izquierdo);
        PreOrden(r->derecho);
    }
}

void ABin::InOrden(nabb r){
    if(r == NULL){
        return;
    }
    else{
        PreOrden(r->izquierdo);
        cout << r->codLetra << "-> " << r->letra;
        PreOrden(r->derecho);
    }
}

void ABin::PosOrden(nabb r){
    if(r == NULL){
        return;
    }
    else{
        PreOrden(r->izquierdo);
        PreOrden(r->derecho);
        cout << r->codLetra << "-> " << r->letra;
    }
}
////////////////////////////////////////////////////////////////////
void AAVL::Insertar(string p, int c){
    nal padre = NULL;
    actual = raiz;
    while(!Vacio(actual) && c != actual->codPalabra){
        padre = actual;
        if(c > actual->codPalabra){
            actual  = actual->derecho;
        }
        else if(c < actual->codPalabra){
            actual  = actual->izquierdo;
        }
    }
    if(!Vacio(actual)){
        return;
    }
    if(Vacio(padre)){
        raiz = new nodoAVL(p, c);
    }
    else if(c < padre->codPalabra){
        padre->izquierdo = new nodoAVL(p, c);
        padre->izquierdo->padre = padre;
        equilibrar(padre, "izquierdo", true);
    }
    else if(c > padre->codPalabra){
        padre->derecho = new nodoAVL(p, c);
        padre->derecho->padre = padre;
        equilibrar(padre, "derecho", true);
    }
}

void AAVL::equilibrar(nal n, string x, bool r){
    bool salir = false;
    while(n && !salir){
        if(r){
            if(x == "izquierdo"){
                n->FE--;
            }
            else{
                n->FE++;
            }
        }
        else{
            if(x == "izquierdo"){
                n->FE++;
            }
            else{
                n->FE--;
            }
        }
        if(n->FE == 0){
            salir = true;
        }
        else if(n->FE == -2){
            if(n->izquierdo->FE == 1){
                RDD(n);
            }
            else{
                RSD(n);
            }
            salir = true;
        }
        else if(n->FE == 2){
            if(n->derecho->FE == -1){
                RDI(n);
            }
            else{
                RSI(n);
            }
            salir = true;
        }
        if(n->padre){
            if(n->padre->derecho == n){
                x = "derecho";
            }
            else{
                x = "izquierdo";
            }
        }
        n = n->padre;
    }
}

void AAVL::RDD(nal n){
    nal padre = n->padre;
    nal P = n;
    nal Q = P->izquierdo;
    nal R = Q->derecho;
    nal B = R->izquierdo;
    nal C = R->derecho;
    if(padre){
        if(padre->derecho == n){
            padre->derecho = R;
        }
        else{
            padre->izquierdo = R;
        }
    }
    else{
        raiz = R;
    }
    Q->derecho = B;
    P->izquierdo = C;
    R->izquierdo = Q;
    R->derecho = P;
    R->padre = padre;
    P->padre = Q->padre = R;
    if(B){
        B->padre = Q;
    }
    if(C){
        C->padre = P;
    }
    switch(R->FE){
    case -1:
        Q->FE = 0;
        P->FE = 1;
        break;
    case 0:
        Q->FE = 0;
        P->FE = 0;
        break;
    case 1:
        Q->FE = -1;
        P->FE = 0;
        break;
    }
    R->FE = 0;
}

void AAVL::RDI(nal n){
    nal padre = n->padre;
    nal P = n;
    nal Q = P->derecho;
    nal R = Q->izquierdo;
    nal B = R->izquierdo;
    nal C = R->izquierdo;
    if(padre){
        if(padre->derecho == n){
            padre->derecho = R;
        }
        else{
            padre->izquierdo = R;
        }
    }
    else{
        raiz = R;
    }
    P->derecho = B;
    Q->izquierdo = C;
    R->izquierdo = P;
    R->derecho = Q;
    R->padre = padre;
    P->padre = Q->padre = R;
    if(B){
        B->padre = P;
    }
    if(C){
        C->padre = Q;
    }
    switch (R->FE) {
    case -1:
        P->FE = 0;
        Q->FE = 1;
        break;
    case 0:
        P->FE = 0;
        Q->FE = 0;
        break;
    case 1:
        P->FE = -1;
        Q->FE = 0;
        break;
    }
    R->FE = 0;
}

void AAVL::RSD(nal n){
    nal padre = n->padre;
    nal P = n;
    nal Q = P->izquierdo;
    nal B = Q->derecho;
    if(padre){
        if(padre->derecho == P){
            padre->derecho = Q;
        }
        else{
            padre->izquierdo = Q;
        }
    }
    else{
        raiz = Q;
    }
    P->izquierdo = B;
    Q->derecho = P;
    P->padre = Q;
    if(B){
        B->padre = P;
    }
    Q->padre = padre;
    P->FE = 0;
    Q->FE = 0;
}

void AAVL::RSI(nal n){
    nal padre = n->padre;
    nal P = n;
    nal Q = P->derecho;
    nal B = Q->izquierdo;
    if(padre){
        if(padre->derecho == P){
            padre->derecho = Q;
        }
        else{
            padre->izquierdo = Q;
        }
    }
    else{
        raiz = Q;
    }
    P->derecho = B;
    Q->izquierdo = P;
    P->padre = Q;
    if(B){
        B->padre = P;
    }
    Q->padre = padre;
    P->FE = 0;
    Q->FE = 0;
}

bool AAVL::esta(int c){
    actual = raiz;
    while(!Vacio(actual)){
        if(c == actual->codPalabra){
            return true;
        }
        else if(c > actual->codPalabra){
            actual = actual->derecho;
        }
        else if(c < actual->codPalabra){
            actual = actual->izquierdo;
        }
    }
    return false;
}

bool AAVL::esta(string c){
    actual = raiz;
    while(!Vacio(actual)){
        if(c == actual->palabra){
            return true;
        }
        else if(c > actual->palabra){
            actual = actual->derecho;
        }
        else if(c < actual->palabra){
            actual = actual->izquierdo;
        }
    }
    return false;
}

nal AAVL::buscar(int c){
    actual = raiz;
    while(!Vacio(actual)){
        if(c == actual->codPalabra){
            return actual;
        }
        else if(c > actual->codPalabra){
            actual = actual->derecho;
        }
        else if(c < actual->codPalabra){
            actual = actual->izquierdo;
        }
    }
    return NULL;
}

nal AAVL::buscar(string p){
    actual = raiz;
    while(!Vacio(actual)){
        if(p == actual->palabra){
            return actual;
        }
        else if(p > actual->palabra){
            actual = actual->derecho;
        }
        else if(p < actual->palabra){
            actual = actual->izquierdo;
        }
    }
    return NULL;
}

void AAVL::PreOrden(nal r){
    if(r == NULL){
        return;
    }
    else{
        cout << r->codPalabra << "-> " << r->palabra;
        PreOrden(r->izquierdo);
        PreOrden(r->derecho);
    }
}

void AAVL::InOrden(nal r){
    if(r == NULL){
        return;
    }
    else{
        PreOrden(r->izquierdo);
        cout << r->codPalabra << "-> " << r->palabra;
        PreOrden(r->derecho);
    }
}

void AAVL::PosOrden(nal r){
    if(r == NULL){
        return;
    }
    else{
        PreOrden(r->izquierdo);
        PreOrden(r->derecho);
        cout << r->codPalabra << "-> " << r->palabra;
    }
}

//////////////////////////////////////////////

void ArbolAA::giro(nodo *temp)
{
    nodo *ptr = temp->izquierda;
    if (temp->padre->izquierda == temp)
        temp->padre->izquierda = ptr;
    else
        temp->padre->derecha = ptr;
    ptr->padre = temp->padre;
    temp->padre = ptr;
    temp->izquierda = ptr->derecha;
    if (temp->izquierda != NULL)
        temp->izquierda->padre = temp;
    ptr->derecha = temp;
    temp->nivel = (temp->izquierda ? temp->izquierda->nivel + 1 : 1);
}

/*
 * Reparto del arbol
 */
bool ArbolAA::reparto(nodo *temp)
{
    nodo* ptr = temp->derecha;
    if (ptr && ptr->derecha && (ptr->derecha->nivel == temp->nivel))
    {
        if (temp->padre->izquierda == temp)
            temp->padre->izquierda = ptr;
        else
            temp->padre->derecha = ptr;
        ptr->padre = temp->padre;
        temp->padre = ptr;
        temp->derecha = ptr->izquierda;
        if (temp->derecha != NULL)
            temp->derecha->padre = temp;
        ptr->izquierda = temp;
        ptr->nivel = temp->nivel + 1;
        return true;
    }
    return false;
}

/*
 * Rebalancear el arbol
 */
void ArbolAA::rebalancear(nodo* temp)
{
    temp->izquierda = NULL;
    temp->derecha = NULL;
    temp->nivel = 1;
    for (temp = temp->padre; temp != raiz; temp = temp->padre)
    {
        if (temp->nivel != (temp->izquierda ? temp->izquierda->nivel + 1 : 1 ))
        {
            giro(temp);
            if (temp->derecha == NULL)
                temp = temp->padre;
            else if (temp->nivel != temp->derecha->nivel)
                temp = temp->padre;
        }
        if (temp->padre != raiz)
        {
            if (reparto(temp->padre) == false)
                break;
        }
    }
}

/*
 * Funcion para insertar en el arbol
 */
int ArbolAA::insertar(int cod, string sinn)
{
    nodo *temp = new nodo;
    temp->codigo = cod;
    temp->sinonimo = sinn;
    temp->nivel = 1;
    temp->cont = 0;
    temp->izquierda = NULL;
    temp->derecha = NULL;
    temp->padre = NULL;
    temp = insertarAux(raiz, temp);
    return temp->cont;
}

/*
 * Funcion auxiliar para insertar en el arbol
 */
nodo* ArbolAA::insertarAux(nodo* temp, nodo* aux)
{
    if (raiz == NULL)
    {
        aux->cont = 1;
        aux->padre = NULL;
        aux->izquierda = NULL;
        aux->derecha = NULL;
        raiz = aux;
        return raiz;
    }
    if (aux->codigo > temp->codigo)
    {
        if (temp->izquierda)
            return insertarAux(temp->izquierda, aux);
        temp->izquierda = aux;
        aux->padre = temp;
        aux->cont = 1;
        rebalancear(aux);
        return aux;
    }
    if (aux->codigo > temp->codigo)
    {
        if (temp->derecha)
            return insertarAux(temp->derecha, aux);
        temp->derecha = aux;
        aux->padre = temp;
        aux->cont = 1;
        rebalancear(aux);
        return aux;
    }
    temp->cont++;
    delete aux;
    return temp;
}
/*
 * Contador del numero de nodos del arbol
 */
int ArbolAA::contnodo(nodo* temp)
{
    if (!temp)
        return 0;
    int cont = 1;
    cont = cont + contnodo(temp->izquierda);
    cont = cont + contnodo(temp->derecha);
    return cont;
}

nodo *ArbolAA::buscar(int c){
    nodo *actual = raiz;
    while(!Vacio(actual)){
        if(c == actual->codigo){
            return actual;
        }
        else if(c > actual->codigo){
            actual = actual->derecha;
        }
        else if(c < actual->codigo){
            actual = actual->izquierda;
        }
    }
    return NULL;
}

///////////////////////////////////

int main(int argc, char *argv[])
{
	ABin arbol;
	nabb aux;
	char caracter;
    string ch2="";
    int numero=0;
    const char * cadena;
	ifstream doc("Ciudades.txt");

   if (doc.is_open())
  	{
	    while ( doc>> noskipws>>caracter)
	    {
	    	
	    	if(caracter!=59 &&caracter!=10)
	    	{
	    		string ch(1,caracter);
		    	ch2+=ch;
			}
			else if(numero==0)
			{
				cadena = ch2.c_str();
				numero=atoi(cadena);
				ch2="";
			}
	    	else
	    	{		
	    		if(!(arbol.esta(numero))&&!(arbol.esta(ch2)))
	    		{
		    		arbol.Insertar(ch2, numero);
		    		cout<<numero<<endl<<ch2<<endl;
		    		
		    	}
		    	else
		    		cout<<"***ERROR:Ciudad repetida***"<<endl;
		    	numero=0;
		    	ch2="";
		    	cadena=NULL;
	    	}
	    }
	    aux=arbol.raiz;
	    arbol.PreOrden(aux);
	    
	    cout<<endl;
	    
		
		cout<<"------------------------------------------------------------------"<<endl<<endl;
    doc.close();
    
	}
	else cout << "No se pudo abrir el documento"<<endl;
//----------------------------------------AVL-------------------------------------------------------------
   ifstream doc2("Cadenas.txt");
	int Cciudad=0;
	int Ccadena=0;
   if (doc2.is_open())
  	{
	    while ( doc2>> noskipws>>caracter)
	    {
	    	if((Ccadena!=0&&Cciudad!=0&&caracter!=10)||(caracter!=59 &&caracter!=10))
	    	{
	    		string ch(1,caracter);
		    	ch2+=ch;
			}
			else if(Cciudad==0)
			{
				cadena = ch2.c_str();
				Cciudad=atoi(cadena);
				//cout<<"ciudad: "<<Cciudad<<endl;
				ch2="";
			}
			else if(Ccadena==0)
			{
				cadena = ch2.c_str();
				Ccadena=atoi(cadena);
				//cout<<"Cadena: "<<Ccadena<<endl;
				ch2="";
			}
	    	else
	    	{	
	    		if(arbol.buscar(Cciudad)==NULL)
	    		{
	    			cout<<"***ERROR:Ciudad no encontrada, revise el archivo de ciudades***"<<endl;
				}
				else
				{
					
					AAVL arbol2;
					nal aux;
									
					aux=arbol.buscar(Cciudad)->ArbolAVL;
					arbol2.raiz=aux;
				    
					if(arbol2.esta(Ccadena) ||arbol2.esta(ch2))
					{
						cout<<"***ERROR:Cadena repetida***"<<endl;
					}
					else
					{
						arbol2.Insertar(ch2,Ccadena);
						arbol.buscar(Cciudad)->ArbolAVL=arbol2.raiz;
						cout<<"info: "<<ch2<<endl;
					}
					Ccadena=0;
		    		Cciudad=0;
		    		ch2="";
		    		cadena=NULL;
		    		
		    	}
		    		
	    	}
	    } 
	    cout<<endl;
	    //Cciudad=4;
	    //cout<<arbol.buscar(Cciudad)->ArbolAVL->derecho->codPalabra<<endl;
		cout<<"------------------------------------------------------------------"<<endl<<endl;
    doc2.close();
    
	}
	else cout << "No se pudo abrir el documento"<<endl;
	
//----------------------------------------RyN-------------------------------------------------------------
   ifstream doc3("Productos.txt");
	Cciudad=0;
	Ccadena=0;
	ch2="";
	int Cproducto=0;
   if (doc3.is_open())
  	{
	    while ( doc3>> noskipws>>caracter)
	    {
	    	if((Ccadena!=0&&Cciudad!=0&&Cproducto!=0&&caracter!=10)||(caracter!=59 &&caracter!=10))
	    	{
	    		//cout<<caracter<<endl;
	    		string ch(1,caracter);
		    	ch2+=ch;
			}
			else if(Cciudad==0)
			{
				cadena = ch2.c_str();
				Cciudad=atoi(cadena);
				//cout<<"ciudad: "<<Cciudad<<endl;
				ch2="";
			}
			else if(Ccadena==0)
			{
				cadena = ch2.c_str();
				Ccadena=atoi(cadena);
				//cout<<"Cadena: "<<Ccadena<<endl;
				ch2="";
			}
			else if(Cproducto==0)
			{
				cadena = ch2.c_str();
				Cproducto=atoi(cadena);
				//cout<<"Producto: "<<Cproducto<<endl;
				ch2="";
			}
	    	else
	    	{	
	    		if(!arbol.esta(Cciudad))
	    		{
	    			cout<<"***ERROR:Ciudad no encontrada, revise el archivo de ciudades***"<<endl;
	    			
				}
				else
				{
					AAVL arbol2;
					nal aux;
					aux=arbol.buscar(Cciudad)->ArbolAVL;
					arbol2.raiz=aux;
				    
					if(!arbol2.esta(Ccadena))
					{
						cout<<"***ERROR:Cadena no encontrada, revise el archivo de cadenas***"<<endl;
					}
					else
					{
						RyN arbol3;
						nRN aux2;
						aux2=arbol2.buscar(Ccadena)->def;
						arbol3.primeroRN=aux2;
						
						if(arbol3.buscar(Cproducto)!=NULL)
						{
							cout<<"***ERROR:Producto repetido***"<<endl;
						}
						else
						{
							arbol3.insercion(Cproducto,ch2);
							arbol2.buscar(Ccadena)->def=arbol3.primeroRN;
							cout<<"info: "<<ch2<<endl;
						}
					
					}
					
					
		    		
		    	}
		    	Ccadena=0;
		    	Cciudad=0;
		    	Cproducto=0;
		    	ch2="";
		    	cadena=NULL;
		    		
	    	}
	    } 
	    cout<<endl;
	    
		cout<<"------------------------------------------------------------------"<<endl<<endl;
    doc3.close();
    
	}
	else cout << "No se pudo abrir el documento"<<endl;
	
	system("pause");
	return 0;
}
