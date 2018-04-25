#pragma once
using namespace std;
#include <SFML/Graphics.hpp>

namespace Motor
{
    class Texto : public sf::Text {
    public:
        Texto();
        void CambiarFuente(sf::Font& fuente);
        void CambiarTexto(string text);
        void CambiarTamanyo(int tam);
        void CambiarPosicion(float x, float y);
        void CambiarOrigen(float x, float y);
        
        float GetAncho();
        float GetAlto();
        float GetX();
        float GetY();
    private:
    };
}