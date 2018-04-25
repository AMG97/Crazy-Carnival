#pragma once
#include <SFML/Graphics.hpp>
#include "Ventana.hpp"

namespace Motor
{
    class Input
    {
    public:
        Input();
        void CerrarVentana();
        unsigned short int BucleEventosMenu();
        void BucleEventosJuego();
        
    private:
        Ventana* _ventana;
    };
}