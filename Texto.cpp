#include "Texto.hpp"
namespace Motor
{
    Texto::Texto()
    {
    }
    
    void Texto::CambiarFuente(sf::Font& fon)
    {
        setFont(fon);
    }
    
    void Texto::CambiarTexto(string text)
    {
        setString(text);
    }
    
    void Texto::CambiarTamanyo(int tam)
    {
        setCharacterSize(tam);
    }
    
    void Texto::CambiarPosicion(float x, float y)
    {
        setPosition(x, y);
    }
    
    void Texto::CambiarOrigen(float x, float y)
    {
        setOrigin(x, y);
    }
    
    float Texto::GetAncho()
    {
        return getGlobalBounds().width;
    }
    
    float Texto::GetAlto()
    {
        return getGlobalBounds().height;
    }
    
    float Texto::GetX()
    {
        return getPosition().x;
    }
    
    float Texto::GetY()
    {
        return getPosition().y;
    }
}