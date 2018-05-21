#include "Hud.hpp"
#include "EstadoJuego.hpp"

namespace Crazy
{
    Hud::Hud(bool mContrarreloj)
    {
        //Inicializar variables
        _juego = Juego::Instance();
        _camara = Camara::Instance();
        _jugador = EstadoJuego::Instance()->_jugador;
        contrarreloj = mContrarreloj;
        elixir = false;
        ataqueEspecial = false;
        parpadea=false;
        
        spRecipVida.CambiarTextura(_juego->recursos.GetTextura("Hud"));
        spVida.CambiarTextura(_juego->recursos.GetTextura("Hud"));
        spEnfriamiento.CambiarTextura(_juego->recursos.GetTextura("Hud"));
        spElixir.CambiarTextura(_juego->recursos.GetTextura("Hud"));

        spriteTimerSeg = 0;
        spriteTimerSeg1 = 0;
        spriteTimerMin = 18;

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
        spVida.EscalarProporcion(1.5, 2);

        spEnfriamiento.setTextureRect(sf::IntRect(2*19, 2*25, 1*97, 2));
        spEnfriamiento.CambiarOrigen(spEnfriamiento.GetAncho()/2, spEnfriamiento.GetAlto()/2);
        spEnfriamiento.CambiarPosicion(261/2, 63/2);
        spEnfriamiento.EscalarProporcion(1.5, 2);
        EnfriamientoVacio();
        
        spElixir.setTextureRect(sf::IntRect(1*13, 4*15.5, 12, 15));
        spElixir.CambiarOrigen(spElixir.GetAncho()/2, spElixir.GetAlto()/2);
        spElixir.CambiarPosicion(51/2, 70/2);
        spElixir.EscalarProporcion(1.5, 1.5);
        
        puntuacion = Texto();
        puntuacion.CambiarFuente(_juego->recursos.GetFuente("DK"));
        puntuacion.CambiarTamanyo(40);
        puntuacion.CambiarPosicion(_camara->getWidth()-150,2);

        
        //Contador Tiempo
        int contX = 500, contY = 20;
        for(int i = 0; i < 5; i++)
        {
            switch(i){
                case 0:
                    spContador[i].setTextureRect(sf::IntRect(107, 60, 9, 11));
                    spContador[i].CambiarOrigen(10/2, 12/2);
                    spContador[i].CambiarPosicion(contX-16, contY);
                    spContador[i].EscalarProporcion(1.5, 1.5);
                    break;
                case 1:
                    spContador[i].setTextureRect(sf::IntRect(134, 60, 9, 11));
                    spContador[i].CambiarOrigen(10/2, 12/2);
                    spContador[i].CambiarPosicion(contX, contY);
                    spContador[i].EscalarProporcion(1.5, 1.5);
                    break;
                case 2:
                    spContador[i].setTextureRect(sf::IntRect(197, 61, 4, 9));
                    spContador[i].CambiarOrigen(4/2, 10/2);
                    spContador[i].CambiarPosicion(contX+10, contY);
                    spContador[i].EscalarProporcion(1.5, 1.5);
                    break;
                case 3:
                    spContador[i].setTextureRect(sf::IntRect(107, 60, 9, 11));
                    spContador[i].CambiarOrigen(10/2, 12/2);
                    spContador[i].CambiarPosicion(contX+21, contY);
                    spContador[i].EscalarProporcion(1.5, 1.5);
                    break;
                case 4:
                    spContador[i].setTextureRect(sf::IntRect(106, 60, 9, 11));
                    spContador[i].CambiarOrigen(10/2, 12/2);
                    spContador[i].CambiarPosicion(contX+34, contY);
                    spContador[i].EscalarProporcion(1.5, 1.5);
                    break;
            }
        }
        contador = 0;
    }
    
    void Hud::Dibujar()
    {
        if(!ataqueEspecial)
            spRecipVida.Parpadear(false);
        _juego->_ventana->DibujarSprite(spVida, _camara);
        _juego->_ventana->DibujarSprite(spEnfriamiento, _camara);
        _juego->_ventana->DibujarSprite(spRecipVida, _camara);
        
        if(elixir)
            _juego->_ventana->DibujarSprite(spElixir, _camara);
        if(contrarreloj)
        {
            for(int i = 0; i < 5; i++)
            {
                _juego->_ventana->DibujarSprite(spContador[i], _camara);
            }
        }
        
        puntuacion.CambiarTexto(to_string(_jugador->getPuntuacion()));
        _juego->_ventana->DibujarTexto(puntuacion, _camara);
    }
    
    void Hud::Parpadear(bool parpadeo)
    {
        parpadea=!parpadea;
        spRecipVida.Parpadear(parpadea);
    }
    
    void Hud::CambiarTexturaContador(){
    
        if(spriteTimerSeg == 0){
            spriteTimerSeg = 81;
            if(spriteTimerSeg1 == 0){
                spriteTimerSeg1 = 45;
                spContador[1].setTextureRect(sf::IntRect(107 + spriteTimerMin, 60, 9, 11));
                spriteTimerMin -= 9;
            }
            else
            {
                spriteTimerSeg1 -= 9;
            }
            spContador[3].setTextureRect(sf::IntRect(107 + spriteTimerSeg1, 60, 9, 11));
        }
        else
        {
            spriteTimerSeg -= 9;
        }
        spContador[4].setTextureRect(sf::IntRect(107 + spriteTimerSeg, 60, 9, 11));
        contador++;
    }
    
    void Hud::CambiarTexturaContadorAumentar(int tiempo)
    {
        spriteTimerSeg1 += (tiempo/10)*9;
        if(spriteTimerSeg1 > 45)
        {
            spriteTimerSeg1 = 0;
            spriteTimerMin += 9;
            spContador[1].setTextureRect(sf::IntRect(107 + spriteTimerMin+9, 60, 9, 11));
        }
        spContador[3].setTextureRect(sf::IntRect(107 + spriteTimerSeg1, 60, 9, 11));
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
        contrarreloj = !contrarreloj;
    }
    
    void Hud::ElixirEncontrado(bool v){
        elixir = v;
        _jugador->SetElixir(elixir);
    }
    bool Hud::getElixir(){
        return elixir;
    }
    
    void Hud::SetAtaqueEspecial(bool ataque){
        ataqueEspecial = ataque;
    }
    
    bool Hud::GetAtaqueEspecial(){
        return ataqueEspecial;
    }
    int Hud::getContador(){
        return contador;
    }
    void Hud::aumentarTiempo(int tiempo)
    {
        contador -= tiempo;
        CambiarTexturaContadorAumentar(tiempo);
    }
}