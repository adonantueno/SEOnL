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
	strncat(datos,user,strlen(user)); 	//al ejecutar el código se ve afectada la cadena y la data es modificada probare conb strlen
	strncat(datos,"&",sizeof(datos));
	strncat(datos,pass,strlen(pass));	//al ejecutar el código se ve afectada la cadena y la data es modificada probare conb strlen

	cout << datos << endl;

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
				user[j+1] = '\0';
			}else{
				pass[j] = datos [i];
				pass[j+1] = '\0';
			}
		}
		i++;
		j++;
	}
};
/*MENSAJE 101 --> IMPLEMENTE STRLEN POR UNICIDAD CON LA CREACION DE LOS DEMAS MENSAJES*/
void crearDatos_M101(char* apellido, char* legajo, char* listaEvaluaciones, char* datos){

	strcpy (datos, "");
	//strncat(datos,apellido,sizeof(datos)+sizeof(apellido));
		strncat(datos,apellido,strlen(datos)+strlen(apellido));
	
	//strncat(datos,"&",sizeof(datos)+sizeof("&"));
		strncat(datos,"&",strlen(datos)+strlen("&"));
		
	//strncat(datos,legajo,sizeof(datos)+sizeof(legajo));
		strncat(datos,legajo,strlen(datos)+strlen(legajo));
		
	//strncat(datos,"&",sizeof(datos)+sizeof("&"));
		strncat(datos,"&",strlen(datos)+strlen("&"));	
	
	//strncat(datos,listaEvaluaciones,sizeof(datos)+sizeof(listaEvaluaciones));
		strncat(datos,listaEvaluaciones,strlen(datos)+strlen(listaEvaluaciones));
	
};

void interpretarDatos_M101 (char* apellido, char* legajo, char* listaEvaluaciones, char* datos){
	int control = 0;
	int i = 0;
	int j = 0;
	char ampersand = '&';

	while ( i < strlen(datos)){

		if (datos[i] == ampersand){
			control++;
			j= -1;
		}
		if(control == 0){
			apellido[j] = datos [i];
			apellido[j+1] = '\0';
		}
		if (control == 1){
			legajo[j] = datos [i];
			legajo[j+1] = '\0';
		}
		if (control == 2){
			listaEvaluaciones[j] = datos [i];
			listaEvaluaciones[j+1] = '\0';
		}
		i++;
		j++;
	}
};
