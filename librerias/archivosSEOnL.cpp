#include "archivosSEOnL.hpp"
#include "estructurasSEOnL.hpp"


int cargarAlumno_A (struct alumno* a){

    FILE *archivoAlumnos;
    archivoAlumnos = fopen("archivos/alumnos.dat", "a");

    //fseek(archivoAlumnos, sizeof(alumno), SEEK_SET);
    fwrite(a, sizeof(alumno), 1, archivoAlumnos);

    fclose(archivoAlumnos);

    return 0;
}

int leerAlumno_A (struct alumno* a, int i){

    FILE *archivoAlumnos;
    archivoAlumnos = fopen("archivos/alumnos.dat", "r");

    fseek(archivoAlumnos, i * sizeof(alumno), SEEK_SET);
    fread(a, sizeof(alumno), 1, archivoAlumnos);

    fclose(archivoAlumnos);

    return 0;
}

long calcularRegistros (){

    long nRegistros;

    FILE *archivoAlumnos;
    archivoAlumnos = fopen("archivos/alumnos.dat", "r");

    fseek(archivoAlumnos, 0, SEEK_END); // Colocar el cursor al final del fichero
    nRegistros = ftell(archivoAlumnos)/sizeof(alumno);

    return nRegistros;
}

int validarAlumno_A (char* user,char* pass){

    struct alumno a;

    int control = 0;
    long i = 0;

    long n = calcularRegistros();

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
}



int cargarExamen_A (char* datosExamen){

    return 0;
}

int leerExamen_A (char* datosExamen){

    return 0;
}

int cargarResultadoAlumno_A (char* resultado){

    return 0;
}

int leerResultadosAlumnos_A (char* resultados){

    return 0;
}
