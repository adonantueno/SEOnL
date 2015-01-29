#ifndef  ARCHIVOS_H
#define  ARCHIVOS_H

#include <iomanip>
#include <fstream>
#include <string.h>

using namespace std;

/* FUNCION : CARGAR ALUMNO -ARCHIVO-
 * ENTRADA :  struct alumno
 * SALIDA  : int
 * DESCRIPCION : a partir de la información del alumno a que recibe como parametro,
 * los almacena en el archivo.
 */
int cargarAlumno_A (struct alumno* a);

/* FUNCION : LEER ALUMNO -ARCHIVO-
 * ENTRADA : struct alumno
 * SALIDA  : void - modificación del parámetro alumno (a)
 * DESCRIPCION : lee el alumno ubicado en la posicion i del archivo.
 ADVERTENCA: si i es mayor al número de registros, devuelve el último registro.
 */
int leerAlumno_A (struct alumno* a, int i);

/* FUNCION : VALIDAR ALUMNO -ARCHIVO-
 * ENTRADA : user, pass
 * SALIDA  : 1 -> Encontro el alumno
             0 -> No encontro el alumno
 * DESCRIPCION : lee el archivo de alumnos y compara cada uno de los almacenados
 * con los parametros ingresados, si encuentra conincidencia retorna 1 informando
 * que los datos corresponden a algun registro. Si lo encuentra, ademas retorna
 * en el parámetro "alumno" los datos correspondientes al mismo.
*/
int validarAlumno_A (char* user,char* pass, struct alumno* alu);

/* FUNCION : VERICAR DATOS ALUMNO -ARCHIVO-
 * ENTRADA :  struct alumno
 * SALIDA  : 1 -> Encontro el alumno coincidiendo legajo o APELLIDO
             0 -> No encontro el alumno
            -1 -> Encontro el alumno coincidiendo user
 * DESCRIPCION : lee el archivo de alumnos y compara cada uno de los almacenados
 * con los parametros ingresados, si encuentra conincidencia retorna segun lo
 * corresponda -1 o 1. Devuelve 0 de no encontrar nada.
*/
int verificarDatosAlumno_A (struct alumno* a);

/* FUNCION : CARGAR EVALUACION -ARCHIVO-
 * ENTRADA :  struct evaluacion
 * SALIDA  : int
 * DESCRIPCION : a partir de la información de la evaluacion que recibe como parametro,
 * la almacena en el archivo.
 */
int cargarEvaluacion_A (struct evaluacion* e);

/* FUNCION : LEER EVALUACION -ARCHIVO-
 * ENTRADA : struct evaluacion,  int
 * SALIDA  : int - modificación del parámetro evaluacion (e)
 * DESCRIPCION : lee la evaluacion ubicada en la posicion i del archivo.
 ADVERTENCA: si i es mayor al número de registros, devuelve el último registro.
 */
int leerEvaluacion_A (struct evaluacion* e, int i);

/* FUNCION : CARGAR RESULTADO -ARCHIVO-
 * ENTRADA :  struct resultado
 * SALIDA  : int
 * DESCRIPCION : a partir de la información del resultados que recibe como parametro,
 * lo almacena en el archivo.
 */
int cargarResultadoAlumno_A (struct resultado* r);

/* FUNCION : LEER RESULTADO -ARCHIVO-
 * ENTRADA : struct resultado,  int
 * SALIDA  : int - modificación del parámetro resultado (r)
 * DESCRIPCION : lee el resultado ubicado en la posicion i del archivo.
 ADVERTENCA: si i es mayor al número de registros, devuelve el último registro.
 */
int leerResultadosAlumnos_A (struct resultado* r, int i);

/* FUNCION : VERIFICAR PENDIENTES-ARCHIVO-
 * ENTRADA :
 * SALIDA  : char* con dos posibles resultados
  : 1 - Evaluacion Pendiente --> codigo y titulo de la evaluacion
  : 2 - Sin Evaluacion Pendiente --> texto "SinEvaluaciones" ?? null
 * DESCRIPCION : lee la lista de evaluaciones,y si no encuentra al alumno en la
 * lista de resultados lo pone como pendiente
 */
char* verificarPendientes_A ();

#endif
