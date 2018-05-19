#pragma once

#include "Estado.hpp"
#include "Juego.hpp"

namespace Crazy
{
    class EstadoEstadisticas : public Estado
    {
    public:
        EstadoEstadisticas();
        static EstadoEstadisticas* Instance();
        void Vaciar();
        
        void Init();
        void ManejarEventos();
        void Actualizar(float tiempoActual);
        void Dibujar(float tiempoActual);
        
        ~EstadoEstadisticas();
    private:
        static EstadoEstadisticas* _pinstance;
        
        Juego* _juego;
        Input* _input;
        Texto t_titulo;
        Texto t_atras;
        SpriteM flecha;
        
        bool teclaPulsada;
        void CargarEstadisticas();
        void Atras();
    };
}