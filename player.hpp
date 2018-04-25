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
class Player {
public:
    Player();
    Player(const Player& orig);
    virtual ~Player();
    void update(sf::Clock *clock);
    void draw(sf::RenderWindow& window);
    void modificarSpriteCorrer();
    void modificarSpriteReposo();
    sf::Sprite getSprite();
    void setDireccion(bool direccion);
    void actualizarFisica();
    
    //Estas sí son de player
    void setVelocidadSalto(float altura);
    float getVelocidadSalto();
    void setVelocidad(float modificacionVelocidad);
    float getVelocidad();
    void recibirDanyo(float danyo);
    void curar(float cura);

protected:
    JuegoHud *juego;
    //Hud *hud;
    bool elegirSprite;
    sf::Texture texturaPj;
    sf::Sprite personaje;
    int contadorSpriteReposo;
    int contadorSpriteCorrer;
    bool direccionIzquierda;
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

