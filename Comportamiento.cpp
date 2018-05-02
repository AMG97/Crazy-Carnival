#include "Comportamiento.hpp"

namespace Crazy
{
    Comportamiento::Comportamiento()
    {
        _juego = Juego::Instance();
        
        sprite.CambiarOrigen(sprite.GetAncho()/2, sprite.GetAlto()/2);
        sprite.CambiarPosicion(_juego->GetAncho()/2, _juego->GetAlto()/2);
        sprite.EscalarProporcion(1.5, 1.5);
    }

    float Comportamiento::GetVida()
    {
        return vida;
    }

    float Comportamiento::GetTotalVida()
    {
        return totalVida;
    }

    void Comportamiento::SetVida(float v)
    {
        vida = v;
    }

    void Comportamiento::ModificarVida(float modificador)
    {
        vida += modificador;
        if (vida < 0)
        {
            vida = 0;
        }
        else if (vida > totalVida)
        {
            vida = totalVida;
        }
    }

    float Comportamiento::GetPosIniX()
    {
        return posIniX;
    }

    float Comportamiento::GetPosIniY()
    {
        return posIniY;
    }

    void Comportamiento::SetPosIniX(float x)
    {
        posIniX = x;
    }

    void Comportamiento::SetPosIniY(float y)
    {
        posIniY = y;
    }
    
    float Comportamiento::GetPosX()
    {
        return posX;
    }

    float Comportamiento::GetPosY()
    {
        return posY;
    }

    void Comportamiento::SetPosX(float x)
    {
        posX = x;
    }

    void Comportamiento::SetPosY(float y)
    {
        posY = y;
    }
    
    void Comportamiento::Dibujar()
    {
        _juego->_ventana->Dibujar(sprite);
    }
}