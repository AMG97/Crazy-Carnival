#pragma once

#include "Estado.hpp"
#include "EstadoMenu.hpp"
#include "Juego.hpp"

// Includes del motor
#include "Texto.hpp"
#include "Input.hpp"
#include "SpriteM.hpp"
using namespace Motor;

// Constantes
#define MENU 0
#define SALIR 1

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
        Texto t_menu;
        Texto t_salir;
        Texto t_atras;
        SpriteM flecha;
        SpriteM flechaAtras;
        
        short int opcion;
        bool teclaPulsada;
        void Atras();
        void CambiarFlecha(Texto texto);
        void CambiarEstado();
    };
}