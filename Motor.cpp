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

    void SpriteM::CambiarTextRect(int x, int y, int width, int height) {
        setTextureRect(sf::IntRect(x,y,width,height));
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
    
    float SpriteM::GetX()
    {
        return getPosition().x;
    }
    
    float SpriteM::GetY()
    {
        return getPosition().y;
    }
    
    void SpriteM::Mover(float v)
    {
        move(v, 0);
    }
    void SpriteM::Mover(float x,float y)
    {
        move(x,y);
    } 
    bool SpriteM::Interseccion(SpriteM s)
    {
        return getGlobalBounds().intersects(s.getGlobalBounds());
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
        background = sf::Color(0,0,0);
    }
    
    bool Ventana::EstaAbierta() {
        return window.isOpen();
    }
    
    void Ventana::Limpiar()
    {
        window.clear(background);
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
    
     void Ventana::DibujarB(SpriteM sprite, Camara& camara)
    {
         sprite.CambiarPosicion(sprite.GetX() + camara.GetCamara().getCenter().x -500, sprite.GetY() + camara.GetCamara().getCenter().y-350);
        window.draw(sprite);
    }
    
    void Ventana::DibujarC(SpriteM sprite)
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
    void Ventana::setBackground(int r, int g, int b) {
        background = sf::Color(r,g,b);
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
    
    ///Define el tamaño de la cámara
    void Camara::setTam(float x, float y) {
        camara.setSize(x,y);
    }
    
    void Camara::mover(int x, int y) {
        camara.move(x,y);
    }

    void Camara::setCentro(int x, int y) {
        camara.setCenter(x,y);
    }

    int Camara::getX() {
        return camara.getCenter().x;
    }

    int Camara::getY() {
        return camara.getCenter().y;
    }
    
    float Camara::getHeight() {
        return camara.getSize().y;
    }

    float Camara::getWidth() {
        return camara.getSize().x;
    }


// Input
    Input::Input()
    {
        _ventana = Ventana::Instance();
        
        eventos.Closed = 1;
        eventos.KeyPressed = 2;
        eventos.KeyReleased = 3;
        eventos.MouseButtonPressed = 4;
        eventos.MouseButtonReleased = 5;
    }
    
    float Input::GetPosicionRatonX()
    {
        return sf::Mouse::getPosition(_ventana->GetVentana()).x;
    }
    
    float Input::GetPosicionRatonY()
    {
       return sf::Mouse::getPosition(_ventana->GetVentana()).y;
    }
    
    Input::Eventos Input::Evento()
    {
        return eventos;
    }
    
    short int Input::GetTipoEvento()
    {
        sf::Event event;
        while (_ventana->GetVentana().pollEvent(event))
        {
            switch(event.type)
            {
                case sf::Event::Closed:
                    _ventana->Cerrar();
                    return eventos.Closed;

                case sf::Event::KeyPressed:
                    return eventos.KeyPressed;

                case sf::Event::KeyReleased:
                    return eventos.KeyReleased;

                case sf::Event::MouseButtonPressed:
                    return eventos.MouseButtonPressed;

                case sf::Event::MouseButtonReleased:
                    return eventos.MouseButtonReleased;

                default:
                    return 0;
            }
        }
    }
    
    bool Input::RatonPulsado(sf::Mouse::Button boton)
    {
        if (sf::Mouse::isButtonPressed(boton)) {
            return  true;
        }
        return  false;
    }
    
    bool Input::TeclaPulsada(sf::Keyboard::Key key)
    {
        if (sf::Keyboard::isKeyPressed(key)) {
            return  true;
        }
        return  false;
    }
    
    bool Input::RatonDer()
    {
        return RatonPulsado(sf::Mouse::Button::Right);
    }
    
    bool Input::RatonIzq()
    {
        return RatonPulsado(sf::Mouse::Button::Left);
    }
    
    bool Input::Der()
    {
        return TeclaPulsada(sf::Keyboard::Right);
    }
    
    bool Input::Izq()
    {
        return TeclaPulsada(sf::Keyboard::Left);
    }
    
    bool Input::Arriba()
    {
        return TeclaPulsada(sf::Keyboard::Up);
    }
    
    bool Input::Abajo()
    {
        return TeclaPulsada(sf::Keyboard::Down);
    }
    
    bool Input::Escape()
    {
        return TeclaPulsada(sf::Keyboard::Escape);
    }
    
    bool Input::BackSpace()
    {
        return TeclaPulsada(sf::Keyboard::BackSpace);
    }
    
    bool Input::Enter()
    {
        return TeclaPulsada(sf::Keyboard::Return);
    }
    
    bool Input::P()
    {
        return TeclaPulsada(sf::Keyboard::P);
    }
    
    bool Input::D()
    {
        return TeclaPulsada(sf::Keyboard::D);
    }
    
    bool Input::C()
    {
        return TeclaPulsada(sf::Keyboard::C);
    }
    
    bool Input::F()
    {
        return TeclaPulsada(sf::Keyboard::F);
    }
    
    bool Input::R()
    {
        return TeclaPulsada(sf::Keyboard::R);
    }
    
    bool Input::E()
    {
        return TeclaPulsada(sf::Keyboard::E);
    }
    
    bool Input::Q()
    {
        return TeclaPulsada(sf::Keyboard::Q);
    }
}