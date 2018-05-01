#pragma once
#include "Juego.hpp"

namespace Crazy
{
    /*SpriteM Hud::spVida;
    SpriteM Hud::spEnfriamiento;*/
    
    class Hud
    {
    public:
        Hud();
        void Dibujar();
        void Parpadear(bool parpadeo);
        
        void CambiarTexturaContador();
        void ModificarVida(float modificador);
        void ModificarEnfriamiento(float modificador);
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