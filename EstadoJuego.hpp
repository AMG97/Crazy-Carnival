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
#include "Espadachina.hpp"
#include "Pistolero.hpp"
#include "EstadoRecompensas.hpp"
#include "GestorArchivo.hpp"

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
        Hud* _hud;
        
        
        Reloj reloj;
        Reloj relojAtaqueEspecial;
        Reloj relojDesplazamiento; //separada la anim de aqui
        Reloj relojContrarreloj;
        Reloj tiempo;
        Reloj tiempoAtaqueEspecial;
        Reloj tiempoDesplazamiento;
        Reloj tiempoContrarreloj;
        
        bool inercia;
        int contador;
        
        Nivel* _level;
        bool terminado;
        bool dibujado_terminado;
        
        void Personaje(string jugador, unsigned short int weapon, bool modoHardcore, bool modoContrareloj);
        void Init();
        void ManejarEventos();
        void Actualizar(float tiempoActual);
        void Dibujar(float tiempoActual);
        void Pausar();
        void Reanudar();
        void getDatosGuardado(string* g_personaje, int* g_arma, int* g_nivel, bool* g_hardcore, bool* g_contrarreloj, bool* g_elixir, int* g_puntos);
        void cargarDatosGuardados(string* g_personaje, int* g_arma, int* g_nivel, bool* g_hardcore, bool* g_contrarreloj, bool* g_elixir, int* g_puntos);
        bool getContrarreloj();
        b2World* GetMundo();
        Nivel* GetNivel();
        void SetMundo(b2World* world);
        unsigned short int getNumNivel();
        void setNumNivel(unsigned short int l);
        void setArma(unsigned short int a);
        
        ~EstadoJuego();
    private:
        static EstadoJuego* _pinstance;
        
        bool normal;
        bool contrarreloj;
        Input* _input;
        bool teclaPulsada;
        string texturaJugador;
        unsigned short int arma;
        
        b2World* _mundo;
        
        unsigned short int lvl_n;
    };
}