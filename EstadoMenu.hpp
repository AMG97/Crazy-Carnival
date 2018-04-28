#pragma once

#include "Estado.hpp"
#include "EstadoJuego.hpp"
#include "Juego.hpp"

// Includes del motor
#include "Texto.hpp"
#include "Input.hpp"
#include "SpriteM.hpp"
using namespace Motor;

// Constantes
#define JUGAR 0
#define AYUDA 1

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
        SpriteM flecha;
        
        void Jugar();
        short int opcion;
        bool teclaPulsada;
        
        void CambiarFlecha(Texto texto);
        void CambiarEstado();
    };
}