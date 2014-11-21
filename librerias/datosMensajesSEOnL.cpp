#include "datosMensajesSEOnL.hpp"


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

void crearDatosMensaje1(char* user, char* pass, char* datos){

	strncat(datos,user,sizeof(datos));
	strncat(datos,"&",sizeof(datos));
	strncat(datos,pass,sizeof(datos));

};

void interpretarDatosMensaje1 (char* user, char* pass, char* datos){
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
