#include "archivosSEOnL.hpp"
#include "estructurasSEOnL.hpp"

#define PATH_ALUMNOS  "archivos/alumnos.dat"
#define PATH_EVALUACIONES "archivos/evaluaciones.dat"
#define PATH_RESULTADOS "archivos/resultados.dat"


/*
 * General para todos
*/

long calcularRegistros (char* path, int size){

    long nRegistros;

    FILE *archivo;
    archivo = fopen(path, "r");

    fseek(archivo, 0, SEEK_END); // Colocar el cursor al final del fichero

    // nRegistros = ftell(archivo)/sizeof(alumno);
    nRegistros = ftell(archivo)/size;

    return nRegistros;
};

/*
 * TRABAJAMOS SOBRE alumnos.dat
*/

int cargarAlumno_A (struct alumno* a){

    FILE *archivoAlumnos;
    archivoAlumnos = fopen(PATH_ALUMNOS, "a");

    //fseek(archivoAlumnos, sizeof(alumno), SEEK_SET);
    fwrite(a, sizeof(alumno), 1, archivoAlumnos);

    fclose(archivoAlumnos);

    return 0;
};

int leerAlumno_A (struct alumno* a, int i){

    FILE *archivoAlumnos;
    archivoAlumnos = fopen(PATH_ALUMNOS, "r");

    fseek(archivoAlumnos, i * sizeof(alumno), SEEK_SET);
    fread(a, sizeof(alumno), 1, archivoAlumnos);

    fclose(archivoAlumnos);

    return 0;
};

int validarAlumno_A (char* user,char* pass){

    struct alumno a;

    int control = 0;
    long i = 0;

    long n = calcularRegistros(PATH_ALUMNOS, sizeof(alumno));

    while ( !control && i < n){
        leerAlumno_A(&a, i);

        if (!  strcmp(user,a.user)){
            if (!  strcmp(pass,a.password)){
                        control = 1;
            }
        }
        i++;
    }
    return control;
};


/*
 * TRABAJAMOS SOBRE evaluaciones.dat
*/

int cargarEvaluacion_A (struct evaluacion* e){

    FILE *archivoEvaluaciones;
    archivoEvaluaciones = fopen(PATH_EVALUACIONES, "a");

    fwrite(e, sizeof(evaluacion), 1, archivoEvaluaciones);

    fclose(archivoEvaluaciones);

    return 0;
}

int leerEvaluacion_A (struct evaluacion* e, int i){

    FILE *archivoEvaluaciones;
    archivoEvaluaciones = fopen(PATH_ALUMNOS, "r");

    fseek(archivoEvaluaciones, i * sizeof(evaluacion), SEEK_SET);
    fread(e, sizeof(alumno), 1, archivoEvaluaciones);

    fclose(archivoEvaluaciones);

    return 0;
}

/*
 * TRABAJAMOS SOBRE resultados.dat
*/


int cargarResultadoAlumno_A (char* resultado){

    return 0;
}

int leerResultadosAlumnos_A (char* resultados){

    return 0;
}
