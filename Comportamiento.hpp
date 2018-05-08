#pragma once
#include "Juego.hpp"

namespace Crazy
{
    class Comportamiento
    {
    public:
        Comportamiento();
        ~Comportamiento() { };
        float GetVida();
        float GetTotalVida();
        void SetVida(float v);
        void ModificarVida(float modificador);
        float GetVelocidad();
        void SetVelocidad(float vel);
        
        float GetPosIniX();
        float GetPosIniY();
        void SetPosIniX(float x);
        void SetPosIniY(float y);

        float GetPosX();
        float GetPosY();
        void SetPosX(float x);
        void SetPosY(float y);
        
        void Dibujar();
        virtual void ModificarSprite() = 0;
        void CambiarDireccionDer();
        void CambiarDireccionIzq();
        bool GetDireccionIzq();
        void Mover();
        void CambiarPosicion(float x, float y);
        
    protected:
        float vida;
        float totalVida;
        float velocidad;
        float posIniX;
        float posIniY;
        float posX;
        float posY;
        
        Juego* _juego;
        SpriteM sprite;
        Reloj relojAnim;
        
        bool direccionIzq;
    };
}