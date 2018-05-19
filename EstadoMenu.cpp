#include "EstadoMenu.hpp"

namespace Crazy
{
    EstadoMenu::EstadoMenu()
    {
        _juego = Juego::Instance();
    }
    
    EstadoMenu* EstadoMenu::_pinstance=0;
    
    EstadoMenu* EstadoMenu::Instance()
    {
        if (_pinstance == 0)
        {
            _pinstance = new EstadoMenu();
        }
        return _pinstance;
    }
    
    void EstadoMenu::Vaciar()
    {
        _pinstance=0;
    }
    
    EstadoMenu::~EstadoMenu()
    {
        delete _input;
        _input = NULL;
        delete _pinstance;
        _pinstance = NULL;
    }
    
    void EstadoMenu::Init()
    {
        _input = new Input();
        opcion = NUEVA;
        teclaPulsada = false;
        tamFuente = 48;
        
        t_titulo.CambiarFuente(_juego->recursos.GetFuente("Z"));
        t_titulo.CambiarTexto("Crazy Carnival");
        t_titulo.CambiarTamanyo(100);
        t_titulo.CentrarOrigen();
        t_titulo.CambiarPosicion((_juego->GetAncho()/2), 100);
        
        t_nueva.CambiarFuente(_juego->recursos.GetFuente("DK"));
        t_nueva.CambiarTexto("Nueva partida");
        t_nueva.CambiarTamanyo(tamFuente);
        t_nueva.CentrarOrigen();
        t_nueva.CambiarPosicion((_juego->GetAncho()/2), t_titulo.GetY()+150);
        
        t_cargar.CambiarFuente(_juego->recursos.GetFuente("DK"));
        t_cargar.CambiarTexto("Cargar partida");
        t_cargar.CambiarTamanyo(tamFuente);
        t_cargar.CentrarOrigen();
        t_cargar.CambiarPosicion((_juego->GetAncho()/2), t_nueva.GetY()+75);
        
        t_borrar.CambiarFuente(_juego->recursos.GetFuente("DK"));
        t_borrar.CambiarTexto("Borrar partida");
        t_borrar.CambiarTamanyo(tamFuente);
        t_borrar.CentrarOrigen();
        t_borrar.CambiarPosicion((_juego->GetAncho()/2), t_cargar.GetY()+75);
        
        t_estadisticas.CambiarFuente(_juego->recursos.GetFuente("DK"));
        t_estadisticas.CambiarTexto("Estadisticas");
        t_estadisticas.CambiarTamanyo(tamFuente);
        t_estadisticas.CentrarOrigen();
        t_estadisticas.CambiarPosicion((_juego->GetAncho()/2), t_borrar.GetY()+75);
        
        t_ayuda.CambiarFuente(_juego->recursos.GetFuente("DK"));
        t_ayuda.CambiarTexto("Ayuda");
        t_ayuda.CambiarTamanyo(tamFuente);
        t_ayuda.CentrarOrigen();
        t_ayuda.CambiarPosicion((_juego->GetAncho()/2), t_estadisticas.GetY()+75);
        
        t_salir.CambiarFuente(_juego->recursos.GetFuente("DK"));
        t_salir.CambiarTexto("Salir");
        t_salir.CambiarTamanyo(tamFuente);
        t_salir.CentrarOrigen();
        t_salir.CambiarPosicion((_juego->GetAncho()/2), t_ayuda.GetY()+75);
        
        flecha.CambiarTextura(_juego->recursos.GetTextura("Flecha"));
        flecha.CambiarOrigen();
        CambiarFlecha(t_nueva);
        flecha.CambiarColorRojo();
        flecha.Escalar(80.0f, 80.0f); // Escalar al 80%
    }
    
    void EstadoMenu::ManejarEventos()
    {
        if (_input->GetTipoEvento() == _input->Evento().KeyPressed)
        {
            if (_input->Enter()) {
                CambiarEstado();
            }
            
            if (_input->Escape()) {
                _juego->_ventana->Cerrar();
            }
            
            if (_input->Arriba()) {
                opcion--;
                if (opcion < NUEVA)
                {
                    opcion = SALIR;
                }
            }
            
            if (_input->Abajo()) {
                opcion++;
                if (opcion > SALIR)
                {
                    opcion = NUEVA;
                }
            }
        }
    }
    
    void EstadoMenu::Actualizar(float tiempoActual)
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
            case AYUDA:
                CambiarFlecha(t_ayuda);
                break;
            case SALIR:
                CambiarFlecha(t_salir);
                break;
        }
    }
    
    void EstadoMenu::Dibujar(float tiempoActual)
    {
        _juego->_ventana->Limpiar();
        
        _juego->_ventana->DibujarTexto(t_titulo);
        _juego->_ventana->DibujarTexto(t_nueva);
        _juego->_ventana->DibujarTexto(t_cargar);
        _juego->_ventana->DibujarTexto(t_borrar);
        _juego->_ventana->DibujarTexto(t_estadisticas);
        _juego->_ventana->DibujarTexto(t_ayuda);
        _juego->_ventana->DibujarTexto(t_salir);
        _juego->_ventana->DibujarSprite(flecha);
        
        _juego->_ventana->Mostrar();
    }
    
    void EstadoMenu::Pausar()
    {
        cout<<"Menu pausado"<<endl;
    }
    
    void EstadoMenu::Reanudar()
    {
        cout<<"Menu reanudado"<<endl;
        _juego->_ventana->setBackground(0,0,0);
    }
    
    void EstadoMenu::CambiarFlecha(Texto texto)
    {
        flecha.CambiarPosicion(texto.GetLeft()-10,texto.GetY()+texto.GetOrigenY()/2);
    }
    
    void EstadoMenu::CambiarEstado()
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
            case AYUDA:
                _juego->maquina.Anyadir(EstadoAyuda::Instance(), false);
                break;
            case SALIR:
                _juego->_ventana->Cerrar();
                break;
        }
    }
    
    void EstadoMenu::NuevaPartida()
    {
        _juego->maquina.Anyadir(EstadoJuego::Instance(), false);
    }
    
    void EstadoMenu::CargarPartida()
    {
        cout<<"Cargar"<<endl;
    }
    
    void EstadoMenu::BorrarPartida()
    {
        cout<<"Borrar"<<endl;
    }
    
    void EstadoMenu::Estadisticas()
    {
        _juego->maquina.Anyadir(EstadoEstadisticas::Instance(), false);
    }
}