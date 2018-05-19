#pragma once

#include "Estado.hpp"
#include "EstadoPausa.hpp"
#include "EstadoMuerte.hpp"
#include "Juego.hpp"
#include "Arma.hpp"
#include "Enemigo.hpp"
#include "EnemigoPistola.hpp"
#include "EnemigoVolador.hpp"
#include "Player.hpp"
#include "Hud.hpp"
#include "Nivel.hpp"

namespace Crazy
{
    class EstadoJuego : public Estado
    {
    public:
        EstadoJuego();
        static EstadoJuego* Instance();
        void Vaciar();
        
        Juego* _juego;
        Player* _jugador;
        
        
        Reloj reloj;
        Reloj relojAtaqueEspecial;
        Reloj relojDesplazamiento; //separada la anim de aqui
        Reloj tiempo;
        Reloj tiempoAtaqueEspecial;
        Reloj tiempoDesplazamiento;
        
        bool inercia;
        int contador;
        
        Nivel* _level;
        
        void Init();
        void ManejarEventos();
        void Actualizar(float tiempoActual);
        void Dibujar(float tiempoActual);
        void Pausar();
        void Reanudar();
        b2World* GetMundo();
        Nivel* GetNivel();
        void SetMundo(b2World* world);
        unsigned short int getNumNivel();
        
        ~EstadoJuego();
    private:
        static EstadoJuego* _pinstance;
        
        Input* _input;
        bool teclaPulsada;
        
        Hud* _hud;
        b2World* _mundo;
        
        unsigned short int lvl_n;
    };
}