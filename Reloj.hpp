#pragma once
using namespace std;
#include <SFML/Graphics.hpp>

namespace Motor
{
    class Reloj : public sf::Clock {
    public:
        Reloj() { };
        float ReiniciarMilisegundos();
        float ReiniciarSegundos();
        float GetSegundos();
        float GetMilisegundos();
    };
}