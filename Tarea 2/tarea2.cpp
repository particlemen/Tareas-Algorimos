#include <iostream>
#include <fstream>
#include <cmath> 

class Avion{

public:
	float x;
	float y;

};

class Closest{

public:
	Avion A1, A2;
	float distancia;

};

Avion split(std::string strToSplit){
	Avion Avioncito;
	std::string::size_type sz;
	Avioncito.x = std::stof(strToSplit,&sz);
	Avioncito.y = std::stof(strToSplit.substr(sz));

	std::cout << "Mi X es " << Avioncito.x << " mientras que mi Y es " << Avioncito.y << ".\n";
	return Avioncito;

}

float distanciaAviones(Avion A1, Avion A2){

	return sqrt((A1.x - A2.x)*(A1.x - A2.x) + (A1.y - A2.y)*(A1.y - A2.y));

}

Closest naive(Avion *Anaive, int beg, int fin){



	int largo = fin-beg;
	Closest Min;
	Min.A1 = Anaive[0];
	Min.A2 = Anaive[1];
	Min.distancia = distanciaAviones(Anaive[0],Anaive[1]);

	for (int i = beg; i < largo; i++){
		for (int j = i+1; j < largo; j++){
			float dist = distanciaAviones(Anaive[i],Anaive[j]);
			if (dist < Min.distancia) {				
				Min.A1 = Anaive[i];
				Min.A2 = Anaive[j];
				Min.distancia = dist;
			}
		}

	}

	return Min;

}


int compareAvionX(const void* a, const void* b){

	Avion *a1 = (Avion *)a;
	Avion *a2 = (Avion *)b;
	return ((a1->x)*10 - (a2->x)*10);

}

int compareAvionY(const void* a, const void* b){

	Avion *a1 = (Avion *)a;
	Avion *a2 = (Avion *)b;
	return ((a1->y)*10 - (a2->y)*10);

}

Closest minDist(Closest A1, Closest A2){

	if (A1.distancia > A2.distancia){
		return A2;
	}
	else{
		return A1;
	}

}

Closest masCercanos(Avion *Aviones, int inicio, int fin){

	if (fin - inicio <= 3){

		Closest cercano;
		cercano = naive(Aviones,inicio,fin);
		return cercano;

	}

	int mitad = (fin - inicio)/2;

	Closest izq = masCercanos(Aviones, inicio, mitad);
	Closest der = masCercanos(Aviones, mitad+1, fin);

	int midway = (Aviones[mitad].x + Aviones[mitad+1].x)/2;

	Closest masCercano = minDist(izq,der);

	std::cout << "Mi punto medio corresponde a " << midway << " y la distancia maxima es " << masCercano.distancia <<"\n";

	Avion cercaMitad[fin-inicio];
	int j = 0;

	for (int i = inicio; i < fin; i++){
		if (abs(Aviones[i].x - midway) < masCercano.distancia){
			cercaMitad[j] = Aviones[i];
			j++;
		}
	}

	qsort(cercaMitad,j,sizeof(Avion),compareAvionY);

	for (int i = 0; i <= j; i++){
		for (int k = i+1; (k <= j) && (abs(cercaMitad[k].y - cercaMitad[i].y) < masCercano.distancia);k++){

			std::cout << "Mi i actual es " << i << " y mi k es " << k << "\n";

			float dist = distanciaAviones(cercaMitad[k],cercaMitad[i]);

			if(dist < masCercano.distancia){
				masCercano.A1 = cercaMitad[k];
				masCercano.A2 = cercaMitad[i];
				masCercano.distancia = dist;
			}
		}
	}

	return masCercano;
	
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

		while(!archivo_entrada.eof()){

			int count;
			getline(archivo_entrada, linea);
			count = std::stoi(linea);
			Avion Aviones[count];

			for(int i = 0; i < count; i++){
				getline(archivo_entrada, linea);
				Aviones[i] = split(linea);
			}

			qsort(Aviones,count,sizeof(Avion),compareAvionX);

			Closest Finito = masCercanos(Aviones,0,count);
			std::cout << "Los aviones mas cercanos son\n" << Finito.A1.x << " " << Finito.A1.y <<"\n" << Finito.A2.x << " " << Finito.A2.y <<"\n\n";

		}

		std::cout << "FIN\n";

	}
}