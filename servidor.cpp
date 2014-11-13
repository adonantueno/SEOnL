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
#include <string.h>
using namespace std;

#define P_SIZE sizeof(struct mensaje)

/*
int hacer_examen ( struct pregunta *p ) {
		char txt[100];
		char opc[20];
		struct pregunta *ppregunta;
		ppregunta = p;
	
		ppregunta->id = 1;
		
		printf ("Ingrese enunciado: ");
		scanf("%s[^\n]",txt);
		strcpy(ppregunta->enunciado, txt);
		
		
		printf("A CONTiNUACION COMIENZA EL INGRESO DE  OPCIONES ");

		for(int j = 0; j < 3; j++){
			printf ("ingrese opción %d: ", j+1);
			scanf("%s[^\n]",opc);
			strcpy(ppregunta->opciones[j],opc);
		
		}
		return 0;
};*/

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
};

bool userValido (string user, string pass){
	bool validacion = 0;
	if (user == "admin" && pass == "1234"){
		validacion = 1;
	}
	return validacion;
};


int main () {
	string user,pass;
	char res;
	int n;
	int i=0;
	int sd;
	int sdc;
	char buffer[P_SIZE];
	struct mensaje* msj;

	struct sockaddr_in cliente;
	struct sockaddr_in servidor;
	struct pregunta preg;
	struct evaluacion examen;
	int cant;
	char enunciado[250];
	char opcion[50];
	int id;
	char nombre[20];
	socklen_t lon = sizeof(cliente);
	
	cout << "usuario: " ; cin >> user;
	cout << "contraseña: " ; cin >> pass;

	if (userValido(user,pass)) {
		int control = 1;
		// itero mientras el usuario quiera continuar;
		while (control){
			system("clear");
			cout << "¿Qué desea Hacer? "<< endl;
			cout << "1) Cargar Exámen "<< endl;
			cout << "2) Ver Resultados de alumnos"<< endl;
			cout << "3) Poner en linea"<< endl;
			cout << "4) Salir"<< endl;
			cin >> res;
			switch (res){
			//trabajo de a dos casos (mayusculas o minusculas ingresadas)
				case '1':
					cout << "Iniciando Examen" << endl;
					cout << "Indique nombre del Examen: "; cin >> nombre;
					examen = cargarEvaluacion(id, nombre);
					cout << "Indique Cantidad de preguntas del Examen: "; cin >> cant;
					cout << "Iniciando carga de preguntas" << endl;
					for (cant; cant > 0 ; cant--)
					{
						cout << "ingrese enunciado: "; cin >> enunciado;
						preg = cargarPregunta(cant,enunciado);
						cout << "Iniciando carga de opciones" << endl;
						for (int j = 0; j < 3 ; j++)
						{
								cout << "ingrese opcion: " << j; cin >>opcion;
								cargarOpcionPregunta(preg ,j,opcion);
						}
						cargarPreguntaEvaluacion(examen,cant,preg);
					}
					imprimirExamen(examen);
					for (int j= 0; j < 5; j++){
						imprimirPregunta(examen.preguntas[j]);
						}
					break;
				case '2':
					/*
					cout << "Cargando exámenes" << endl;
					
					//sdc = accept ( sd, (struct sockaddr *) &cliente, &lon );
					
					n = send ( sdc , buffer, P_SIZE, 0 );
					//For exámenes tattata...
					cout << "enviado" << endl;
					sleep (10);
					*/
					break;
				case '3':
						cout << "--- --- EN LINEA --- ---"<< endl;
						servidor.sin_family = AF_INET;
						servidor.sin_port = htons(4444);
						servidor.sin_addr.s_addr = INADDR_ANY;
						
						sd = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
						
						if (bind(sd, (struct sockaddr *) &servidor, sizeof(servidor)) < 0) {
							perror("Error en bind");
							exit(-1);
						}
						
						listen ( sd , 5 );
						sdc = accept ( sd, (struct sockaddr *) &cliente, &lon );
						
						msj = (struct mensaje*) buffer;
						
						n = leer_mensaje ( sdc , buffer , P_SIZE );
						cout << "codigo recibido: " << ntohs(msj->codigo) << endl;
						cout << "subcodigo recibido: " << ntohs(msj->subcodigo) << endl;
						cout << "leng recibido: " << ntohl(msj->longitud) << endl;
						cout << "datos recibido: " << msj->datos << endl;
						switch (ntohs(msj->codigo)){
								/*case '0':
									// MENSAJE DE REGISTRO
								break;*/
								case 1:
									//MENSAJE DE LOGUEO
									cout << "entro logueo" << endl;
								break;
								default:
									//ACK ERROR 203
									cout << "error de codigo" << endl;
						}
						close (sdc);
					break;
				case '4':
					control = 0;
					break;
				default:
				cout << "Opcion INCORRECTA"<< endl;
			}
		}
		cout << "Gracias por usar S.E.On.L. "<<endl;
	}else {
		cout << "Error de loggeo, comuniquese con su administrador"<< endl;
	}
	close (sd);
	return 0;
}
