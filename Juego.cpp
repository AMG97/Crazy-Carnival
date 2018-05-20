#include "Juego.hpp"
#include "EstadoMenu.hpp"

namespace Crazy
{
    Juego* Juego::_pinstance=0;
    
    Juego* Juego::Instance()
    {
        if (_pinstance == 0)
        {
            _pinstance = new Juego();
        }
        return _pinstance;
    }
    
    Juego::~Juego()
    {
        delete _pinstance;
        _pinstance = NULL;
    }
    
    void Juego::Iniciar()
    {
        ancho = 1024;
        alto = 720;
        titulo = "Crazy Carnival";
        _ventana = Ventana::Instance();
        _ventana->CrearVentana(ancho, alto, titulo);
        
        // Cargar fuentes
        recursos.CargarFuente("DK","resources/font/dk-face-your-fears.ttf");
        recursos.CargarFuente("Z","resources/font/zombified.ttf");
        
        recursos.CargarTextura("Flecha","resources/flecha.png");
        recursos.CargarTextura("Flechas","resources/flechas.png");
        recursos.CargarTextura("Hud","resources/HUD.png");
        recursos.CargarTextura("Objetos","resources/SpritesObjetos.png");
        recursos.CargarTextura("Playa","resources/SpritesPlaya.png");
        recursos.CargarTextura("Espadachina","resources/espadachina.png");
        recursos.CargarTextura("Espada1","resources/espada1.png");
        recursos.CargarTextura("Espada2","resources/espada2.png");
        recursos.CargarTextura("Enemigo-Pistola1","resources/enemigo-pistola.png");
        recursos.CargarTextura("Puñal","resources/puñal.png");
        recursos.CargarTextura("Bala","resources/bala.png");
        recursos.CargarTextura("Enemigo-Volador","resources/enemigo-pajaro.png");
        recursos.CargarTextura("Cangrejo","resources/CrabSprite.png");
        //recursos.CargarTextura("TipoDuro","resources/tipoDuro.png");
        
        // Temporal
        recursos.CargarTextura("Ayuda","resources/ayuda.png");
        
        maquina.Anyadir(EstadoMenu::Instance());
        //maquina.Anyadir(EstadoJuego::Instance());
        
        while (_ventana->EstaAbierta())
        {
            tiempoActual = reloj.ReiniciarMilisegundos();
            
            maquina.ProcesarPilaEstados();
            maquina.GetEstadoActivo()->ManejarEventos();
            
            // Actualiza 15 veces por segundo
            if (tiempoActual >= (1/15)) {
                maquina.GetEstadoActivo()->Actualizar(tiempoActual);
                tiempoActual = reloj.ReiniciarMilisegundos();
            }
            
            // Actualiza siempre
            maquina.GetEstadoActivo()->Dibujar(tiempoActual);
        }
    }
    
    int Juego::GetAlto()
    {
        return alto;
    }
    
    int Juego::GetAncho()
    {
        return ancho;
    }
    
    string Juego::GetTitulo()
    {
        return titulo;
    }
    
    short int Juego::GetSlot()
    {
        return slot;
    }
    
    void Juego::SetSlot(short int s)
    {
        slot = s;
    }
}