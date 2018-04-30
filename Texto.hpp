#pragma once
using namespace std;
#include <SFML/Graphics.hpp>

namespace Motor
{
    class Texto : public sf::Text {
    public:
        Texto() { };
        void CambiarFuente(sf::Font& fuente);
        void CambiarTexto(string text);
        void CambiarTamanyo(int tam);
        void CambiarPosicion(float x, float y);
        void CentrarOrigen();
        void CambiarOrigen(float x, float y);
        
        float GetOrigenX();
        float GetOrigenY();
        float GetAncho();
        float GetAlto();
        float GetTop();
        float GetLeft();
        float GetX();
        float GetY();
    };
}