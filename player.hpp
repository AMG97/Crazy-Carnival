/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   player.hpp
 * Author: fv
 *
 * Created on March 24, 2018, 12:01 PM
 */

#ifndef PLAYER_HPP
#define PLAYER_HPP
#include <Box2D/Box2D.h>

class Hud;
class JuegoHud;
class Arma;
class Player {
public:
    Player();
    Player(const Player& orig);
    virtual ~Player();
    void update(sf::Clock *clock);
    void draw(sf::RenderWindow& window);
    void modificarSpriteCorrer();
    void modificarSpriteReposo();
    void modificarSpriteAtaque1();
    void modificarSpriteAtaque2();
    sf::Sprite getSprite();
    void setDireccion(bool direccion);
    bool getDireccion();
    void actualizarFisica();
    
    void setVelocidadSalto(float altura);
    float getVelocidadSalto();
    void setVelocidad(float modificacionVelocidad);
    float getVelocidad();
    void recibirDanyo(float danyo);
    void curar(float cura);
    bool getAtaque1();
    void setAtaque1(bool b,sf::Vector2i posra);
    bool getAtaque2();
    void setAtaque2(bool b,sf::Vector2i posra);
    void reposo(int n);
    Arma* getArma();

protected:
    JuegoHud *juego;
    //Hud *hud;
    bool elegirSprite;
    sf::Texture texturaPj;
    sf::Sprite personaje;
    int contadorSpriteReposo;
    int contadorSpriteCorrer;
    int contadorSpriteAtaque1;
    int contadorSpriteAtaque2;
    sf::Vector2i posraton;
    bool direccionIzquierda;
    bool Ataque1;
    bool Ataque2;
    float angulo;
    Arma *arma;
    float static vida;
    float static enfriamiento;
    float static totalVida;
    float static totalEnfriamiento;
    sf::Vector2f velocidad;
    b2World *mundo;
    b2Body *jugador;
    b2BodyDef jugadorDef;
    b2Fixture *fixJugador;
    b2FixtureDef fixJugadorDef;
    b2PolygonShape  shapeJugador;
};

#endif /* PLAYER_HPP */

