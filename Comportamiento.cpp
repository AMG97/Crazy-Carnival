#include "Comportamiento.hpp"

namespace Crazy
{
    Comportamiento::Comportamiento()
    {
        _juego = Juego::Instance();
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
    
    float Comportamiento::GetVelocidad()
    {
        return velocidad;
    }
    
    void Comportamiento::SetVelocidad(float vel)
    {
        velocidad = vel;
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
        return sprite.GetX();
    }

    float Comportamiento::GetPosY()
    {
        return sprite.GetY();
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
    
    void Comportamiento::CambiarDireccionDer()
    {
        direccionIzq = false;
        sprite.EscalarProporcion(-1.0, 1.0);
    }
    
    void Comportamiento::CambiarDireccionIzq()
    {
        direccionIzq = true;
        sprite.EscalarProporcion(-1.0, 1.0);
    }
    
    bool Comportamiento::GetDireccionIzq()
    {
        return direccionIzq;
    }
    
    void Comportamiento::Mover()
    {
        sprite.Mover(velocidad);
    }
    
    void Comportamiento::CambiarPosicion(float x, float y)
    {
        sprite.CambiarPosicion(x, y);
    }
}