#include "estructurasSEOnL.hpp"

/*
struct mensaje {
		uint16_t codigo;
		uint16_t subcodigo;
		uint32_t longitud;
		char datos [300]; //numero maximo de datos a enviar
};

struct pregunta {
		int id;
		char enunciado[250]; //los números de caracteres los saque de un texto
		char opciones[3][50];
};
struct evaluacion {
		int id;
		char titulo [20];
		struct pregunta preguntas[20];
};
*/

struct pregunta cargarPregunta (int id, char enunciado[250]){

	struct pregunta p;
	p.id = id;
	strncpy ( p.enunciado , enunciado , sizeof(enunciado));
	return p;
};

void cargarOpcionPregunta (struct pregunta& p, int pos, char opcion[50]){
	strncpy (p.opciones[pos], opcion , sizeof(opcion));
};
 
void imprimirPregunta (struct pregunta p){
	cout << p.id << ") " << p.enunciado << endl;

	for (int i=0; !sizeof(p.opciones[i]); i++ ){
		cout << " "<< (i+1) << ".- " << p.opciones[i] << endl;
	}
}; 

struct evaluacion cargarEvaluacion (int id, char titulo[20]){

	struct evaluacion e;
	e.id = id;
	strncpy ( e.titulo, titulo , sizeof(titulo));
	return e;
};

void cargarPreguntaEvaluacion (struct evaluacion& e, int pos, struct pregunta preg){
	e.preguntas[pos] = preg;
};

void imprimirExamen (struct evaluacion e){
	cout << e.id << ") "<< e.titulo << endl; 
};

void cargarMensaje (struct mensaje* msj, uint16_t codigo,uint16_t subcodigo,uint32_t longitud ,char datos [300]){
	msj->codigo = codigo;
	msj->subcodigo = subcodigo;
	msj->longitud = longitud;
	strncpy ( msj->datos, datos , sizeof(datos));
};
