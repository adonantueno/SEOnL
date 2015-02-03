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
		int correcta;
};
struct evaluacion {
		int id;
		char titulo [20];
		struct pregunta preguntas[20];
};
struct alumno {
	char legajo [11];
	char apellido [30];
	char user [10];
	char password [10];
};
* */
struct resultado {
	int idEvaluacion;
	char tituloEvaluacion [20];
	char legajoAlumno [11];
	char apellidoAlumno [30];
	float nota;
};

struct pregunta cargarPregunta (int id, char enunciado[250]){

	struct pregunta p;
	p.id = id;
	strcpy ( p.enunciado , enunciado );
	return p;
};

void cargarOpcionPregunta (struct pregunta& p, int pos, char opcion[50]){
	strcpy (p.opciones[pos], opcion);
};

void imprimirPregunta (struct pregunta p){
	cout << p.id << ") " << p.enunciado << endl;

	for (int i=0; i < 3; i++ ){
		cout << " "<< (i+1) << ".- " << p.opciones[i] << endl;
	}
};

struct evaluacion cargarEvaluacion (int id, char titulo[20]){

	struct evaluacion e;
	e.id = id;
	strcpy ( e.titulo, titulo );
	return e;
};

void cargarPreguntaEvaluacion (struct evaluacion& e, int pos, struct pregunta preg){
	e.preguntas[pos] = preg;
};

void imprimirEvaluacion (struct evaluacion e){
	cout << e.id << ") "<< e.titulo << endl;
};

void cargarMensaje (struct mensaje* msj, uint16_t codigo,uint16_t subcodigo,uint32_t longitud ,char datos [300]){
	msj->codigo = codigo;
	msj->subcodigo = subcodigo;
	msj->longitud = longitud;
	strcpy ( msj->datos, datos );
};

struct resultado crearResultado (int idEvaluacion,char tituloEvaluacion [20],char legajoAlumno [11],char apellidoAlumno [30],float nota){

	struct resultado r;

	r.idEvaluacion = idEvaluacion;
	strcpy ( r.tituloEvaluacion, tituloEvaluacion );
	strcpy ( r.legajoAlumno, legajoAlumno );
	strcpy ( r.apellidoAlumno, apellidoAlumno );
	r.nota = nota;

	return r;
};
