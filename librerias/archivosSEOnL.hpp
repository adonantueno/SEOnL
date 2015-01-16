#ifndef  ARCHIVOS_H
#define  ARCHIVOS_H


#include <iomanip>
#include <fstream>
#include <string.h>
using namespace std;

/* FUNCION : CARGAR ALUMNO -ARCHIVO-
 * ENTRADA :  user, pass, legajo, nombre
 * SALIDA  : int - 0--> cargado correctamente 1--> error I/O
 * DESCRIPCION : a partir de la información del alumno que recibe como parametros.
 los almacena en el archivo de la forma user&pass&legajo&nombre
 */
int cargarAlumno_A (struct alumno a);

int cargarAlumno_A(char* user, char* pass, char* legajo, char* nombre);

int LeerAlumnos_A (char* datosAlumno);

int cargarExamen_A (char* datosExamen);

int leerExamen_A (char* datosExamen);

int cargarResultadoAlumno_A (char* resultado);

int leerResultadosAlumnos_A (char* resultados);



#endif
