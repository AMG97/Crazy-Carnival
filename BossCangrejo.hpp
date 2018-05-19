#pragma once
#include "Enemigo.hpp"
#include "Arma.hpp"
#include "Juego.hpp"
#include "Proyectil.hpp"

namespace Crazy
{
    class Player;
    class BossCangrejo: public Enemigo {
    public:
        BossCangrejo(float posx, float posy);
        BossCangrejo(const BossCangrejo& orig);
        virtual ~BossCangrejo();
        void Update(int Posx, int Posy, Player *p);
        void Update(int Posx, int Posy);
        void Dibujar();
        void ModificarSpriteCorrer();
        void ModificarSpriteAtaque1();
        void ModificarSprite();
        void ModificarSpriteAtaque2();
        void MoverX(float x);
        void MoverY();
        void BorrarProyectil(int i);
    private:
        float danyo;
        int contadorSpriteAtaque2;
        float caida;
        bool Ataque2;
        Reloj tAtaque2;
        Reloj tAtaqueFinal;
        vector<Proyectil*> proyectiles;
    };

}

