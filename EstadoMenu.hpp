#pragma once

#include "Estado.hpp"
#include "EstadoSeleccion.hpp"
#include "EstadoEstadisticas.hpp"
#include "EstadoAyuda.hpp"
#include "Juego.hpp"

// Constantes
#define NUEVA 0
#define CARGAR 1
#define BORRAR 2
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
        Texto t_nueva;
        Texto t_cargar;
        Texto t_borrar;
        Texto t_estadisticas;
        Texto t_ayuda;
        Texto t_salir;
        Texto t_explicar;
        Texto t_explicar2;
        SpriteM flecha;
        SpriteM flechas;
        
        short int opcion;
        bool teclaPulsada;
        short int tamFuente;
        
        void CambiarFlecha(Texto texto);
        void CambiarEstado();
        
        void NuevaPartida();
        void CargarPartida();
        void BorrarPartida();
        void Estadisticas();
        void Ayuda();
        void Salir();
    };
}