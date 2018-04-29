/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   hud.cpp
 * Author: fv
 * 
 * Created on March 24, 2018, 12:03 PM
 */

#include <iostream>
#include <SFML/Graphics.hpp>
#include "player.hpp"
#include "hud.hpp"
#include "juegoHud.hpp"

using namespace std;

    sf::Sprite Hud::spVida;
    sf::Sprite Hud::spEnfriamiento;

Hud::Hud() {
    
    //Inicializar variables
    contrarreloj = false;
    elixir = false;
    ataqueEspecial = false;
    texturaHud = juego->establecerTexturas("/home/fv/NetBeansProjects/Crazy-Carnival/resources/HUD.png");
    spRecipVida.setTexture(texturaHud);
    spVida.setTexture(texturaHud);
    spEnfriamiento.setTexture(texturaHud);
    spElixir.setTexture(texturaHud);
    spriteTimerSeg = 0;
    spriteTimerSeg1 = 0;
    spriteTimerMin = 36;
    
    for(int i = 0; i < 5; i++)
    {
        spContador[i].setTexture(texturaHud);
    }
        
    //Se elige el sprite del sheet
    spRecipVida.setTextureRect(sf::IntRect(0*210, 0*40, 210, 40));
    //Se sitúa el centro del sprite y su ubicación
    spRecipVida.setOrigin(210/2, 40/2);
    spRecipVida.setPosition(210/2, 40/2);
    
    spVida.setTextureRect(sf::IntRect(3*13, 2*20, 136, 4));
    spVida.setOrigin(136/2, 4/2);
    spVida.setPosition(212/2, 22/2);
    
    spEnfriamiento.setTextureRect(sf::IntRect(2*19, 2*25, 0*97, 2));
    spEnfriamiento.setOrigin(98/2, 2/2);
    spEnfriamiento.setPosition(174/2, 42/2);
    
    spElixir.setTextureRect(sf::IntRect(1*13, 4*15.5, 12, 15));
    spElixir.setOrigin(12/2, 16/2);
    spElixir.setPosition(34/2, 48/2);
    
    for(int i = 0; i < 5; i++)
    {
        switch(i){
            case 0:
                spContador[i].setTextureRect(sf::IntRect(106, 60, 9, 11));
                spContador[i].setOrigin(10/2, 12/2);
                spContador[i].setPosition(591, 20);
                break;
            case 1:
                spContador[i].setTextureRect(sf::IntRect(151, 60, 9, 11));
                spContador[i].setOrigin(10/2, 12/2);
                spContador[i].setPosition(600, 20);
                break;
            case 2:
                spContador[i].setTextureRect(sf::IntRect(196, 61, 4, 9));
                spContador[i].setOrigin(4/2, 10/2);
                spContador[i].setPosition(607, 20);
                break;
            case 3:
                spContador[i].setTextureRect(sf::IntRect(106, 60, 9, 11));
                spContador[i].setOrigin(10/2, 12/2);
                spContador[i].setPosition(614, 20);
                break;
            case 4:
                spContador[i].setTextureRect(sf::IntRect(106, 60, 9, 11));
                spContador[i].setOrigin(10/2, 12/2);
                spContador[i].setPosition(623, 20);
                break;
        }
    }
}

Hud::Hud(const Hud& orig) {
}

Hud::~Hud() {
}
void Hud::draw(sf::RenderWindow& window){
    window.draw(spVida);
    window.draw(spEnfriamiento);
    window.draw(spRecipVida);
    if(elixir)
        window.draw(spElixir);
    if(contrarreloj)
    {
        for(int i = 0; i < 5; i++)
        {
            window.draw(spContador[i]);
        }
    }   
}
void Hud::dibujar(sf::RenderWindow &window, bool color)
{
    if(color)
    {
        spRecipVida.setColor(sf::Color(50, 125, 255, 255));
    }
    else
    {
        spRecipVida.setColor(sf::Color(255, 255, 255, 255));
    }
}
void Hud::cambiarTexturaContador(){
    
    if(spriteTimerSeg == 0){
        spriteTimerSeg = 81;
        if(spriteTimerSeg1 == 0){
            spriteTimerSeg1 = 45;
            spContador[1].setTextureRect(sf::IntRect(106 + spriteTimerMin, 60, 9, 11));
            spriteTimerMin -= 9;
        }
        else
        {
            spriteTimerSeg1 -= 9;
        }
        spContador[3].setTextureRect(sf::IntRect(106 + spriteTimerSeg1, 60, 9, 11));
    }
    else
    {
        spriteTimerSeg -= 9;
    }
    spContador[4].setTextureRect(sf::IntRect(106 + spriteTimerSeg, 60, 9, 11));
}
void Hud::modificarVida(float modificador){
    float porcentBarra;
    
    vida += modificador;
    porcentBarra = vida / totalVida;
    if(vida > totalVida)
    {
        vida = totalVida;
    }

    spVida.setTextureRect(sf::IntRect(3*13, 2*20, porcentBarra * 136, 4));
}
void Hud::modificarEnfriamiento(float modificador){
    float porcentBarra;
    enfriamiento += modificador;
    porcentBarra = enfriamiento / totalEnfriamiento;
    if(enfriamiento > totalEnfriamiento)
    {
        enfriamiento = totalEnfriamiento;
    }
    else if(enfriamiento < 0.0)
    {
        enfriamiento = 0.0;
    }
    spEnfriamiento.setTextureRect(sf::IntRect(2*19, 2*25, porcentBarra * 97, 2));
}
void Hud::modoContrarreloj(){
    if(contrarreloj){
        contrarreloj = false;
    }
    else{
        contrarreloj = true;
    }
}
void Hud::elixirEncontrado(){
    if(elixir){
        elixir = false;
    }
    else{
        elixir = true;
    }
}
void Hud::setAtaqueEspecial(bool ataque){
    ataqueEspecial = ataque;
}
sf::Sprite Hud::getSpriteRecipienteVida()
{
    return spRecipVida;
}
bool Hud::getAtaqueEspecial(){
    return ataqueEspecial;
}
