#include <string>

#include "GestorArchivo.hpp"
#include "EstadoJuego.hpp"

namespace Crazy{

    GestorArchivo* GestorArchivo::Instance() {
        if(pinstance==0){
            pinstance = new GestorArchivo();
        }
        return pinstance;
    }
    GestorArchivo* GestorArchivo::pinstance=0;

    GestorArchivo::GestorArchivo(){
        slot = 3;
    }

    GestorArchivo::~GestorArchivo() {
    }

    void GestorArchivo::Iniciar(unsigned short int n_slot) {
        slot = n_slot;
        
        doc_save = TiXmlDocument(("saves/Save"+to_string(slot)+".xml").c_str());
        doc_stat = TiXmlDocument(("saves/Stats"+to_string(slot)+".xml").c_str());
    }

    bool GestorArchivo::exists(string nombre) {
        if(nombre=="Stats"){
            return doc_stat.LoadFile();
        }else{
            return doc_save.LoadFile();
        }
    }

    bool GestorArchivo::borrarGuardado() {
        if(remove(doc_save.Value())!=0)
            std::cerr << "Error al borrar el archivo de guardado";
        else
            return true;
        
        return false;
    }


    void GestorArchivo::borrarSlot() {
        if(remove(doc_stat.Value())!=0)
            std::cerr << "Error al borrar el archivo";
        
        borrarGuardado();
    }

    map<string, float>* GestorArchivo::getTotalStats() {
        return &stats;
    }

    void GestorArchivo::cargarStats() {
        if(exists("Stats")){
            
        }
    }

    float GestorArchivo::getStat(string name) {
        map<string,float>::iterator it = stats.find(name);
        if(it!=stats.end())
            return it->second;
        else
            return -1;
    }

    bool GestorArchivo::addStat(string name, float valor) {
        map<string,float>::iterator it = stats.find(name);
        if(it!=stats.end()){
            it->second+=valor;
            return true;
        }else
            return false;
    }

    bool GestorArchivo::setStat(string name, float valor) {
        map<string,float>::iterator it = stats.find(name);
        if(it!=stats.end()){
            it->second=valor;
            return true;
        }else
            return false;
    }

    void GestorArchivo::guardarPartida() {
        borrarGuardado();
        doc_save = TiXmlDocument(("saves/Save"+to_string(slot)+".xml").c_str());
        
        string personaje;
        int arma, puntos, nivel;
        bool hardcore, contrarreloj, elixir;
        
        
        EstadoJuego::Instance()->getDatosGuardado(&personaje,&arma,&nivel,&hardcore,&contrarreloj,&elixir,&puntos);
        
        TiXmlElement xml_player("player");
        doc_save.LinkEndChild(&xml_player);
        xml_player.SetAttribute("personaje",personaje.c_str());
        xml_player.SetAttribute("arma",(int)arma);
        xml_player.SetAttribute("hardcore",hardcore);
        xml_player.SetAttribute("contrarreloj",contrarreloj);
        xml_player.SetAttribute("elixir",elixir);
        xml_player.SetAttribute("puntos",puntos);
        xml_player.SetAttribute("nivel",nivel);
        
        
            
        if(doc_save.SaveFile(("saves/Save"+to_string(slot)+".xml").c_str()))
            cout<< "Se ha guardado bien"<<endl;
        else
            cerr<<"Ha habido alguna clase de error al guardar"<<endl;
    }
    
    void GestorArchivo::nuevoSlot() {
        if(doc_save.SaveFile(("saves/Stats"+to_string(slot)+".xml").c_str()))
            cout<< "Se ha guardado bien el Stat"<<endl;
        else
            cerr<<"Ha habido alguna clase de error al guardar Stats"<<endl;
    }

    bool GestorArchivo::cargarPartida() {
        if(exists("save")){
            TiXmlElement* xml_player = doc_save.FirstChildElement("player");

            string personaje; personaje = xml_player->Attribute("personaje");
            int arma; xml_player->QueryIntAttribute("arma",&arma);
            int puntos; xml_player->QueryIntAttribute("puntos",&puntos);
            int nivel; xml_player->QueryIntAttribute("nivel",&nivel);
            bool hardcore; xml_player->QueryBoolAttribute("hardcore",&hardcore);
            bool contrarreloj; xml_player->QueryBoolAttribute("contrarreloj",&contrarreloj);
            bool elixir; xml_player->QueryBoolAttribute("elixir",&elixir);



            EstadoJuego::Instance()->cargarDatosGuardados(&personaje,&arma,&nivel,&hardcore,&contrarreloj,&elixir,&puntos);
            return true;
        }else
            return false;
    }


}