#pragma once

#include <iostream>
using namespace std;

#include "EstadosManager.hpp"

#include "Ventana.hpp"
#include "Recursos.hpp"
using namespace Motor;

namespace Crazy
{
    class Juego {
    public:
        static Juego* Instance();
        
        EstadosManager maquina;
        Ventana* _ventana;
        Recursos recursos;
        
        int ancho;
        int alto;
        string titulo;
        
        void Iniciar();
        
        ~Juego();
    private:
        Juego() { };
        Juego(const Juego &);
        Juego &operator=(const Juego &);
        static Juego* _pinstance;
        
        
        float tiempoActual;
    };
}