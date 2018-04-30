#include "Input.hpp"
namespace Motor
{
    Input::Input()
    {
        _ventana = Ventana::Instance();
        t.Arriba = false;
        t.Abajo = false;
        t.Izq = false;
        t.Der = false;
        t.Enter = false;
        t.BackSpace = false;
        t.Escape = false;
        t.RatonIzq = false;
        t.RatonDer = false;
    }
    
    void Input::CerrarVentana()
    {
        _ventana->Cerrar();
    }
    
    bool Input::BucleEventos()
    {
        //Bucle de obtención de eventos
        sf::Event event;
        while (_ventana->GetVentana().pollEvent(event))
        {
            switch(event.type)
            {
                //Si se recibe el evento de cerrar la ventana la cierro
                case sf::Event::Closed:
                    CerrarVentana();
                break;
                    
                // Pulsar una tecla
                case sf::Event::KeyPressed:
                    
                    //Verifico cual se pulsa
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                        t.Escape=true;
                    }
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
                        t.Arriba=true;
                    }
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
                        t.Abajo=true;
                    }
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
                        t.Izq=true;
                    }
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
                        t.Der=true;
                    }
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) {
                        t.Enter=true;
                    }
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace)) {
                        t.BackSpace=true;
                    }
                    return true;
                break;
                
                case sf::Event::KeyReleased:
                    t.Escape=false;
                    t.Arriba=false;
                    t.Abajo=false;
                    t.Izq=false;
                    t.Der=false;
                    t.Enter=false;
                    t.BackSpace=false;
                break;
                    
                // Pulsar boton raton
                case sf::Event::MouseButtonPressed:
                    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                        t.RatonIzq=true;
                    }
                    if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
                        t.RatonDer=true;
                    }
                    return true;
                break;
                
                // Soltar boton raton
                case sf::Event::MouseButtonReleased:
                        t.RatonIzq=false;
                        t.RatonDer=false;
                break;
            }
        }
        return false;
    }
    
    Teclas Input::GetTeclas()
    {
        return t;
    }
    
    float Input::GetPosicionRatonX()
    {
        return sf::Mouse::getPosition(_ventana->GetVentana()).x;
    }
    
    float Input::GetPosicionRatonY()
    {
       return sf::Mouse::getPosition(_ventana->GetVentana()).y;
    }
}