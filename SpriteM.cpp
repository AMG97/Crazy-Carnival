#include "SpriteM.hpp"
namespace Motor
{
    SpriteM::SpriteM()
    {
    }
    
    void SpriteM::CambiarTextura(sf::Texture &textura)
    {
        setTexture(textura);
    }
    
    void SpriteM::CambiarPosicion(float x, float y)
    {
        setPosition(x, y);
    }
    
    void SpriteM::CentrarOrigen()
    {
        setOrigin(getTexture()->getSize().x/2, getTexture()->getSize().y/2);
    }
    
    void SpriteM::CambiarOrigen()
    {
        setOrigin(getTexture()->getSize().x, getTexture()->getSize().y/2);
    }
    
    void SpriteM::CambiarOrigen(float x, float y)
    {
        setOrigin(x, y);
    }
    
    void SpriteM::CambiarColorRojo()
    {
        setColor(sf::Color::Red);
    }
    
    void SpriteM::Rotar(float angulo)
    {
        rotate(angulo);
    }
    
    void SpriteM::Escalar(float x, float y)
    {
        scale(x/getTexture()->getSize().x, y/getTexture()->getSize().y);
    }
    
    float SpriteM::GetAncho()
    {
        return getGlobalBounds().width;
    }
    
    float SpriteM::GetAlto()
    {
        return getGlobalBounds().height;
    }
    
    float SpriteM::GetX()
    {
        return getPosition().x;
    }
    
    float SpriteM::GetY()
    {
        return getPosition().y;
    }
}