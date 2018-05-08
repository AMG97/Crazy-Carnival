#pragma once
#include "Juego.hpp"

namespace Crazy
{
    class Proyectil {
    public:
        Proyectil(int n, float dan, float ang, SpriteM sp);
        Proyectil(const Proyectil& orig);
        virtual ~Proyectil();
        bool Update();
        SpriteM GetProyectil();
        float GetDanyo();
        void Dibujar();
    private:
        SpriteM sprite;
        int alcance;
        float danyo;
        float angulo;
        int velocidad;
        float PosIniX;
        float PosIniY;
        Juego* _juego;

    };
}


