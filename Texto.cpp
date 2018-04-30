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
    
    void Texto::CentrarOrigen()
    {
        setOrigin(GetAncho()/2, GetAlto()/2);
    }
    
    void Texto::CambiarOrigen(float x, float y)
    {
        setOrigin(x, y);
    }
    
    float Texto::GetOrigenX()
    {
        return getOrigin().x;
    }
    
    float Texto::GetOrigenY()
    {
        return getOrigin().y;
    }
    
    float Texto::GetAncho()
    {
        return getGlobalBounds().width;
    }
    
    float Texto::GetAlto()
    {
        return getGlobalBounds().height;
    }
    
    float Texto::GetTop()
    {
        return getGlobalBounds().top;
    }
    
    float Texto::GetLeft()
    {
        return getGlobalBounds().left;
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