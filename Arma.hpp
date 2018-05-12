#pragma once
#include "Juego.hpp"
#include "Proyectil.hpp"

#define REPOSO 0
#define CORRER 1
#define SALTO 2
#define ATAQUE1  3
#define ATAQUE2  4

namespace Crazy
{
    class Player;
    class Enemigo;

    class Arma {
    public:
        Arma(int n, float x, float y, bool p);
        Arma(const Arma& orig);
        virtual ~Arma();
        void BorrarProyectil(int i);
        void Dibujar();
        void ModificarSprite(int estado, int n, int x, int y, float angulo);
        void Disparar(float angulo);
        float GetDanyo();
        void CambiarDireccion();
        void Update(float x, float y, Player *p);
        void Update(float x, float y, vector<Enemigo*>e, Player *p);
    private:
        float danyo;
        SpriteM sprite;
        vector<Proyectil*> proyectiles;
        int tipo;
        Juego* _juego;
        bool player;

    };
}



