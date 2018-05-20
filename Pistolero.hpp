#pragma once
#include "Player.hpp"
#include "Arma.hpp"
#include "Enemigo.hpp"

// Constantes
#define REPOSO 0
#define CORRER 1
#define CORRERATRAS 5
#define SALTO 2
#define ATAQUE1 3
#define ATAQUE2 4
#define DESLIZARSE 6

namespace Crazy
{
    class Pistolero : public Player
    {
    public:
        Pistolero(int arma);
        void ModificarSprite();
        void Reposo(int n);  
        void Update(vector<Enemigo*> e);

    private:

    };
}

