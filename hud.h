/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   hud.h
 * Author: fv
 *
 * Created on March 24, 2018, 12:03 PM
 */

#ifndef HUD_H
#define HUD_H

class JuegoHud;
class Player;
class Hud : public Player {

private:
    JuegoHud *juego;
    sf::Texture texturaHud;
    sf::Sprite spRecipVida;
    sf::Sprite spVida;
    sf::Sprite spEnfriamiento;
    sf::Sprite spElixir;
    sf::Sprite spContador [5];
    bool contrarreloj;
    bool elixir;
    int spriteTimerSeg;
    int spriteTimerSeg1;
    int spriteTimerMin;
    
public:
    Hud();
    Hud(const Hud& orig);
    virtual ~Hud();
    void draw(sf::RenderWindow &window);
    void cambiarTexturaContador();
    void modificarVida(float modificador);
    void modificarEnfriamiento(float modificador);
    void modoContrarreloj();
    void elixirEncontrado();
};

#endif /* HUD_H */

