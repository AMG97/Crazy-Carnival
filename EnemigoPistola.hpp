#pragma once
#include "Enemigo.hpp"
#include "Arma.hpp"
#include "Juego.hpp"

namespace Crazy
{
    class EnemigoPistola: public Enemigo {
    public:
        EnemigoPistola(float posx, float posy);
        EnemigoPistola(const EnemigoPistola& orig);
        virtual ~EnemigoPistola();
        void Update(int Posx,int Posy);
        void Dibujar();
        void ModificarSpriteCorrer();
        void ModificarSpriteAtaque1();
        void ModificarSprite();
    private:

    };
}


