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

#ifndef HUD_HPP
#define HUD_HPP

namespace Crazy{
    class JuegoHud;
    class Player;
    class Hud : public Player {

    private:
        JuegoHud *juego;
        sf::Texture texturaHud;
        sf::Sprite spRecipVida;
        sf::Sprite static spVida;
        sf::Sprite static spEnfriamiento;
        sf::Sprite spElixir;
        sf::Sprite spContador [5];
        bool contrarreloj;
        bool elixir;
        bool ataqueEspecial;
        int spriteTimerSeg;
        int spriteTimerSeg1;
        int spriteTimerMin;

    public:
        Hud();
        Hud(const Hud& orig);
        virtual ~Hud();
        void draw(sf::RenderWindow &window);
        void dibujar(sf::RenderWindow &window, bool color);
        void cambiarTexturaContador();
        static void modificarVida(float modificador);
        static void modificarEnfriamiento(float modificador);
        void modoContrarreloj();
        void elixirEncontrado();
        void setAtaqueEspecial(bool ataque);
        sf::Sprite getSpriteRecipienteVida();
        bool getAtaqueEspecial();
    };
}
#endif /* HUD_HPP */

