#ifndef  ESTRUCTURAS_H
#define  ESTRUCTURAS_H
#include <iostream>
#include <string>
using namespace std;

/*
 * ESTRUCTURA: mensaje
 * codigo: identificador del mensaje
 * subcodigo: propio del tipo de mensaje de ACK
 * longitud: longitud total del mesaje incluida la cabecera
 * datos: contenido del mensaje
 */
struct mensaje {
		uint8_t codigo;
		uint8_t subcodigo;
		uint16_t longitud;
		string datos;
};
/*
 * ESTRUCTURA: pregunta
 * id: identificador único de la pregunta
 * enunciado: enunciado de la pregunta del examen
 * opciones: array de opciones con un límite de 3.
 * */
struct pregunta {
		int id;
		string enunciado;
		string opciones[3];
};

/*
 * ESTRUCTURA: evaluacion
 * id: identificador único de la evaluación
 * titulo: titulo o nombre de la avaluación
 * preguntas: array de preguntas de la evaluacion con un limite de 20
 *  * */
struct evaluacion {
		int id;
		string titulo;
		struct pregunta preguntas[20];
};

/* METODOS */

/* 
 * FUNCION : CARGAR PREGUNTA
 * ENTRADA : int id de la pregunta, string enunciado de la pregunta
 * SALIDA  : estructura del tipo pregunta
 * DESCRIPCION : devuelve una estructura del tipo pregunta con los campos
 * modificados segun los parametros ingresados
*/
struct pregunta cargarPregunta (int id, string enunciado);

/* FUNCION : CARGAR OPCION PREGUNTA
 * ENTRADA : estructura del tipo pregunta (referencia) int numero de 
 * opcion,string enunciado de la pregunta
 * SALIDA  : void - campos modificados en la estructura referenciada
 * DESCRIPCION : le agregar una opcion a la estructura pasada por referencia
 *  en la posicion indicada
*/
void cargarOpcionPregunta (struct pregunta& p, int pos, string opcion);

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
struct evaluacion cargarEvaluacion (int id, string titulo);

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
 * FUNCION : IMPRIMIR EXAMEN
 * ENTRADA : estructura del tipo examen
 * SALIDA  : impresion por pantalla
 * DESCRIPCIÓN : imprime por un formato determinado (2) la evaluacion
 * recibida como parámetro
 * (2) formato
 * evaluacion.id ) evaluacion.titulo
 */
void imprimirExamen (struct evaluacion e);


#endif
