#include "EstadoMuerte.hpp"
#include "EstadoMenu.hpp"

namespace Crazy
{
    EstadoMuerte::EstadoMuerte()
    {
        _juego = Juego::Instance();
    }
    
    EstadoMuerte* EstadoMuerte::_pinstance=0;
    
    EstadoMuerte* EstadoMuerte::Instance()
    {
        if (_pinstance == 0)
        {
            _pinstance = new EstadoMuerte();
        }
        return _pinstance;
    }
    
    void EstadoMuerte::Vaciar()
    {
        _pinstance=0;
    }
        
    EstadoMuerte::~EstadoMuerte()
    {
        delete _input;
        _input = NULL;
        delete _pinstance;
        _pinstance = NULL;
    }
    
    void EstadoMuerte::Init()
    {
        Camara* _camara=Camara::Instance();
        _input = new Input();
        dibujado= false;
        t_titulo.CambiarFuente(_juego->recursos.GetFuente("Z"));
        t_titulo.CambiarTexto("Has Muerto");
        t_titulo.CambiarTamanyo(100);
        t_titulo.CentrarOrigen();
        t_titulo.CambiarPosicion(_camara->getX(), _camara->getY()-100);
        
        t_atras.CambiarFuente(_juego->recursos.GetFuente("DK"));
        t_atras.CambiarTexto("Pulsa escape para volver al menu inicial");
        t_atras.CambiarTamanyo(50);
        t_atras.CentrarOrigen();
        t_atras.CambiarPosicion(_camara->getX(), _camara->getY()+100);
        
    }
    
    void EstadoMuerte::ManejarEventos()
    {
        if (_input->GetTipoEvento() == _input->Evento().KeyPressed)
        {
            if(_input->Escape()){
                _juego->_ventana->SetCamaraPorDefecto();
                _juego->maquina.SaltarAlMenu();
            }
        }
    }
    
    void EstadoMuerte::Actualizar(float tiempoActual)
    {
        
    }
    
    void EstadoMuerte::Dibujar(float tiempoActual)
    {
        if(!dibujado){
            dibujado=true;
            _juego->_ventana->setBackground2(0,0,0,100);
            _juego->_ventana->Dibujar(t_titulo);
            _juego->_ventana->Dibujar(t_atras);

            _juego->_ventana->Mostrar();
        }
    }
}