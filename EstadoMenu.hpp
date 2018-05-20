#pragma once

#include "Estado.hpp"
#include "EstadoPartidas.hpp"
#include "EstadoEstadisticas.hpp"
#include "EstadoAyuda.hpp"
#include "Juego.hpp"

// Constantes
#define JUGAR 0
#define ESTADISTICAS 3
#define AYUDA 4
#define SALIR 5

namespace Crazy
{
    class EstadoMenu : public Estado
    {
    public:
        EstadoMenu();
        static EstadoMenu* Instance();
        void Vaciar();
        
        void Init();
        void ManejarEventos();
        void Actualizar(float tiempoActual);
        void Dibujar(float tiempoActual);
        void Pausar();
        void Reanudar();
        
        ~EstadoMenu();
    private:
        static EstadoMenu* _pinstance;
        
        Juego* _juego;
        Input* _input;
        Texto t_titulo;
        Texto t_jugar;
        Texto t_estadisticas;
        Texto t_ayuda;
        Texto t_salir;
        
        SpriteM flecha;
        
        short int opcion;
        bool teclaPulsada;
        short int tamFuente;
        
        void CambiarFlecha(Texto texto);
        void CambiarEstado();
        
        void Jugar();
        void Estadisticas();
        void Ayuda();
        void Salir();
    };
}