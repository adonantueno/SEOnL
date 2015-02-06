#ifndef  ESTRUCTURAS_H
#define  ESTRUCTURAS_H

#include <iostream>
#include <string.h>
#include <stdint.h>

using namespace std;

/*
 * ESTRUCTURA: mensaje
 * codigo: identificador del mensaje
 * subcodigo: propio del tipo de mensaje de ACK
 * longitud: longitud total del mesaje incluida la cabecera
 * datos: contenido del mensaje
 */
struct mensaje {
		uint16_t codigo;
		uint16_t subcodigo;
		uint32_t longitud;
		char datos [500]; //numero maximo de datos a enviar
};
/*
 * ESTRUCTURA: pregunta
 * id: identificador único de la pregunta
 * enunciado: enunciado de la pregunta de la evaluacion
 * opciones: array de opciones con un límite de 3.
 * */
struct pregunta {
		int id;
		char enunciado[250]; //los números de caracteres los saque de un texto
		char opciones[3][50];
		int correcta;
};

/*
 * ESTRUCTURA: evaluacion
 * id: identificador único de la evaluación
 * titulo: titulo o nombre de la avaluación
 * preguntas: array de preguntas de la evaluacion con un limite de 20
 *  * */
struct evaluacion {
		int id;
		char titulo [20];
		struct pregunta preguntas[20];
};

/*
* ESTRUCTURA: alumno
* legajo: identificador del alumno universitario
* apellido: apellido del alumno
* user: nombre del usuario en el sistma utilizado para el login
* password: contraseña del alumno.
*/

struct alumno {
	char legajo [11];
	char apellido [30];
	char user [10];
	char password [10];
};

/*
* ESTRUCTURA: resultado
* idEvaluacion: identificador de la evaluacion realizada
* TituloEvaluacion: titulo o nombre de la avaluación
* legajo: identificador del alumno universitario
* apellido: apellido del alumno
* nota: resultado de la evaluacion realizada por el alumno.
*/

struct resultado {
	int idEvaluacion;
	char tituloEvaluacion [20];
	char legajoAlumno [11];
	char apellidoAlumno [30];
	int nota;
};


/* FUNCIONES */

/*
 * FUNCION : CARGAR PREGUNTA
 * ENTRADA : int id de la pregunta, string enunciado de la pregunta
 * SALIDA  : estructura del tipo pregunta
 * DESCRIPCION : devuelve una estructura del tipo pregunta con los campos
 * modificados segun los parametros ingresados
*/
struct pregunta cargarPregunta (int id, char enunciado[250]);

/* FUNCION : CARGAR OPCION PREGUNTA
 * ENTRADA : estructura del tipo pregunta (referencia) int numero de
 * opcion,string enunciado de la pregunta
  * SALIDA  : void - campos modificados en la estructura referenciada
 * DESCRIPCION : le agregar una opcion a la estructura pasada por referencia
 *  en la posicion indicada
*/
void cargarOpcionPregunta (struct pregunta& p, int pos, char opcion[50]);

/*
 * FUNCION : IMPRIMIR PREGUNTA
 * ENTRADA : estructura del tipo pregunta
 * SALIDA  : impresion por pantalla
 * DESCRIPCIÓN : imprime por un formato determinado (1) la pregunta
 *  recibida como parámetro
 * (1) formato
 * pregunta.id ) pregunta.enuncido
 *  i ) pregunta.opciones[i]
 */
void imprimirPregunta (struct pregunta p);

/*
 * FUNCION : CARGAR EVALUACION
 * ENTRADA : int id de la evaluacion, string titulo de la evaluacion
 * SALIDA  : estructura del tipo evaluacion
 * DESCRIPCION : devuelve una estructura del tipo evaluacion con los
 *  campos modificados segun los parametros ingresados
*/
struct evaluacion cargarEvaluacion (int id, char titulo[20]);

/*
 * FUNCION : CARGAR  PREGUNTA  EVALUACION
 * ENTRADA : estructura del tipo evaluacion (referencia), int numero de
 * pregunta, estructura del tipo pregunta
 * SALIDA  : void - campos modificados en la estructura referenciada
 * DESCRIPCION : le agregar una pregunta a la estructura pasada por referencia
 *  en la posicion indicada
*/
void cargarPreguntaEvaluacion (struct evaluacion& e, int pos, struct pregunta preg);

/*
 * FUNCION : IMPRIMIR EVALUACION
 * ENTRADA : estructura del tipo evaluacion
 * SALIDA  : impresion por pantalla
 * DESCRIPCIÓN : imprime por un formato determinado (2) la evaluacion
 * recibida como parámetro
 * (2) formato
 * evaluacion.id ) evaluacion.titulo
 */
void imprimirEvaluacion (struct evaluacion e);

/*
 * FUNCION : CARGAR MENSAJE
 * ENTRADA : codigo, subcodigo, longitud y campo de datos del mensaje
 * SALIDA  : puntero tipo mensaje
 * DESCRIPCIÓN : crea un mensaje segun caracteristicas del protocolo a
 * partir de los datos pasados por parametro.
 */
void cargarMensaje (struct mensaje* msj, uint16_t codigo,uint16_t subcodigo,uint32_t longitud ,char datos [300]);

/*
 * FUNCION : CREAR RESULTADO
 * ENTRADA : idEvaluacion, tituloEvaluacion, legajoAlumno,apellidoAlumno, nota
 * SALIDA  : estructura del tipo resultado.
 * DESCRIPCIÓN : crea un resultado a partir de los atrutos cargados a partir de
 * los parámatros asignados.
*/
struct resultado crearResultado (int idEvaluacion,char tituloEvaluacion [20],char legajoAlumno [11],char apellidoAlumno [30],int nota);

/*
 * FUNCION : IMPRIMIR RESULTADO
 * ENTRADA : estructura del tipo resultado
 * SALIDA  : impresion por pantalla
 * DESCRIPCIÓN : imprime por un formato determinado (3) el resultado
 * recibido como parámetro
 * (2) formato
 * resultado.tituloEvaluacion | resultado.legajoAlumno resultado.apellidoAlumno | resultado.nota
 */
void imprimirResultado(struct resultado resultado);
#endif
