/**
 * @file main.cpp
 * @brief Programa que permite la gestión de prof.getBaseDatos() de una asignatura.
 * @date 11-12-2018
 *
 * Este fichero forma parte del proyecto realizado para la gestión de prof.getBaseDatos(),
 * para la asignatura Ingeniería del Software de la Universidad de Córdoba.
 */

#include <stdlib.h>
#include <iostream>
#include <string>
#include "is.hpp"

#define MAX_ALUMNOS 150
#define FILE_CREDENCIALES "credenciales.bin"
#define FILE_BBDD_LOCAL "localdata.bin"

enum MENU_OPTS
{
    ADD_ALUMNO = 1,
    MODIFICAR = 2,
    BORRAR = 3,
    MOSTRAR = 4,
    GUARDAR = 5,
    CARGAR = 6,
    GUARDAR_COPIA = 7,
    CARGAR_COPIA = 8,
    ADD_PROFESOR = 9,
    SALIR = 0
};


void pulseEnter();
bool acceder(profesor &prof);
unsigned escribirMenu(bool esCoordinador);
void obtenerAlumno(alumno &a);
void mostrarAlumno(const alumno &a);
void mostrarAlumnos(std::list<alumno> &listaAlumnos);

int main(void)
{
    profesor prof;
    bool b;
    alumno alumnoAux;
    std::string stringAux;
    std::list<alumno> resultado;
    unsigned option;

    /*
    // Inicio de sesión del usuario.
    do {
        b = acceder(prof);
        if (not b) {
            std::cout << "Datos erróneos. Por favor, inténtelo otra vez. ";
            pulseEnter();
        }
    } while (not b); */

    do {
        switch(option = escribirMenu(prof.getEsCoordinador())) {
            case ADD_ALUMNO:
                if (prof.getBaseDatos().getNumeroAlumnos() >= MAX_ALUMNOS) {
                    std::cout << "El número máximo de alumnos ha sido alcanzado. ";
                }
                else {
                    obtenerAlumno(alumnoAux);
                    if (prof.getBaseDatos().anadirAlumno(alumnoAux) == true) {
                        std::cout << "Alumno añadido correctamente. ";
                    }
                    else {
                        std::cout << "Ha ocurrido algún problema durante la inserción. ";
                    }
                }
                pulseEnter();
                break;

            case MODIFICAR:
                if (prof.getBaseDatos().getNumeroAlumnos() == 0) {
                    std::cout << "La lista de alumnos está vacía. ";
                    pulseEnter();
                }
                break;

            case BORRAR:
                if (prof.getBaseDatos().getNumeroAlumnos() == 0) {
                    std::cout << "La lista de alumnos está vacía. ";
                }
                else {
                    std::system("clear");
                    std::cout << "BORRAR ALUMNO: " << std::endl;
                    std::cout << "\tDNI del alumno a eliminar: ";
                    std::cin >> stringAux;

                    b = prof.getBaseDatos().getAlumno(stringAux, alumnoAux);
                    if (b == true) {
                        std::cout << "El alumno seleccionado es el siguiente:" << std::endl;
                        mostrarAlumno(alumnoAux);
                        std::cout << "¿Desea eliminarlo de la base de datos? (S/N): ";
                        std::cin >> stringAux;
                        if (stringAux == "S" or stringAux == "s") {
                            prof.getBaseDatos().eliminarAlumno(alumnoAux.getDni());
                            std::cout << "Alumno eliminado correctamente. ";
                        }
                    }
                    else {
                        std::cout << "No se ha encontrado al alumno. ";
                    }
                }
                pulseEnter();
                break;

            case MOSTRAR:
                prof.getBaseDatos().buscarAlumnos(resultado, "", "", 0);
                mostrarAlumnos(resultado);
                std::cout << prof.getBaseDatos().getNumeroAlumnos() << " resultados coincidentes. ";
                pulseEnter();
                break;

            case GUARDAR:
                prof.getBaseDatos().guardarFichero(FILE_BBDD_LOCAL);
                std::cout << "Cambios guardados correctamente. ";
                pulseEnter();
                break;

            case CARGAR:
                prof.getBaseDatos().cargarFichero(FILE_BBDD_LOCAL);
                std::cout << "Datos cargados correctamente. ";
                pulseEnter();
                break;

            case GUARDAR_COPIA:
                if (prof.getEsCoordinador()) {
                    std::cout << "Indique el nombre de la copia de seguridad: ";
                    std::cin >> stringAux;
                    prof.getBaseDatos().guardarFichero(stringAux);
                    std::cout << "Copia de seguridad guardada correctamente. ";
                    pulseEnter();
                }
                break;

            case CARGAR_COPIA:
                if (prof.getEsCoordinador()) {
                    std::cout << "Indique el nombre de la copia de seguridad: ";
                    std::cin >> stringAux;
                    prof.getBaseDatos().cargarFichero(stringAux);
                    std::cout << "Datos cargados correctamente. ";
                    pulseEnter();
                }
                break;

            case ADD_PROFESOR:
                if (prof.getEsCoordinador()) {

                }
                break;

            case SALIR:
                break;
        }
    } while (option != SALIR); 

	exit(EXIT_SUCCESS);	
}

