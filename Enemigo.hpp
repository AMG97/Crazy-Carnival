#pragma once
#include "Comportamiento.hpp"
#include "Arma.hpp"
#include "Juego.hpp"

namespace Crazy
{
    class Enemigo : public Comportamiento {
    public:
        Enemigo();
        Enemigo(const Enemigo& orig);
        virtual ~Enemigo();
        virtual void Update(int Posx,int Posy)=0;
        virtual void Update(int Posx,int Posy,Player* p)=0;
        void Dibujar()=0;
        virtual void ModificarSpriteCorrer()=0;
        virtual void ModificarSpriteAtaque1()=0;
        virtual void ModificarSprite()=0;
        void SetDireccion(bool direccion);
        void RecibirDanyo(float dan);
    protected:
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


