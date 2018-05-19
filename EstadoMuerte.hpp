#pragma once

#include "Estado.hpp"
#include "Juego.hpp"

namespace Crazy
{
    class EstadoMuerte : public Estado
    {
    public:
        EstadoMuerte();
        static EstadoMuerte* Instance();
        void Vaciar();
        
        void Init();
        void ManejarEventos();
        void Actualizar(float tiempoActual);
        void Dibujar(float tiempoActual);
        
        ~EstadoMuerte();
    private:
        static EstadoMuerte* _pinstance;
        
        Juego* _juego;
        Input* _input;
        Texto t_titulo;
        Texto t_atras;
        bool dibujado;
    };
}


