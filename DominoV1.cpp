// Práctica del Dominó, realizada por Daniel Cobos Peñas

#include <iostream>
#include <ctime>
#include <string>
#include <stdlib.h>
#include <windows.h>
#include <algorithm>
#include <fstream>
using namespace std;

// PROTOTIPOS: 

// Creamos una funcion que nos muestre por pantalla el menu de opciones y que despues nos retorne la opcion que hemos elegido
int mostrarMenu();
// Creamos una funcion que nos genere un numero aleatorio entre el 0 y el 6 para poder generar las fichas
short int aleat(int limiteSuperior);
// Creamos una funcion que nos genere una ficha al azar, con sus dos numeros y con la forma que va a tener cada ficha
string fichaToStr(int limiteSuperior);
// Esta funcion nos muestra el tablero que va a contener todas las variables importantes
void mostrarTablero(string ficha, string tablero, int numColocadas, int numRobadas);
// Con este bool el programa va a saber si se puede o no colocar la ficha a la izquierda sin giro
bool puedePonerIzq(string tablero, string ficha);
// Con este bool el programa va a saber si se puede o no colocar la ficha a la izquierda con giro
bool puedePonerIzqGiro(string tablero, string ficha);
// Con este bool el programa va a saber si se puede o no colocar la ficha a la derecha
bool puedePonerDer(string tablero, string ficha);
// Con este bool el programa va a saber si se puede o no colocar la ficha a la derecha con giro
bool puedePonerDerGiro(string tablero, string ficha);
// Con esta funcion vamos a actualizar el tablero para que se le sume la nueva ficha por la izquierda
string ponerFichaIzq(string tablero, string ficha);
// Con esta funcion vamos a actualizar el tablero para que se le sume la nueva ficha por la derecha
string ponerFichaDer(string tablero, string ficha);
// Con esta funcion la ficha que tenemos va a girar automaticamente cuando se llame a la funcion
string giroFicha(string ficha);
// Con esta funcion generamos una nueva ficha que va a ser la que robamos (Esta funcion nos la podemos ahorrar)
string robarFicha(string fichaRobada, short int limiteSuperior);
// Con esta funcion guardamos todas las variables que forman el juego en un archivo de texto que se crea autoticamente
void partidaGuardada(string ficha, string tablero, int numColocadas, int numRobadas, int limiteSuperior);
// Con esta funcion cargamos las variables ya guardadas en el documento de texto
void partidaCargada(string& ficha, string& tablero, int& numColocadas, int& numRobadas, int& limiteSuperior);
// Genera un menu cuando se elige la opcion de guardar partida
int menuGuardado();

