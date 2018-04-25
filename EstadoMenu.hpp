#pragma once

#include "Estado.hpp"
#include "EstadoJuego.hpp"
#include "Juego.hpp"

// Includes del motor
#include "Texto.hpp"
#include "Input.hpp"
using namespace Motor;

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
        
        void Jugar();
        unsigned short int opcion;
    };
}