#include "Tarea.h"
#include <iostream>

using namespace std;

// Constructor
Tarea::Tarea(string t, string d, Prioridad p, string fL) {
    titulo = t;
    descripcion = d;
    prioridad = p;
    fechaLimite = fL;
    completada = false;
}

// Convierte el enum Prioridad a texto legible
string Tarea::prioridadATexto(Prioridad p) const {
    switch (p) {
        case Prioridad::BAJA:
            return "Baja";
        case Prioridad::MEDIA:
            return "Media";
        case Prioridad::ALTA:
            return "Alta";
        default:
            return "Desconocida";
    }
}

// Marca la tarea como completada
void Tarea::marcarCompletada() {
    completada = true;
}

// Muestra la informacion de la tarea en consola
void Tarea::mostrar() const {
    cout << "Titulo: " << titulo << endl;
    cout << "Descripcion: " << descripcion << endl;
    cout << "Prioridad: " << prioridadATexto(prioridad) << endl;
    cout << "Fecha limite: " << fechaLimite << endl;
    cout << "Estado: " << (completada ? "Completada" : "Pendiente") << endl;
    cout << "-------------------------" << endl;
}

// Getters
string Tarea::getTitulo() const {
    return titulo;
}

string Tarea::getDescripcion() const {
    return descripcion;
}

Prioridad Tarea::getPrioridad() const {
    return prioridad;
}

bool Tarea::estaCompletada() const {
    return completada;
}

string Tarea::getFechaLimite() const {
    return fechaLimite;
}

// Setters
void Tarea::setTitulo(string nuevoTitulo) {
    titulo = nuevoTitulo;
}

void Tarea::setDescripcion(string nuevaDescripcion) {
    descripcion = nuevaDescripcion;
}

void Tarea::setPrioridad(Prioridad nuevaPrioridad) {
    prioridad = nuevaPrioridad;
}

void Tarea::setFechaLimite(string nuevaFecha) {
    fechaLimite = nuevaFecha;
}

void Tarea::setCompletada(bool c) { 
    completada = c; 

}