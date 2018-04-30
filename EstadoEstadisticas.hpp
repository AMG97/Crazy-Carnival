#pragma once

#include "Estado.hpp"
#include "EstadoMenuPartidas.hpp"
#include "Juego.hpp"

// Includes del motor
#include "Texto.hpp"
#include "Input.hpp"
#include "SpriteM.hpp"
using namespace Motor;

namespace Crazy
{
    class EstadoEstadisticas : public Estado
    {
    public:
        EstadoEstadisticas();
        static EstadoEstadisticas* Instance();
        
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