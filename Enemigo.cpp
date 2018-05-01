/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Enemigo.cpp
 * Author: fv
 * 
 * Created on May 1, 2018, 8:23 PM
 */

#include <SFML/Graphics/Texture.hpp>

#include "Enemigo.hpp"
#include "Arma.hpp"
Enemigo::Enemigo() {
    texturaEnemigo.loadFromFile("resources/enemigo-pistola.png");
    enemigo.setTexture(texturaEnemigo);
    enemigo.setTextureRect(sf::IntRect(0, 0, 70, 80));
    enemigo.setOrigin(70/2, 80/2);
    enemigo.setPosition(600, 480/2);
    posini=enemigo.getPosition();
    pos=posini;
    vida = 60.0;
    contadorSpriteCorrer = 0;
    contadorSpriteAtaque1= 0;
    Ataque1=false;
    arma= new Arma(0, pos);
    angulo=0;
    setDireccion(true);
    velocidad= 2.1;
    alcance=sf::Vector2f(300,50);
    movimiento=200;
    tAtaque.restart();
    tDesp.restart();
}

void Enemigo::modificarSpriteAtaque1(){
    enemigo.setTextureRect(sf::IntRect(contadorSpriteAtaque1*70, 80,70,80));
    contadorSpriteAtaque1++;
    if(contadorSpriteAtaque1==2){
        contadorSpriteAtaque1=0;
        arma->disparar(angulo);
        tAtaque.restart();
        Ataque1=false;
    }
}

void Enemigo::modificarSpriteCorrer(){
    enemigo.setTextureRect(sf::IntRect(contadorSpriteCorrer*70,0,70,80));
    contadorSpriteCorrer++;
    if(contadorSpriteCorrer==3){
        contadorSpriteCorrer=0;
    }
}

void Enemigo::setDireccion(bool direccion)
{
    direccionIzquierda = direccion;
    if(direccionIzquierda && enemigo.getScale().x==1.0){
        enemigo.scale(-1.0, 1.0);
    }
    else if(!direccionIzquierda && enemigo.getScale().x==-1.0){
        enemigo.scale(-1.0, 1.0);
    }
}
    

void Enemigo::update(sf::Vector2f posplayer){
    sf::Vector2f diferencia=sf::Vector2f(posplayer.x-pos.x,posplayer.y-pos.y);
    angulo=atan2(diferencia.x,diferencia.y);
    arma->update(pos);
    bool mov=false;
    if(abs(diferencia.x)<alcance.x && abs(diferencia.y)<alcance.y){
        cout<<tDesp.getElapsedTime().asSeconds()<<endl;
        if(posplayer.x>pos.x && posplayer.x-pos.x>100){
            if(direccionIzquierda)
                setDireccion(false);
            enemigo.move(velocidad,0);
            pos=enemigo.getPosition();
            mov=true;
        }
        else if(posplayer.x<pos.x && pos.x-posplayer.x>100){
            if(!direccionIzquierda)
                setDireccion(true);
            enemigo.move(-velocidad,0);
            pos=enemigo.getPosition();
            mov=true;
        }
        if(tAtaque.getElapsedTime().asSeconds()>1.5){
            Ataque1=true;
        }
        if(tDesp.getElapsedTime().asSeconds()>0.1){
            if(Ataque1){
                modificarSpriteAtaque1();
                tDesp.restart();
            }
            else if(tAtaque.getElapsedTime().asSeconds()<1.2 && mov && tDesp.getElapsedTime().asSeconds()>0.2){
                modificarSpriteCorrer();
                tDesp.restart();
            }
        }
    }else{
        if(direccionIzquierda){
            if(posini.x-pos.x>movimiento){
                setDireccion(false);
            }else{
                enemigo.move(-velocidad,0);
                pos=enemigo.getPosition();
                if(tDesp.getElapsedTime().asSeconds()>0.1){
                    if(Ataque1){
                        modificarSpriteAtaque1();
                        tDesp.restart();
                    }
                    else if(tDesp.getElapsedTime().asSeconds()>0.2){
                        modificarSpriteCorrer();
                        tDesp.restart();
                    }
                }
            }
        }
        else{
            if(pos.x-posini.x>movimiento){
                setDireccion(true);
            }else{
                enemigo.move(velocidad,0);
                pos=enemigo.getPosition();
            }
            if(tDesp.getElapsedTime().asSeconds()>0.1){
                if(Ataque1){
                    modificarSpriteAtaque1();
                    tDesp.restart();
                }
                else if(tDesp.getElapsedTime().asSeconds()>0.2){
                    modificarSpriteCorrer();
                    tDesp.restart();
                }
            }
        }
    }
}
void Enemigo::draw(sf::RenderWindow& window){
    window.draw(enemigo);
    arma->draw(window);
}

Enemigo::Enemigo(const Enemigo& orig) {
}

Enemigo::~Enemigo() {
}

