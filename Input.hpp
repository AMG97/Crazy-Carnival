#pragma once
#include <SFML/Graphics.hpp>
#include "Ventana.hpp"

namespace Motor
{
    class Input
    {
    public:
        struct Teclas {
            bool Pausar;
            bool Arriba;
            bool Abajo;
            bool Izq;
            bool Der;
            bool Enter;
            bool BackSpace;
            bool Escape;
            bool RatonIzq;
            bool RatonDer;
        };
        Input();
        void CerrarVentana();
        bool BucleEventos();
        Teclas GetTeclas();
        float GetPosicionRatonX();
        float GetPosicionRatonY();
        
    private:
        Ventana* _ventana;
        Teclas teclas;
    };
}