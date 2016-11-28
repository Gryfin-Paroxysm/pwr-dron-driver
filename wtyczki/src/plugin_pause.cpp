#include "plugin_pause.hh"

void C_pause::wyswietl_komende() const{
    std::cout << zwroc_nazwe_komendy() << " " << _czas_w_ms << std::endl;
}

void C_pause::wyswietl_skladnie_komendy() const{
    std::cout << "   Pause  czas [ms]" << std::endl;
}

const char* C_pause::zwroc_nazwe_komendy() const{
    return "Pause";
}

bool C_pause::wykonaj_komende(C_dron *dron) const{
	if(usleep(_czas_w_ms) == -1) return false;
    return true;
}

bool C_pause::odczytaj_komende(std::istream& strumien_komendy){
    strumien_komendy >> _czas_w_ms;
    if(strumien_komendy.fail())
        return false;
    return true;
}

extern "C" C_plugin* stworz(){
    return new C_pause;
}

extern "C" void usun(C_plugin* objekt){
    delete objekt;
}
