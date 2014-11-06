#include <stdlib.h>
#include <iostream>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>


#define P_SIZE sizeof(struct pregunta)

struct pregunta {
	int id;
	char enunciado[100];
	char opciones[3][20];
};

struct evaluacion {
	int id;
	char nombre[20];
	struct pregunta preguntas[5];
};

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
}

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
}

using namespace std;

int main () {
	char user,pass;
	char res;
	
	int n;
	int sd;
	int sdc;
	
	char buffer[P_SIZE]; //[P_SIZE]
	
	struct pregunta *preg;
	struct sockaddr_in cliente;
	struct sockaddr_in servidor;
	
	cout << "usuario: " 	; cin >> user;
	cout << "contraseña: " ; cin >> pass;
	
	//int valido = FunciónLoggeo(user,pass);
	int valido = 1;
	
	servidor.sin_family = AF_INET;
	servidor.sin_port = htons(4444);
	servidor.sin_addr.s_addr = INADDR_ANY;
	
	sd = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	
	if (bind(sd, (struct sockaddr *) &servidor, sizeof(servidor)) < 0) {
		perror("Error en bind");
		exit(-1);
	}
	
	listen ( sd , 5 );
	
	if (valido) {
		
		socklen_t lon = sizeof(cliente);
		sdc = accept ( sd, (struct sockaddr *) &cliente, &lon );
		
		int control = 1;
		// itero mientras el usuario quiera continuar;
		while (control){
			system("clear");
			cout << "¿Qué desea Hacer? "<< endl;
			cout << "1) Cargar Exámen "<< endl;
			cout << "2) Ver Resultados de alumnos"<< endl;
			cout << "3) Poner en linea"<< endl;;
			cout << "4) Salir"<< endl;
			cin >> res;
			switch (res){
			//trabajo de a dos casos (mayusculas o minusculas ingresadas)
				case '1':
					preg = (struct pregunta *) buffer;
					
					n= hacer_examen(preg); //podria hacerla void
					
					
					printf ("Enunciado: %s ",preg->enunciado); //
					//send ( sdc , buffer, P_SIZE, 0 );
					
					//cout << "Cargando exámen" << endl;
					//ACA LLAMARÍAMOS A LAS FUNCIONES DE LA LIBRERIA
					// QUE VAMOS A CREAR

					break;
				case '2':
					cout << "Cargando exámenes" << endl;
					
					//sdc = accept ( sd, (struct sockaddr *) &cliente, &lon );
					
					n = send ( sdc , buffer, P_SIZE, 0 );
					//For exámenes tattata...
					cout << "enviado" << endl;
					sleep (10);
					break;
				case '3':
					//A LA ESCUCHA DE LO QUE MANDEN LOS CLIENTES
					//SERIA EL "listen"
					break;
				case '4':
					control = 0;
					break;
				default:
				cout << "Opcion INCORRECTA"<< endl;
			}
		}
		close(sdc);
		cout << "Gracias por usar S.E.On.L. "<<endl;
	}else {
		cout << "Error de loggeo, comuniquese con su administrador";
	}
	close (sd);
}
