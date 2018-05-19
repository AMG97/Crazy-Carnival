#include "EstadosManager.hpp"
#include <iostream>
using namespace std;

namespace Crazy
{
    void EstadosManager::Anyadir( Estado* nuevoEstado, bool reemplazar)
    {
        anyadiendo = true;
        reemplazando = reemplazar;
        estado = move(nuevoEstado);
    }
    
    void EstadosManager::Eliminar()
    {
        eliminando = true;
    }
    
    void EstadosManager::ProcesarPilaEstados()
    {
        if ( eliminando && !estados.empty())
        {
            estados.top()->Vaciar();
            estados.pop();
            
            if (!estados.empty())
            {
                estados.top()->Reanudar();
            }
            eliminando = false;
        }
        
        if (anyadiendo)
        {
            if (!estados.empty())
            {
                if (reemplazando)
                {
                    estados.top()->Vaciar();
                    estados.pop();
                }
                else
                {
                    estados.top()->Pausar();
                }
            }
            
            estados.push(move(estado));
            estado=0;
            estados.top()->Init();
            anyadiendo = false;
        }
    }
    
    Estado* &EstadosManager::GetEstadoActivo()
    {
        return estados.top();
    }
    
    void EstadosManager::SaltarAlMenu()
    {
        for (short int est=0; est<estados.size(); est++)
        {
            estados.top()->Vaciar();
            estados.pop();
        }
        estados.top()->Reanudar();
    }
}