#include <iostream> 
#include <windows.h> //Agregado para cambiar el color
#include <conio.h> //Para el getch...
#include <cmath> //Funciones matematicas: sqrt
#include <string>

// Retorna la cantidad de elementos en el array.
#define ARRAY_SIZE( array ) ( sizeof( ( array ) ) / sizeof( ( array[0] ) ) )

using namespace std;

//Cambia el color de las letras.
void color( int X ){ 
	SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE),X); 
	/* 
		0 = Negro 
		1 = Azul 
		2 = Verde 
		3 = Aguamarina 
		4 = Rojo 
		5 = Purpura 
		6 = Amarillo 
		7 = Blanco 
		8 = Gris 
		9 = Azul claro 
	*/
}

/*
	Para rellenar la parte de una tabla de verdad que contiene las proposiciones simples. 
		Ejemplo: 
			Si la tabla contiene 3 proposiciones simples ( P, Q y R ). ( cantProp = 3 ) 
				P = [V,F,V,F,V,F,V,F]
				Q = [V,V,F,F,V,V,F,F]
				R = [V,V,V,V,F,F,F,F]
			Se puede ver que P cambia cada 1 valor, Q cada 2 y R cada 4.
		Para obtener este valor, se multiplica 1 x 2 tantas veces como indique el parametro que es igual (numero de Proposicion - 1).
			numeroProp = 2.
				1 x 2 = 2.
			numeroProp = 3.
			 	1 x 2 x 2 = 4.
		
	Recive por parametro:
	- El numero de proposicion
	
	Retorna cada cuanto tiene que cambiar su valor al llenar una columna. 
	Ejemplo:
		1 - Recibo 2. (Que podria ser la proposicion "Q")
				Retorno: 2.
			Recibo 3. ( "R" )
				Retorno: 4. 
*/
int cambiarCada (int numeroProp){
	int resultado = 1;
	for (int i = 1; i < numeroProp; i++){
		resultado *= 2;
	}
	return resultado;
}
 
/* 
	Recive por parametro: 
	- 1 columna (Array) correspondiente a una proposicion simple.
	- El numero de proposicion. Ejemplo, si tengo "P, Q y R" y yo le paso Q, este valor valdria 2.
	- La cantidad de filas que se puede decir como la cantidad de combinaciones que tiene la tabla de Verdad.
	
	Al final de esta funcion el primer parametro va a estar conformado por un orden de True y False. 
	Ejemplo:
		1 - Recibo la columna ( Array ).
		2 - El numero de proposicion es 3 ( R ).
		3 - Tiene 8 filas.
	
	Al finalizar, el array estara conformado de la siguiente manera: [1,1,1,1,0,0,0,0]
*/
void llenarBasicoArray ( bool *tablaDeVerdad, int numeroProp, int cantidadFilas){	
 	bool ingresar = true;

 	int cambio  = cambiarCada(numeroProp);
 	int cantidadIngresado = 0;
 	
 	// Se repite hasta que halla guardado tantos elementos como espacios en el Array (Columna de la tabla).
 	while( cantidadIngresado < cantidadFilas ){
 		// Se reppite hasta que sea momento de cambiar de valor de verdad.
 		for ( int i = 0; i < cambio; i++){
 			*(tablaDeVerdad+cantidadIngresado) = ingresar;
			cantidadIngresado++;
 		}
 		// Invierto el valor de verdad a guardar.
		ingresar = !ingresar;
	}
}

/* 
	Operacion Logica: Y. 
		Retorna true, si: Los dos valores son veraderos.
*/
int operadorY (int p1, int p2){
	if( p1 && p2 ){
		return true;
	} else {
		return false;
	}
}

/* 
	Operacion Logica: O. 
		Retorna true, si: Alguno de los dos valores son verdaderos.
*/
int operadorO (int p1, int p2){
	if( p1 || p2){
		return true;
	} else {
		return false;
	}
}

/* 
	Operacion Logica: Entonces. 
		Retorna true, si: El primer valor (p1) es falso ó Los dos valores (p1 y p2) son verdaderos.
*/
int operadorEntonces (int p1, int p2){
	if ( !p1 ){
		return true;
	} else if ( p2 ){
		return true;
	} else {
		return false;
	}
}

