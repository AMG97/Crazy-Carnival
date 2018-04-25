#pragma once

#include <iostream>
using namespace std;

#include "EstadosManager.hpp"

#include "Ventana.hpp"
using namespace Motor;

namespace Crazy
{
    class Juego {
    public:
        static Juego* Instance();
        
        EstadosManager maquina;
        Ventana* _ventana;
        
        void Iniciar();
        
        ~Juego();
    private:
        Juego() { };
        Juego(const Juego &);
        Juego &operator=(const Juego &);
        static Juego* _pinstance;
        
        int ancho;
        int alto;
        string titulo;
        float tiempoActual;
    };
}