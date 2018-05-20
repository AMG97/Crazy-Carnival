#include "EstadoPartidas.hpp"

namespace Crazy
{
    EstadoPartidas::EstadoPartidas()
    {
        _juego = Juego::Instance();
    }
    
    EstadoPartidas* EstadoPartidas::_pinstance=0;
    
    EstadoPartidas* EstadoPartidas::Instance()
    {
        if (_pinstance == 0)
        {
            _pinstance = new EstadoPartidas();
        }
        return _pinstance;
    }
    
    void EstadoPartidas::Vaciar()
    {
        _pinstance=0;
    }
        
    EstadoPartidas::~EstadoPartidas()
    {
        delete _input;
        _input = NULL;
        delete _pinstance;
        _pinstance = NULL;
    }
    
    void EstadoPartidas::Init()
    {
        ComprobarPartidas();
        _input = new Input();
        tamFuente = 48;
        slotGuardar = SLOT1;
        
        t_titulo.CambiarFuente(_juego->recursos.GetFuente("Z"));
        t_titulo.CambiarTexto("Partidas");
        t_titulo.CambiarTamanyo(100);
        t_titulo.CentrarOrigen();
        t_titulo.CambiarPosicion((_juego->GetAncho()/2), 100);
        
        t_slot1.CambiarFuente(_juego->recursos.GetFuente("DK"));
        t_slot1.CambiarTamanyo(tamFuente);
        t_slot1.CentrarOrigen();
        t_slot1.CambiarPosicion((_juego->GetAncho()/2), t_titulo.GetY()+150);
        
        t_slot2.CambiarFuente(_juego->recursos.GetFuente("DK"));
        t_slot2.CambiarTamanyo(tamFuente);
        t_slot2.CentrarOrigen();
        t_slot2.CambiarPosicion((_juego->GetAncho()/2), t_slot1.GetY()+75);
        
        t_slot3.CambiarFuente(_juego->recursos.GetFuente("DK"));
        t_slot3.CambiarTamanyo(tamFuente);
        t_slot3.CentrarOrigen();
        t_slot3.CambiarPosicion((_juego->GetAncho()/2), t_slot2.GetY()+75);
        
        
            /*t_cargar.CambiarFuente(_juego->recursos.GetFuente("DK"));
        t_cargar.CambiarTexto("Cargar partida");
        t_cargar.CambiarTamanyo(tamFuente);
        t_cargar.CentrarOrigen();
        t_cargar.CambiarPosicion((_juego->GetAncho()/2), t_jugar.GetY()+75);
        
        t_borrar.CambiarFuente(_juego->recursos.GetFuente("DK"));
        t_borrar.CambiarTexto("Borrar partida");
        t_borrar.CambiarTamanyo(tamFuente);
        t_borrar.CentrarOrigen();
        t_borrar.CambiarPosicion((_juego->GetAncho()/2), t_cargar.GetY()+75);
             
        t_estadisticas.CambiarFuente(_juego->recursos.GetFuente("DK"));
        t_estadisticas.CambiarTexto("Estadisticas");
        t_estadisticas.CambiarTamanyo(tamFuente);
        t_estadisticas.CentrarOrigen();
        t_estadisticas.CambiarPosicion((_juego->GetAncho()/2), t_jugar.GetY()+75);
        */
        
        if (!hayPartidas) {
            t_explicar.CambiarFuente(_juego->recursos.GetFuente("DK"));
            t_explicar.CambiarTamanyo(tamFuente-5);
            t_explicar.CambiarTexto("Elige el slot para guardar partida");
            t_explicar.CentrarOrigen();
            t_explicar.CambiarPosicion((_juego->GetAncho()/2), t_slot3.GetY()+150);
        } else {
            
            t_op1.CambiarFuente(_juego->recursos.GetFuente("DK"));
            t_op1.CambiarTamanyo(tamFuente);
            t_op1.CambiarTexto("Elige el slot para guardar partida");
            t_op1.CentrarOrigen();
            t_op1.CambiarPosicion(150, t_slot3.GetY()+150);
            
            
            
            
            
            
            
            flechaOp.CambiarTextura(_juego->recursos.GetTextura("Flecha"));
            flechaOp.CambiarOrigen();
            flechaOp.Escalar(60.0f, 60.0f); // Escalar al 60%
            flechaOp.CambiarColorVerde();
            CambiarFlecha(flechaOp, t_op1);
        }
        
        flecha.CambiarTextura(_juego->recursos.GetTextura("Flecha"));
        flecha.CambiarOrigen();
        flecha.CambiarColorRojo();
        flecha.Escalar(80.0f, 80.0f); // Escalar al 80%
        CambiarFlecha(flecha, t_slot1);
        
        t_atras.CambiarFuente(_juego->recursos.GetFuente("DK"));
        t_atras.CambiarTexto("Volver");
        t_atras.CambiarTamanyo(50);
        t_atras.CentrarOrigen();
        t_atras.CambiarPosicion(100, (_juego->GetAlto()-100));
        
        flechaAtras.CambiarTextura(_juego->recursos.GetTextura("Flecha"));
        flechaAtras.CambiarOrigen();
        flechaAtras.CambiarColorRojo();
        flechaAtras.Rotar(180.0f);
        flechaAtras.CambiarPosicion(60, t_atras.GetY()-30);
        flechaAtras.Escalar(70.0f, 70.0f); // Escalar al 70%
    }
    
    void EstadoPartidas::ManejarEventos()
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
            
            if (_input->RatonSobre(t_slot1))
            {
                CambiarFlecha(flecha, t_slot1);
                slotGuardar = SLOT1;
            }
            if (_input->RatonSobre(t_slot2))
            {
                CambiarFlecha(flecha, t_slot2);
                slotGuardar = SLOT2;
            }
            if (_input->RatonSobre(t_slot3))
            {
                CambiarFlecha(flecha, t_slot3);
                slotGuardar = SLOT3;
            }
            
