/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Arma.cpp
 * Author: fv
 * 
 * Created on April 28, 2018, 4:02 PM
 */

#include "Arma.hpp"
#include "player.hpp"
#include "Enemigo.hpp"

Arma::Arma(int n, sf::Vector2f pos) {
    if(n==1){
        texturaArma=juego->establecerTexturas("resources/espada1.png");
        danyo=50;
    }else if(n==2){
        texturaArma=juego->establecerTexturas("resources/espada2.png");
        danyo=60;
    }else if(n==0){
        danyo=70;
        texturaArma=juego->establecerTexturas("resources/enemigo-pistola.png");
    }
    tipo=n;
    arma.setTexture(texturaArma);
    arma.setTextureRect(sf::IntRect(0*60, 0*80, 60, 80));
    arma.setOrigin(60/2, 80/2);
    arma.setPosition(pos);
}

void Arma::modificarSpriteReposo(int n, sf::Vector2f pos){
    arma.setTextureRect(sf::IntRect(n*60, 0*80, 60, 80));
    arma.setOrigin(30,40);
    arma.setPosition(pos);
}

void Arma::modificarSpriteCorrer(int n, sf::Vector2f pos){
    arma.setPosition(pos);
    arma.setTextureRect(sf::IntRect(n*60, 1*80, 60, 80));
    arma.setOrigin(30,40);
}

void Arma::modificarSpriteAtaque2(int n, sf::Vector2f pos){
    arma.setPosition(pos);
    arma.setTextureRect(sf::IntRect(n*100, 360, 100, 80));
    arma.setOrigin(50,40);
}

void Arma::modificarSpriteAtaque1(int n, int n2, sf::Vector2f pos){
    if(n2==1){
        arma.setPosition(pos);
        arma.setTextureRect(sf::IntRect(n*90, 240, 90, 120));
        arma.setOrigin(45,60);
    }else{
        arma.setPosition(pos);
        arma.setTextureRect(sf::IntRect(n*100, 150, 100, 90));
        arma.setOrigin(50,45);
    }
}

sf::Sprite Arma::getSprite(){
    return arma;
}

void Arma::scale(float nx, float ny){
    arma.scale(nx,ny);
}

void Arma::draw(sf::RenderWindow& window){
    if(tipo!=0)
    window.draw(arma);
    for(int i=0;i<proyectiles.size();i++){
        proyectiles[i]->draw(window);
    }
}

void Arma::update(sf::Vector2f pos, vector<Enemigo*>e){
    arma.setPosition(pos.x,pos.y-10);
    for(int i=0;i<proyectiles.size();i++){
        bool b=proyectiles[i]->update();
        if(!b){
            borrarProyectil(i);
        }
        else{ 
            for(int j=0;j<e.size();j++){
                if(proyectiles[i]->getProyectil().getGlobalBounds().intersects(e[j]->getSprite().getGlobalBounds())){
                    e[j]->recibirDanyo(proyectiles[i]->getDanyo());
                    borrarProyectil(i);
                }
            }
        }
    }
}

void Arma::update(sf::Vector2f pos, Player* p){
    arma.setPosition(pos.x,pos.y-10);
    for(int i=0;i<proyectiles.size();i++){
        bool b=proyectiles[i]->update();
        if(!b){
            borrarProyectil(i);
        }
        else if(proyectiles[i]->getProyectil().getGlobalBounds().intersects(p->getSprite().getGlobalBounds())){
            p->recibirDanyo(proyectiles[i]->getDanyo());
            borrarProyectil(i);
        }
    }
}

void Arma::disparar(float angulo){
    int t;
    if(tipo==1 || tipo==2){
        t=1;
    }else
        t=2;
    Proyectil *p=new Proyectil(t, danyo, angulo, arma);
    proyectiles.push_back(p);
}

void Arma::borrarProyectil(int i){
    Proyectil *tmp=proyectiles[i];
    proyectiles.erase(proyectiles.begin()+i);
    delete tmp;
}

Arma::Arma(const Arma& orig) {
}

Arma::~Arma() {
}

