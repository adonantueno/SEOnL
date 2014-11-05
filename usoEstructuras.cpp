#include <iostream>
#include <string>
using namespace std;

int main () {
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

	evaluacion e;
	pregunta p;
		
	e.id = 1;
	cout << "Ingrese titulo de la Evaluación : "; getline(cin,e.titulo);
	cout << endl;
	cout << " A CONTUNUACION COMIENZA EL INGRESO DE PREGUNTAS "<< endl;
	for (int i=0; i< 2; i++){
		p.id = i;
		cout << "Ingrese Enunciado : ";getline(cin,p.enunciado);
		cout << endl;
		cout << " A CONTUNUACION COMIENZA EL INGRESO DE  OPCIONES "<< endl;
		cout << " (PRIMERO INGRESE LA CORRECTA) "<< endl;
		for(int j =0; j<3; j++){
			cout << "Ingrese opcion "<< j+1 <<": ";getline(cin,p.opciones[j]);
		cout << endl;
		}
		e.preguntas[i] = p;
	}
	
	cout << " Examen Creado!!! "<< endl;
	cout << "Evaluación "<< e.id << " :: " << e.titulo << endl ;
	cout << "Preguntas "<< endl;
	for (int i=0; i< 2; i++){
		p.id = i;
		cout << " Enunciado :" << e.preguntas[i].enunciado << endl;
		cout << " Opciones "<< endl;
		for(int j =0; j<3; j++){
			cout << j+1 <<") " << e.preguntas[i].opciones[j] << endl;
		}
	}	
	return 0;
}