void pulseEnter() 
{
    std::cout << "Pulse ENTER para continuar. ";
    std::cin.ignore();
    std::cin.ignore();
}

bool acceder(profesor &prof) 
{
    std::string usuario;
    std::string password;

    std::system("clear");
    std::cout << "ACCEDER:" << std::endl;

    std::cout << "\tNombre de usuario: ";
    std::cin >> usuario;

    std::cout << "\tContraseña: ";
    std::cin >> password;

    return prof.iniciarSesion(FILE_CREDENCIALES, usuario, password);
}

// Imprime por pantalla el menu de opciones.
unsigned escribirMenu(bool esCoordinador) 
{
    unsigned option;

    std::system("clear");
    std::cout << "Menú de opciones:" << std::endl;
    std::cout << "\t1. Añadir alumno." << std::endl;
    std::cout << "\t2. Modificar alumno." << std::endl;
    std::cout << "\t3. Eliminar alumno." << std::endl;
    std::cout << "\t4. Mostrar alumno." << std::endl;
    std::cout << "\t5. Guardar cambios." << std::endl;
    std::cout << "\t6. Cargar cambios." << std::endl;

    // Opciones reservadas a los profesores coordinadores.
    if (esCoordinador) {
        std::cout << "\t7. Guardar copia de seguridad." << std::endl;
        std::cout << "\t8. Cargar copia de seguridad." << std::endl;
        std::cout << "\t9. Añadir profesor colaborador." << std::endl;
    }
    std::cout << "\t0. Salir del programa." << std::endl;

    // Se pide la opción al usuario.
    std::cout << "Seleccione opción: ";
    std::cin >> option;

    return option;
}

void obtenerAlumno(alumno &a)
{
    std::string aux;

    std::system("clear");
    std::cout << "AÑADIR ALUMNO: " << std::endl;

    std::cout << "\tDNI: ";
    std::cin >> aux;
    a.setDni(aux);

    std::cout << "\tNombre: ";
    std::cin >> aux;
    a.setNombre(aux);

    std::cout << "\tApellidos: ";
    std::cin >> aux;
    a.setApellidos(aux);

    std::cout << "\tTelefono: ";
    std::cin >> aux;
    a.setTelefono(aux);

    std::cout << "\te-mail: ";
    std::cin >> aux;
    a.setEmail(aux);

    std::cout << "\tDirección postal: ";
    std::cin >> aux;
    a.setDireccion(aux);

    std::cout << "\tFecha de nacimiento (dd/mm/aaaa): ";
    std::cin >> aux;
    a.setFechaNacimiento(aux);

    std::cout << "\tCurso más alto matriculado: ";
    std::cin >> aux;
    a.setCurso(atoi(aux.c_str()));

    std::cout << "\tGrupo: ";
    std::cin >> aux;
    a.setGrupo(atoi(aux.c_str()));

    std::cout << "\t¿Es líder del grupo? (S/N): ";
    std::cin >> aux;
    a.setEsLider(aux == "S" or aux == "s"? true : false);
}

void mostrarAlumno(const alumno &a) {
    std::cout << "\tDNI: " << a.getDni() << std::endl;
    std::cout << "\tNombre: " << a.getNombre() << std::endl;
    std::cout << "\tApellidos: " << a.getApellidos() << std::endl;
    std::cout << "\tTelefono: " << a.getTelefono() << std::endl;
    std::cout << "\te-mail: " << a.getEmail() << std::endl;
    std::cout << "\tDirección postal: " << a.getDireccion() << std::endl;
    std::cout << "\tFecha de nacimiento: " << a.getFechaNacimiento() << std::endl;
    std::cout << "\tCurso más alto matriculado: " << a.getCurso() << std::endl;
    std::cout << "\tGrupo: " << a.getGrupo() << std::endl;
    std::cout << "\tLider del Grupo: " << (a.getEsLider()? "TRUE" : "FALSE") << std::endl;
}

void mostrarAlumnos(std::list<alumno> &listaAlumnos) {
    std::list<alumno>::iterator iter;

    std::cout << "MOSTRAR ALUMNOS:" << std::endl;
    for (iter = listaAlumnos.begin(); iter != listaAlumnos.end(); iter++) {
        mostrarAlumno(*iter);
        std::cout << std::endl;
    }
}