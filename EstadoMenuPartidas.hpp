#pragma once

#include "Estado.hpp"
#include "EstadoMenu.hpp"
#include "EstadoJuego.hpp"
#include "Juego.hpp"

// Includes del motor
#include "Texto.hpp"
#include "Input.hpp"
#include "SpriteM.hpp"
using namespace Motor;

// Constantes
#define NUEVA 0
#define CARGAR 1
#define BORRAR 2

namespace Crazy
{
    class EstadoMenuPartidas : public Estado
    {
    public:
        EstadoMenuPartidas();
        static EstadoMenuPartidas* Instance();
        
        void Init();
        void ManejarEventos();
        void Actualizar(float tiempoActual);
        void Dibujar(float tiempoActual);
        
        ~EstadoMenuPartidas();
    private:
        static EstadoMenuPartidas* _pinstance;
        
        Juego* _juego;
        Input* _input;
        Texto t_titulo;
        
        Texto t_nueva;
        Texto t_cargar;
        Texto t_borrar;
        Texto t_atras;
        SpriteM flecha;
        SpriteM flechaAtras;
        
        short int opcion;
        bool teclaPulsada;
        
        void CambiarFlecha(Texto texto);
        void CambiarEstado();
        
        void NuevaPartida();
        void CargarPartida();
        void BorrarPartida();
        void Atras();
    };
}