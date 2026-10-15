#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include "Tarea.h"
#include "ListaDeTareas.h"
using namespace std;

void ListaDeTareas::agregarTarea(const Tarea& tarea) {
    tareasEnLista.push_back(tarea);
}

bool ListaDeTareas::eliminarTarea(int indice) {
    if (indice >= tareasEnLista.size() || indice < 0){
        return false;
    } else {
        tareasEnLista.erase(tareasEnLista.begin() + indice);
        return true;
    }
}

bool ListaDeTareas::marcarCompletada(int indice) {
   if (indice >= tareasEnLista.size() || indice < 0) {
        return false;
    } else {
        tareasEnLista[indice].marcarCompletada();
        return true;
    }
}

int ListaDeTareas::cantidad() const {
    int cantidadTareas = tareasEnLista.size();
    return cantidadTareas;
}

void ListaDeTareas::mostrarTodas() const {
    if (tareasEnLista.size() == 0) {
        cout << "No hay tareas registradas." << endl;
        return;
    } else {
        for (int i = 0; i < tareasEnLista.size(); i++) {
            cout << i+1 << ". ";
            tareasEnLista[i].mostrar();
        }
    }
   
}

void ListaDeTareas::mostrarPendientes() const {
    for (int i = 0; i < tareasEnLista.size(); i++) {
         if (tareasEnLista[i].estaCompletada()) {
                continue;
            } else {
                cout << i+1 << ". ";
                tareasEnLista[i].mostrar();
            }
        }
}