int main() 
{
	int a = 0;
	int limiteSuperior = 6;
	srand(time(NULL));
	string ficha = fichaToStr(limiteSuperior);
	string tablero = fichaToStr(limiteSuperior);
	int numColocadas = 0;
	int numRobadas = 0;
	int opcion;
	while (a == 0)
	{

		// Con system("cls") conseguimos borrar la consola para a continuacion volver a llamar a las funciones pero que aparezacan con las variables actualizadas
		system("cls");
		mostrarTablero(ficha, tablero, numColocadas, numRobadas);
		opcion = mostrarMenu();

		if (opcion > 5 || opcion < 0)
		{

			cout << "La opcion elegida no es valida, espere tres segundos para intentarlo de nuevo";
			Sleep(3000);

		}
		else if (opcion == 0)
		{
			return 0;
		}
		else if (opcion == 1)
		{


			if (puedePonerIzq(tablero, ficha) == true)
			{

				string nuevaFichaIzq;
				nuevaFichaIzq = ponerFichaIzq(tablero, ficha);
				numColocadas++;
				ficha = fichaToStr(limiteSuperior);
				tablero = nuevaFichaIzq;

			}
			else if (puedePonerIzqGiro(tablero, ficha) == true)
			{

				ficha = giroFicha(ficha);
				string nuevaFichaIzq;
				nuevaFichaIzq = ponerFichaIzq(tablero, ficha);
				numColocadas++;
				ficha = fichaToStr(limiteSuperior);
				tablero = nuevaFichaIzq;

			}
			else
			{
				cout << "\n No puede colocar la ficha aqui \n";
				Sleep(1000);
			}

		}
		else if (opcion == 2) 
		{


			if (puedePonerDer(tablero, ficha) == true)
			{

				string nuevaFichaDer;
				nuevaFichaDer = ponerFichaDer(tablero, ficha);
				numColocadas++;
				ficha = fichaToStr(limiteSuperior);
				tablero = nuevaFichaDer;

			}
			else if (puedePonerDerGiro(tablero, ficha) == true)
			{
				ficha = giroFicha(ficha);
				string nuevaFichaDer;
				nuevaFichaDer = ponerFichaDer(tablero, ficha);
				numColocadas++;
				ficha = fichaToStr(limiteSuperior);
				tablero = nuevaFichaDer;

			}
			else 
			{
				cout << "\n No puede colocar la ficha aqui \n";
				Sleep(1000);
			}
		}
		else if (opcion == 3)
		{

			if (puedePonerDer(tablero, ficha) == false && puedePonerIzq(tablero, ficha) == false && puedePonerIzqGiro(tablero, ficha) == false && puedePonerDerGiro(tablero, ficha) == false)
			{
				string fichaRobada;
				fichaRobada = robarFicha(fichaRobada, limiteSuperior);
				ficha = fichaRobada;
				numRobadas++;
			}
			else
			{
				cout << "\n No puede robar si su ficha puede ser jugada \n";
				Sleep(1000);
			}

		}
		else if (opcion == 4) 
		{
			int opcion = menuGuardado();
			int f = 0;
			while (f == 0) 
			{
				switch (opcion)
				{

				case 1: // Opcion de guardar partida
					partidaGuardada(ficha, tablero, numColocadas, numRobadas, limiteSuperior);
					f = 1;
					break;

				case 2: // Opcion de cargar partida

					partidaCargada(ficha, tablero, numColocadas, numRobadas, limiteSuperior);
					f = 1;
					break;

				case 3: // Opcion de volver al juego

					f = 1;
					break;


				default: //  Cualquier opcion distinta
					cout << "Por favor introduzca un numero valido: ";

				}
			}

		}
		else if (opcion == 5) 
        {
			cout << "Introduzca el numero maximo de puntos, de seis a nueve: ";
			int c = 0;
			while (c == 0) {
				cin >> limiteSuperior;
				if (limiteSuperior >= 6 && limiteSuperior <= 9)
				{
					cout << "Ha cambiado a " << limiteSuperior << "puntos";
					c = 1;
				}
				else
				{
					cout << "Porfavor introduzca un numero entre el seis y el nueve: ";
				}
			}
		}
		else 
		{
		    return 0;
		}
	}
}

// Creamos una funcion que nos muestre por pantalla el menu de opciones y que despues nos retorne la opcion que hemos elegido
int mostrarMenu()
{

	int opcionvalida;
	cout << " ------------------ " << endl << "| MENU DE OPCIONES |" << endl << " ------------------ " << endl;
	cout << "Las fichas se giraran automaticamente si se pueden colocar" << endl;
	cout << "1. Poner ficha por la izquierda" << endl;
	cout << "2. Poner ficha por la derecha" << endl;
	cout << "3. Robar ficha nueva" << endl;
	cout << "4. Guardar partida / Cargar partida" << endl;
	cout << "5. Cambie el numero maximo de puntos (de 6 a 9)" << endl;
	cout << "0. Salir" << endl << endl;
	cout << "Elija opcion: ";
	cin >> opcionvalida;
	return opcionvalida;

}

// Creamos una funcion que nos genere un numero aleatorio entre el 0 y el 6 para poder generar las fichas
short int aleat(int limiteSuperior)ç
{

	int numAleat;
	numAleat = rand() % (limiteSuperior + 1);
	return numAleat;
}

