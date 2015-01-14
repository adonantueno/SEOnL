#include "archivosSEOnL.hpp"


int cargarAlumno_A(char* user, char* pass, char* legajo, char* nombre){
    char datos [60] = "";

    strncat(datos,user,sizeof(datos));
	strncat(datos,"&",sizeof(datos));
	strncat(datos,pass,sizeof(datos));
    strncat(datos,"&",sizeof(datos));
    strncat(datos,legajo,sizeof(datos));
    strncat(datos,"&",sizeof(datos));
    strncat(datos,nombre,sizeof(datos));

     ofstream archivo;
     archivo.open("archivos/alumnos.dat", ios::out );
     archivo << datos;
     archivo.close();

    return 0;
}

int LeerAlumnos_A (char* datosAlumno){


    return 0;
}

int cargarExamen_A (char* datosExamen){

    return 0;
}

int leerExamen_A (char* datosExamen){

    return 0;
}

int cargarResultadoAlumno_A (char* resultado){

    return 0;
}

int leerResultadosAlumnos_A (char* resultados){

    return 0;
}
