#pragma once
#include "Juego.hpp"
#include "Player.hpp"   

namespace Crazy
{
    /*SpriteM spVida;
    SpriteM spEnfriamiento;*/
    
    class Hud
    {
    public:
        Hud(bool nDificultar, bool mContrarreloj);
        void Dibujar();
        void Parpadear(bool parpadeo);
        
        void CambiarTexturaContador();
        void ModificarVida(float vida, float totalVida);
        void ModificarEnfriamiento(float enfriamiento, float totalEnfriamiento);
        void EnfriamientoVacio();
        void ModoContrarreloj();
        void ElixirEncontrado(bool v);
        bool getElixir();
        void SetAtaqueEspecial(bool ataque);
        SpriteM GetSpriteRecipienteVida();
        bool GetAtaqueEspecial();
        
    private:
        Juego* _juego;
        Player* _jugador;
        Camara* _camara;
        SpriteM spRecipVida;
        SpriteM spVida;
        SpriteM spEnfriamiento;
        SpriteM spElixir;
        SpriteM spContador [5];
        Texto puntuacion;
        
        bool contrarreloj;
        bool elixir;
        bool parpadea;
        bool ataqueEspecial;
        int spriteTimerSeg;
        int spriteTimerSeg1;
        int spriteTimerMin;
    };
}