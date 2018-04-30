#pragma once
#include <SFML/Graphics.hpp>
#include "Ventana.hpp"

namespace Motor
{
    struct Teclas {
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

    class Input
    {
    public:
        Input();
        void CerrarVentana();
        bool BucleEventos();
        Teclas GetTeclas();
        float GetPosicionRatonX();
        float GetPosicionRatonY();
        
    private:
        Ventana* _ventana;
        Teclas t;
    };
}