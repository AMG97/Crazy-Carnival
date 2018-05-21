#include "EstadoRecompensas.hpp"

namespace Crazy
{
    EstadoRecompensas::EstadoRecompensas(short int p)
    {
        _juego = Juego::Instance();
        personaje = p;
        ComprobarPersonaje();
    }
    
    EstadoRecompensas* EstadoRecompensas::_pinstance=0;
    
    EstadoRecompensas* EstadoRecompensas::Instance(short int p)
    {
        if (_pinstance == 0)
        {
            _pinstance = new EstadoRecompensas(p);
        }
        return _pinstance;
    }
    
    void EstadoRecompensas::Vaciar()
    {
        _pinstance=0;
    }
        
    EstadoRecompensas::~EstadoRecompensas()
    {
        delete _input;
        _input = NULL;
        delete _pinstance;
        _pinstance = NULL;
    }
    
    void EstadoRecompensas::Init()
    {
        _input = new Input();
        contadorSpriteReposo = 0;
        opcion = R1;
        separacion = 275;
        altura = 300;
        
        t_titulo.CambiarFuente(_juego->recursos.GetFuente("DK"));
        t_titulo.CambiarTexto("Elige mejora");
        t_titulo.CambiarTamanyo(100);
        t_titulo.CentrarOrigen();
        t_titulo.CambiarPosicion((_juego->GetAncho()/2), 75);
        
        r1.CambiarOrigen(ancho/2,alto/2);
        r1.CambiarPosicion((_juego->GetAncho()/2)-separacion, t_titulo.GetY()+altura);
        r1.EscalarProporcion(proporcion, proporcion);
        
        r2.CambiarOrigen(ancho/2,alto/2);
        r2.CambiarPosicion((_juego->GetAncho()/2), t_titulo.GetY()+altura);
        r2.EscalarProporcion(proporcion, proporcion);
        
        r3.CambiarOrigen(ancho/2,alto/2);
        r3.CambiarPosicion((_juego->GetAncho()/2)+separacion, t_titulo.GetY()+altura);
        r3.EscalarProporcion(proporcion, proporcion);
        
        flecha.CambiarTextura(_juego->recursos.GetTextura("Flecha"));
        flecha.CambiarOrigen();
        flecha.Rotar(90.0f);
        CambiarFlecha(r1);
        flecha.CambiarColorRojo();
        flecha.Escalar(50.0f, 50.0f); // Escalar al 50%
        
        t_conti.CambiarFuente(_juego->recursos.GetFuente("DK"));
        t_conti.CambiarTexto("Continuar");
        t_conti.CambiarTamanyo(48);
        t_conti.CentrarOrigen();
        t_conti.CambiarPosicion(915, (_juego->GetAlto()-100));
        
        flechaContinuar.CambiarTextura(_juego->recursos.GetTextura("Flecha"));
        flechaContinuar.CambiarOrigen();
        flechaContinuar.CambiarPosicion(964, t_conti.GetY()-30);
        flechaContinuar.Escalar(75.0f, 75.0f); // Escalar al 80%
        flechaContinuar.CambiarColorRojo();
    }
    
    void EstadoRecompensas::ManejarEventos()
    {
        if (_input->GetTipoEvento() == _input->Evento().KeyPressed)
        {
            /*if (_input->BackSpace()
                || _input->Escape())
            {
                Atras();
            }*/
            
        } else {
            // Color rojo/blanco del texto
            _input->RatonSobre(t_conti);
            
            if (_input->RatonSobre(r1))
            {
                CambiarFlecha(r1);
                opcion = R1;
            }
            if (_input->RatonSobre(r2))
            {
                CambiarFlecha(r2);
                opcion = R2;
            }
            if (_input->RatonSobre(r3))
            {
                CambiarFlecha(r3);
                opcion = R3;
            }
            
            // Clic sobre texto
            if (_input->RatonIzq()) {
                
                if(_input->IsTextoClicked(t_conti))
                {
                    Continuar();
                }
            }
        }
    }
    