            /*if (_input->RatonSobre(t_cargar))
            {
                CambiarFlecha(t_cargar);
                opcion = CARGAR;
            }
            if (_input->RatonSobre(t_borrar))
            {
                CambiarFlecha(t_borrar);
                opcion = BORRAR;
            }
            if (_input->RatonSobre(t_estadisticas))
            {
                CambiarFlecha(t_estadisticas);
                opcion = ESTADISTICAS;
            }*/
            
            // Clic sobre texto
            if (_input->RatonIzq()) {
                if (_input->IsTextoClicked(t_atras))
                {
                    Atras();
                }
                
                if ((_input->IsTextoClicked(t_slot1)) ||
                    (_input->IsTextoClicked(t_slot2)) ||
                    (_input->IsTextoClicked(t_slot3)))
                {
                    NuevaPartida();
                }
                
                /*
                if(_input->IsTextoClicked(t_cargar))
                {
                    CargarPartida();
                }
                if(_input->IsTextoClicked(t_borrar))
                {
                    BorrarPartida();
                }
                if(_input->IsTextoClicked(t_estadisticas))
                {
                    Estadisticas();
                }*/
            }
        }
    }
    
    void EstadoPartidas::Actualizar(float tiempoActual)
    {
        /*Habrá un archivo save
Había pensado hacer el slot como dos archivos: Estadisticas y Save
Si existe Estadísticas, Nueva partida*; si existe Estadísticas y Save, Reanudar;
Si no, Nueva partida*/
        switch(slotGuardar)
        {
            case SLOT1:
                break;
            case SLOT2:
                break;
            case SLOT3:
                break;
        }
    }
    
    void EstadoPartidas::Dibujar(float tiempoActual)
    {
        _juego->_ventana->Limpiar();
        
        _juego->_ventana->DibujarTexto(t_titulo);
        _juego->_ventana->DibujarTexto(t_slot1);
        _juego->_ventana->DibujarTexto(t_slot2);
        _juego->_ventana->DibujarTexto(t_slot3);
        
        if (!hayPartidas) {
            _juego->_ventana->DibujarTexto(t_explicar);
        } else {
            _juego->_ventana->DibujarSprite(flechaOp);
            
            _juego->_ventana->DibujarTexto(t_op1);
            _juego->_ventana->DibujarTexto(t_op2);
            _juego->_ventana->DibujarTexto(t_op3);
        }
        
        _juego->_ventana->DibujarSprite(flecha);
        _juego->_ventana->DibujarTexto(t_atras);
        _juego->_ventana->DibujarSprite(flechaAtras);

        _juego->_ventana->Mostrar();
    }
    
    void EstadoPartidas::ComprobarPartidas()
    {
        hayPartidas = false;
        t_slot1.CambiarTexto("Slot 1");
        t_slot2.CambiarTexto("Slot 2");
        t_slot3.CambiarTexto("Slot 3");
        
        /*ifstream leerPartida;
        ifstream leerEstadisticas;
        string ruta = "";
        
        cout << "Llega maldito" <<endl;
        
        for (short int num=1; num<=slots; num++)
        {
            partidas[num] = new bool[archivos];
            ruta = CARPETA+PARTIDA+to_string(num)+EXTENSION;
            
            leerPartida.open(ruta);
            if (leerPartida.is_open()) // Si hay partida
            {
                hayPartidas = true;
                partidas[num][0] = true;
                CambiarSlot(num);
                
                ruta = CARPETA+STATS+to_string(num)+EXTENSION;
                leerEstadisticas.open(ruta);

                if (leerEstadisticas.is_open()) { // Si hay estadisticas
                    partidas[num][1] = true;
                } else {
                    partidas[num][1] = false;
                }

                leerEstadisticas.close();
            } else {
                partidas[num][0] = false;
            }
            leerPartida.close();
        }*/
    }
    
    void EstadoPartidas::CambiarSlot(short int num)
    {
        switch(num)
        {
            case 1:
                t_slot1.CambiarTexto("Partida 1");
                break;
            case 2:
                t_slot2.CambiarTexto("Partida 2");
                break;
            case 3:
                t_slot3.CambiarTexto("Partida 3");
                break;
        }
    }
    
    void EstadoPartidas::Opciones(Texto texto)
    {
        
    }
    
    void EstadoPartidas::Atras()
    {
        _juego->maquina.Eliminar();
    }
    
    void EstadoPartidas::CambiarFlecha(SpriteM f, Texto texto)
    {
        f.CambiarPosicion(texto.GetLeft()-10,texto.GetY()+texto.GetOrigenY()/2);
    }
    
    void EstadoPartidas::NuevaPartida()
    {
        cout << "Guardar en: " << slotGuardar << endl;
        
        // Liberamos la memoria dinamica
        /*for (short int num=1; num<=slots; num++)
        {
            delete[] partidas[num];
        }
        delete[] partidas;
        partidas = NULL;*/
        
        _juego->SetSlot(slotGuardar);
        
        // Cambiamos de estado la maquina
        _juego->maquina.Anyadir(EstadoSeleccion::Instance(), true);
    }
    
    void EstadoPartidas::CargarPartida()
    {
        cout<<"Cargar"<<endl;
    }
    
    void EstadoPartidas::BorrarPartida()
    {
        cout<<"Borrar"<<endl;
    }
    
    void EstadoPartidas::Estadisticas()
    {
        _juego->maquina.Anyadir(EstadoEstadisticas::Instance(), false);
    }
}