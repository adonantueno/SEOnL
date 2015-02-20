#include "archivosSEOnL.hpp"
#include "estructurasSEOnL.hpp"

/*
 * General para todos
*/

long calcularRegistros (char* path, int size){

    long nRegistros;

    FILE *archivo;
    archivo = fopen(path, "r");

    fseek(archivo, 0, SEEK_END); // Colocar el cursor al final del fichero

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

int validarAlumno_A (char* user,char* pass, struct alumno* alu){

    struct alumno a;

    int control = 0;
    long i = 0;

    long n = calcularRegistros(PATH_ALUMNOS, sizeof(alumno));

    while ( !control && i < n){
        leerAlumno_A(&a, i);
        if (!  strcmp(user,a.user)){
            if (!  strcmp(pass,a.password)){
                        control = 1;
                        strcpy (alu->apellido,a.apellido);
                        strcpy (alu->legajo,a.legajo);
            }
        }
        i++;
    }
    return control;
};

int verificarDatosAlumno_A (struct alumno* a){

    struct alumno alumno;

    int control = 0;
    long i = 0;

    long n = calcularRegistros(PATH_ALUMNOS, sizeof(alumno));

    while ( !control && i < n){
        leerAlumno_A(&alumno, i);

        if (!  strcmp(a->user,alumno.user)){
            control = -1;
        }
        if (!strcmp(a->legajo,alumno.legajo) || !strcmp(a->apellido,alumno.apellido)){
            control = 1;
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
};

int leerEvaluacion_A (struct evaluacion* e, int i){

    FILE *archivoEvaluaciones;
    archivoEvaluaciones = fopen(PATH_EVALUACIONES, "r");

    fseek(archivoEvaluaciones, i * sizeof(evaluacion), SEEK_SET);
    fread(e, sizeof(evaluacion), 1, archivoEvaluaciones);

    fclose(archivoEvaluaciones);

    return 0;
};

int buscarEvaluacion_A (struct evaluacion* e, int id){

    struct evaluacion evaluacion;

    int control = 0;
    long i = 0;

    long n = calcularRegistros(PATH_EVALUACIONES, sizeof(evaluacion));

    while ( !control && i < n){
        leerEvaluacion_A(&evaluacion, i);
        if ( e->id == id){
            control = 1;
        }
        i++;
    }
    return control;
};
/*
 * TRABAJAMOS SOBRE resultados.dat
*/


int cargarResultadoAlumno_A (struct resultado* r){

    FILE *archivoResultados;

    archivoResultados = fopen(PATH_RESULTADOS, "a");
    fwrite(r, sizeof(resultado), 1, archivoResultados);
    fclose(archivoResultados);

    return 0;
};

int leerResultadoAlumnos_A (struct resultado* r, int i){


    FILE *archivoResultados;
    archivoResultados = fopen(PATH_RESULTADOS, "r");

    fseek(archivoResultados, i * sizeof(resultado), SEEK_SET);
    fread(r, sizeof(resultado), 1, archivoResultados);

    fclose(archivoResultados);

    return 0;
};

void verificarPendientes_A (char* legajo, int id, char* datosEvaluacion){


    struct resultado resultado;

    int control = 0;
    long i = 0;

    long n = calcularRegistros(PATH_RESULTADOS, sizeof(resultado));


    while ( !control && i < n){
        leerResultadoAlumnos_A(&resultado, i);

        if (!strcmp(resultado.legajoAlumno,legajo) && resultado.idEvaluacion == id){
            control = -1;
            strcpy (datosEvaluacion,"");
        }
        i++;
    }
};
