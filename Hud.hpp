#pragma once
#include "Juego.hpp"

namespace Crazy
{
    /*SpriteM spVida;
    SpriteM spEnfriamiento;*/
    
    class Hud
    {
    public:
        Hud();
        void Dibujar();
        void Parpadear(bool parpadeo);
        
        void CambiarTexturaContador();
        void ModificarVida(float vida, float totalVida);
        void ModificarEnfriamiento(float enfriamiento, float totalEnfriamiento);
        void EnfriamientoVacio();
        void ModoContrarreloj();
        void ElixirEncontrado();
        void SetAtaqueEspecial(bool ataque);
        SpriteM GetSpriteRecipienteVida();
        bool GetAtaqueEspecial();
        
    private:
        Juego* _juego;
        SpriteM spRecipVida;
        SpriteM spVida;
        SpriteM spEnfriamiento;
        SpriteM spElixir;
        SpriteM spContador [5];
        
        bool contrarreloj;
        bool elixir;
        bool ataqueEspecial;
        int spriteTimerSeg;
        int spriteTimerSeg1;
        int spriteTimerMin;
    };
}