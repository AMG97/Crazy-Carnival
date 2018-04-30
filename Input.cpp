#include "Input.hpp"
namespace Motor
{
    Input::Input()
    {
        _ventana = Ventana::Instance();
        teclas.Pausar = false;
        teclas.Arriba = false;
        teclas.Abajo = false;
        teclas.Izq = false;
        teclas.Der = false;
        teclas.Enter = false;
        teclas.BackSpace = false;
        teclas.Escape = false;
        teclas.RatonIzq = false;
        teclas.RatonDer = false;
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
                        teclas.Escape=true;
                    }
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
                        teclas.Arriba=true;
                    }
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
                        teclas.Abajo=true;
                    }
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
                        teclas.Izq=true;
                    }
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
                        teclas.Der=true;
                    }
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) {
                        teclas.Enter=true;
                    }
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace)) {
                        teclas.BackSpace=true;
                    }
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::P)) {
                        teclas.Pausar=true;
                    }
                    return true;
                break;
                
                case sf::Event::KeyReleased:
                    teclas.Pausar = false;
                    teclas.Escape=false;
                    teclas.Arriba=false;
                    teclas.Abajo=false;
                    teclas.Izq=false;
                    teclas.Der=false;
                    teclas.Enter=false;
                    teclas.BackSpace=false;
                break;
                    
                // Pulsar boton raton
                case sf::Event::MouseButtonPressed:
                    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                        teclas.RatonIzq=true;
                    }
                    if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
                        teclas.RatonDer=true;
                    }
                    return true;
                break;
                
                // Soltar boton raton
                case sf::Event::MouseButtonReleased:
                        teclas.RatonIzq=false;
                        teclas.RatonDer=false;
                break;
            }
        }
        return false;
    }
    
    Input::Teclas Input::GetTeclas()
    {
        return teclas;
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