#pragma once
#include "Reloj.hpp"

namespace Motor
{
    float Reloj::ReiniciarMilisegundos()
    {
        return restart().asMilliseconds();
    }
    
    float Reloj::ReiniciarSegundos()
    {
        return restart().asSeconds();
    }
    
    float Reloj::GetSegundos()
    {
        return getElapsedTime().asSeconds();
    }
    
    float Reloj::GetMilisegundos()
    {
        return getElapsedTime().asMilliseconds();
    }
}

