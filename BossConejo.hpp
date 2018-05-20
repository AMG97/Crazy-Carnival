#pragma once
#include "Enemigo.hpp"
#include "Arma.hpp"
#include "Juego.hpp"
#include "Proyectil.hpp"

namespace Crazy
{
    class Player;
    class BossConejo: public Enemigo {
    public:
        BossConejo(float posx, float posy);
        BossConejo(const BossConejo& orig);
        virtual ~BossConejo();
        void Update(int Posx, int Posy, Player *p);
        void Update(int Posx, int Posy);
        void Dibujar();
        void ModificarSpriteCorrer();
        void ModificarSpriteAtaque1();
        void ModificarSprite();
        void ModificarSpriteAtaque2();
        void ModificarSpriteSalto();
        void MoverX(float x);
        void MoverY();
        void BorrarProyectil(int i);
    private:
        float danyo;
        int contadorSpriteAtaque2;
        int contadorSpriteSalto;
        float caida;
        bool Ataque2;
        bool zanahorias;
        Reloj tAtaque2;
        Reloj tAtaqueFinal;
        vector<Proyectil*> proyectiles;
    };

}

