#include "EstadoJuego.hpp"

namespace Crazy
{
    EstadoJuego::EstadoJuego()
    {
        _juego = Juego::Instance();
        _input = new Input();
    }
    
    EstadoJuego* EstadoJuego::_pinstance=0;
    
    EstadoJuego* EstadoJuego::Instance()
    {
        if (_pinstance == 0)
        {
            _pinstance = new EstadoJuego();
        }
        return _pinstance;
    }
    
    EstadoJuego::~EstadoJuego()
    {
        delete _input;
        _input = NULL;
        delete _pinstance;
        _pinstance = NULL;
    }
    
    void EstadoJuego::Init()
    {
        t_titulo.CambiarFuente(_juego->recursos.GetFuente("Z"));
        t_titulo.CambiarTexto("Jugar");
        t_titulo.CambiarTamanyo(100);
        t_titulo.CambiarOrigen(t_titulo.GetAncho()/2, t_titulo.GetAlto()/2);
        t_titulo.CambiarPosicion((_juego->ancho/2), 150);
        
    }
    
    void EstadoJuego::ManejarEventos()
    {
        _input->BucleEventos();
    }
    
    void EstadoJuego::Actualizar(float tiempoActual)
    {
        
    }
    
    void EstadoJuego::Dibujar(float tiempoActual)
    {
        _juego->_ventana->Limpiar();
        
        _juego->_ventana->draw(t_titulo);
        
        _juego->_ventana->Mostrar();
    }
    
}