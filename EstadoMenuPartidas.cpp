#include "EstadoMenuPartidas.hpp"
namespace Crazy
{
    EstadoMenuPartidas::EstadoMenuPartidas()
    {
        _juego = Juego::Instance();
    }
    
    EstadoMenuPartidas* EstadoMenuPartidas::_pinstance=0;
    
    EstadoMenuPartidas* EstadoMenuPartidas::Instance()
    {
        if (_pinstance == 0)
        {
            _pinstance = new EstadoMenuPartidas();
        }
        return _pinstance;
    }
    
    EstadoMenuPartidas::~EstadoMenuPartidas()
    {
        delete _input;
        _input = NULL;
        delete _pinstance;
        _pinstance = NULL;
    }
    
    void EstadoMenuPartidas::Init()
    {
        _input = new Input();
        opcion = NUEVA;
        teclaPulsada = false;
        
        t_titulo.CambiarFuente(_juego->recursos.GetFuente("Z"));
        t_titulo.CambiarTexto("Crazy Carnival");
        t_titulo.CambiarTamanyo(100);
        t_titulo.CentrarOrigen();
        t_titulo.CambiarPosicion((_juego->ancho/2), 150);
        
        t_nueva.CambiarFuente(_juego->recursos.GetFuente("DK"));
        t_nueva.CambiarTexto("Nueva partida");
        t_nueva.CambiarTamanyo(50);
        t_nueva.CentrarOrigen();
        t_nueva.CambiarPosicion((_juego->ancho/2), t_titulo.GetY()+200);
        
        t_cargar.CambiarFuente(_juego->recursos.GetFuente("DK"));
        t_cargar.CambiarTexto("Cargar partida");
        t_cargar.CambiarTamanyo(50);
        t_cargar.CentrarOrigen();
        t_cargar.CambiarPosicion((_juego->ancho/2), t_nueva.GetY()+75);
        
        t_borrar.CambiarFuente(_juego->recursos.GetFuente("DK"));
        t_borrar.CambiarTexto("Borrar partida");
        t_borrar.CambiarTamanyo(50);
        t_borrar.CentrarOrigen();
        t_borrar.CambiarPosicion((_juego->ancho/2), t_cargar.GetY()+75);
        
        t_estadisticas.CambiarFuente(_juego->recursos.GetFuente("DK"));
        t_estadisticas.CambiarTexto("Estadisticas");
        t_estadisticas.CambiarTamanyo(50);
        t_estadisticas.CentrarOrigen();
        t_estadisticas.CambiarPosicion((_juego->ancho/2), t_borrar.GetY()+75);
        
        
        flecha.CambiarTextura(_juego->recursos.GetTextura("Flecha"));
        flecha.CambiarOrigen();
        CambiarFlecha(t_nueva);
        flecha.CambiarColorRojo();
        flecha.Escalar(80.0f, 80.0f); // Escalar al 80%
        
        t_atras.CambiarFuente(_juego->recursos.GetFuente("DK"));
        t_atras.CambiarTexto("Volver");
        t_atras.CambiarTamanyo(50);
        t_atras.CentrarOrigen();
        t_atras.CambiarPosicion(100, (_juego->alto-100));
        
        flechaAtras.CambiarTextura(_juego->recursos.GetTextura("Flecha"));
        flechaAtras.CambiarOrigen();
        flechaAtras.Rotar(180.0f);
        flechaAtras.CambiarPosicion(60, t_atras.GetY()-30);
        flechaAtras.Escalar(70.0f, 70.0f); // Escalar al 70%
    }
    
    void EstadoMenuPartidas::ManejarEventos()
    {
        teclaPulsada = _input->BucleEventos();
        
        if (teclaPulsada) {
            if (_input->GetPressed().Arriba) {
                opcion--;
                if (opcion < NUEVA)
                {
                    opcion = ESTADISTICAS;
                }
            }

            if (_input->GetPressed().Abajo) {
                opcion++;
                if (opcion > ESTADISTICAS)
                {
                    opcion = NUEVA;
                }
            }
            
            if (_input->GetPressed().Enter) {
                CambiarEstado();
            }
            
            if (_input->GetPressed().BackSpace
                || _input->GetPressed().Escape)
            {
                Atras();
            }
            
            teclaPulsada = false;
        }
    }
    
    void EstadoMenuPartidas::Actualizar(float tiempoActual)
    {
        switch (opcion)
        {
            case NUEVA:
                CambiarFlecha(t_nueva);
                break;
            case CARGAR:
                CambiarFlecha(t_cargar);
                break;
            case BORRAR:
                CambiarFlecha(t_borrar);
                break;
            case ESTADISTICAS:
                CambiarFlecha(t_estadisticas);
                break;
        }
    }
    
    void EstadoMenuPartidas::Dibujar(float tiempoActual)
    {
        _juego->_ventana->Limpiar();
        
        _juego->_ventana->draw(t_titulo);
        _juego->_ventana->draw(t_nueva);
        _juego->_ventana->draw(t_cargar);
        _juego->_ventana->draw(t_borrar);
        _juego->_ventana->draw(t_estadisticas);
        _juego->_ventana->draw(flecha);
        _juego->_ventana->draw(t_atras);
        _juego->_ventana->draw(flechaAtras);
        
        _juego->_ventana->Mostrar();
    }
    
    void EstadoMenuPartidas::CambiarFlecha(Texto texto)
    {
        flecha.CambiarPosicion(texto.GetLeft()-10,texto.GetY()+texto.GetOrigenY()/2);
    }
    
    void EstadoMenuPartidas::CambiarEstado()
    {
        switch (opcion)
        {
            case NUEVA:
                NuevaPartida();
                break;
            case CARGAR:
                CargarPartida();
                break;
            case BORRAR:
                BorrarPartida();
                break;
            case ESTADISTICAS:
                Estadisticas();
                break;
        }
    }
    
    void EstadoMenuPartidas::NuevaPartida()
    {
        _juego->maquina.Anyadir(new EstadoJuego());
    }
    
    void EstadoMenuPartidas::CargarPartida()
    {
        cout<<"Cargar"<<endl;
    }
    
    void EstadoMenuPartidas::BorrarPartida()
    {
        cout<<"Borrar"<<endl;
    }
    
    void EstadoMenuPartidas::Estadisticas()
    {
        _juego->maquina.Anyadir(new EstadoEstadisticas());
    }
    
    void EstadoMenuPartidas::Atras()
    {
        _juego->maquina.Anyadir(new EstadoMenu());
    }
}