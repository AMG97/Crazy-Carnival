#pragma once
#include "Reloj.hpp"

namespace Motor
{
    float Reloj::RestartMiliseconds()
    {
        return restart().asMilliseconds();
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

