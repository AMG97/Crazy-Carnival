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
#include "Arma.hpp"

using namespace std;

    float Player::vida;
    float Player::enfriamiento;
    float Player::totalVida = vida;
    float Player::totalEnfriamiento;

Player::Player() {
    //pruebas jugador, variables
    elegirSprite = true;
    if(elegirSprite)
        texturaPj = juego->establecerTexturas("resources/espadachina-sin.png");
    else
        texturaPj = juego->establecerTexturas("resources/espadachina-sin.png");
    personaje.setTexture(texturaPj);
    personaje.setTextureRect(sf::IntRect(0*60, 0*80, 60, 80));
    personaje.setOrigin(60/2, 80/2);
    personaje.setPosition(640/2, 480/2);
    vida = 300.0;
    enfriamiento = 0.0;
    totalVida = vida;
    totalEnfriamiento = 50.0;
    posraton=sf::Vector2i(0,0);
    contadorSpriteReposo = 0;
    contadorSpriteCorrer = 0;
    contadorSpriteAtaque1= 0;
    contadorSpriteAtaque2= 0;
    Ataque1=false;
    Ataque2=false;
    Atacado2=false;
    arma= new Arma(2,personaje.getPosition());
    angulo=0;
    direccionIzquierda = false;
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
    jugadorDef.position = b2Vec2(jugador->GetPosition().x + velocidad.x, jugador->GetPosition().y + velocidad.y*jugador->GetGravityScale());
    jugador = mundo->CreateBody(&jugadorDef);
    personaje.setPosition(jugador->GetPosition().x, jugador->GetPosition().y);
}
void Player::draw(sf::RenderWindow& window){
    window.draw(personaje);
    arma->draw(window);
}
void Player::modificarSpriteCorrer()
{
    personaje.setTextureRect(sf::IntRect(contadorSpriteCorrer*60, 1*80, 60, 80));
    arma->modificarSpriteCorrer(contadorSpriteCorrer, personaje.getPosition());
    if((velocidad.x>0 && direccionIzquierda) ||(velocidad.x<0 && !direccionIzquierda)){
        contadorSpriteCorrer--;
        if(contadorSpriteCorrer == -1)
        {
            contadorSpriteCorrer = 5;
        }
    }else{
        contadorSpriteCorrer++;
        if(contadorSpriteCorrer == 6)
        {
            contadorSpriteCorrer = 0;
        }
    }
}

void Player::modificarSpriteAtaque2()
{
    float x=personaje.getPosition().x;
    float y=personaje.getPosition().y;
    personaje.setTextureRect(sf::IntRect(contadorSpriteAtaque2*100, 360, 100, 80));
    if(contadorSpriteAtaque2==0){
            personaje.setOrigin(100/2,80/2);
            if(!direccionIzquierda)
                personaje.setPosition(x,y-10);
            else
                personaje.setPosition(x,y-10);
            jugadorDef.type = b2BodyType::b2_dynamicBody;
            jugadorDef.position = b2Vec2(personaje.getPosition().x, personaje.getPosition().y);
            jugador = mundo->CreateBody(&jugadorDef);
            shapeJugador.SetAsBox(personaje.getGlobalBounds().width / 2, personaje.getGlobalBounds().height / 2);
            fixJugadorDef.shape = &shapeJugador;
            fixJugador = jugador->CreateFixture(&fixJugadorDef);
            if(this->EnfriamientoLleno()){
                tAtaque2.restart();
                Hud::modificarEnfriamiento(-50.0);
            }
        }
    arma->modificarSpriteAtaque2(contadorSpriteAtaque2, personaje.getPosition());
    contadorSpriteAtaque2++;
    if(contadorSpriteAtaque2 == 9)
    {
        reposo(2);
    }
    else if(contadorSpriteAtaque2==5){
        float x=personaje.getPosition().x;
        float y=personaje.getPosition().y;
        sf::Vector2f diferencia=sf::Vector2f(posraton.x-x,posraton.y-y);
        float angulo=atan2(diferencia.x,diferencia.y);
        arma->disparar(angulo);
    }
}

