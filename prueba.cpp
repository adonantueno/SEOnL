#include "librerias/estructurasSEOnL.hpp"
#include <iostream>
using namespace std;

int main (){
	struct mensaje m;	
	struct pregunta p;
	string enunciado = "un enunciado";
	string opcion;	
	p = cargarPregunta(1, enunciado);
	 opcion = "verdadero";
	cargarOpcionPregunta(p, 0, opcion); 
	 opcion = "falso";
	cargarOpcionPregunta(p, 1, opcion);
	 
	struct evaluacion e;
	string titulo = "Primer parcial";
	 e = cargarEvaluacion(1,titulo);
	 cargarPreguntaEvaluacion (e,1,p);

	imprimirExamen(e);
	imprimirPregunta(p);
	m.longitud = 10;
	m.codigo = 2;
	m.subcodigo = 101;
	cout << m.longitud << m.codigo  << m.subcodigo << endl;

		return 0;
}
