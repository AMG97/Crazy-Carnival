#pragma once
#include <SFML/Graphics.hpp>
#include "Ventana.hpp"

namespace Motor
{
    struct Teclas {
        bool Arriba;
        bool Abajo;
        bool Enter;
        bool BackSpace;
        bool Escape;
    };

    class Input
    {
    public:
        Input();
        void CerrarVentana();
        bool BucleEventos();
        Teclas GetPressed();
        
    private:
        Ventana* _ventana;
        Teclas t;
    };
}