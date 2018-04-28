#pragma once
using namespace std;
#include <SFML/Graphics.hpp>

namespace Motor
{
    class SpriteM : public sf::Sprite {
    public:
        SpriteM();
        void CambiarTextura(sf::Texture &textura);
        void CambiarPosicion(float x, float y);
        void CentrarOrigen();
        void CambiarOrigen();
        void CambiarOrigen(float x, float y);
        void CambiarColorRojo();
        void Rotar(float angulo);
        void Escalar(float x, float y);
        
        float GetAncho();
        float GetAlto();
        float GetX();
        float GetY();
        
    private:
    };
}