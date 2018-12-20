#include <iostream>
#include <fstream>
#include <cmath>
#include <algorithm>

class piedra {

public:
    int tipo; //2 = grande, 1 = pequeño, 0 = usada.
    int izq, der,pos;
};

int MenorDistancia(piedra *rio, int largo){
 
    int maximo = 0;
    int PosibleSalto, PosibleSalto2;
    for(int i = 0; i < largo; i++)
    {
        if (rio[i].tipo == 2) {
            if (rio[i+1].tipo == 2 && rio[i].der >= maximo) {// G --- G
                maximo = std::max(rio[i].der,maximo);
            }
            else if (rio[i+1].tipo == 1) { // G --- P 
                PosibleSalto = rio[i+1].der + rio[i+1].izq;
                if (rio[i+2].tipo == 2) {// G--P--G
                    i++;
                    maximo = std::max(PosibleSalto, maximo);
                }
                else if (rio[i+2].tipo == 1) {//G--P--P
                    i++;
                    PosibleSalto2 = rio[i+1].der + rio[i+1].izq;
                    maximo = std::max(std::min(PosibleSalto,PosibleSalto2),maximo);
                }
            }
                   
        }
        else if (rio[i].tipo == 1) { // P
            rio[i].tipo = 0;
            if (rio[i+1].tipo == 2) { // P --- G
                maximo = std::max(rio[i].izq + rio[i].der, maximo);
            }
            else if (rio[i+1].tipo == 1){ // P --- P
                PosibleSalto = rio[i].izq +  rio[i].der + rio[i+1].der;
                if (rio[i+2].tipo == 2){ // P --- P --- G
                    i++;
                    maximo = std::max(rio[i+1].izq + rio[i+1].der, maximo);
                }
                if (rio[i+2].tipo == 1){ // P --- P --- P

                	PosibleSalto2 = rio[i+2].der + rio[i+2].izq;

                	if (PosibleSalto < PosibleSalto2){
                		maximo = std::max(PosibleSalto, maximo);
                		rio[i+1].izq = rio[i+1].izq + rio[i].izq;
                	} 
                	else {

                		maximo = std::max(PosibleSalto2, maximo);
                		i++;

                	}

                }
            }


            
            
        }
        
        
    }
    return maximo;
    

}

int main(int argc, char const *argv[])
{
	if (argc < 2){
		std::cout << "No se ha pasado el nombre del input como argumento\n Intentelo otra vez\n";
	}
	else if (argc > 2){
		std::cout << "Paso muchos argumentos o el nombre contenia un espacio, si es asi ponga el nombre entre comillas\n";
	}
	else{
		std::ofstream archivo_salida;
		std::ifstream archivo_entrada;
		std::string linea;
		archivo_salida.open ("output.txt");//abrimos el archivo de salida
		archivo_entrada.open (argv[1]);//abrimos el archivo de entrada
		int Rocas, Largo, i=0, posicion;
		archivo_entrada >> Rocas;
		archivo_entrada >> Largo;
		piedra Piedritas[Rocas + 2];

		Piedritas[0].tipo = 2;
		Piedritas[0].pos = 0;
		Piedritas[0].izq = 0;
		Piedritas[Rocas + 1].der = 0;
		Piedritas[Rocas + 1].tipo = 2;
		Piedritas[Rocas + 1].pos = Largo;

		for (i = 1; i <= Rocas; i++){
			
			archivo_entrada >> linea;

			if (linea[0] == 'G') Piedritas[i].tipo = 2;
			else {
				Piedritas[i].tipo = 1;
			}

			linea.erase(0,2);
			posicion = std::stoi(linea);

			Piedritas[i].pos = posicion;
			Piedritas[i].izq = posicion - Piedritas[i-1].pos;
			Piedritas[i-1].der = Piedritas[i].izq;
			
		}

		Piedritas[Rocas + 1].izq = Largo - Piedritas[Rocas].pos;
		Piedritas[Rocas].der = Piedritas[Rocas + 1].izq;

		std::cout << MenorDistancia(Piedritas,Rocas+2) << "\n";

	return 1;

	}
}


