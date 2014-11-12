#include <iostream>
#include <string>
using namespace std;

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



