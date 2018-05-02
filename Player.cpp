#include "Player.hpp"

namespace Crazy
{
    Player::Player()
    {
        totalVida = 60.0f;
        vida = totalVida;
        enfriamiento = 0.0f;
        totalEnfriamiento = 30.0f;
        ataqueEspecial = false;
        contadorSpriteReposo = 0;
        contadorSpriteCorrer = 0;
        contadorSpriteSalto = 0;
    }
    
    float Player::GetEnfriamiento()
    {
        return enfriamiento;
    }
    
    float Player::GetTotalEnfriamiento()
    {
        return totalEnfriamiento;
    }
    
    void Player::SetEnfriamiento(float e)
    {
        enfriamiento = e;
    }
    
    void Player::ModificarEnfriamiento(float modificador)
    {
        enfriamiento += modificador;
        if(enfriamiento > totalEnfriamiento)
        {
            enfriamiento = totalEnfriamiento;
        }
        else if(enfriamiento < 0.0)
        {
            enfriamiento = 0.0;
        }
    }
    
    bool Player::GetAtaqueEspecial()
    {
        return ataqueEspecial;
    }
    
    void Player::SetAtaqueEspecial(bool ataque)
    {
        ataqueEspecial = ataque;
    }
    
    bool Player::AtaqueEspecialActivado()
    {
        ataqueEspecial = false;
        if (enfriamiento == totalEnfriamiento)
        {
            ataqueEspecial = true;
        }
        return ataqueEspecial;
    }
    
    int Player::GetEstadoPersonaje()
    {
        return estadoPersonaje;
    }
    
    void Player::SetEstadoPersonaje(int estado)
    {
        estadoPersonaje = estado;
    }
        
    void Player::Curar(float cura){
        ModificarVida(cura);
    }
    
    void Player::RecibirDanyo(float danyo)
    {
        ModificarVida(-danyo);
        ModificarEnfriamiento(danyo * 0.75f);
    }
    
}