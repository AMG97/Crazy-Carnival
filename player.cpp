/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   player.cpp
 * Author: fv
 * 
 * Created on March 24, 2018, 12:01 PM
 */

#include <SFML/Graphics.hpp>

#include "juegoHud.hpp"
#include "player.hpp"
#include "iostream"
#include "hud.hpp"
#include <Box2D/Box2D.h>

using namespace std;

    float Player::vida;
    float Player::enfriamiento;
    float Player::totalVida = vida;
    float Player::totalEnfriamiento;

Player::Player() {
    //pruebas jugador, variables
    elegirSprite = true;
    if(elegirSprite)
        texturaPj = juego->establecerTexturas("./resources/Sprite-espadachina.png");
    else
        texturaPj = juego->establecerTexturas("./resources/Sprite-espadachina.png");
    personaje.setTexture(texturaPj);
    personaje.setTextureRect(sf::IntRect(0*60, 0*80, 60, 80));
    personaje.setOrigin(60/2, 80/2);
    personaje.setPosition(640/2, 480/2);
    vida = 60.0;
    enfriamiento = 0.0;
    totalVida = vida;
    totalEnfriamiento = 30.0;
    
    contadorSpriteReposo = 0;
    contadorSpriteCorrer = 0;
    estadoPersonaje = 0;
    velocidad.x = 0.0;
    velocidad.y = 0.0;
    mundo = new b2World(b2Vec2(0.0, 9.81));
    jugadorDef.type = b2BodyType::b2_dynamicBody;
    jugadorDef.position = b2Vec2(personaje.getPosition().x, personaje.getPosition().y);
    jugador = mundo->CreateBody(&jugadorDef);
    shapeJugador.SetAsBox(personaje.getGlobalBounds().width / 2, personaje.getGlobalBounds().height / 2);
    fixJugadorDef.shape = &shapeJugador;
    fixJugadorDef.density = 1.0;
    fixJugadorDef.friction = 0.0;
    fixJugadorDef.restitution = 0.0;
    fixJugador = jugador->CreateFixture(&fixJugadorDef);
}

Player::Player(const Player& orig) {
}

Player::~Player() {
}
void Player::update(sf::Clock *clock){
    //this->actualizarFisica();
    //jugador->ApplyForce(b2Vec2(jugador->GetPosition().x + velocidad.x*10, jugador->GetPosition().y + velocidad.y), jugador->GetPosition(), false);
    jugadorDef.position = b2Vec2(jugador->GetPosition().x + velocidad.x, jugador->GetPosition().y + jugador->GetAngularVelocity()*jugador->GetGravityScale());
    jugador = mundo->CreateBody(&jugadorDef);
    personaje.setPosition(jugador->GetPosition().x, jugador->GetPosition().y);
}
void Player::draw(sf::RenderWindow& window){
    window.draw(personaje);
}
void Player::modificarSpriteCorrer()
{
    personaje.setTextureRect(sf::IntRect(contadorSpriteCorrer*65, 1*85, 60, 80));
    contadorSpriteCorrer++;
    if(contadorSpriteCorrer == 6)
    {
        contadorSpriteCorrer = 0;
    }
}
void Player::modificarSpriteReposo()
{
    personaje.setTextureRect(sf::IntRect(contadorSpriteReposo*60, 0*85, 60, 80));
    contadorSpriteReposo++;
    if(contadorSpriteReposo == 8)
    {
        contadorSpriteReposo = 0;
    }
}
sf::Sprite Player::getSprite()
{
    return personaje;
}
void Player::setEstadoPersonaje(int direccion)
{
    estadoPersonaje = direccion;
    if((estadoPersonaje == 2 || estadoPersonaje == 4) && personaje.getScale().x > 0.0){
        personaje.scale(-1.0, 1.0);
    }
    else if((estadoPersonaje == 1 || estadoPersonaje == 3) && personaje.getScale().x < 0.0)
        personaje.scale(-1.0, 1.0);
}
//Devuelve el entero que indica el estado del personaje
int Player::getEstadoPersonaje()
{
    return estadoPersonaje;
}
//Funciones que se quedarán en player
void Player::setVelocidadSalto(float modificacionVelocidad)
{   
    //int contador;
    if(modificacionVelocidad < 0.0){
        //contador = 0;
        //while(modificacionVelocidad < 0.0){
        jugador->SetAngularVelocity(modificacionVelocidad);
        /*    modificacionVelocidad++;
        }*/
    }
    else
    {
        jugador->SetAngularVelocity(jugador->GetGravityScale() + modificacionVelocidad);
    }
    //b2Vec2 velocidadSalto = b2Vec2(velocidad.x, modificacionVelocidad);
    //jugador->ApplyForce(b2Vec2(jugador->GetPosition().x, jugador->GetPosition().y + 2000.0), jugador->GetPosition(), false);
//bool maximoAlcanzado = topeSalto;
    /*if(velocidad.y <= 2.0 && velocidad.y >= -2.0)
    {
        if(modificacionVelocidad == 0.0)
        {
            cout <<"el 4"<< endl;
            velocidad.y = 0.0;
        }
        else if(velocidad.y > -2.0 && velocidad.y < -1.6 && modificacionVelocidad < 0.0){
            cout <<"el 2"<< endl;
            velocidad.y = -2.0;
        }
        else if(velocidad.y < 2.0 && velocidad.y > 1.6 && modificacionVelocidad > 0.0){
            cout <<"el 1"<< endl;
            velocidad.y = 2.0;
        }
        else if((velocidad.y < 2.0 && modificacionVelocidad > 0.0) || (velocidad.y > -2.0 && modificacionVelocidad < 0.0)){
            cout <<"el 3"<< endl;
            velocidad.y += modificacionVelocidad;
        }
    }*/
}
float Player::getVelocidadSalto()
{
    return velocidad.y;
}
void Player::setVelocidad(float modificacionVelocidad)
{
    velocidad.x = modificacionVelocidad;
}
float Player::getVelocidad()
{
    return velocidad.x;
}
void Player::recibirDanyo(float danyo){
    vida -= danyo;
    enfriamiento += danyo * 0.75;
    Hud::modificarVida(-danyo);
    Hud::modificarEnfriamiento(danyo * 0.75);
    cout << "Daño" <<endl;
}
void Player::curar(float cura){
    vida += cura;
    Hud::modificarVida(cura);
}
void Player::actualizarFisica(){
    mundo->Step(1/60, 8, 8);
    mundo->ClearForces();
}
b2Body *Player::getCuerpo(){
    return jugador;
}
float Player::getEnfriamiento()
{
    return enfriamiento;
}
float Player::getTotalEnfriamiento()
{
    return totalEnfriamiento;
}

