#pragma once

#include "Estado.hpp"
#include "EstadoMenuPartidas.hpp"
#include "EstadoAyuda.hpp"
#include "Juego.hpp"

// Constantes
#define JUGAR 0
#define AYUDA 1
#define SALIR 2

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
        Input* _input;
        Texto t_titulo;
        Texto t_jugar;
        Texto t_ayuda;
        Texto t_salir;
        Texto t_explicar;
        Texto t_explicar2;
        SpriteM flecha;
        SpriteM flechas;
        
        short int opcion;
        bool teclaPulsada;
        
        void CambiarFlecha(Texto texto);
        void CambiarEstado();
    };
}