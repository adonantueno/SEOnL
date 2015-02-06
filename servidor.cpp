#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

#include <arpa/inet.h>
#include <netdb.h>

#include "librerias/estructurasSEOnL.hpp"
#include "librerias/datosMensajesSEOnL.hpp"
#include "librerias/archivosSEOnL.hpp"


/* TRAEN LAS LIBRERIAS

#include <sys/socket.h>
#include <netinet/in.h>

#include <iostream>
#include <string.h>

using namespace std;
*/


#define P_SIZE sizeof(struct mensaje)

bool userValido (string user, string pass){
	bool validacion = 0;
	if (user == "admin" && pass == "1234"){
		validacion = 1;
	}
	return validacion;
};

int main () {
	string user,pass;
	char user_cliente[10], pass_cliente[10];

	//VARIABLES QUE FORMAN EL MENSAJE
	uint16_t c, sc;					//Variables del codigo y subcodigo del mensaje
	uint32_t ln;					  //Variable de logitud del mensaje
	char datos [500] = "";
	char pendientes [100] = "";

	char buffer[P_SIZE];

	char res;
	int i;
	int sd;
	int sdc;

	struct sockaddr_in cliente;
	struct sockaddr_in servidor;

	struct pregunta preg;
	struct pregunta* pregunta;
	struct evaluacion evaluacion;
	struct mensaje* msj;
	struct alumno* alu;
	struct alumno alumno;
	struct resultado result;

	int cant;
	char enunciado[250];
	char opcion[50];
	int id;
	char titulo[20];
	socklen_t lon;

	long n; 					// usado para la cantidad de registros

    int codEvaluaciones;		  // codigo de evaluacion a poner en linea
	int valido;			   	// usada para validar usuario cliente
	int verificaAlu; 			  // usada para verificar registro.
	int conexion = 1; 		   //  usada para mantener la conexion.
	int control = 1;			// usada para estar activo mientras el usuario lo desee.
	int controlSelecion = 1;     // usada para el control de la seleccion de evaluacion en linea


	cout << "usuario: " ; cin >> user;
	cout << "contraseña: " ; cin >> pass;

	if (userValido(user,pass)) {

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
					/*
					cout << "Iniciando Examen" << endl;
					cout << "Indique titulo del Examen: "; cin >> titulo;
					examen = cargarEvaluacion(id, titulo);
					cout << "Indique Cantidad de preguntas del Examen: "; cin >> cant;
					cout << "Iniciando carga de preguntas" << endl;
					for (cant; cant > 0 ; cant--)
					{
						cout << "ingrese enunciado : "; cin >> enunciado;
						preg = cargarPregunta(cant,enunciado);
						cout << "Iniciando carga de opciones" << endl;
						for (int j = 0; j < 3 ; j++)
						{
								cout << "ingrese opcion: " << j; cin >>opcion;
								cargarOpcionPregunta(preg ,j,opcion);
						}
						cargarPreguntaEvaluacion(examen,cant,preg);
					}
					*/
					leerEvaluacion_A(&evaluacion, 0);

					imprimirEvaluacion(evaluacion);
					for (int k= 0; k < 5; k++){
						imprimirPregunta(evaluacion.preguntas[k]);
					}
					cout << "Presione una tecla para continuar..."; cin.ignore();cin.get();
					break;

				case '2':
					/*
					Le dariamos a seleccionar una evaluacion y a partir de alli
					buscacmos en el archivo de resultados.
					*/
					n = calcularRegistros(PATH_RESULTADOS, sizeof(resultado));
					while ( i < n){
						leerResultadoAlumnos_A (&result, i);
						imprimirResultado(result);
						i++;
					}
					cout << "Presione una tecla para continuar..."; cin.ignore();cin.get();
					break;

				case '3':
					servidor.sin_family = AF_INET;
					servidor.sin_port = htons(4444);
					servidor.sin_addr.s_addr = INADDR_ANY;
					sd = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

					if (bind(sd, (struct sockaddr *) &servidor, sizeof(servidor)) < 0) {
						perror("Error en bind");
						cout << "Se produjo un error al realizar el enlace, esto se puede deber";
						cout << " a que hay procesos anteriores todabia trabajando." << endl;;
						cout << "Verifique su lista de procesos e intente mas tarde" << endl;
						control = 0;
					}else {
						/*
						*Primero le pedimos que elija la evaluacion a poner en linea
						*/

						while (controlSelecion){

							cout << "Seleccione una evaluacion a poner en Linea..." << endl;

						    n = calcularRegistros(PATH_EVALUACIONES, sizeof(evaluacion));
							i = 0;
						    while ( i < n){
						        leerEvaluacion_A(&evaluacion, i);
								imprimirEvaluacion(evaluacion);
						        i++;
						    }
							cout << "---" << endl;
							cout << "Código de evaluacion: " ; cin >> codEvaluaciones;
							controlSelecion = 0;
							if ( ! buscarEvaluacion_A (&evaluacion, codEvaluaciones)) {
								cout << "codigo incorrecto, vuelva a intentarlo" << endl;
								controlSelecion = 1;
							}
						}
						//ya tengo la evaluacion que realizaran los alumnos que se conecten.

						listen ( sd , 5 );
						cout << "--- --- EN LINEA --- ---"<< endl;
						//Está en linea hasta que el usuario quiera terminar!.
						while(conexion){
							strcmp ("",buffer);
							lon = sizeof(cliente);
							sdc = accept ( sd, (struct sockaddr *) &cliente, &lon );
							while (leerMensaje ( sdc , buffer , P_SIZE ) > 0){

							msj = (struct mensaje*) buffer;
							reordenarBytes (msj);

							switch (msj->codigo){
								case 0:
									cout << "entro Registro" << endl;
									alu = (struct alumno*) msj->datos;

									verificaAlu = verificarDatosAlumno_A (alu);
									if (verificaAlu == 0){
										strcpy(alu->password, "123abc");
										cargarAlumno_A(alu);
										//-------------- CREO EL MENSAJE----------------
										crearDatos(alu->password, datos);
										c = 9;
										sc = 100;
										ln = 16 + 16 + 32 + sizeof(datos);
										msj = (struct mensaje*) buffer;
									}else{
										if (verificaAlu > 0 ){
											crearDatos("Alumno ya registrado.", datos);
											c = 9;
											sc = 200;
											ln = 16 + 16 + 32 + sizeof(datos);
											msj = (struct mensaje*) buffer;
										}else{
											//-------------- CREO EL MENSAJE----------------
											crearDatos("User ya utilazado (opte por otro).", datos);
											c = 9;
											sc = 200;
											ln = 16 + 16 + 32 + sizeof(datos);
											msj = (struct mensaje*) buffer;
										}
									}
									//----------------- ENVIO --------------------
									cargarMensaje(msj,c,sc,ln,datos);
									ordenarBytes (msj);
									send ( sdc , buffer, P_SIZE, 0 );

									break;
								case 1:
									cout << "entro logueo" << endl;
									interpretarDatos_M1(user_cliente, pass_cliente,msj->datos);
									if( validarAlumno_A (user_cliente,pass_cliente, &alumno )) {
										// primero cargo los datos de la evaluación
										// luego, los borro si es que ya lo hizo.
										strcpy (pendientes, evaluacion.titulo);
										verificarPendientes_A(alumno.legajo,evaluacion.id, pendientes);
										//-------------- CREO EL MENSAJE----------------

										crearDatos_M101 (alumno.apellido,alumno.legajo,pendientes,datos);
										c = 9;
										sc = 101;
										ln = 16 + 16 + 32 + sizeof(datos);
										msj = (struct mensaje*) buffer;
										//----------------- ENVIO --------------------
										cargarMensaje(msj,c,sc,ln,datos);
										ordenarBytes (msj);
										send ( sdc , buffer, P_SIZE, 0 );


										//-------------------- Espero respuesta --------------------
										leerMensaje ( sdc , buffer , P_SIZE );
										reordenarBytes (msj);
										if (msj->codigo == 3){
											/*COMINEZA EL LOOP DE LA EVALUACION*/
											//msj = (struct mensaje*) buffer;

											int p = 0;						//contador de pregunta
											int calificacion = 0;				//almacena la calificacion
											//while (evaluacion.preguntas[p] != NULL)
											while (p < 5){
												strcpy (datos, "");
												pregunta = (struct pregunta*) msj->datos;
												pregunta->id = evaluacion.preguntas[p].id;
												strcpy (pregunta->enunciado, evaluacion.preguntas[p].enunciado);
												strcpy (pregunta->opciones[0], evaluacion.preguntas[p].opciones[0]);
												strcpy (pregunta->opciones[1], evaluacion.preguntas[p].opciones[1]);
												strcpy (pregunta->opciones[2], evaluacion.preguntas[p].opciones[2]);


												//----------------- ENVIO --------------------
												c = 4;
												sc = 0;
												ln = 16 + 16 + 32 + sizeof(msj->datos);
												cargarMensaje(msj,c,sc,ln,msj->datos);
												ordenarBytes (msj);
												send ( sdc , buffer, P_SIZE, 0 );

												//-------------------- Espero respuesta --------------------
												leerMensaje ( sdc , buffer , P_SIZE );
												reordenarBytes (msj);
												if (atoi(msj->datos) == evaluacion.preguntas[p].correcta){		//aca creo q va evaluacion.preguntas[p].correcta en ves de   pregunta->correcta
													calificacion = calificacion+2;								//sumo de a (10/cant de preg)
												}
												p++;
											}
											cout << "calificacion: " << calificacion << endl;
											char cc;
											sprintf(&cc, "%d", calificacion);
											crearDatos(&cc, datos);
											//----------------- ENVIO --------------------
											c = 9;
											sc = 103;
											ln = 16 + 16 + 32 + sizeof(datos);
											cargarMensaje(msj,c,sc,ln,datos);
											ordenarBytes (msj);
											send ( sdc , buffer, P_SIZE, 0 );
											//----------------- almaceno en archivo --------------------
											result = crearResultado (evaluacion.id,evaluacion.titulo,alumno.legajo,alumno.apellido,calificacion);
											cargarResultadoAlumno_A (&result);
										}else{
												if (msj->subcodigo ==104)
												{
													cout << "El alumno ya realizó el examen" << endl;
												}else
												{
													crearDatos("No selecciono evaluación a realizar", datos);
													//----------------- ENVIO --------------------
													c = 9;
													sc = 202;
													ln = 16 + 16 + 32 + sizeof(datos);
													cargarMensaje(msj,c,sc,ln,datos);
													ordenarBytes (msj);
													send ( sdc , buffer, P_SIZE, 0 );
												}


											}

									}else{
										// -------------- CREO EL MENSAJE----------------
										crearDatos ("Error de loggeo Usuario o contraseña incorrecto.", datos);
										c = 9;
										sc = 201;
										ln = 16 + 16 + 32 + sizeof(datos);
										msj = (struct mensaje*) buffer;
										// ----------------- ENVIO --------------------
										cargarMensaje(msj,c,sc,ln,datos);
										ordenarBytes (msj);
										send ( sdc , buffer, P_SIZE, 0 );
									}
									break;

								case 8:
									cout << "entro cierre sesión " << endl;
									conexion = 0;
									break;

								default:
									//ACK EROR 203
									cout << "error de codigo" << endl;
							} // swicht codigo
						}
						close (sdc);
						} //while conexion
					} //else conectado
					break;

				case '4':
					control = 0;
					break;

				default:
				cout << "Opcion INCORRECTA"<< endl;
			}
		}

	}else {
		cout << "Error de loggeo, comuniquese con su administrador"<< endl;
	}
	close (sd);
	cout << "Gracias por usar S.E.On.L. "<<endl;
	return 0;
}
