#include <stdlib.h>
#include <iostream>
#include <string>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

#define P_SIZE sizeof(struct pregunta)		//en un futuro tendría que tomar como referencia el size de un examen

#define algoque no existe

struct pregunta {
	int id;
	char enunciado;
	char opciones[3];
};

struct evaluacion {
	int id;
	char nombre;
	struct pregunta preguntas[5];
};


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
	
	int sd;						//Socket descriptor, identifica a la comunicación establecida
	int lon;					//Dimension del archivo que describe al servidor
	int n;
	
	string user,pass;			//Encargados de validar al usuario (para un futuro)
	char res, r;
	
	struct sockaddr_in servidor;	//Describe al servidor (protocolo que maneja, ip, y puerto)
	
	struct pregunta *preg;			//Será un puntero a una estructura de tipo pregunta utilizado para la presentación
	
	//char teclado[512];
	char buffer[P_SIZE];			//Tamaño del Buffer
	
	cout << "usuario: " ; cin >> user;
	cout << "contraseña: " ; cin >> pass;

	
	sd = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	
	servidor.sin_family = AF_INET;
	servidor.sin_port = htons(4444);
	servidor.sin_addr.s_addr = inet_addr("127.0.0.1");
	
	//RESPUESTA = mensajeLoggeo(user,pass);
	//ACA DEBERÍAMOS CAPTURAR SI EL MENSAJE DE RESPUESTA ES LA LISTA
	//DE EXÁMENES O EL MENSAJE DE ERRO
	
	int valido = 1;

	lon = sizeof(servidor);
	
	//Se hace un casteo a sockaddr de la estructura servidor que es sockadrr_in &puntero y se establece la conexión
	
	if ( connect ( sd , (struct sockaddr *) &servidor, lon ) < 0 ) {
		perror ("Error en connect");
		exit(-1);
	}

	if (valido) {
		int control = 1;
		// itero mientras el usuario quiera continuar;
		
		preg = (struct pregunta *) buffer;
		
		while (control){
			system("clear");
			cout << "¿Qué desea Hacer? " << endl;
			cout << "1) Consultar Exámenes "<< endl;
			cout << "2) Salir"<< endl;
			cin >> res;
			switch (res){
			//trabajo de a dos casos (mayusculas o minusculas ingresadas)
				case '1':
					
					n = leer_mensaje (sd, buffer, P_SIZE );
					
					printf("La pregunta es: %c \n Y las opciones: %c, %c, %c \n", ntohs(preg->enunciado), ntohs(preg->opciones[0]), ntohs(preg->opciones[1]), ntohs(preg->opciones[2]));
					
					cout << "escoja una opción " ; cin >> r;
					
					//printf("eligió: %c \n" , r);
					sleep (10);
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
	return 0;
}
