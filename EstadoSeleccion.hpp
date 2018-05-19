#pragma once

#include "Estado.hpp"
#include "Juego.hpp"
#include "EstadoJuego.hpp"

// Constantes
#define P1 0
#define P2 1
#define P3 2
#define P4 3

namespace Crazy
{
    class EstadoSeleccion : public Estado
    {
    public:
        EstadoSeleccion();
        static EstadoSeleccion* Instance();
        void Vaciar();
        
        void Init();
        void ManejarEventos();
        void Actualizar(float tiempoActual);
        void Dibujar(float tiempoActual);
        void Atras();
        
        ~EstadoSeleccion();
    private:
        static EstadoSeleccion* _pinstance;
        
        Juego* _juego;
        Input* _input;
        Texto t_titulo;
        Texto t_atras;
        SpriteM flechaAtras;
        short int opcion;
        
        SpriteM p1;
        SpriteM p2;
        SpriteM flecha;
        short int contadorSpriteReposo;
        Reloj relojAnim;
        
        void CambiarFlecha(SpriteM personaje);
        void Elegir();
        void Animar();
    };
}