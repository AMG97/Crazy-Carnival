#include "EstadoEstadisticas.hpp"
namespace Crazy
{
    EstadoEstadisticas::EstadoEstadisticas()
    {
        _juego = Juego::Instance();
    }
    
    EstadoEstadisticas* EstadoEstadisticas::_pinstance=0;
    
    EstadoEstadisticas* EstadoEstadisticas::Instance()
    {
        if (_pinstance == 0)
        {
            _pinstance = new EstadoEstadisticas();
        }
        return _pinstance;
    }
    
    void EstadoEstadisticas::Vaciar()
    {
        _pinstance=0;
    }
    
    EstadoEstadisticas::~EstadoEstadisticas()
    {
        delete _input;
        _input = NULL;
        delete _pinstance;
        _pinstance = NULL;
    }
    
    void EstadoEstadisticas::Init()
    {
        _input = new Input();
        teclaPulsada = false;
        
        t_titulo.CambiarFuente(_juego->recursos.GetFuente("Z"));
        t_titulo.CambiarTexto("Estadisticas");
        t_titulo.CambiarTamanyo(100);
        t_titulo.CentrarOrigen();
        t_titulo.CambiarPosicion((_juego->GetAncho()/2), 150);
        
        t_texto.CambiarFuente(_juego->recursos.GetFuente("DK"));
        t_texto.CambiarTexto("Proximamente");
        t_texto.CambiarTamanyo(80);
        t_texto.CentrarOrigen();
        t_texto.CambiarPosicion((_juego->GetAncho()/2-20), t_titulo.GetY()+200);
        t_texto.CambiarColorRojo();
        t_texto.rotate(-20);
        
        t_atras.CambiarFuente(_juego->recursos.GetFuente("DK"));
        t_atras.CambiarTexto("Volver");
        t_atras.CambiarTamanyo(50);
        t_atras.CentrarOrigen();
        t_atras.CambiarPosicion(100, (_juego->GetAlto()-100));
        
        flecha.CambiarTextura(_juego->recursos.GetTextura("Flecha"));
        flecha.CambiarOrigen();
        flecha.CambiarColorRojo();
        flecha.Rotar(180.0f);
        flecha.CambiarPosicion(60, t_atras.GetY()-30);
        flecha.Escalar(70.0f, 70.0f); // Escalar al 70%
    }
    
    void EstadoEstadisticas::ManejarEventos()
    {
        if (_input->GetTipoEvento() == _input->Evento().KeyPressed)
        {
            if (_input->BackSpace()
                || _input->Escape())
            {
                Atras();
            }
        } else {
            // Color rojo/blanco del texto
            _input->RatonSobre(t_atras);
            
            // Clic sobre texto
            if (_input->RatonIzq()) {
                if(_input->IsTextoClicked(t_atras))
                {
                    Atras();
                }
            }
        }
    }
    
    void EstadoEstadisticas::Actualizar(float tiempoActual)
    {
        
    }
    
    void EstadoEstadisticas::Dibujar(float tiempoActual)
    {
        _juego->_ventana->Limpiar();
        
        _juego->_ventana->DibujarTexto(t_titulo);
        _juego->_ventana->DibujarTexto(t_texto);
        _juego->_ventana->DibujarTexto(t_atras);
        _juego->_ventana->DibujarSprite(flecha);
        
        _juego->_ventana->Mostrar();
    }
    
    void EstadoEstadisticas::CargarEstadisticas()
    {
        
    }
    
    void EstadoEstadisticas::Atras()
    {
        _juego->maquina.SaltarAlMenu();
    }
}
