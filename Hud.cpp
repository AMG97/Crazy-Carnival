#include "Hud.hpp"

namespace Crazy
{
    Hud::Hud()
    {
        //Inicializar variables
        _juego = Juego::Instance();
        contrarreloj = true;
        elixir = true;
        ataqueEspecial = true;

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
        spRecipVida.CambiarOrigen(spRecipVida.GetX()/2, spRecipVida.GetY()/2);
        spRecipVida.CambiarPosicion(315/2, 60/2);
        spRecipVida.EscalarProporcion(1.5, 1.5);

        spVida.setTextureRect(sf::IntRect(3*13, 2*20, 136, 4));
        spVida.CambiarOrigen();
        spVida.CambiarPosicion(318/2, 133/2);
        spVida.EscalarProporcion(1.5, 1.5);

        spEnfriamiento.setTextureRect(sf::IntRect(2*19, 2*25, 0*97, 2));
        spEnfriamiento.CambiarOrigen();
        spEnfriamiento.CambiarPosicion(261/2, 163/2);
        spEnfriamiento.EscalarProporcion(1.5, 1.5);

        spElixir.setTextureRect(sf::IntRect(1*13, 4*15.5, 12, 15));
        spElixir.CambiarOrigen();
        spElixir.CambiarPosicion(51/2, 172/2);
        spElixir.EscalarProporcion(1.5, 1.5);

        for(int i = 0; i < 5; i++)
        {
            switch(i){
                case 0:
                    spContador[i].setTextureRect(sf::IntRect(106, 60, 9, 11));
                    spContador[i].CambiarOrigen(10/2, 12/2);
                    spContador[i].CambiarPosicion(591, 20);
                    spContador[i].EscalarProporcion(1.5, 1.5);
                    break;
                case 1:
                    spContador[i].setTextureRect(sf::IntRect(151, 60, 9, 11));
                    spContador[i].CambiarOrigen(10/2, 12/2);
                    spContador[i].CambiarPosicion(600, 20);
                    spContador[i].EscalarProporcion(1.5, 1.5);
                    break;
                case 2:
                    spContador[i].setTextureRect(sf::IntRect(196, 61, 4, 9));
                    spContador[i].CambiarOrigen(4/2, 10/2);
                    spContador[i].CambiarPosicion(607, 20);
                    spContador[i].EscalarProporcion(1.5, 1.5);
                    break;
                case 3:
                    spContador[i].setTextureRect(sf::IntRect(106, 60, 9, 11));
                    spContador[i].CambiarOrigen(10/2, 12/2);
                    spContador[i].CambiarPosicion(614, 20);
                    spContador[i].EscalarProporcion(1.5, 1.5);
                    break;
                case 4:
                    spContador[i].setTextureRect(sf::IntRect(106, 60, 9, 11));
                    spContador[i].CambiarOrigen(10/2, 12/2);
                    spContador[i].CambiarPosicion(623, 20);
                    spContador[i].EscalarProporcion(1.5, 1.5);
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
    
    void Hud::ModificarVida(float modificador){
        float porcentBarra;

        /*float vida = jugador.GetVida();
        
        vida += modificador;
        porcentBarra = vida / totalVida;
        if(vida > totalVida)
        {
            vida = totalVida;
        }

        spVida.setTextureRect(sf::IntRect(3*13, 2*20, porcentBarra * 136, 4));
    */}
    
    void Hud::ModificarEnfriamiento(float modificador){
        float porcentBarra;
        
        /*enfriamiento += modificador;
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
    */}
    
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