#include "Player.hpp"
#include "Motor.hpp"

namespace Crazy
{
    Player::Player(string textura)
    {
        totalVida = 60.0f;
        vida = totalVida;
        enfriamiento = 0.0f;
        totalEnfriamiento = 30.0f;
        ataqueEspecial = false;
        direccionIzq = false;
        estado = REPOSO;
        contadorSpriteCorrer = 0;
        contadorSpriteReposo = 0;
        contadorSpriteSalto = 0;
        
        sprite.CambiarTextura(_juego->recursos.GetTextura(textura));
        sprite.CambiarTextRect(0*60, 0*80, 60, 80);
        
        
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
    
    void Player::Curar(float cura){
        ModificarVida(cura);
    }
    
    void Player::RecibirDanyo(float danyo)
    {
        ModificarVida(-danyo);
        ModificarEnfriamiento(danyo * 0.75f);
    }
    
    short int Player::GetEstado()
    {
        return estado;
    }
    
    short int  Player::GetCorrerDer()
    {
        return CORRER_DER;
    }
    
    short int  Player::GetCorrerIzq()
    {
        return CORRER_IZQ;
    }
    
    short int  Player::GetSaltarDer()
    {
        return SALTO_DER;
    }
    
    short int  Player::GetSaltarIzq()
    {
        return SALTO_IZQ;
    }
    
    short int  Player::GetReposo()
    {
        return REPOSO;
    }
    
    void Player::SetEstado(short int est)
    {
        estado = est;
    }
    
    /*float Player::GetVelocidadSalto()
    {
        return velocidad;
    }*/
    
    /*void Player::SetVelocidadSalto(float velS)
    {
        //_cuerpo->SetAngularVelocity(_mundo->GetGravity().y + velS);
    }*/
    
    void Player::ModificarSprite()
    {
        if (relojAnim.GetSegundos() >= 0.1f)
        {
            switch(estado)
            {
                case CORRER_IZQ:
                case CORRER_DER:
                    sprite.CambiarTextRect(contadorSpriteCorrer*65, 1*80, 65, 80);
                    contadorSpriteCorrer++;
                    if(contadorSpriteCorrer == 6)
                    {
                        contadorSpriteCorrer = 0;
                    }
                break;

                case SALTO_DER:
                case SALTO_IZQ:
                    sprite.CambiarTextRect(contadorSpriteSalto*65, 7*80, 65, 90);
                    contadorSpriteSalto++;
                    if(contadorSpriteSalto == 3)
                    {
                        contadorSpriteSalto = 0;
                    }
                break;

                case REPOSO:
                    sprite.CambiarTextRect(contadorSpriteReposo*60, 0*80, 60, 80);
                    contadorSpriteReposo++;
                    if(contadorSpriteReposo == 8)
                    {
                        contadorSpriteReposo = 0;
                    }
                break;
            }
            relojAnim.ReiniciarSegundos();
        }
    }
    
    void Player::CambiarDireccion()
    {
        if (((estado == CORRER_IZQ) || (estado == SALTO_IZQ)) 
            && (!direccionIzq))
        {
            cout << "Dir IZQ"<<endl;
            CambiarDireccionIzq();
        }
        else if (((estado == CORRER_DER) || (estado == SALTO_DER)) 
            && (direccionIzq))
        {
            cout << "Dir DER"<<endl;
            CambiarDireccionDer();
        }
    }
    
}