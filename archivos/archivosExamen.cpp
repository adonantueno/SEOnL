#include <iostream>
#include <string.h>
#include <stdint.h>
#include <iomanip>
#include <fstream>
#include "/home/adonantueno/Documents/UTN-FRLP/ProyectoWorking/working/librerias/archivosSEOnL.hpp"

using namespace std;

//#define PATH_EVALUACIONES = "Evaluaciones.dat";

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

int cargarEvaluacion_A (struct alumno* a);

int leerEvaluacion_A (struct alumno* a);

int main (){

    struct evaluacion e2;

    FILE * archivoEvaluaciones;
	long nRegistros;
    archivoEvaluaciones = fopen("evaluaciones.dat", "r");
    fseek(archivoEvaluaciones, 0, SEEK_END); 						// Colocar el cursor al final del fichero
    nRegistros = ftell(archivoEvaluaciones)/sizeof(evaluacion);
	cout << "tiene " << nRegistros << " registro/s " << endl;
    for (int i=0 ; i< nRegistros ; i++ ) {
        fseek(archivoEvaluaciones, i * sizeof(evaluacion), SEEK_SET);
        fread(&e2, sizeof(evaluacion), 1, archivoEvaluaciones);
        cout << e2.id << " " << e2.titulo << endl;
        int cont = 0;
        while ( !e2.preguntas[cont].id == 0)
		{		
			cout << "id: " << e2.preguntas[cont].id << endl;
			cout << "enunciado: " << e2.preguntas[cont].enunciado << endl;
			for (int j = 0; j < 3; j++)
			{
				cout << "	opcion: "<< j+1 << " " << e2.preguntas[cont].opciones[j] << endl;
			}
			cout << "	correcta: " << e2.preguntas[cont].correcta << endl;
			cont++;
		}        
    }
    fclose(archivoEvaluaciones);
}

/*	HAY QUE VER PORQUE DEFINO EL LUGAR DONDE ESTAN LAS CABECERAS PERO QUIZA PUEDAN QUEDAR DIRECTAMENTE AQUI...
 * 
int cargarEvaluacion_A (struct evaluacion* e){

    FILE *archivoEvaluaciones;
    archivoEvaluaciones = fopen(PATH_EVALUACIONES, "a");

    fwrite(e, sizeof(evaluacion), 1, archivoEvaluaciones);

    fclose(archivoEvaluaciones);

    return 0;
};

int leerEvaluacion_A (struct evaluacion* e, int i){

    FILE *archivoEvaluaciones;
    archivoEvaluaciones = fopen(PATH_EVALUACIONES, "r");

    fseek(archivoEvaluaciones, i * sizeof(evaluacion), SEEK_SET);
    fread(e, sizeof(evaluacion), 1, archivoEvaluaciones);

    fclose(archivoEvaluaciones);

    return 0;
};
*/
