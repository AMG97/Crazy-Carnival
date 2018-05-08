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
        
        posIniX = 60;
        posIniY = _juego->GetAlto()/2;
        
        sprite.CambiarTextura(_juego->recursos.GetTextura(textura));
        sprite.CambiarTextRect(0*60, 0*80, 60, 80);
        sprite.CambiarOrigen(sprite.GetAncho()/2, sprite.GetAlto()/2);
        sprite.CambiarPosicion(posIniX, posIniY);
        sprite.EscalarProporcion(1.5, 1.5);
        
        //TO DO: Box2d + façade
        _mundo = new b2World(b2Vec2(0.0, 9.8));
        cuerpoDef.type = b2BodyType::b2_dynamicBody;
        cuerpoDef.position = b2Vec2(sprite.GetX(), sprite.GetY());
        _cuerpo = _mundo->CreateBody(&cuerpoDef);
        
        cout <<"Ancho :"<<sprite.GetAncho()<<endl;
        cout <<"Alto :"<<sprite.GetAlto()<<endl;
        
        formaCuerpo.SetAsBox(sprite.GetAncho() / 2, sprite.GetAlto() / 2);
        fixCuerpoDef.shape = &formaCuerpo;
        fixCuerpoDef.density = 1.0;
        fixCuerpoDef.friction = 0.0;
        fixCuerpoDef.restitution = 0.0;
        _fixCuerpo = _cuerpo->CreateFixture(&fixCuerpoDef);
        
        guardado = false;
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
    
    void Player::SetVelocidadSalto(float velS)
    {
        velSalto = velS;
        _cuerpo->SetAngularVelocity(_mundo->GetGravity().y + velS);
    }
    
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
    
    b2World* Player::GetMundo()
    {
        return _mundo;
    }
    
    b2Body* Player::GetCuerpo()
    {
        return _cuerpo;
    }
    
    void Player::SetCuerpo()
    {
        _cuerpo = _mundo->CreateBody(&cuerpoDef);
    }
    
    b2BodyDef Player::GetCuerpoDefinicion()
    {
        return cuerpoDef;
    }
    
    void Player::SetCuerpoDefinicionPosicion(float32 posX, float32 posY)
    {
        cuerpoDef.position = b2Vec2(posX + velocidad, posY + _cuerpo->GetAngularVelocity());
    }
       
    b2Fixture* Player::GetFixtureCuerpo()
    {
        return _fixCuerpo;
    }
    
    b2FixtureDef Player::GetFixtureCuerpoDefinicion()
    {
        return fixCuerpoDef;
    }
    b2PolygonShape Player::GetForma()
    {
        return formaCuerpo;
    }
    
    void Player::SetAhora()
    {
        if (!guardado)
        {
            xAhora = sprite.GetX();
            yAhora = sprite.GetY();
            guardado = true;
        }
    }
    
    float Player::GetXAhora()
    {
        return xAhora;
    }
    
    float Player::GetYAhora()
    {
        return yAhora;
    }
    
    void Player::Saltar()
    {
        sprite.move(0, velSalto);
    }
}