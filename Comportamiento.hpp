#pragma once
#include "Juego.hpp"
#include "Arma.hpp"

namespace Crazy
{
    class Arma;
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
        
        virtual void Dibujar()=0;
        virtual void ModificarSprite() = 0;
        void CambiarDireccionDer();
        void CambiarDireccionIzq();
        bool GetDireccionIzq();
        void Mover();
        void CambiarPosicion(float x, float y);
        void SetAngulo(int x, int y);
        float GetAngulo();
        Arma* GetArma();
        SpriteM GetSprite();
        
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
        
        float angulo;
        Arma* _arma;
    };
}