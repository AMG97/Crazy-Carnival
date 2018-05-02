#pragma once
#include "Juego.hpp"

namespace Crazy
{
    class Comportamiento
    {
    public:
        Comportamiento();
        float GetVida();
        float GetTotalVida();
        void SetVida(float v);
        void ModificarVida(float modificador);
        
        float GetPosIniX();
        float GetPosIniY();
        void SetPosIniX(float x);
        void SetPosIniY(float y);

        float GetPosX();
        float GetPosY();
        void SetPosX(float x);
        void SetPosY(float y);
        
        void Dibujar();
        
    protected:
        float vida;
        float totalVida;
        float posIniX;
        float posIniY;
        float posX;
        float posY;
        
        Juego* _juego;
        SpriteM sprite;
    };
}