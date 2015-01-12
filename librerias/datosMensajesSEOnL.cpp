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

/*MENSAJE 0*/

void crearDatos_M0(char* user, char* pass, char* datos){

	strncat(datos,legajo,sizeof(datos));
	strncat(datos,"&",sizeof(datos));
	strncat(datos,nombre,sizeof(datos));
    strncat(datos,"&",sizeof(datos));
    strncat(datos,user,sizeof(datos));
};

void interpretarDatos_M0 (char* user, char* pass, char* datos){

	 int control = 0;
 	int i = 0;
 	int j = 0;
 	char ampersand = '&';

    while ( i < strlen(datos1)){
        if (datos1[i] == ampersand){
            control++;
        	j= -1;
        }
		if(control == 0){
				legajo1[j] = datos1 [i];
			}
        if (control == 1){
				nombre1[j] = datos1 [i];
		}

        if (control == 2){
				user1[j] = datos1 [i];
		}
		i++;
		j++;
	}
};


/*MENSAJE 1*/

void crearDatos_M1(char* user, char* pass, char* datos){

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