/* 
	Operacion Logica: Si y solo Si. 
		Retorna true, si los valores son iguales.
*/
int operadorSii (int p1, int p2){
	if ( p1 == p2 ){
		return true;
	} else {
		return false;
	}
}

/* 
	Operacion Logica: O exclusivo. 
		Retorna true, si los valores son distitnos.
*/
int operadorOEx (int p1, int p2){
	if ( p1 != p2 ){
		return true;
	} else {
		return false;
	}
}

/*
	Recive por parametro: 
	- 2 columnas de la tabla de verdad.
	- Columna donde almacenar el resultado de la operacion entre las dos anteriores.
	- La operacion logica que se desea realizar entre las dos columnas.
	- La cantidad de combinaciones posibles en la tabla que contiene dichas columnas.
	
	Al final de esta funcion el tercer parametro ( columnaResultante ) estara conformada por una operacion entre
		el primer parametro ( columna1 ) y el segundo ( columna2 ).
*/
void llenarColumna ( bool *columna1, bool *columna2, bool *columnaResultante, int operacionLogica, int cantidadFilas){
	for ( int i = 0; i < cantidadFilas; i++){
		switch( ( operacionLogica - 1 ) ){
			case 0: // ( P ^ Q )
				*(columnaResultante+i) = operadorY( *( columna1 + i ), *( columna2 + i ) );
				break;
			case 1: // ( P v Q )
				*(columnaResultante+i) = operadorO( *( columna1 + i ), *( columna2 + i ) );
				break;
			case 2: // ( P => Q )
				*(columnaResultante+i) = operadorEntonces( *( columna1 + i ), *( columna2 + i ) );
				break;
			case 3: // ( P <=> Q )
				*(columnaResultante+i) = operadorSii( *( columna1 + i ), *( columna2 + i ) );
				break;
			case 4: // ( P _v_ Q )
				*(columnaResultante+i) = operadorOEx( *( columna1 + i ), *( columna2 + i ) );
				break;
			default: // Por las dudas... 
				*(columnaResultante+i) = false;
				break;
		}
	}
}

/*
	Suma todos los valores de un array y en base a su resultado retorna el tipo de proposicion compuesta que es.
	Ya que los falsos son iguales a 0, y los verdaderos a 1. 
	Si la suma de todos los valores es igual al tamaño del array significa que todos son 1, por ende todos verdaderos por ende tautologia.
	Si la suma da 0 significa que todos sus valores son 0, por ende son falsos, por ende es una contradiccion.
	Si la suma es mayor a 0 pero menor a la cantidad total de elementos significa que no esta lleno ni de 1 ni de 0, por ende contingencia.
*/
string tipoProposicion ( bool *columnaFinal, int cantidadFilas){
	int resultado = 0;
	for ( int  i = 0; i < cantidadFilas; i++ ){
		resultado +=*(columnaFinal+i);
	}
	if ( resultado == 0){
		return "Contradiccion";
	} else if ( resultado >= 1 && resultado < cantidadFilas ){
		return "Contingencia";
	} else {
		return "Tautologia";
	}
}

