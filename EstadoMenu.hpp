#pragma once

#include "Estado.hpp"
#include "Juego.hpp"

namespace Crazy
{
    class EstadoMenu : public Estado
    {
    public:
        EstadoMenu();
        static EstadoMenu* Instance();
        
        void Init();
        void ManejarEventos();
        void Actualizar(float tiempoActual);
        void Dibujar(float tiempoActual);
        
        ~EstadoMenu();
    private:
        static EstadoMenu* _pinstance;
        
        Juego* _juego;
        
    };
}