#include <iostream> 
#include <windows.h> //Agregado para cambiar el color
#include <conio.h> //Para el getch...
#include <cmath> //Funciones matematicas: sqrt
#include <string>

#define ARRAY_SIZE( array ) ( sizeof( ( array ) ) / sizeof( ( array[0] ) ) )

using namespace std;

/*
	Para rellenar la parte de una tabla de verdad que contiene las proposiciones simples. 
		Ejemplo: 
			Si la tabla contiene 3 proposiciones simples ( P, Q y R ). ( cantProp = 3 ) 
				P = [V,F,V,F,V,F,V,F]
				Q = [V,V,F,F,V,V,F,F]
				R = [V,V,V,V,F,F,F,F]
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

int operadorY (int p1, int p2){
	if( p1 && p2 ){
		return true;
	} else {
		return false;
	}
}

int operadorO (int p1, int p2){
	if( p1 || p2){
		return true;
	} else {
		return false;
	}
}

int operadorEntonces (int p1, int p2){
	if ( !p1 ){
		return true;
	} else if ( p2 ){
		return true;
	} else {
		return false;
	}
}

int operadorSii (int p1, int p2){
	if ( p1 == p2 ){
		return true;
	} else {
		return false;
	}
}

int operadorOEx (int p1, int p2){
	if ( p1 != p2 ){
		return true;
	} else {
		return false;
	}
}

void llenarColumna ( bool *columna1, bool *columna2, bool *columnaResultante, int operacionLogica){
	
}

int main(int argc, char **argv){
	int cantProp = 3;
	
	//cout << " Ingrese una cantidad de proposiciones mayor a 3\n";
	// Le pido al usuario que ingrese cuantas proposiciones va a utilizar. No menos de 3 por la consigna e.e 
	/*
	while ( cantProp < 3 ){
		cout << " Cantidad de proposiciones = ";
		cin >> cantProp;
	}
	*/
	// La cantidad de combinaciones que se pueden dar es igual a  2 elevado Cantidad de Proposiciones.
		// Ejemplo: Si tenemos 3 proposiciones ( P, Q y R ) existen 2^3 combinaciones osea 8 combinaciones.
	int cantFilas = pow ( 2, cantProp );

	// Se crea la tabla.
	bool tablaDeVerdad[cantProp + 2][cantFilas];
	
	// Se establecen los valores de las proposiciones simples.
	for ( int i = 0; i < cantProp; i++){
		llenarBasicoArray( tablaDeVerdad[i] , ( i + 1 ), cantFilas);
	}
	
	
	char proposiciones[] = { 'P', 'Q', 'R'};
	// INICIO DIBUJO TABLA.
	for ( int i = 0; i < cantProp; i++){
		cout << proposiciones[i] << " | ";
	}
	
	cout << "\n---------------\n"; 
	
	for ( int y = 0; y < cantFilas; y++ ){
		for ( int x = 0; x < cantProp; x++){
			//cout << "[" << x << "][" << y << "] = \t" << tablaDeVerdad[x][y] << " | ";
			cout << tablaDeVerdad[x][y] << " | ";
		}
		cout << endl;
	}
	// FIN DIBUJO TABLA.
	
	int operador1, operador2;
	string operadoresLogicos[] = { "^", "v", "=>", "<=>", "_V_"};
	
	cout << "\n Operadores Logicos: \n";
	for ( int i = 0; i < ARRAY_SIZE(operadoresLogicos); i++){
		cout << "\n\t Operador " << operadoresLogicos[i] << "\t: " << ( i + 1);
	}
	
	cout << "\n\n Que operador desea poner entre P y Q?: ";
	cin >> operador1;
	
	cout << "\n Que operador desa poner entre ( P " << operadoresLogicos[operador1 - 1] << " Q ) y R?: ";
	cin >> operador2;
	
	cout << "\n Resultador = ( P " << operadoresLogicos[operador1 - 1] << " Q ) " << operadoresLogicos[operador2 - 1] << " R" << endl;
	
	cout << "\n\nFINNNNNNNNNNNNNNN" <<endl;
	system("pause");
	return 0;
}

/*
	Generar un programa donde dada una proposicion compuesta (de al menos 3 terminos), 
  		se indique si se trata de una tautologia, contradiccion o contingencia. 
			Las interfaces y los metodos de entrada del programa seran definidios por el grupo.
*/