int main(int argc, char **argv){
	color(8);
	cout<<"\t Proposicion Compuesta.\n";
	cout<<"\t ----------------------\n\n";
	cout<<"Consigna:\n";
	cout<<"---------\n";
	cout<<"\t**************************************************************************************\n";
	cout<<"\t* Generar un programa donde dada una proposicion compuesta (de al menos 3 terminos), *\n";
 	cout<<"\t* se indique si se trata de una tautologia, contradiccion o contingencia.            *\n";
 	cout<<"\t* Las interfaces y los metodos de entrada del programa seran definidos por el grupo. *\n";
 	cout<<"\t**************************************************************************************\n\n";
	
	int cantProp = 0;
	
	do{
		cout << " Cantidad de proposiciones simples ( Mayor o igual que 3 y menor o igual a 5): ";
		color(7);
		cin >> cantProp;
		color(8);
	}while( ( cantProp < 3 ) || ( cantProp > 5 ) );
	
	// La cantidad de combinaciones que se pueden dar es igual a  2 elevado Cantidad de Proposiciones.
		// Ejemplo: Si tenemos 3 proposiciones ( P, Q y R ) existen 2^3 combinaciones osea 8 combinaciones.
	int cantFilas = pow ( 2, cantProp );

	// Se crea la tabla, que en realidad es un array bidimensional.
	bool tablaDeVerdad[cantProp + 2][cantFilas];
	
	// Se establecen los valores de las proposiciones simples. (En este caso seria: P, Q, R y S.)
		// Se le pasa solo las "columnas" que contienen las proposiciones simples.
	for ( int i = 0; i < cantProp; i++ ){
		llenarBasicoArray( tablaDeVerdad[i] , ( i + 1 ), cantFilas);
	}
	
	/* 
	En esta array, se almacenara el indice de operador logico elegido entre las distintas proposiciones.
	 	Su tamaño se debe a que en este programa siempre en cantidad hay un operador logico menos la cantidad de proposiciones.
		 	Ejemplo si tenemos 4 proposiciones simples: P, Q, R y S
			 	La proposicion compuesta quedaria como: ( P ol Q ) ol ( R ol S ). ol = Algun operador logico.
	*/
	int cantidadOperadores = ( cantProp - 1 );
	
	int operadores[cantidadOperadores];
	
	// Nombre de las proposiciones simples.
	char proposiciones[] = { 'P', 'Q', 'R', 'S', 'T' };
	
	// Para representar en la consola con simbolos similares a los utilizados en Matematica Discreta.
	string operadoresLogicos[] = { "^", "v", "=>", "<=>", "_V_"};
	
	color(3);
	cout << "\n \tOperadores Logicos: \n";
	cout << "\t-------------------\n";
	for ( int i = 0; i < ARRAY_SIZE(operadoresLogicos); i++){
		cout << "\n\t\t Operador " << operadoresLogicos[i] << "\t: "; 
		color(1); 
		cout << ( i + 1 ); 
		color(3);
	}
	cout << endl;
	
	string textoOp1 = string( 1, proposiciones[0] );
	string textoOp2 = string( 1, proposiciones[1] );
	
	for ( int i = 0; i < cantidadOperadores; i++ ){
		cout << "\n Que operador logico desea poner entre ( ";
		color(1);
		cout << textoOp1;
			color(9);
			cout << " y ";
			color(1);
			cout << textoOp2;
		color(3);
		cout << " )?: ";
		
		color(1);
		cin >> operadores[i];
		color(3);
		
		textoOp1 = "( " + textoOp1 + " " + operadoresLogicos[operadores[i] - 1] + " " +textoOp2 + " )";
		
		if( ( i + 2 ) < cantProp){
			textoOp2 = proposiciones[i + 2];
		}
	}
	
	cout << "\n\n\tOperacion compuesta resultante: "; color(6); cout << textoOp1 << endl; color(3);
	cout << "\t-------------------------------" << endl;
	
	int indice = 0;
	
	for ( int i = 0; i < cantidadOperadores; i++ ){
		llenarColumna( tablaDeVerdad[indice], tablaDeVerdad[i + 1], tablaDeVerdad[cantProp + i], operadores[i], cantFilas );
		
		if ( i == 0){
			indice = cantidadOperadores;
		}
		
		indice++;
	}
	
	cout << "\n\n";
	
	for ( int y = 0; y < cantFilas; y++ ){
		cout << "\t\t";
		for ( int x = 0; x < ( ( ( 2 * cantProp ) - 1 ) ); x++){
			cout << " | " << tablaDeVerdad[x][y] << " | ";
		}
		cout << endl;
	}
	
	cout << "\n La proposiscion es una " << tipoProposicion( tablaDeVerdad[6], cantFilas ) << "." <<endl,
	
	color(8);
	cout << "\n\n(Las primeras " << cantProp << " columnas corresponden a las proposiciones simples y la ultima columna corresponde a " << textoOp1 << " ). " << endl;
	system("pause");
	return 0;
}

/*
	Generar un programa donde dada una proposicion compuesta (de al menos 3 terminos), 
  		se indique si se trata de una tautologia, contradiccion o contingencia. 
			Las interfaces y los metodos de entrada del programa seran definidios por el grupo.
*/
