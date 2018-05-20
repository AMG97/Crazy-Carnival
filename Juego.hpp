#pragma once

#include "EstadosManager.hpp"

#include "Motor.hpp"
using namespace Motor;

namespace Crazy
{
    class Juego {
    public:
        static Juego* Instance();
        ~Juego();
        
        EstadosManager maquina;
        Ventana* _ventana;
        Recursos recursos;
        void Iniciar();
        int GetAncho();
        int GetAlto();
        std::string GetTitulo();
        short int GetSlot();
        void SetSlot(short int s);
        
    private:
        Juego() { };
        Juego(const Juego &);
        Juego &operator=(const Juego &);
        static Juego* _pinstance;
        
        int ancho;
        int alto;
        std::string titulo;
        float tiempoActual;
        Reloj reloj;
        
        // Slot guardado
        short int slot;
    };
}