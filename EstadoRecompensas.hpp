#pragma once

#include "Estado.hpp"
#include "Juego.hpp"

// Constantes
#define R1 0
#define R2 1
#define R3 2

namespace Crazy
{
    class EstadoRecompensas : public Estado
    {
    public:
        EstadoRecompensas();
        static EstadoRecompensas* Instance();
        void Vaciar();
        
        void Init();
        void ManejarEventos();
        void Actualizar(float tiempoActual);
        void Dibujar(float tiempoActual);
        
        ~EstadoRecompensas();
    private:
        static EstadoRecompensas* _pinstance;
        
        Juego* _juego;
        Input* _input;
        Texto t_titulo;
        
        SpriteM r1;
        SpriteM r2;
        SpriteM r3;
        short int opcion;
        short int separacion;
        short int altura;
        float proporcion;
        
        SpriteM flecha;
        short int contadorSpriteReposo;
        Reloj relojAnim;
        
        SpriteM flechaContinuar;
        Texto t_conti;
        
        void CambiarFlecha(SpriteM personaje);
        void Animar();
        void Continuar();
        void CambiarEstadoMaquina();
    };
}