#pragma once

#include "Estado.hpp"
#include "EstadoMenu.hpp"
#include "Juego.hpp"

namespace Crazy
{
    class EstadoAyuda : public Estado
    {
    public:
        EstadoAyuda();
        static EstadoAyuda* Instance();
        
        void Init();
        void ManejarEventos();
        void Actualizar(float tiempoActual);
        void Dibujar(float tiempoActual);
        
        ~EstadoAyuda();
    private:
        static EstadoAyuda* _pinstance;
        
        Juego* _juego;
        Input* _input;
        Texto t_titulo;
        Texto t_atras;
        SpriteM flecha;
        
        bool teclaPulsada;
        void Atras();
    };
}