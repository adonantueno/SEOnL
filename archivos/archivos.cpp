#include <iostream>
#include <string.h>
#include <stdint.h>
#include <iomanip>
#include <fstream>

using namespace std;

struct alumno {
	char legajo [11];
	char apellido [30];
	char user [10];
	char password [10];
};

int cargarAlumno_A (struct alumno* a);

int LeerAlumno_A (struct alumno* a);

int main (){

    struct alumno a1;

    struct alumno a2;

    FILE * archivoAlumnos;
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



    archivoAlumnos = fopen("alumnos.dat", "r");


    fseek(archivoAlumnos, 0, SEEK_END); // Colocar el cursor al final del fichero
    nRegistros = ftell(archivoAlumnos)/sizeof(alumno);

	cout << "tiene " << nRegistros << " registros " << endl;

    for (int i=0 ; i< nRegistros ; i++ ) {

        fseek(archivoAlumnos, i * sizeof(alumno), SEEK_SET);
        fread(&a2, sizeof(alumno), 1, archivoAlumnos);
        cout << a2.legajo << " " << a2.password <<" " << a2.apellido << " " << a2.user << endl;
    }
    fclose(archivoAlumnos);


}


int cargarAlumno_A (struct alumno* a){

    FILE *archivoAlumnos;
    fseek(archivoAlumnos, sizeof(alumno), SEEK_SET);
    fwrite(&a, sizeof(alumno), 1, archivoAlumnos);
    fclose(archivoAlumnos);

    return 0;
}

int LeerAlumno_A (struct alumno* a){

    struct alumno* alu;

    FILE *archivoAlumnos;
    archivoAlumnos = fopen("archivos/alumnos.dat", "r");

    fseek(archivoAlumnos, sizeof(alumno), SEEK_SET);
    fread(&alu, sizeof(alumno), 1, archivoAlumnos);

    cout << alu->legajo << " " << alu->password <<" " << alu->apellido << " " << alu->user << endl;
    fclose(archivoAlumnos);

    return 0;
}