void Player::modificarSpriteAtaque1()
{
    float x=personaje.getPosition().x;
    float y=personaje.getPosition().y;
    sf::Vector2f diferencia=sf::Vector2f(posraton.x-x,posraton.y-y);
    if(contadorSpriteAtaque1==0){
        angulo=atan2(diferencia.x,diferencia.y)*180/3.141592;
        if(angulo<0)
            angulo=-angulo;
    }
    cout<<angulo<<endl;
    if(angulo>135){
        personaje.setTextureRect(sf::IntRect(contadorSpriteAtaque1*90, 240, 90, 120));
        if(contadorSpriteAtaque1==0){
            personaje.setOrigin(90/2,120/2);
            if(!direccionIzquierda)
                personaje.setPosition(x+15,y-30);
            else
                personaje.setPosition(x-15,y-30);
            jugadorDef.type = b2BodyType::b2_dynamicBody;
            jugadorDef.position = b2Vec2(personaje.getPosition().x, personaje.getPosition().y);
            jugador = mundo->CreateBody(&jugadorDef);
            shapeJugador.SetAsBox(personaje.getGlobalBounds().width / 2, personaje.getGlobalBounds().height / 2);
            fixJugadorDef.shape = &shapeJugador;
            fixJugador = jugador->CreateFixture(&fixJugadorDef);
        }
        arma->modificarSpriteAtaque1(contadorSpriteAtaque1,1, personaje.getPosition());
        contadorSpriteAtaque1++;
        
        if(contadorSpriteAtaque1 == 5)
        {
            reposo(1);
        }
        
    }else{
        personaje.setTextureRect(sf::IntRect(contadorSpriteAtaque1*100, 150, 100, 90));
        if(contadorSpriteAtaque1==0){
            personaje.setOrigin(100/2,90/2);
            if(!direccionIzquierda)
                personaje.setPosition(x,y-15);
            else
                personaje.setPosition(x,y-15);
            jugadorDef.type = b2BodyType::b2_dynamicBody;
            jugadorDef.position = b2Vec2(personaje.getPosition().x, personaje.getPosition().y);
            jugador = mundo->CreateBody(&jugadorDef);
            shapeJugador.SetAsBox(personaje.getGlobalBounds().width / 2, personaje.getGlobalBounds().height / 2);
            fixJugadorDef.shape = &shapeJugador;
            fixJugador = jugador->CreateFixture(&fixJugadorDef);
        }
        arma->modificarSpriteAtaque1(contadorSpriteAtaque1,2, personaje.getPosition());
        contadorSpriteAtaque1++;
        if(contadorSpriteAtaque1 == 6)
        {
            reposo(1);
        }
        
    }
}
void Player::modificarSpriteReposo()
{
    personaje.setTextureRect(sf::IntRect(contadorSpriteReposo*60, 0*80, 60, 80));
    arma->modificarSpriteReposo(contadorSpriteReposo,personaje.getPosition());
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
void Player::setDireccion(bool direccion)
{
    direccionIzquierda = direccion;
    if(direccionIzquierda && personaje.getScale().x==1.0){
        personaje.scale(-1.0, 1.0);
        arma->scale(-1.0,1.0);
    }
    else if(!direccionIzquierda && personaje.getScale().x==-1.0){
        personaje.scale(-1.0, 1.0);
        arma->scale(-1.0, 1.0);
    }
}
//Funciones que se quedarán en player
void Player::setVelocidadSalto(float modificacionVelocidad)
{   
    //b2Vec2 velocidadSalto = b2Vec2(velocidad.x, modificacionVelocidad);
    //jugador->ApplyForce(b2Vec2(jugador->GetPosition().x, jugador->GetPosition().y + 2000.0), jugador->GetPosition(), false);
//bool maximoAlcanzado = topeSalto;
    if(velocidad.y <= 2.0 && velocidad.y >= -2.0)
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
    }
}
float Player::getVelocidadSalto()
{
    return velocidad.y;
}
void Player::setVelocidad(float modificacionVelocidad)
{
    if(velocidad.x <= 2.0 && velocidad.x >= -2.0)
    {
        if(velocidad.x < 2.0 && velocidad.x > 1.8 && modificacionVelocidad > 0.0)
            velocidad.x = 2.0;
        else if(velocidad.x > -2.0 && velocidad.x < -1.8 && modificacionVelocidad < 0.0)
            velocidad.x = -2.0;
        else if((velocidad.x < 2.0 && modificacionVelocidad > 0.0) || (velocidad.x > -2.0 && modificacionVelocidad < 0.0))
            velocidad.x += modificacionVelocidad;
        else if(modificacionVelocidad == 0.0){
            if((velocidad.x > 0.0 && velocidad.x < 0.2) || ((velocidad.x < 0.0 && velocidad.x > 0.2)))
                velocidad.x = 0.0;
            else if(velocidad.x > 0.0)
                velocidad.x -= 0.2;
            else if(velocidad.x < 0.0)
                velocidad.x += 0.2;
        }
    }
}
float Player::getVelocidad()
{
    return velocidad.x;
}
void Player::recibirDanyo(float danyo){
    Hud::modificarVida(-danyo);
    Hud::modificarEnfriamiento(danyo * 0.25);
    if(vida<0){
        //cout<<"Jugador muerto"<<endl;
    }else{
        //cout<<"Jugador recibe danyo:"<<danyo<<endl;
    }
    cout<<"Vida jugador: "<<vida<<endl;
}
void Player::curar(float cura){
    vida += cura;
    Hud::modificarVida(cura);
}
void Player::actualizarFisica(){
    mundo->Step(1/60, 8, 8);
    mundo->ClearForces();
}