    void EstadoRecompensas::Actualizar(float tiempoActual)
    {
    }
    
    void EstadoRecompensas::Dibujar(float tiempoActual)
    {
        _juego->_ventana->Limpiar();
        
        _juego->_ventana->DibujarTexto(t_titulo);
        Animar();
        _juego->_ventana->DibujarSprite(r1);
        _juego->_ventana->DibujarSprite(r2);
        _juego->_ventana->DibujarSprite(r3);
        _juego->_ventana->DibujarSprite(flecha);
        _juego->_ventana->DibujarTexto(t_conti);
        _juego->_ventana->DibujarSprite(flechaContinuar);

        _juego->_ventana->Mostrar();
    }
    
    void EstadoRecompensas::CambiarFlecha(SpriteM personaje)
    {
        flecha.CambiarPosicion(personaje.GetX(),personaje.GetY()-personaje.GetAlto()/2);
    }
    
    void EstadoRecompensas::ComprobarPersonaje()
    {
        proporcion = 2.0f;
        r1.CambiarTextura(_juego->recursos.GetTextura("Recompensas"));
        r2.CambiarTextura(_juego->recursos.GetTextura("Recompensas"));
        r3.CambiarTextura(_juego->recursos.GetTextura("Recompensas"));
        
        switch(personaje)
        {
            case 1: // Espadachina
                ancho = 72;
                alto = 72;
                r1.CambiarTextRect(0*ancho, 0*alto, ancho, alto);
                r2.CambiarTextRect(1*ancho, 0*alto, ancho, alto);
                r3.CambiarTextRect(2*ancho, 0*alto, ancho, alto);
                break;
                
            case 2: // Pistolero
                ancho = 116;
                alto = 61;
                r1.CambiarTextRect(0*ancho, 0*alto+72, ancho, alto);
                r2.CambiarTextRect(0*ancho, 1*alto+72, ancho, alto);
                r3.CambiarTextRect(0*ancho, 2*alto+72, ancho, alto);
                break;
        }
    }
    
    void EstadoRecompensas::Animar()
    {
        if (relojAnim.GetSegundos() >= 0.11f)
        {
            switch(opcion)
            {
                case R1:
                    r1.ColorTransparente();
                    r2.CambiarColorBlanco();
                    r3.CambiarColorBlanco();
                    break;
                case R2:
                    r2.ColorTransparente();
                    r1.CambiarColorBlanco();
                    r3.CambiarColorBlanco();
                    break;
                case R3:
                    r3.ColorTransparente();
                    r1.CambiarColorBlanco();
                    r2.CambiarColorBlanco();
                    break;
            }
            relojAnim.ReiniciarSegundos();
        } else {
            switch(opcion)
            {
                case R1:
                    r1.CambiarColorBlanco();
                    break;
                case R2:
                    r2.CambiarColorBlanco();
                    break;
                case R3:
                    r3.CambiarColorBlanco();
                    break;
            }
        }
    }
    
    void EstadoRecompensas::Continuar()
    {
        //Hacer cosas, supongo
        //pasar la variable opcion
        short int a;
        if(personaje==1){//Espadachina
            switch (opcion){
                case R1:
                    a=2;
                    break;
                case R2:
                    a=3;
                    break;
                case R3:
                    a=4;
                    break;
            }
        }else{
            switch (opcion){
                case R1:
                    a=6;
                    break;
                case R2:
                    a=7;
                    break;
                case R3:
                    a=8;
                    break;
            }
        }
        EstadoJuego::Instance()->setArma(a);
        EstadoJuego::Instance()->setNumNivel(2);
        EstadoJuego::Instance()->Init();
        CambiarEstadoMaquina();
    }
    void EstadoRecompensas::CambiarEstadoMaquina()
    {
        _juego->maquina.Eliminar();
    }
}