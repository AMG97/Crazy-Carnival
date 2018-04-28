#pragma once
#include <SFML/Graphics.hpp>
#include "Ventana.hpp"

namespace Motor
{
    struct Teclas {
        bool Arriba;
        bool Abajo;
        bool Enter;
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