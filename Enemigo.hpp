#pragma once
#include "Comportamiento.hpp"
#include "Arma.hpp"
#include "Juego.hpp"

namespace Crazy
{
    class Enemigo : public Comportamiento {
    public:
        Enemigo(int n);
        Enemigo(const Enemigo& orig);
        virtual ~Enemigo();
        void Update(int Posx,int Posy);
        void Dibujar();
        void ModificarSpriteCorrer();
        void ModificarSpriteAtaque1();
        void ModificarSprite();
        void SetDireccion(bool direccion);
        void RecibirDanyo(float dan);
    private:
        float alcancex;
        float alcancey;
        float posinix;
        float posiniy;
        int contadorSpriteCorrer;
        int contadorSpriteAtaque1;
        bool Ataque1;
        float movimiento;
        Reloj tAtaque;
        Reloj tDesp;
    };
}


