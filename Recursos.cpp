#include "Recursos.hpp"

namespace Motor
{
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
}