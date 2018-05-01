#include "EstadoAyuda.hpp"

namespace Crazy
{
    EstadoAyuda::EstadoAyuda()
    {
        _juego = Juego::Instance();
    }
    
    EstadoAyuda* EstadoAyuda::_pinstance=0;
    
    EstadoAyuda* EstadoAyuda::Instance()
    {
        if (_pinstance == 0)
        {
            _pinstance = new EstadoAyuda();
        }
        return _pinstance;
    }
    
    EstadoAyuda::~EstadoAyuda()
    {
        delete _input;
        _input = NULL;
        delete _pinstance;
        _pinstance = NULL;
    }
    
    void EstadoAyuda::Init()
    {
        _input = new Input();
        teclaPulsada = false;
        
        t_titulo.CambiarFuente(_juego->recursos.GetFuente("Z"));
        t_titulo.CambiarTexto("Ayuda");
        t_titulo.CambiarTamanyo(100);
        t_titulo.CentrarOrigen();
        t_titulo.CambiarPosicion((_juego->GetAncho()/2), 150);
        
        t_atras.CambiarFuente(_juego->recursos.GetFuente("DK"));
        t_atras.CambiarTexto("Volver");
        t_atras.CambiarTamanyo(50);
        t_atras.CentrarOrigen();
        t_atras.CambiarPosicion(100, (_juego->GetAlto()-100));
        
        flecha.CambiarTextura(_juego->recursos.GetTextura("Flecha"));
        flecha.CambiarOrigen();
        flecha.Rotar(180.0f);
        flecha.CambiarPosicion(60, t_atras.GetY()-30);
        flecha.Escalar(70.0f, 70.0f); // Escalar al 70%
    }
    
    void EstadoAyuda::ManejarEventos()
    {
        teclaPulsada = _input->BucleEventos();
        
        if (teclaPulsada) {
            if (_input->GetTeclas().BackSpace
                || _input->GetTeclas().Escape)
            {
                Atras();
            }
            teclaPulsada = false;
        }
    }
    
    void EstadoAyuda::Actualizar(float tiempoActual)
    {
        
    }
    
    void EstadoAyuda::Dibujar(float tiempoActual)
    {
        _juego->_ventana->Limpiar();
        
        _juego->_ventana->Dibujar(t_titulo);
        _juego->_ventana->Dibujar(t_atras);
        _juego->_ventana->Dibujar(flecha);
        
        _juego->_ventana->Mostrar();
    }
    
    void EstadoAyuda::Atras()
    {
        _juego->maquina.Anyadir(new EstadoMenu());
    }
}