void Player::setAtaque1(bool b, sf::Vector2i posra){
    Ataque1=b;
    posraton=posra;
}
void Player::setAtaque2(bool b, sf::Vector2i posra){
    Ataque2=b;
    posraton=posra;
    Atacado2=true;
}

bool Player::getAtaque1(){
    return Ataque1;
}
bool Player::getAtaque2(){
    return Ataque2;
}

bool Player::getDireccion(){
    return direccionIzquierda;
}

void Player::reposo(int n){
    personaje.setTextureRect(sf::IntRect(0*60, 0*80, 60, 80));
    float x=personaje.getPosition().x;
    float y=personaje.getPosition().y;
    personaje.setOrigin(60/2,80/2);
    if(n==1){
            Ataque1=false;
            contadorSpriteAtaque1 = 0;
            if(angulo>135){
                if(!direccionIzquierda)
                    personaje.setPosition(x-15,y+30);
                else
                    personaje.setPosition(x+15,y+30);
            }else{
                    personaje.setPosition(x,y+15);
            }
    }else{
        Ataque2=false;
        contadorSpriteAtaque2 = 0;
        personaje.setPosition(x,y+10);
        
    }
    posraton=sf::Vector2i(0,0);
    jugadorDef.type = b2BodyType::b2_dynamicBody;
    jugadorDef.position = b2Vec2(personaje.getPosition().x, personaje.getPosition().y);
    jugador = mundo->CreateBody(&jugadorDef);
    shapeJugador.SetAsBox(personaje.getGlobalBounds().width / 2, personaje.getGlobalBounds().height / 2);
    fixJugadorDef.shape = &shapeJugador;
    fixJugador = jugador->CreateFixture(&fixJugadorDef);
    
}

Arma* Player::getArma(){
    return arma;
}

bool Player::EnfriamientoLleno(){
    if(enfriamiento>=totalEnfriamiento)
        return true;
    else 
        return false;
}

float Player::gettAtaque2(){
    if(!Atacado2)
        return 5;
    else
    return tAtaque2.getElapsedTime().asSeconds();
}