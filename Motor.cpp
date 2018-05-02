#include "Motor.hpp"
namespace Motor
{
// Reloj
    float Reloj::ReiniciarMilisegundos()
    {
        return restart().asMilliseconds();
    }
    
    float Reloj::ReiniciarSegundos()
    {
        return restart().asSeconds();
    }
    
    float Reloj::GetSegundos()
    {
        return getElapsedTime().asSeconds();
    }
    
    float Reloj::GetMilisegundos()
    {
        return getElapsedTime().asMilliseconds();
    }
    
// Texto
    void Texto::CambiarFuente(sf::Font& fon)
    {
        setFont(fon);
    }
    
    void Texto::CambiarTexto(string text)
    {
        setString(text);
    }
    
    void Texto::CambiarTamanyo(int tam)
    {
        setCharacterSize(tam);
    }
    
    void Texto::CambiarPosicion(float x, float y)
    {
        setPosition(x, y);
    }
    
    void Texto::CentrarOrigen()
    {
        setOrigin(GetAncho()/2, GetAlto()/2);
    }
    
    void Texto::CambiarOrigen(float x, float y)
    {
        setOrigin(x, y);
    }
    
    float Texto::GetOrigenX()
    {
        return getOrigin().x;
    }
    
    float Texto::GetOrigenY()
    {
        return getOrigin().y;
    }
    
    float Texto::GetAncho()
    {
        return getGlobalBounds().width;
    }
    
    float Texto::GetAlto()
    {
        return getGlobalBounds().height;
    }
    
    float Texto::GetTop()
    {
        return getGlobalBounds().top;
    }
    
    float Texto::GetLeft()
    {
        return getGlobalBounds().left;
    }
    
    float Texto::GetX()
    {
        return getPosition().x;
    }
    
    float Texto::GetY()
    {
        return getPosition().y;
    }
    
// Recursos
    void Recursos::CargarTextura(string nombre, string fichero)
    {
        sf::Texture tex;
        if (tex.loadFromFile(fichero))
        {
            texturas[nombre] = tex;
        }
        else
        {
            cerr << "Error cargando la imagen "<< fichero;
            exit(0);
        }
    }
    
    sf::Texture &Recursos::GetTextura(string nombre)
    {
        return texturas.at(nombre);
    }
        
    void Recursos::CargarFuente(string nombre, string fichero)
    {
        sf::Font fuente;
        if (fuente.loadFromFile(fichero))
        {
            fuentes[nombre] = fuente;
        }
        else
        {
            cerr << "Error cargando la fuente "<< fichero;
            exit(0);
        }
    }
    
    sf::Font &Recursos::GetFuente(string nombre)
    {
        return fuentes.at(nombre);
    }
    
// SpriteM
    void SpriteM::CambiarTextura(sf::Texture &textura)
    {
        setTexture(textura);
    }
    
    void SpriteM::CambiarPosicion(float x, float y)
    {
        setPosition(x, y);
    }
    
    void SpriteM::CentrarOrigen()
    {
        setOrigin(getTexture()->getSize().x/2, getTexture()->getSize().y/2);
    }
    
    void SpriteM::CambiarOrigen()
    {
        setOrigin(getTexture()->getSize().x, getTexture()->getSize().y/2);
    }
    
    void SpriteM::CambiarOrigen(float x, float y)
    {
        setOrigin(x, y);
    }
    
    void SpriteM::CambiarColorRojo()
    {
        setColor(sf::Color::Red);
    }
    
    void SpriteM::Rotar(float angulo)
    {
        rotate(angulo);
    }
    
    void SpriteM::Escalar(float x, float y)
    {
        scale(x/getTexture()->getSize().x, y/getTexture()->getSize().y);
    }
    void SpriteM::EscalarProporcion(float x, float y)
    {
        scale(x, y);
    }
    
    void SpriteM::Parpadear(bool parpadeo)
    {
        if (parpadeo)
        {
            setColor(sf::Color(50, 125, 255, 255));
        }
        else
        {
            setColor(sf::Color(255, 255, 255, 255));
        }
    }
    
    float SpriteM::GetAncho()
    {
        return getGlobalBounds().width;
    }
    
    float SpriteM::GetAlto()
    {
        return getGlobalBounds().height;
    }
    
    float SpriteM::GeEscalarX()
    {
        return getScale().x;
    }
    
    float SpriteM::GeEscalarY()
    {
        return getScale().y;
    }
    
    float SpriteM::GetX()
    {
        return getPosition().x;
    }
    
    float SpriteM::GetY()
    {
        return getPosition().y;
    }

// Ventana
    Ventana* Ventana::_pinstance=0;
    
    Ventana* Ventana::Instance()
    {
        if (_pinstance == 0)
        {
            _pinstance = new Ventana();
        }
        return _pinstance;
    }
    
    Ventana::~Ventana()
    {
        delete _pinstance;
        _pinstance = NULL;
    }
    
    void Ventana::CrearVentana(int ancho, int alto, string titulo) {
        window.create(sf::VideoMode(ancho, alto), titulo);

        //Activa la sincronizacion vertical (60 fps)
        window.setVerticalSyncEnabled(true); 
        window.setFramerateLimit(60);
    }
    
    bool Ventana::EstaAbierta() {
        return window.isOpen();
    }
    
    void Ventana::Limpiar()
    {
        window.clear();
    }
    
    void Ventana::Mostrar()
    {
        window.display();
    }
    
    void Ventana::Cerrar()
    {
        window.close();
    }
    
    void Ventana::Dibujar(Texto txt)
    {
        window.draw(txt);
    }
    
    void Ventana::Dibujar(SpriteM sprite)
    {
        window.draw(sprite);
    }
    void Ventana::setCamara(Camara &camara)
    {
        window.setView(camara.GetCamara());
    }
    
    sf::RenderWindow& Ventana::GetVentana()
    {
        return window;
    }
// Cámara
    Camara* Camara::_pinstance2=0;
    
    Camara* Camara::Instance()
    {
        if (_pinstance2 == 0)
        {
            _pinstance2 = new Camara();
        }
        return _pinstance2;
    }
    
    Camara::~Camara()
    {
        delete _pinstance2;
        _pinstance2 = NULL;
    }
    
    void Camara::CrearCamara(float centroX, float centroY, float ancho, float alto)
    {
        camara.reset(sf::FloatRect(centroX, centroY, ancho, alto));
    }
            
    sf::View& Camara::GetCamara()
    {
        return camara;
    }
// Input
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
		
        //Pruebas
        teclas.D = false;
        teclas.C = false;
        teclas.F = false;
        teclas.R = false;
        teclas.E = false;
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
					
                    //Pruebas
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
                        teclas.D=true;
                    }
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::C)) {
                        teclas.C=true;
                    }
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::F)) {
                        teclas.F=true;
                    }
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
                        teclas.R=true;
                    }
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)) {
                        teclas.E=true;
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
					
                    //Pruebas
                    teclas.D = false;
                    teclas.C = false;
                    teclas.F = false;
                    teclas.R = false;
                    teclas.E = false;
                    return false;
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