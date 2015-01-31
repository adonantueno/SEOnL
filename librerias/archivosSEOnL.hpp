#ifndef  ARCHIVOS_H
#define  ARCHIVOS_H

#include <iomanip>
#include <fstream>
#include <string.h>

using namespace std;


#define PATH_ALUMNOS  "archivos/alumnos.dat"
#define PATH_EVALUACIONES "archivos/evaluaciones.dat"
#define PATH_RESULTADOS "archivos/resultados.dat"

/* FUNCION : CALCULAR REGISTROS -ARCHIVO-
 * ENTRADA : path (un define de la lista de la libreria) - size del registro
 * SALIDA  : long
 * DESCRIPCION : calcula la cantaidad de registros que tiene el archivo almacenado
 * en el path correspondiente. Modos de uso:
           - calcularRegistros(PATH_ALUMNOS, sizeof(alumno));
           - calcularRegistros(PATH_EVALUACIONES, sizeof(evaluacion));
           - calcularRegistros(PATH_RESULTADOS, sizeof(resultado));
 */
long calcularRegistros (char* path, int size);

// ------------------------ ALUMNOS ------------------------------------

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



// ------------------------ EVALUACIONes ------------------------------------

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

/* FUNCION : BUSCAR EVALUACION -ARCHIVO-
 * ENTRADA : struct evaluacion,  int
 * SALIDA  : int - modificación del parámetro evaluacion (e)
              0 - No encontró la evaluacion del id ingresado - evaluacion (e) vacio
              1 - Se encontró la evaluacion del id ingresado - evaluacion (e)
 * DESCRIPCION : busca dentro del archivo las evaluaciones y devuelve si es que
 * la encuentra en el parámetro e
 */
int buscarEvaluacion_A (struct evaluacion* e, int id);

 // ------------------------ RESULTADOS ------------------------------------

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
 * ENTRADA : char* legajo, int id, char* datosEvaluacion
 * SALIDA  : null
 * DESCRIPCION : lee la lista de evaluaciones,y si no encuentra al alumno en la
 * lista de resultados, modifica el continido de datosEvalucion.
 */
void verificarPendientes_A (char* legajo, int id, char* datosEvaluacion);

#endif
