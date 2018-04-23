#pragma once

#include <iostream>
#include "EstadosManager.hpp"
using namespace std;

namespace Crazy
{
    class Juego {
    public:
        static Juego* Instance();
        
        EstadosManager maquina;
        
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