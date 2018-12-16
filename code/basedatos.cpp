/**
 * @file basedatos.hpp
 * @brief Implementación de los métodos de la clase baseDatos.
 * @date 27-11-2018
 *
 * Este fichero forma parte del proyecto realizado para la gestión de alumnos,
 * para la asignatura Ingeniería del Software de la Universidad de Córdoba.
 */

#include <list>
#include <string>
#include <iostream>
#include <fstream>
#include "alumno.hpp"
#include "basedatos.hpp"

bool baseDatos::anadirAlumno(const alumno &nuevoAlumno) {
    if (getNumeroAlumnos() >= 150) {
        return false;
    }

    alumnos_.push_back(nuevoAlumno);
    return true;
}

bool baseDatos::anadirAlumno(std::string dni, std::string nombre, 
    std::string apellidos, std::string telefono, std::string email, 
    std::string direccion, std::string fechaNacimiento, unsigned curso, 
    unsigned grupo, bool esLider) {

    if (getNumeroAlumnos() >= 150) {
        return false;
    }

    alumno nuevoAlumno(dni, nombre, apellidos, telefono, email, direccion, fechaNacimiento, 
        curso, grupo, esLider);

    alumnos_.push_back(nuevoAlumno);
    return true;
}

bool baseDatos::modificarAlumno(std::string dni, alumno nuevoAlumno) {
    std::list<alumno>::iterator iter;

	if (getNumeroAlumnos() == 0) {
	    return false;
	}

	for (iter = alumnos_.begin(); iter != alumnos_.end(); iter++) {
		if (iter->getDni() == dni) {
			iter->setDni(nuevoAlumno.getDni());
            iter->setNombre(nuevoAlumno.getNombre());
            iter->setApellidos(nuevoAlumno.getApellidos());
            iter->setTelefono(nuevoAlumno.getTelefono());
            iter->setEmail(nuevoAlumno.getEmail());
            iter->setDireccion(nuevoAlumno.getDireccion());
            iter->setFechaNacimiento(nuevoAlumno.getFechaNacimiento());
            iter->setCurso(nuevoAlumno.getCurso());
            iter->setGrupo(nuevoAlumno.getGrupo());
            iter->setEsLider(nuevoAlumno.getEsLider());
			return true;
		}

	}

    return false;
}

bool baseDatos::eliminarAlumno(std::string dni)
{
    std::list<alumno>::iterator iter;

	if (getNumeroAlumnos() == 0) {
	    return false;
	}

	for (iter = alumnos_.begin(); iter != alumnos_.end(); iter++) {
		if (iter->getDni() == dni){
			alumnos_.erase(iter);
			return true;
		}

	}

	return false;
}

bool baseDatos::getAlumno(std::string dni, alumno &a)
{
    std::list<alumno>::iterator iter;

    for (iter = alumnos_.begin(); iter != alumnos_.end(); iter++) {
        if (dni == iter->getDni()) {
            a.setDni(iter->getDni());
            a.setNombre(iter->getNombre());
            a.setApellidos(iter->getApellidos());
            a.setTelefono(iter->getTelefono());
            a.setEmail(iter->getEmail());
            a.setDireccion(iter->getDireccion());
            a.setFechaNacimiento(iter->getFechaNacimiento());
            a.setCurso(iter->getCurso());
            a.setGrupo(iter->getGrupo());
            a.setEsLider(iter->getEsLider());
            return true;
        }
    }

    return false;
}

void baseDatos::buscarAlumnos(std::list<alumno> &resultado, 
    std::string apellidos, std::string dni, unsigned grupo)
{
    std::list<alumno>::iterator iter;
    alumno nuevoAlumno;

    resultado.clear();
    for (iter = alumnos_.begin(); iter != alumnos_.end(); iter++) {
        if (apellidos == "" or apellidos == iter->getApellidos()) {
            if (dni == "" or dni == iter->getDni()) {
                if (grupo == 0 or grupo == iter->getGrupo()) {
                    nuevoAlumno.setDni(iter->getDni());
                    nuevoAlumno.setNombre(iter->getNombre());
                    nuevoAlumno.setApellidos(iter->getApellidos());
                    nuevoAlumno.setTelefono(iter->getTelefono());
                    nuevoAlumno.setEmail(iter->getEmail());
                    nuevoAlumno.setDireccion(iter->getDireccion());
                    nuevoAlumno.setFechaNacimiento(iter->getFechaNacimiento());
                    nuevoAlumno.setCurso(iter->getCurso());
                    nuevoAlumno.setGrupo(iter->getGrupo());
                    nuevoAlumno.setEsLider(iter->getEsLider());

                    resultado.push_back(nuevoAlumno);
                }
            }
        }
    }
}

void baseDatos::guardarFichero(std::string nombreFichero) {
    std::ofstream outfile(nombreFichero, std::ios::binary);
    std::list<alumno>::iterator iter;

    if (outfile.is_open()) {
        for (iter = alumnos_.begin(); iter != alumnos_.end(); iter++) {
            outfile << iter->getDni() + ',' 
                    << iter->getNombre() + ',' 
                    << iter->getApellidos() + ',' 
                    << iter->getTelefono() + ','
                    << iter->getEmail() + ',' 
                    << iter->getDireccion() + ',' 
                    << iter->getCurso() + ',' 
                    << iter->getFechaNacimiento() + ','
                    << iter->getGrupo() + ',' 
                    << (iter->getEsLider()? "TRUE" : "FALSE") + '\n';
        }
        
        outfile.close();
    }
}

void baseDatos::cargarFichero(std::string nombreFichero) {
    std::ifstream infile(nombreFichero, std::ios::binary);
    std::string dni; 
    std::string nombre;
    std::string apellidos;
    std::string telefono; 
    std::string email; 
    std::string direccion; 
    std::string fechaNacimiento;
    unsigned curso;
    unsigned grupo;  
    bool esLider;
    std::string aux;

    if (infile.is_open()) {
        alumnos_.clear();

        while (getline(infile, dni, ',')) {
            getline(infile, nombre, ',');
            getline(infile, apellidos, ',');
            getline(infile, telefono, ',');
            getline(infile, email, ',');
            getline(infile, direccion, ',');
            getline(infile, aux, ',');
            curso = atoi(aux.c_str());
            getline(infile, fechaNacimiento, ',');
            getline(infile, aux, ',');
            grupo = atoi(aux.c_str());
            getline(infile, aux);
            esLider = (aux == "TRUE");

            anadirAlumno(dni, nombre, apellidos, telefono, email, 
                direccion, fechaNacimiento, curso, grupo, esLider);
        }

        infile.close();
    }
}