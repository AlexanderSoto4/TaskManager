#ifndef TAREA_H
#define TAREA_H

#include <string>
using namespace std;




enum class Prioridad { BAJA, MEDIA, ALTA};

class Tarea 
{ 
    private: 
        string titulo;
        string descripcion;
        Prioridad prioridad;
        bool completada;
        string fechaLimite;

    public: 
        Tarea(string t, string d, Prioridad p, string fL);
        string prioridadATexto(Prioridad p) const;
        void marcarCompletada();
        void mostrar() const;
        //Getters
        string getTitulo() const;
        string getDescripcion() const;
        Prioridad getPrioridad() const;
        bool estaCompletada() const;
        string getFechaLimite() const;
        //Setters
        void setTitulo(string nuevoTitulo);
        void setDescripcion(string nuevaDescripcion);
        void setPrioridad(Prioridad nuevaPrioridad);
        void setFechaLimite(string nuevaFecha);
        void setCompletada(bool completada);
        


};

#endif