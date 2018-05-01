#pragma once

#include "Estado.hpp"
#include "EstadoMenu.hpp"
#include "EstadoJuego.hpp"
#include "EstadoEstadisticas.hpp"
#include "Juego.hpp"

// Constantes
#define NUEVA 0
#define CARGAR 1
#define BORRAR 2
#define ESTADISTICAS 3

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
        Texto t_estadisticas;
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
        void Estadisticas();
        void Atras();
    };
}