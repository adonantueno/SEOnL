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
    /*archivoAlumnos = fopen("alumnos.dat", "a");

    strcpy (a1.legajo, "05-22811-4");
    strcpy (a1.apellido, "PASTORINO");
    strcpy (a1.user, "pas");
    strcpy (a1.password, "abc123");
    fwrite(&a1, sizeof(alumno), 1, archivoAlumnos);

    //fseek(archivoAlumnos, sizeof(alumno), SEEK_SET);
    //fwrite(&a1, sizeof(alumno), 1, archivoAlumnos);
    fclose(archivoAlumnos);*/

	long nRegistros;



    archivoEvaluaciones = fopen("evaluaciones.dat", "r");


    fseek(archivoEvaluaciones, 0, SEEK_END); // Colocar el cursor al final del fichero
    nRegistros = ftell(archivoEvaluaciones)/sizeof(evaluacion);

	cout << "tiene " << nRegistros << " registros " << endl;

    for (int i=0 ; i< nRegistros ; i++ ) {

        fseek(archivoEvaluaciones, i * sizeof(evaluacion), SEEK_SET);
        fread(&e2, sizeof(evaluacion), 1, archivoEvaluaciones);
        cout << e2.id << " " << e2.titulo << endl;
        while ( !e2.preguntas[i].id == 0)
		{		
			cout << "id: " << e2.preguntas[i].id << endl;
			cout << "enunciado: " << e2.preguntas[i].enunciado << endl;
			for (int j = 0; j < 3; j++)
			{
				cout << "	opcion: "<< j+1 << " " << e2.preguntas[i].opciones[j] << endl;
			}
			cout << "	correcta: " << e2.preguntas[i].correcta << endl;
			i++;
		}        
    }
    fclose(archivoEvaluaciones);


}

/*
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
