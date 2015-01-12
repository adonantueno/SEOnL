#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

#include "librerias/estructurasSEOnL.hpp"
#include "librerias/datosMensajesSEOnL.hpp"

//#include <iostream> --> Traen las librerias con
//#include <string.h> --> Traen las librerias con
//using namespace std; --> Traen las librerias con

#define P_SIZE sizeof(struct mensaje)


int main () {

	int sd;						//Socket descriptor, identifica a la comunicación establecida
	int lon;					//Dimension del archivo que describe al servidor
	int n;
	int conect = 1; // Control de la conexion
	char user[10],pass[10];			//Encargados de validar al usuario (para un futuro)
	char res_registro, res, r;
	uint16_t c, sc;
	uint32_t ln;
	struct sockaddr_in servidor;	//Describe al servidor (protocolo que maneja, ip, y puerto)

	char buffer[P_SIZE];		//Tamaño del Buffer

	char datos [300] = "";
	struct mensaje* msj;

	/*
	* -------------------- SETTEO EL SOCKET -------------------
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
	if (connect ( sd , (struct sockaddr *) &servidor, lon ) < 0){
		perror ("Error en connect");
		cout << "Se produjo un error al intentar la conexión, esto se puede deber";
		cout << " a que el servidor este fuera de linea" << endl;;
		cout << "Intente mas tarde" << endl;
	}else{
		int control = 1;
		// itero mientras el usuario quiera continuar;

		while (control){
			system("clear");
			cout << "¿Qué desea Hacer? " << endl;
			cout << "1) Registrarse "<< endl;
			cout << "2) Ingresar "<< endl;
			cout << "3) Salir"<< endl;
			cin >> res;

			switch (res){
				case '1':
						break;
						case '2':
						cout << "Ingrse sus datos para ingresar" << endl;
						cout << "usuario: " ; cin >> user;
						cout << "contraseña: " ; cin >> pass;
						/*
					 	* -------------------- CREO EL MENSAJE----------
					 	*/
						crearDatos_M1(user,pass,datos);
						c = htons(atoi("1"));
						sc = htons(atoi("0"));
						ln = htonl(16 + 16 + 32 + sizeof(datos));
						msj = (struct mensaje*) buffer;
						cargarMensaje(msj,c,sc,ln,datos);
						/*
					 	* -------------------- ENVIO ------------------------------
					 	*/
						send ( sd, buffer, P_SIZE, 0 );
						system("clear");
						cout << "Entrasta al SEOnL" << endl;
						cout << "Desear realizar evaluacion (s/n)"<< endl;
						break;

				case '3':
						control = 0;
						break;

				default:
					cout << "Opcion INCORRECTA"<< endl;
			}
		}
		close(sd);

	}
	cout << "Gracias por usar S.E.On.L. "<<endl;
	return 0;
}
