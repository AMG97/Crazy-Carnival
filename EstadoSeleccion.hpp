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
        Texto t_jugar;
        SpriteM flechaAtras;
        SpriteM flechaJugar;
        short int opcion;
        short int player;
        
        SpriteM p1;
        SpriteM p2;
        /*SpriteM p3;
        SpriteM p4;*/
        SpriteM flecha;
        short int contadorSpriteReposo;
        Reloj relojAnim;
        
        // TODO: 
        bool modoNormal;
        Texto t_modo;
        Texto t_normal;
        Texto t_pesadilla;
        SpriteM flechaM;
        
        bool modoContrarreloj;
        Texto t_modoC;
        Texto t_si;
        Texto t_no;
        SpriteM flechaMC;
        
        
        void CambiarFlecha(SpriteM personaje);
        void CambiarFlecha(SpriteM f, Texto texto);
        void Elegir();
        void Animar();
        void Player1();
        void Player2();
        /*void Player3();
        void Player4();*/
        void Jugar();
        void CambiarEstadoMaquina();
    };
}