// Creamos una funcion que nos genere una ficha al azar, con sus dos numeros y con la forma que va a tener cada ficha
string fichaToStr(int limiteSuperior) 
{

	string ficha;
	ficha = "|" + to_string(aleat(limiteSuperior)) + "-" + to_string(aleat(limiteSuperior)) + "|";
	return ficha;

}

// Esta funcion nos muestra el tablero que va a contener todas las variables importantes
void mostrarTablero(string ficha, string tablero, int numColocadas, int numRobadas)
{

	cout << "\n DOMINO V.1" << endl;
	cout << " ------------------ " << endl << "|     TABLERO      |" << endl << " ------------------ " << endl;
	cout << tablero << endl;
	cout << "\nFichas colocadas: " << numColocadas << " - " << "Fichas robadas: " << numRobadas << endl;
	cout << "Tu ficha: " << ficha << endl;
}

// Con este bool el programa va a saber si se puede o no colocar la ficha a la izquierda sin giro
bool puedePonerIzq(string tablero, string ficha)
{
	if (tablero[1] == ficha[3])
	{
		return true;
	}
	else 
	{
		return false;
	}

}
// Con este bool el programa va a saber si se puede o no colocar la ficha a la izquierda con giro
bool puedePonerIzqGiro(string tablero, string ficha)
{
	if (ficha[1] == tablero[1])
	{
		return true;
	}
	else 
	{
		return false;
	}
}

// Con este bool el programa va a saber si se puede o no colocar la ficha a la derecha
bool puedePonerDer(string tablero, string ficha) 
{

	if (tablero[tablero.length() - 2] == ficha[1]) 
	{
		return true;
	}
	else 
	{
		return false;
	}
}
// Con este bool el programa va a saber si se puede o no colocar la ficha a la derecha con giro
bool puedePonerDerGiro(string tablero, string ficha) 
{
	if (tablero[tablero.length() - 2] == ficha[3])
	{
		return true;
	}
	else
	{
		return false;
	}
}

// Con esta funcion vamos a actualizar el tablero para que se le sume la nueva ficha por la izquierda
string ponerFichaIzq(string tablero, string ficha)
{
	tablero = ficha + tablero;
	return tablero;
}

// Con esta funcion vamos a actualizar el tablero para que se le sume la nueva ficha por la derecha
string ponerFichaDer(string tablero, string ficha)
{
	tablero = tablero + ficha;
	return tablero;
}

// Con esta funcion la ficha que tenemos va a girar automaticamente cuando sea necesario
string giroFicha(string ficha)
{

	string aux_ficha(ficha.begin(), ficha.end());
	reverse(aux_ficha.begin(), aux_ficha.end());
	return aux_ficha;

}

// Con esta funcion generamos una nueva ficha que va a ser la que robamos (Esta funcion nos la podemos ahorrar)
string robarFicha(string fichaRobada, short int limiteSuperior)
{

	fichaRobada = fichaToStr(limiteSuperior);
	return fichaRobada;

}

// Con esta funcion guardamos todas las variables que forman el juego en un archivo de texto automaticamente
void partidaGuardada(string ficha, string tablero, int numColocadas, int numRobadas, int limiteSuperior) 
{

	ofstream archivo;
	archivo.open("guardado.txt");
	archivo << ficha << endl << tablero << endl << numColocadas << endl << numRobadas << endl << limiteSuperior;
	archivo.close();
}

// Con esta funcion cargamos las variables ya guardadas en el documento de texto
void partidaCargada(string& ficha, string& tablero, int& numColocadas, int& numRobadas, int& limiteSuperior)
{
	ifstream archivo;
	archivo.open("guardado.txt");
	getline(archivo, ficha);
	getline(archivo, tablero);
	archivo >> numColocadas >> numRobadas >> limiteSuperior;
	archivo.close();
}

// Genera un menu cuando se elige la opcion de guardar partida
int menuGuardado()
{
	int opcionGuardado;
	cout << "\n1. Guardar partida" << endl;
	cout << "2. Cargar anterior partida" << endl;
	cout << "3. Volver al juego" << endl;
	cout << "Elija un opcion: ";
	cin >> opcionGuardado;
	return opcionGuardado;
}



