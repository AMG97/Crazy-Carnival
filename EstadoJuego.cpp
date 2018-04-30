#include "EstadoJuego.hpp"
namespace Crazy
{
    EstadoJuego::EstadoJuego()
    {
        _juego = Juego::Instance();
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
        _input = new Input();
        teclaPulsada = false;
        
        t_titulo.CambiarFuente(_juego->recursos.GetFuente("Z"));
        t_titulo.CambiarTexto("Jugar");
        t_titulo.CambiarTamanyo(100);
        t_titulo.CambiarOrigen(t_titulo.GetAncho()/2, t_titulo.GetAlto()/2);
        t_titulo.CambiarPosicion((_juego->ancho/2), 150);
        
    }
    
    void EstadoJuego::ManejarEventos()
    {
        teclaPulsada = _input->BucleEventos();
        
        if (teclaPulsada) {
            if (_input->GetTeclas().Escape)
            {
                _input->CerrarVentana();
                _input->DesactivarTecla(_input->GetTeclas().Escape);
                cout << "ESCAPE";
            }
            
            if (_input->GetTeclas().RatonIzq)
            {
                _input->DesactivarTecla(_input->GetTeclas().RatonIzq);
                cout << "Raton izquierda: " << _input->GetPosicionRatonX() << ", "<< _input->GetPosicionRatonY()<< endl;
            }
            
            if (_input->GetTeclas().RatonDer)
            {
                _input->DesactivarTecla(_input->GetTeclas().RatonDer);
                cout << "Raton derecha: " << _input->GetPosicionRatonX() << ", "<< _input->GetPosicionRatonY()<< endl;
            }
            
            teclaPulsada = false;
        }
    }
    
    void EstadoJuego::Actualizar(float tiempoActual)
    {
        
    }
    
    void EstadoJuego::Dibujar(float tiempoActual)
    {
        _juego->_ventana->Limpiar();
        
        _juego->_ventana->Dibujar(t_titulo);
        
        _juego->_ventana->Mostrar();
    }
}