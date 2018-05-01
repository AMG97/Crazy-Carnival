#pragma once

#include "Estado.hpp"
#include "EstadoMenu.hpp"
#include "Juego.hpp"

// Constantes
#define ABANDONAR 0
#define OP1 1
#define OP2 2

namespace Crazy
{
    class EstadoPausa : public Estado
    {
    public:
        EstadoPausa();
        static EstadoPausa* Instance();
        
        void Init();
        void ManejarEventos();
        void Actualizar(float tiempoActual);
        void Dibujar(float tiempoActual);
        
        ~EstadoPausa();
    private:
        static EstadoPausa* _pinstance;
        
        Juego* _juego;
        Input* _input;
        Texto t_titulo;
        Texto t_frase;
        Texto t_frase2;
        Texto t_op;
        Texto t_op2;
        Texto t_atras;
        SpriteM flecha;
        SpriteM flechaAtras;
        
        short int opcion;
        bool teclaPulsada;
        bool abandonar;
        void Atras();
        void CambiarFlecha(Texto texto);
        void CambiarEstado();
        void Abandonar();
        void Confirmar();
    };
}