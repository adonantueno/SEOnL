#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

#include <arpa/inet.h>
#include <netdb.h>

#include "librerias/estructurasSEOnL.hpp"
#include "librerias/datosMensajesSEOnL.hpp"

/* TRAEN LAS LIBRERIAS

#include <sys/socket.h>
#include <netinet/in.h>

#include <iostream>
#include <string.h>

using namespace std;
*/

#define P_SIZE sizeof(struct mensaje)


int main () {

	char user[10], pass[10];
	char apellido[30], legajo[11];

	int sd;							 //Socket descriptor, identifica a la comunicación establecida
	int lon;							//Dimension del archivo que describe al servidor

	struct alumno* alu;
	char pendientes[20];
	char res;
	char resEvaluacion;
	char resVer;

	//VARIABLES QUE FORMAN EL MENSAJE
	uint16_t c, sc;					//Variables del codigo y subcodigo del mensaje
	uint32_t ln;					  //Variable de logitud del mensaje
	char datos [10000];

	struct sockaddr_in servidor;	//Describe al servidor (protocolo que maneja, ip, y puerto)
	char buffer[P_SIZE];		//Tamaño del Buffer
	struct mensaje* msj;
	struct pregunta* pregunta;
	struct evaluacion* evaluacion;

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
					msj = (struct mensaje*) buffer;
					alu = (struct alumno*) msj ->datos;
					cout << "Ingrese sus datos de alumno" << endl;
					cout << "Legajo (en la forma 99-99999-9): " ; cin >> alu->legajo;
					cout << "Apellido: "; cin >> alu->apellido;
					cout << "usuario: ";  cin >> alu->user;
					cout << "El sistema generará su contraseña automaticamente" << endl;
					// -------------------- CREO EL MENSAJE----------
					c  = 0;
					sc = 0;
					ln = 16 + 16 + 32 + sizeof(msj->datos);
					//-------------------- ENVIO ------------------------------
					cargarMensaje(msj,c,sc,ln,msj->datos);
					ordenarBytes (msj);
					send ( sd, buffer, P_SIZE, 0 );
					//-------------------- Espero respuesta --------------------
					leerMensaje ( sd , buffer , P_SIZE );
					reordenarBytes (msj);
					if (msj->codigo = 9){
						if (msj->subcodigo == 100){
							cout << "su contraseña es: " << msj->datos << endl;
							cout << "Vuelva al menu y elija la opción ingresar" << endl;
						}
						if (msj->subcodigo == 200){
							cout << "Ocurrió un error en el registro" << endl;
							cout << msj->datos << endl;
						}
					cout << "Presione una tecla para continuar..."; cin.ignore();cin.get();
					}else {
						cout << "error en la comunicación " << endl;
					}

					break;

				case '2':
					cout << "Ingrse sus datos para ingresar" << endl;
					cout << "usuario: " ; cin >> user;
					cout << "contraseña: " ; cin >> pass;


					//------------------- CREO EL MENSAJE----------
					crearDatos_M1(user,pass,datos);
					c =  1;
					sc = 0;
					ln = 16 + 16 + 32 + sizeof(datos);
					msj = (struct mensaje*) buffer;
					// -------------------- ENVIO ------------------------------
					cargarMensaje(msj,c,sc,ln,datos);
					ordenarBytes (msj);
					send ( sd, buffer, P_SIZE, 0 );
					//-------------------- Espero respuesta --------------------
					leerMensaje ( sd , buffer , P_SIZE );
					reordenarBytes (msj);
					system("clear");
					if (msj->subcodigo == 101){
						cout << "Entraste al SEOnL" << endl;
						interpretarDatos_M101 (apellido, legajo, pendientes, msj->datos);
						cout << "Hola " << legajo << " " << apellido << endl;
						cout << "--- --- Evaluaciones para realizar --- ---" << endl;
						if(!strcmp(pendientes,"")){
							//preparo msj para que el servidor no se quede esperando
							//no se si se manda aca o abajo
							cout<<"Sin evaluaciones para realizar"<<endl;
							crearDatos("",datos);
							c=9; 					//evaluar cual tiene que ser el codigo
							sc=104;
							ln=16 + 16 + 32 + sizeof(datos);
							msj = (struct mensaje*) buffer;
							// -------------------- ENVIO ------------------------------
							cargarMensaje(msj,c,sc,ln,datos);
							ordenarBytes (msj);
							send ( sd, buffer, P_SIZE, 0 );

						}else{
							cout << pendientes << endl;
							cout << "Desear realizar evaluacion (s/n)"<< endl;
							cin >> resEvaluacion;
							if (resEvaluacion == 's'){
								/*COMINEZA EL LOOP DE LA EVALUACION*/
								//------------------- CREO EL MENSAJE----------
								crearDatos("null",datos);
								c =  3;
								sc = 0;
								ln = 16 + 16 + 32 + sizeof(datos);
								msj = (struct mensaje*) buffer;
								// -------------------- ENVIO ------------------------------
								cargarMensaje(msj,c,sc,ln,datos);
								ordenarBytes (msj);
								send ( sd, buffer, P_SIZE, 0 );
								//-------------------- Espero respuesta --------------------
								leerMensaje ( sd , buffer , P_SIZE );
								reordenarBytes (msj);
								char respuesta;
								while (msj->codigo == 4){
									pregunta = (struct pregunta*) msj->datos;
									imprimirPregunta(*pregunta);
									cout << "respuesta: "; cin >> respuesta;
									//------------------- CREO EL MENSAJE----------
									crearDatos(&respuesta,datos);
									c =  5;
									sc = 0;
									ln = 16 + 16 + 32 + sizeof(datos);
									msj = (struct mensaje*) buffer;
									// -------------------- ENVIO ------------------------------
									cargarMensaje(msj,c,sc,ln,datos);
									ordenarBytes (msj);
									send ( sd, buffer, P_SIZE, 0 );
									//-------------------- Espero respuesta --------------------
									leerMensaje ( sd , buffer , P_SIZE );
									reordenarBytes (msj);
								}
								if (msj->codigo == 9 && msj->subcodigo == 103){
									cout << "Tu nota es: " << msj->datos << endl;
									cout << "¿Desea ver la evaluacion compelta? (s/n)" << endl;
									cin >> resVer;
									//------------------- CREO EL MENSAJE----------
									crearDatos("s",datos);
									c =  6;
									sc = 0;
									ln = 16 + 16 + 32 + sizeof(datos);
									// -------------------- ENVIO ------------------------------
									cargarMensaje(msj,c,sc,ln,datos);
									ordenarBytes (msj);
									send ( sd, buffer, P_SIZE, 0 );
									if(resVer == 's'){
										//solo si quiere ver espero la respuesta
										//-------------------- Espero respuesta --------------------
										leerMensaje ( sd , buffer , P_SIZE );
										reordenarBytes (msj);
										evaluacion = (struct evaluacion*) msj->datos;
										imprimirEvaluacionCompleta (*evaluacion);
										//cout << msj->datos << endl;
									}
								}else{
									//posiblemente 202
									cout << msj->datos << endl;
								}
							}else{//no quire hacer evaluación
								crearDatos("",datos);
								c=9; 					//evaluar cual tiene que ser el codigo
								sc=104;
								ln=16 + 16 + 32 + sizeof(datos);
								msj = (struct mensaje*) buffer;
								// -------------------- ENVIO ------------------------------
								cargarMensaje(msj,c,sc,ln,datos);
								ordenarBytes (msj);
								send ( sd, buffer, P_SIZE, 0 );
							}
						}
						cout << "Presione una tecla para continuar..."; cin.ignore();cin.get();

					}else{
						if (msj->subcodigo == 201){
							cout << "ocurrio un error." << endl;
							cout << msj->datos << endl;
							cin.ignore();cin.get();
						}
					}
					break;

				case '3':
					// -------------------- CREO EL MENSAJE----------
					crearDatos("null",datos);
					c =  8;
					sc = 0;
					ln = 16 + 16 + 32 + sizeof(datos);
					msj = (struct mensaje*) buffer;
					// -------------------- ENVIO ------------------------------
					cargarMensaje(msj,c,sc,ln,datos);
					ordenarBytes (msj);
					send ( sd, buffer, P_SIZE, 0 );

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
