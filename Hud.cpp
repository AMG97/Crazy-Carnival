#include "Hud.hpp"

namespace Crazy
{
    Hud::Hud()
    {
        //Inicializar variables
        _juego = Juego::Instance();
        _camara = Camara::Instance();
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
        spRecipVida.CambiarOrigen(spRecipVida.GetAncho()/2, spRecipVida.GetAlto()/2);
        spRecipVida.CambiarPosicion(315/2, 60/2);
        spRecipVida.EscalarProporcion(1.5, 1.5);

        spVida.setTextureRect(sf::IntRect(3*13, 2*20, 136, 4));
        spVida.CambiarOrigen(spVida.GetAncho()/2, spVida.GetAlto()/2);
        spVida.CambiarPosicion(318/2, 33/2);
        spVida.EscalarProporcion(1.5, 1.5);

        spEnfriamiento.setTextureRect(sf::IntRect(2*19, 2*25, 1*97, 2));
        spEnfriamiento.CambiarOrigen(spEnfriamiento.GetAncho()/2, spEnfriamiento.GetAlto()/2);
        spEnfriamiento.CambiarPosicion(261/2, 63/2);
        spEnfriamiento.EscalarProporcion(1.5, 1.5);
        EnfriamientoVacio();
        
        spElixir.setTextureRect(sf::IntRect(1*13, 4*15.5, 12, 15));
        spElixir.CambiarOrigen(spElixir.GetAncho()/2, spElixir.GetAlto()/2);
        spElixir.CambiarPosicion(51/2, 70/2);
        spElixir.EscalarProporcion(1.5, 1.5);

        for(int i = 0; i < 5; i++)
        {
            switch(i){
                case 0:
                    spContador[i].setTextureRect(sf::IntRect(106, 60, 9, 11));
                    spContador[i].CambiarOrigen(10/2, 12/2);
                    spContador[i].CambiarPosicion(884, 20);
                    spContador[i].EscalarProporcion(1.5, 1.5);
                    break;
                case 1:
                    spContador[i].setTextureRect(sf::IntRect(154, 60, 9, 11));
                    spContador[i].CambiarOrigen(10/2, 12/2);
                    spContador[i].CambiarPosicion(900, 20);
                    spContador[i].EscalarProporcion(1.5, 1.5);
                    break;
                case 2:
                    spContador[i].setTextureRect(sf::IntRect(198, 61, 4, 9));
                    spContador[i].CambiarOrigen(4/2, 10/2);
                    spContador[i].CambiarPosicion(910, 20);
                    spContador[i].EscalarProporcion(1.5, 1.5);
                    break;
                case 3:
                    spContador[i].setTextureRect(sf::IntRect(106, 60, 9, 11));
                    spContador[i].CambiarOrigen(10/2, 12/2);
                    spContador[i].CambiarPosicion(921, 20);
                    spContador[i].EscalarProporcion(1.5, 1.5);
                    break;
                case 4:
                    spContador[i].setTextureRect(sf::IntRect(106, 60, 9, 11));
                    spContador[i].CambiarOrigen(10/2, 12/2);
                    spContador[i].CambiarPosicion(934, 20);
                    spContador[i].EscalarProporcion(1.5, 1.5);
                    break;
            }
        }
    }
    
    void Hud::Dibujar()
    {
        _juego->_ventana->DibujarB(spVida, *_camara);
        _juego->_ventana->DibujarB(spEnfriamiento, *_camara);
        _juego->_ventana->DibujarB(spRecipVida, *_camara);
        
        if(elixir)
            _juego->_ventana->DibujarB(spElixir, *_camara);
        if(contrarreloj)
        {
            for(int i = 0; i < 5; i++)
            {
                _juego->_ventana->DibujarB(spContador[i], *_camara);
            }
        }
    }
    
    void Hud::Parpadear(bool parpadeo)
    {
        SetAtaqueEspecial(!parpadeo);
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
    
    void Hud::ModificarVida(float vida, float totalVida){
        float porcentaje = vida/totalVida;
        spVida.setTextureRect(sf::IntRect(3*13, 2*20, porcentaje * 136, 4));
    }
    
    void Hud::ModificarEnfriamiento(float enfriamiento, float totalEnfriamiento)
    {
        float porcentaje = enfriamiento/totalEnfriamiento;
        spEnfriamiento.setTextureRect(sf::IntRect(2*19, 2*25, porcentaje * 97, 2));
    }
    
    void Hud::EnfriamientoVacio()
    {
        spEnfriamiento.setTextureRect(sf::IntRect(2*19, 2*25, 0, 2));
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
    
    bool Hud::GetAtaqueEspecial(){
        return ataqueEspecial;
    }
}