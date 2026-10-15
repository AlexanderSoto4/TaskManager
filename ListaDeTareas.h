#ifndef LISTADETAREAS_H
#define LISTADETAREAS_H

#include <vector>
#include "Tarea.h"
using namespace std;


class ListaDeTareas {

    private: 
        vector<Tarea>tareasEnLista;
        
    public:
        void agregarTarea(const Tarea& tarea);
        bool eliminarTarea(int indice);
        bool marcarCompletada(int indice);
        void mostrarTodas() const;
        void mostrarPendientes() const;
        int cantidad() const;
        const vector<Tarea>& obtenerTareas() const { return tareasEnLista; }
        
    
        


};

#endif
