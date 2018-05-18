#pragma once
#include "Enemigo.hpp"
#include "Arma.hpp"
#include "Juego.hpp"

namespace Crazy
{
    class Player;
    class EnemigoVolador: public Enemigo {
    public:
        EnemigoVolador(float posx, float posy);
        EnemigoVolador(const EnemigoVolador& orig);
        virtual ~EnemigoVolador();
        void Update(int Posx,int Posy, Player *p);
        void Update(int Posx,int Posy);
        void Dibujar();
        void ModificarSpriteCorrer();
        void ModificarSpriteAtaque1();
        void ModificarSprite();
        void Mover(float x, float y);
    private:
        float danyo;
        bool direccionSubir;
    };

}

