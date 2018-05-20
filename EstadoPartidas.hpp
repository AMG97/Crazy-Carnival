#pragma once

#include "Estado.hpp"
#include "Juego.hpp"
#include "EstadoSeleccion.hpp"
#include "EstadoEstadisticas.hpp"
#include <fstream>              // Para leer y escribir un fichero

// Constantes
#define SLOT1 1
#define SLOT2 2
#define SLOT3 3

#define NUEVA 0
#define CARGAR 1
#define BORRAR 2
#define ESTADISTICAS 3

namespace Crazy
{
    class EstadoPartidas : public Estado
    {
    public:
        EstadoPartidas();
        static EstadoPartidas* Instance();
        void Vaciar();
        
        void Init();
        void ManejarEventos();
        void Actualizar(float tiempoActual);
        void Dibujar(float tiempoActual);
        
        ~EstadoPartidas();
    private:
        static EstadoPartidas* _pinstance;
        
        Juego* _juego;
        Input* _input;
        Texto t_titulo;
        short int tamFuente;
        
        const string CARPETA = "saves/";
        const string PARTIDA = "Save";
        const string STATS = "Stats";
        const string EXTENSION = ".xml";

        short int slots = 3;
        short int archivos = 2;
        bool** partidas = new bool*[slots];
        bool hayPartidas;
        
        Texto t_slot1;
        Texto t_slot2;
        Texto t_slot3;
        SpriteM flecha;
        short int slotGuardar;
        
        SpriteM flechaOp;
        Texto t_op1;
        Texto t_op2;
        Texto t_op3;
        
        Texto t_explicar;
        Texto t_atras;
        SpriteM flechaAtras;
        
        void ComprobarPartidas();
        void CambiarSlot(short int num);
        void Opciones(Texto texto);
        
        void Atras();
        void CambiarFlecha(SpriteM f, Texto texto);
        void NuevaPartida();
        void CargarPartida();
        void BorrarPartida();
        void Estadisticas();
    };
}