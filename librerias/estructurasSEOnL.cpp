#include "estructurasSEOnL.hpp"

/*
struct mensaje {
		uint8_t codigo;
		uint8_t subcodigo;
		uint16_t longitud;
		string datos;
};

struct pregunta {
		int id;
		string enunciado;
		string opciones[3];
};

struct evaluacion {
		int id;
		string titulo;
		struct pregunta preguntas[20];
};
*/

struct pregunta cargarPregunta (int id, string enunciado){
	struct pregunta p;
	p.id = id;
	p.enunciado = enunciado;
	return p;
};

void cargarOpcionPregunta (struct pregunta& p, int pos, string opcion){
	p.opciones[pos] = opcion;
};
 
void imprimirPregunta (struct pregunta p){
	cout << p.id << ") " << p.enunciado << endl;
	for (int i=0; !p.opciones[i].empty(); i++ ){
		cout << " "<< (i+1) << ".- " << p.opciones[i] << endl;
	}
}; 
 
struct evaluacion cargarEvaluacion (int id, string titulo){
	struct evaluacion e;
	e.id = id;
	e.titulo = titulo;
	return e;
};

void cargarPreguntaEvaluacion (struct evaluacion& e, int pos, struct pregunta preg){
	e.preguntas[pos] = preg;
};

void imprimirExamen (struct evaluacion e){
	cout << e.id << ") "<< e.titulo << endl; 
};

void cargarMensaje (struct mensaje* msj, uint8_t codigo,uint8_t subcodigo, string dat){
	msj->codigo = codigo;
	msj->subcodigo = subcodigo;
	msj->longitud = 8 + 8 + dat.size();
	msj->datos = dat;
};
