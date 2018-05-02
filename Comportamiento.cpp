#include "Comportamiento.hpp"

namespace Crazy
{
    Comportamiento::Comportamiento()
    {
        _juego = Juego::Instance();
        //TO DO If jugador = 1, espadachina; if jugador = 2, tipo duro ... jugador 4
        spJugador.CambiarTextura(_juego->recursos.GetTextura("Espadachina"));
        spJugador.setTextureRect(sf::IntRect(0*60, 0*80, 60, 80));
        spJugador.CambiarOrigen(spJugador.GetAncho()/2, spJugador.GetAlto()/2);
        spJugador.CambiarPosicion(_juego->GetAncho()/2, _juego->GetAlto()/2);
        spJugador.EscalarProporcion(1.5, 1.5);
        velocidad = 0.0;
        estadoPersonaje = 0;
        contadorSpriteCorrer = 0;
        contadorSpriteReposo = 0;
        contadorSpriteSalto = 0;
        
        //TO DO: Box2d + façade
        _mundo = new b2World(b2Vec2(0.0, 9.8));
        cuerpoDef.type = b2BodyType::b2_dynamicBody;
        cuerpoDef.position = b2Vec2(spJugador.GetX(), spJugador.GetY());
        _cuerpo = _mundo->CreateBody(&cuerpoDef);
        formaCuerpo.SetAsBox(spJugador.GetAncho() / 2, spJugador.GetAlto() / 2);
        fixCuerpoDef.shape = &formaCuerpo;
        fixCuerpoDef.density = 1.0;
        fixCuerpoDef.friction = 0.0;
        fixCuerpoDef.restitution = 0.0;
        _fixCuerpo = _cuerpo->CreateFixture(&fixCuerpoDef);
    }
    
    float Comportamiento::GetVida()
    {
        return vida;
    }
    
    float Comportamiento::GetTotalVida()
    {
        return totalVida;
    }
    
    SpriteM Comportamiento::GetSpriteM()
    {
        return spJugador;
    }
    
    void Comportamiento::SetVida(float v)
    {
        vida = v;
    }
    
    void Comportamiento::SetVelocidad(float vel)
    {
        velocidad = vel;
    }
    
    float Comportamiento::GetVelocidad()
    {
        return velocidad;
    }
    
    void Comportamiento::SetVelocidadSalto(float velS)
    {
        _cuerpo->SetAngularVelocity(_mundo->GetGravity().y + velS);
    }
    
    /*float Comportamiento::GetVelocidadSalto()
    {
        return velocidad;
    }*/
    
    int Comportamiento::GetEstadoPersonaje()
    {
        return estadoPersonaje;
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
    
    void Comportamiento::ModificarSprite()
    {
        if(estadoPersonaje == 1 || estadoPersonaje == 2)
        {
            spJugador.setTextureRect(sf::IntRect(contadorSpriteCorrer*65, 1*80, 65, 80));
            contadorSpriteCorrer++;
            if(contadorSpriteCorrer == 6)
            {
                contadorSpriteCorrer = 0;
            }
        }
        else if(estadoPersonaje == 3 || estadoPersonaje == 4)
        {
            spJugador.setTextureRect(sf::IntRect(contadorSpriteSalto*65, 7*80, 65, 90));
            contadorSpriteSalto++;
            if(contadorSpriteSalto == 3)
            {
                contadorSpriteSalto = 0;
            }
        }
        else if(estadoPersonaje == 0)
        {
            spJugador.setTextureRect(sf::IntRect(contadorSpriteReposo*60, 0*80, 60, 80));
            contadorSpriteReposo++;
            if(contadorSpriteReposo == 8)
            {
                contadorSpriteReposo = 0;
            }
        }
    }
    
    void Comportamiento::Mover(float posX, float posY)
    {
        spJugador.CambiarPosicion(posX, posY);
    }
    
    void Comportamiento::Dibujar()
    {
        _juego->_ventana->Dibujar(spJugador);
    }
    
    b2World* Comportamiento::GetMundo()
    {
        return _mundo;
    }
    
    b2Body* Comportamiento::GetCuerpo()
    {
        return _cuerpo;
    }
    
    void Comportamiento::SetCuerpo()
    {
        _cuerpo = _mundo->CreateBody(&cuerpoDef);
    }
    
    b2BodyDef Comportamiento::GetCuerpoDefinicion()
    {
        return cuerpoDef;
    }
    
    void Comportamiento::SetCuerpoDefinicionPosicion(float32 posX, float32 posY)
    {
        cuerpoDef.position = b2Vec2(posX + velocidad, posY + _cuerpo->GetAngularVelocity());
    }
       
    b2Fixture* Comportamiento::GetFixtureCuerpo()
    {
        return _fixCuerpo;
    }
    
    b2FixtureDef Comportamiento::GetFixtureCuerpoDefinicion()
    {
        return fixCuerpoDef;
    }
    b2PolygonShape Comportamiento::GetForma()
    {
        return formaCuerpo;
    }
}