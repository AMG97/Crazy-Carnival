#pragma once

#include "Estado.hpp"
#include "EstadoPausa.hpp"
#include "Juego.hpp"

#include "Player.hpp"
#include "Hud.hpp"
#include "Nivel.hpp"

namespace Crazy
{
    class EstadoJuego : public Estado
    {
    public:
        EstadoJuego();
        static EstadoJuego* Instance();
        
        Juego* _juego;
        Player* _jugador;
        
        void Init();
        void ManejarEventos();
        void Actualizar(float tiempoActual);
        void Dibujar(float tiempoActual);
        void Pausar();
        void Reanudar();
        
        ~EstadoJuego();
    private:
        static EstadoJuego* _pinstance;
        
        Input* _input;
        bool teclaPulsada;
        
        Hud* _hud;
        Nivel* _level;
    };
}