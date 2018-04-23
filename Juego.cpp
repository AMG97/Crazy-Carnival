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
        
        
        maquina.Anyadir(new EstadoMenu(), true);
        
        while (_ventana->EstaAbierta())
        {
            //tiempoActual = motor->RestartMiliseconds();
            
            maquina.ProcesarPilaEstados();
            maquina.GetEstadoActivo()->ManejarEventos();
            
            // Actualiza 15 veces por segunto
            if (tiempoActual >= (1/15)) {
                maquina.GetEstadoActivo()->Actualizar(tiempoActual);
                //tiempoActual = motor->RestartMiliseconds();
            }
            
            // Actualiza siempre
            maquina.GetEstadoActivo()->Dibujar(tiempoActual);
        }
    }
}