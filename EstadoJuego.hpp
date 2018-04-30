#pragma once

#include "Estado.hpp"
#include "EstadoPausa.hpp"
#include "Juego.hpp"

// Includes del motor
#include "Texto.hpp"
#include "Input.hpp"

#include "Reloj.hpp"

using namespace Motor;

namespace Crazy
{
    class EstadoJuego : public Estado
    {
    public:
        EstadoJuego();
        static EstadoJuego* Instance();
        
        void Init();
        void ManejarEventos();
        void Actualizar(float tiempoActual);
        void Dibujar(float tiempoActual);
        void Pausar();
        void Reanudar();
        
        ~EstadoJuego();
    private:
        static EstadoJuego* _pinstance;
        
        Juego* _juego;
        Input* _input;
        Texto t_titulo;
        bool teclaPulsada;
    };
}