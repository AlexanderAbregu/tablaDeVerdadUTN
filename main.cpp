#include <iostream> 
#include <windows.h> //Agregado para cambiar el color
#include <conio.h> //Para el getch...
#include <cmath> //Funciones matematicas: sqrt

using namespace std;

/*
	Para rellenar la parte de una tabla de verdad que contiene las proposiciones simples. 
		Ejemplo: 
			Si la tabla contiene 3 proposiciones simples ( P, Q y R ). ( cantProp = 3 ) 
				P = [V,F,V,F,V,F,V,F]
				Q = [V,V,F,F,V,V,F,F]
				R = [V,V,V,V,F,F,F,F]
			Como se puede ver la ultima proposicion cambia de valor cada a la mitad de la tabla
*/
int cambiarCada (int numeroProp){
	int resultado = 1;
	for (int i = 1; i < numeroProp; i++){
		resultado *= 2;
	}
	return resultado;
}
 
void llenarBasicoArray ( bool *tablaDeVerdad, int numeroProp, int cantidadFilas){	
 	bool ingresar = true;

 	int cambio  = cambiarCada(numeroProp);
 	int cantidadIngresado = 0;
 	 	
 	do{ 
 		for ( int i = 0; i < cambio; i++){
 			*(tablaDeVerdad+cantidadIngresado) = ingresar;
			cantidadIngresado++;
 		}
		ingresar = !ingresar;
	}while( cantidadIngresado < cantidadFilas );
}
   
int main(int argc, char **argv){
	int cantProp = 0;
	
	cout << " Ingrese una cantidad de proposiciones mayor a 3\n";
	// Le pido al usuario que ingrese cuantas proposiciones va a utilizar. No menos de 3 por la consigna e.e 
	while ( cantProp < 3 ){
		cout << " Cantidad de proposiciones = ";
		cin >> cantProp;
	}
	
	// La cantidad de combinaciones que se pueden dar es igual a  2 elevado Cantidad de Proposiciones.
		// Ejemplo: Si tenemos 3 proposiciones ( P, Q y R ) existen 2^3 combinaciones osea 8 combinaciones.
	int cantFilas = pow ( 2, cantProp );

	bool tablaDeVerdad[cantProp][cantFilas];
	
	for ( int i = 0; i < cantProp; i++){
		llenarBasicoArray( tablaDeVerdad[i] , ( i + 1 ), cantFilas);
	}
			
	for ( int y = 0; y < cantFilas; y++ ){
		for ( int x = 0; x < cantProp; x++){
			cout << "[" << x << "][" << y << "] = \t" << tablaDeVerdad[x][y] << " | ";
		}
		cout << endl;
	}
		
	cout << "FINNNNNNNNNNNNNNN" <<endl;
	system("pause");
	return 0;
}

/*
	Generar un programa donde dada una proposicion compuesta (de al menos 3 terminos), 
  		se indique si se trata de una tautologia, contradiccion o contingencia. 
			Las interfaces y los metodos de entrada del programa seran definidios por el grupo.
*/
