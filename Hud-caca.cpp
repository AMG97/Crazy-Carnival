#include "Hud-caca.hpp"

namespace Crazy
{
    Hud::Hud()
    {
        //Inicializar variables
        _juego = Juego::Instance();
        contrarreloj = false;
        elixir = false;
        ataqueEspecial = false;

        spRecipVida.CambiarTextura(_juego->recursos.GetTextura("Hud"));
        spVida.CambiarTextura(_juego->recursos.GetTextura("Hud"));
        spEnfriamiento.CambiarTextura(_juego->recursos.GetTextura("Hud"));
        spElixir.CambiarTextura(_juego->recursos.GetTextura("Hud"));

        spriteTimerSeg = 0;
        spriteTimerSeg1 = 0;
        spriteTimerMin = 36;

        for(int i = 0; i < 5; i++)
        {
            spContador[i].CambiarTextura(_juego->recursos.GetTextura("Hud"));
        }

        //Se elige el sprite del sheet
        spRecipVida.setTextureRect(sf::IntRect(0*210, 0*40, 210, 40));
        //Se sitúa el centro del sprite y su ubicación
        spRecipVida.setOrigin(210/2, 40/2);
        spRecipVida.setPosition(315/2, 60/2);
        spRecipVida.setScale(1.5, 1.5);

        spVida.setTextureRect(sf::IntRect(3*13, 2*20, 136, 4));
        spVida.setOrigin(136/2, 4/2);
        spVida.setPosition(318/2, 33/2);
        spVida.setScale(1.5, 1.5);

        spEnfriamiento.setTextureRect(sf::IntRect(2*19, 2*25, 0*97, 2));
        spEnfriamiento.setOrigin(98/2, 2/2);
        spEnfriamiento.setPosition(261/2, 63/2);
        spEnfriamiento.setScale(1.5, 1.5);

        spElixir.setTextureRect(sf::IntRect(1*13, 4*15.5, 12, 15));
        spElixir.setOrigin(12/2, 16/2);
        spElixir.setPosition(51/2, 72/2);
        spElixir.setScale(1.5, 1.5);

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
    
    void Hud::Dibujar()
    {
        _juego->_ventana->Dibujar(spVida);
        _juego->_ventana->Dibujar(spEnfriamiento);
        _juego->_ventana->Dibujar(spRecipVida);
        
        if(elixir)
            _juego->_ventana->Dibujar(spElixir);
        if(contrarreloj)
        {
            for(int i = 0; i < 5; i++)
            {
                _juego->_ventana->Dibujar(spContador[i]);
            }
        }
    }
    
    void Hud::Parpadear(bool parpadeo)
    {
        spRecipVida.Parpadear(parpadeo);
    }
    
    void Hud::CambiarTexturaContador(){
    
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
    
    void Hud::ModificarVida(float vida, float totalVida)
    {
        spVida.setTextureRect(sf::IntRect(3*13, 2*20, (vida/totalVida) * 136, 4));
    }
    
    void Hud::ModificarEnfriamiento(float enfriamiento, float totalEnfriamiento)
    {
        spEnfriamiento.setTextureRect(sf::IntRect(2*19, 2*25, (enfriamiento/totalEnfriamiento) * 97, 2));
    }
    
    void Hud::ModoContrarreloj(){
        if(contrarreloj){
            contrarreloj = false;
        }
        else{
            contrarreloj = true;
        }
    }
    
    void Hud::ElixirEncontrado(){
        if(elixir){
            elixir = false;
        }
        else{
            elixir = true;
        }
    }
    
    void Hud::SetAtaqueEspecial(bool ataque){
        ataqueEspecial = ataque;
    }
    
    SpriteM Hud::GetSpriteRecipienteVida()
    {
        return spRecipVida;
    }
    bool Hud::GetAtaqueEspecial(){
        return ataqueEspecial;
    }
}