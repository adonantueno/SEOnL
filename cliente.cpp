#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

#include "librerias/estructurasSEOnL.hpp"

#include <iostream>
#include <string>
using namespace std;

#define P_SIZE 200 //sizeof(struct mensaje)	//en un futuro tendría que tomar como referencia el size de un examen

/*
int leer_mensaje ( int sd, char * buffer, int total ) {
    int bytes;
    int leido;

    leido = 0;
    bytes = 1;

    while ( (leido < total) && (bytes > 0) ) {

        bytes = recv ( sd , buffer + leido , total - leido , 0);

        leido = leido + bytes;

    }

    return ( leido );

};*/


int main () {

	int sd;						//Socket descriptor, identifica a la comunicación establecida
	int lon;					//Dimension del archivo que describe al servidor
	int n;
	string user,pass;			//Encargados de validar al usuario (para un futuro)
	char res, r;
	uint16_t c, sc;
	uint32_t ln;
	struct sockaddr_in servidor;	//Describe al servidor (protocolo que maneja, ip, y puerto)
	
	char buffer[P_SIZE]; //[P_SIZE]		//Tamaño del Buffer
	string datos;
	struct mensaje* msj = new mensaje;

	cout << "usuario: " ; cin >> user;
	cout << "contraseña: " ; cin >> pass;
	
	/*
	 * -------------------- COMIENZO CON LA CONEXION --------------------
	 */
	msj = (struct mensaje*) buffer;
	datos = user + "&&" + pass;
	c = htons(atoi("1"));
	sc = htons(atoi("0"));
	ln = htonl(16 + 16 + 32 + datos.size());
	cargarMensaje(msj,c,sc,ln,datos);

	/*
	 * -------------------- SETTEO EL SOCKET --------------------------- 
	 */
	sd = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	servidor.sin_family = AF_INET;
	servidor.sin_port = htons(4444);
	servidor.sin_addr.s_addr = inet_addr("127.0.0.1");
	lon = sizeof(servidor);
	
	//Se hace un casteo a sockaddr de la estructura servidor que es sockadrr_in &puntero y se establece la conexión
	/*
	 *  -------------------- CONECTO ---------------------------
	 */
	if ( connect ( sd , (struct sockaddr *) &servidor, lon ) < 0 ) {
		perror ("Error en connect");
		exit(-1);
	}else{
		cout << "ya me conecte"<< endl;
	}
	/*
	 * -------------------- ENVIO ---------------------------
	 */ 
	cout << "codigo enviado: " << htons(msj->codigo) << endl;
	cout << "subcodigo enviado: " << htons(msj->subcodigo) << endl;
	cout << "leng enviado: " << htonl(msj->longitud) << endl;
	cout << "datos enviado: " << msj->datos << endl; 
	send ( sd, buffer, P_SIZE, 0 );
	cout << "envie" << endl;
	if (1) {
		int control = 1;
		// itero mientras el usuario quiera continuar;

		while (control){
			system("clear");
			cout << "¿Qué desea Hacer? " << endl;
			cout << "1) Consultar Exámenes "<< endl;
			cout << "2) Salir"<< endl;
			cin >> res;
			switch (res){
			//trabajo de a dos casos (mayusculas o minusculas ingresadas)
				case '1':
					/*
					n = leer_mensaje (sd, buffer, P_SIZE );
					
					preg= (struct pregunta*) buffer;
					
					printf("La pregunta es: %s \n Y las opciones: %s, %s, %s \n", preg->enunciado, preg->opciones[0], preg->opciones[1], preg->opciones[2]);
					
					cout << "escoja una opción " ; cin >> r;
					
					printf("eligió: %c \n" , r);
					sleep (10);
					*/
					break;
					
				case '2':
					//mensajeCerrarSesion();
					control = 0;
					break;
				default:
					cout << "Opcion INCORRECTA"<< endl;
			}
		}
		
		close(sd);
		cout << "Gracias por usar S.E.On.L. "<<endl;
	}else {
		//int valido = mensajeRegistro(legajo, nombre ,user);
	}
	delete msj;
	return 0;
}
