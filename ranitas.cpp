#include <iostream>
#include <fstream>
#include <cmath>
#include <algorithm>

class piedra {

public:
    int tipo; //2 = grande, 1 = pequeño, 0 = usada.
    int izq, der;
};

int MenorDistancia(piedra *rio, int largo){
 
    int maximo = 0;
    int PosibleSalto, PosibleSalto2;
    for(int i = 0; i < largo; i++)
    {
        if (rio[i].tipo == 2) {
            if (rio[i+1].tipo == 2 && rio[i].der >= maximo) {// G --- G
                maximo = rio[i].der;
            }
            else if (rio[i+1].tipo == 1) { // G --- P 
                PosibleSalto = rio[i+1].der + rio[i+1].izq;
                if (rio[i+2].tipo == 2) {// G--P--G
                    i++;
                    maximo = std::min(PosibleSalto, maximo);
                }
                else if (rio[i+2].tipo == 1) {//G--P--P
                    i++;
                    PosibleSalto2 = rio[i+1].der + rio[i+1].izq;
                    maximo = std::min(std::min(PosibleSalto,PosibleSalto2),maximo);
                }
            }
                   
        }
        else if (rio[i].tipo == 1) {
            rio[i].tipo = 0;
            if (rio[i+1].tipo == 2) {
                maximo = std::min(rio[i].izq + rio[i].der, maximo);
            }
            else if (rio[i+1].tipo == 1){
                PosibleSalto = rio[i].izq +  rio[i].der + rio[i+1].der;
                if (rio[i+2].tipo == 2){
                    i++;
                    maximo = std::min(rio[i+1].izq + rio[i+1].der, maximo);
                }
            }


            
            
        }
        
        
    }
    

}

