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
class Hud {

private:
    JuegoHud *juego;
    sf::Texture texturaHud;
    sf::Sprite spRecipVida;
    sf::Sprite spVida;
    
public:
    Hud();
    Hud(const Hud& orig);
    virtual ~Hud();
};

#endif /* HUD_H */

