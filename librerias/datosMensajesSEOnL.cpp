#include "datosMensajesSEOnL.hpp"
#include "estructurasSEOnL.hpp"

int leerMensaje ( int sd, char * buffer, int total ) {
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

void ordenarBytes (struct mensaje* m){

	m->codigo = htons(m->codigo);
	m->subcodigo = htons(m->subcodigo);
	m->longitud = htonl (m->longitud);
};

void reordenarBytes (struct mensaje* m){

	m->codigo = ntohs(m->codigo);
	m->subcodigo = ntohs(m->subcodigo);
	m->longitud = ntohl (m->longitud);
};


/*MENSAJE 0*/

/*
NO SON NECESARIOS CREAR E INTERPRETAR LOS DATOS DEL MENSAJE 0 YA QUE MANDAMOS DIRECTAMENTE
LA ESTRUCTURA DE DATOS ALUMNO POR TANTO SOLO CON APUNTAR AL ATRIBUTO DATOS DEL MENSAJE
ALCANZA PARA QUE PUEDA INTERPRETARSE Y CREARSE DIRECTAMENTE.

*/

/*GENERAL PARA VARIOS MENSAJES, CUANDO EL CAMPO DE DATOS ESTA COMPUESTO POR UNA
CADENA DE TEXTO SOLA.- Mayormente en los ACK*/

void crearDatos (char* texto, char* datos){

	strcpy (datos, "");
	strcpy(datos, texto); // ACA IRIA LA LISTA DE Evaliaciones
}


/*MENSAJE 1*/

void crearDatos_M1(char* user, char* pass, char* datos){

	strcpy (datos, "");
	strncat(datos,user,sizeof(datos));
	strncat(datos,"&",sizeof(datos));
	strncat(datos,pass,sizeof(datos));

};

void interpretarDatos_M1 (char* user, char* pass, char* datos){

	int control = 1;
	int i = 0;
	int j = 0;
	char ampersand = '&';

	while ( i < strlen(datos)){
		if (datos[i] == ampersand){
			control = 0;
			j= -1;
		}else{
			if(control){
				user[j] = datos [i];
			}else{
				pass[j] = datos [i];
			}
		}
		i++;
		j++;
	}
};
