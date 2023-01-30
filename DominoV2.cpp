// Trabajo realizado por: Daniel Cobos Peñas
// DOMINO V.2

#include <iostream>
#include <stdlib.h>
#include <ctime>
#include <string>
#include <windows.h>
#include <fstream>
using namespace std;

// Defino la estructura ficha
typedef struct {
	int numIzq;
	int numDer;
} tFicha;

// PROTOTIPOS:
// Funcion que genera el pozo con las 28 fichas
void generarPozo(tFicha pozo[28]);
// Funcion que desordena el pozo
void desordenaPozo(tFicha pozo[28]);
// Funcion que muestra por pantalla el tablero y las fichas que tenemos
void mostrarTablero(string tablero, int numColocadas, int numRobadas, string ficha, int& contador);
// Funcion que devuelve la opcion seleccionada en un menu 
int mostrarMenu();
// Funcion que coge un elemento del pozo y lo convierte en la estructura de una ficha
string fichaEstructura(tFicha pozo[28], int i);
// Funcion que genera el array de string fichas del jugador
void fichas(tFicha pozo[28], string fichasJugador[28]);
// Comprueba si se puede colocar la ficha seleccionada a la izquierda del tablero
bool puedePonerIzq(string fichasJugador[28], int opcion, string tablero);
// Comprueba si se puede colocar la ficha seleccionada a la derecha del tablero
bool puedePonerDer(string fichasJugador[28], int opcion, string tablero);
// Comprueba si no hay ninguna ficha que se puede colocar, para poder permitir robar
bool puedeRobar(string fichasJugador[28], int& contador, string tablero);
// Coloca la ficha a la izquierda del tablero
string ponerFichaIzq(string fichassJugador[28], string& tablero, int opcion);
// Coloca la ficha a la derecha del tablero
string ponerFichaDer(string fichassJugador[28], string tablero, int opcion);
// Coloca todas las fichas de las que dispone el jugador 
string fichasMazo(string fichasJugador[28], int& contador);
// Elimina la ficha que justamente se coloca en el tablero
void eliminarFicha(int& numFichas, string fichasJugador[28], tFicha pozo[28], int pos);
// Invierte la ficha para que se coloque correctamente en el tablero
string giroFicha(string fichasJugador[28], int opcion);
// Con esta funcion calculamos los puntos totales que se obtienen cuando acaba la partida y quedan fichas en tu mazo
int calcularPuntos(tFicha pozo[28], int contador);
// Genera un menu cuando se elige la opcion de guardar partida
int menuGuardado();
// Con esta funcion guardamos todas las variables que forman el juego en un archivo de texto creado automaticamente y que se sobreescribe cada vez que se guarda
void partidaGuardada(string fichasJugador[28], string tablero, int numFichas, int contador, int numColocadas, int numRobadas);
// Con esta funcion cargamos la partida guardada en un archivo existente
void partidaCargada(string fichasJugador[28], string& tablero, int& numFichas, int& contador, int& numColocadas, int& numRobadas, string& ficha);

int main() {

	srand(time(0));
	// Declaracion de variables y arreglos
	tFicha pozo[28];
	string fichasJugador[28];
	// Contador nos va a servir para ver cuantas fichas tiene el usuario en la mano
	int contador = 0;
	// NumFichas nos va a servir para ver cuantas fichas tenemos tanto en el pozo como en la mano
	int numFichas = 27;
	// Nos dice cuantas fichas hemos colocado
	int numColocadas = 0;
	// Nos dice cuantas veces hemos robado
	int numRobadas = 0;

	// Desarrollo
	generarPozo(pozo);
	desordenaPozo(pozo);
	string tablero = fichaEstructura(pozo, contador);
	contador++;
	fichas(pozo, fichasJugador);
	contador = 7;
	string ficha = fichasMazo(fichasJugador, contador);
	int op, a;

	a = 0;
	while (a == 0)
	{
		// Cuando el contador es distinto de cero, es decir, el usuario dispone de fichas en la mano
		if (contador != 0)
		{
			system("cls");
			mostrarTablero(tablero, numColocadas, numRobadas, ficha, contador);
			op = mostrarMenu();

			// Opcion: colocar por la izquierda
			if (op == 1)
			{
				int opcion;
				cout << "Que ficha quiere colocar: ";
				cin >> opcion;
				if (opcion > 0 && opcion <= contador)
				{
					if (puedePonerIzq(fichasJugador, opcion, tablero) == true)
					{
						tablero = ponerFichaIzq(fichasJugador, tablero, opcion);
						eliminarFicha(numFichas, fichasJugador, pozo, opcion);
						contador--;
						ficha = fichasMazo(fichasJugador, contador);
						numColocadas++;
					}
					else
					{
						cout << "Movimiento no valido";
						Sleep(2000);
					}
				}
				else if (opcion >= contador)
				{
					cout << "No existe ninguna ficha correspondiente al valor que ha introducido";
					Sleep(2000);
				}
			}
			// Opcion = colocar por la derecha
			else if (op == 2)
			{
				int opcion;
				cout << "Que ficha quiere colocar: ";
				cin >> opcion;
				if (opcion > 0 && opcion <= contador)
				{
					if (puedePonerDer(fichasJugador, opcion, tablero) == true)
					{
						tablero = ponerFichaDer(fichasJugador, tablero, opcion);
						eliminarFicha(numFichas, fichasJugador, pozo, opcion);
						contador--;
						ficha = fichasMazo(fichasJugador, contador);
						numColocadas++;

					}
					else
					{
						cout << "Movimiento no valido";
						Sleep(2000);
					}
				}
				else if (opcion >= contador)
				{
					cout << "No existe ninguna ficha correspondiente al valor que ha introducido";
					Sleep(2000);
				}
			}
			// Opcion - robar ficha
			else if (op == 3)
			{
				if (contador < numFichas)
				{
					if (puedeRobar(fichasJugador, contador, tablero) == true)
					{
						contador++;
						ficha = fichasMazo(fichasJugador, contador);
						numRobadas++;
					}
					else if (puedeRobar(fichasJugador, contador, tablero) == false)
					{
						cout << "No puedes robar si puedes colocar alguna de tus fichas";
						Sleep(2000);
					}
				}
				else if (contador = numFichas)
				{
					cout << "Finalizando partida en 3, 2, 1 ....";
					Sleep(3000);
					int puntos = calcularPuntos(pozo, contador);
					system("cls");
					// Con esto muestro por pantalla un resumen de la partida con datos que pueden resultar interesantes al usuario
					cout << endl << "NO PODIAS COLOCAR MAS FICHAS, GAME OVER" << endl;
					cout << endl << "Resumen de partida: " << endl;
					cout << " - Fichas colocadas = " << numColocadas << endl;
					cout << " - Fichas robadas = " << numRobadas << endl;
					cout << " - Fichas restantes en tu mano = " << numFichas << endl;
					cout << " - Puntos finales de partida = " << puntos << endl;
					cout << endl << "Pulse cualquier tecla para salir" << endl;
					a = 1;
				}
				else
				{
					cout << "No tienes mas fichas disponibles";
					Sleep(2000);
				}
			}
			// opcion - guardar partida
			else if (op == 4)
			{
				system("cls");
				mostrarTablero(tablero, numColocadas, numRobadas, ficha, contador);
				int opcion;
				opcion = menuGuardado();
				switch (opcion)
				{
				case 1:
					partidaGuardada(fichasJugador, tablero, numFichas, contador, numColocadas, numRobadas);
					cout << "Partida guardada con exito";
					Sleep(1000);
					break;

				case 2:
					partidaCargada(fichasJugador, tablero, numFichas, contador, numColocadas, numRobadas, ficha);
					break;

				case 3:
					break;

				default:
					cout << "Opcion no valida";
					Sleep(1000);
				}
			}
			// Opcion - salir
			else if (op == 0)
			{
				a = 1;
			}
			else
			{
				cout << "Opcion no valida";
				Sleep(1000);
			}
		}
		// Cuando el contador llega a 0, es decir, no quedan fichas
		else if (contador == 0)
		{
			cout << "Partida finalizando en 3, 2, 1 .....";
			Sleep(3000);
			system("cls");
			// Con esto muestro por pantalla un resumen de la partida con datos que pueden resultar interesantes al usuario
			cout << endl << "ENHORABUENA, HA GANADO" << endl;
			cout << endl << "Resumen de partida: " << endl;
			cout << " - Fichas colocadas = " << numColocadas << endl;
			cout << " - Fichas robadas = " << numRobadas << endl;
			cout << " - Fichas restantes en tu mano = " << contador << endl;
			cout << " - Fichas restantes en el mazo = " << numFichas - contador << endl;
			cout << " - Su tablero ha quedado asi: " << endl << tablero << endl;
			cout << endl << "Pulse cualquier tecla para salir" << endl;
			a = 1;
		}
	}
	return 0;
}

// Con esta funcion inicializamos el array de tipo string fichasJugador
void fichas(tFicha pozo[28], string fichasJugador[28])
{
	int a = 0;
	for (a; a < 28; a++)
	{
		fichasJugador[a] = fichaEstructura(pozo, a);
	}
}

string fichasMazo(string fichasJugador[28], int& contador)
{
	int i = 1;
	string ficha;
	for (i; i <= contador; i++)
	{
		ficha = ficha + fichasJugador[i] + " ";
	}
	return ficha;
}

// Con esta funcion eliminamos de los arrays las fichas que hemos colocado
void eliminarFicha(int& numFichas, string fichasJugador[28], tFicha pozo[28], int pos)
{
	for (int i = pos; i < numFichas; i++)
	{
		fichasJugador[i] = fichasJugador[i + 1];
		pozo[i] = pozo[i + 1];
	}
	numFichas--;
}

// Con este bool comprobamos si se puede o no poner alguna ficha a la izquierda del tablero
bool puedePonerIzq(string fichasJugador[28], int opcion, string tablero)
{
	bool is_valido;

	if (fichasJugador[opcion][1] == tablero[1] || fichasJugador[opcion][3] == tablero[1])
	{
		is_valido = true;
	}
	else
	{
		is_valido = false;
	}
	return is_valido;
}


// Con esta funcion la ficha que tenemos va a girar automaticamente cuando sea necesario
string giroFicha(string fichasJugador[28], int opcion)
{
	string aux_ficha(fichasJugador[opcion].begin(), fichasJugador[opcion].end());
	reverse(aux_ficha.begin(), aux_ficha.end());
	return aux_ficha;
}


// Funcion para colocar la ficha por la izquierda
string ponerFichaIzq(string fichasJugador[28], string& tablero, int opcion)
{
	// Con estos ifs se comprueba si la ficha tiene que colocarse girada o no
	if (fichasJugador[opcion][3] == tablero[1])
	{
		string ficha = fichasJugador[opcion];
		tablero = ficha + tablero;
	}
	else if (fichasJugador[opcion][1] == tablero[1])
	{
		string ficha = giroFicha(fichasJugador, opcion);
		tablero = ficha + tablero;
	}
	return tablero;
}

// Funcion que comprueba si cualquier ficha se puede colocar a la derecha del tablero
bool puedePonerDer(string fichasJugador[28], int opcion, string tablero)
{
	bool is_valido;
	if (fichasJugador[opcion][1] == tablero[tablero.length() - 2] || fichasJugador[opcion][3] == tablero[tablero.length() - 2])
	{
		is_valido = true;
	}
	else
	{
		is_valido = false;
	}
	return is_valido;
}

// Funcion para colocar la ficha por la derecha
string ponerFichaDer(string fichasJugador[28], string tablero, int opcion)
{
	// Con estos ifs se comprueba si la ficha va a tener que colocarse girada o no
	if (fichasJugador[opcion][1] == tablero[tablero.length() - 2])
	{
		string ficha = fichasJugador[opcion];
		tablero = tablero + ficha;
	}
	else if (fichasJugador[opcion][3] == tablero[tablero.length() - 2])
	{
		string ficha = giroFicha(fichasJugador, opcion);
		tablero = tablero + ficha;
	}
	return tablero;
}

// Comprueba si puede robar ficha siempre que no coloque
bool puedeRobar(string fichasJugador[28], int& contador, string tablero)
{
	bool puedeRobar = false;
	int a = 1;
	for (a; a <= contador; a++)
	{
		if (fichasJugador[a][1] == tablero[1] || fichasJugador[a][3] == tablero[1] || fichasJugador[a][1] == tablero[tablero.length() - 2] || fichasJugador[a][3] == tablero[tablero.length() - 2])
		{
			// En cuanto haya uno que si se pueda colocar, se interrumpe el for y se retorna false
			puedeRobar = false;
			break;
		}
		else
		{
			puedeRobar = true;
		}
	}
	return puedeRobar;
}

// Genera un pozo con 28 fichas distintas
void generarPozo(tFicha pozo[28])
{
	// Generamos pozo teniendo en cuenta que no puede haber dos fichas iguales
	tFicha ficha;
	int contador = 0;
	for (ficha.numIzq = 0; ficha.numIzq <= 6; ficha.numIzq++)
	{
		for (ficha.numDer = ficha.numIzq; ficha.numDer <= 6; ficha.numDer++)
		{
			pozo[contador].numIzq = ficha.numIzq;
			pozo[contador].numDer = ficha.numDer;
			contador++;
		}
	}
}




// Esta funcion define la estructura de la ficha
string fichaEstructura(tFicha pozo[28], int i)
{
	string ficha;
	ficha = "|" + to_string(pozo[i].numIzq) + "-" + to_string(pozo[i].numDer) + "|";
	return ficha;

}

// Esta funcion muestra el tablero con sus respectivos datos
void mostrarTablero(string tablero, int numColocadas, int numRobadas, string ficha, int& contador)
{
	cout << "\n DOMINO V.2" << endl;
	cout << " ------------------ " << endl << "|     TABLERO      |" << endl << " ------------------ " << endl;
	cout << tablero << endl;
	cout << "\nFichas colocadas: " << numColocadas << endl << endl << "Fichas robadas: " << numRobadas << endl << endl;
	cout << "Tus fichas: " << endl << endl << ficha << endl;
	// Con estos bucles for hacemos que aparezca debajo de cada ficha el numero que le corresponde para que sea muy sencillo para el usuario
	for (int i = 1; i <= contador && i < 10; i++)
	{
		cout << " (" << i << ")  ";
	}
	for (int i = 10; i <= contador; i++)
	{
		cout << " (" << i << ") ";
	}
}

// Esta funcion crea el menu y retorna la opcion que has elegido de dicho menu
int mostrarMenu()
{
	int opcionvalida;
	cout << endl << "\n ------------------ " << endl << "| MENU DE OPCIONES |" << endl << " ------------------ " << endl;
	cout << "Las fichas se giraran automaticamente si se pueden colocar" << endl;
	cout << "1. Poner ficha por la izquierda" << endl;
	cout << "2. Poner ficha por la derecha" << endl;
	cout << "3. Robar ficha nueva" << endl;
	cout << "4. Guardar partida / Cargar partida" << endl;
	cout << "0. Salir" << endl << endl;
	cout << "Elija opcion: ";
	cin >> opcionvalida;
	return opcionvalida;
}

//  Desoderna el pozo
void desordenaPozo(tFicha pozo[28])
{
	// Usando el algoritmo de fisher-yates
	int idx;
	tFicha tmp;
	for (int i = 27; i >= 0; i--)
	{
		idx = rand() % (i + 1);
		if (i != idx)
		{
			tmp = pozo[i];
			pozo[i] = pozo[idx];
			pozo[idx] = tmp;
		}
	}
}

// Con esta funcion calculamos los puntos totales que se obtienen cuando acaba la partida y quedan fichas en tu mazo
int calcularPuntos(tFicha pozo[28], int contador)
{
	int puntos = 0;
	// Con este for sumamos los puntos progresivamente, ficha por ficha
	for (int i = 1; i <= contador; i++)
	{
		puntos = puntos + pozo[i].numIzq + pozo[i].numDer;
	}
	return puntos;
}

// Genera un menu cuando se elige la opcion de guardar partida
int menuGuardado()
{
	int opcionGuardado;
	cout << endl << "\n ------------------ " << endl << "| MENU DE GUARDADO |" << endl << " ------------------ " << endl;
	cout << "1. Guardar partida" << endl;
	cout << "2. Cargar anterior partida" << endl;
	cout << "3. Volver al juego" << endl;
	cout << "Elija un opcion: ";
	cin >> opcionGuardado;
	return opcionGuardado;
}

// Con esta funcion guardamos todas las variables que forman el juego en un archivo de texto creado automaticamente y que se sobreescribe cada vez que se guarda
void partidaGuardada(string fichasJugador[28], string tablero, int numFichas, int contador, int numColocadas, int numRobadas)
{
	// Creamos archivo
	ofstream archivo;
	archivo.open("guardado.txt");
	archivo << contador << endl;
	// Escribimos en el archivo las fichas de las que dispone el jugador en ese momento
	for (int i = 1; i <= contador; i++)
	{
		archivo << fichasJugador[i] << endl;
	}
	archivo << tablero << endl << numFichas << endl;
	// Escribimos en el archivo las fichas tanto de la mano como del pozo
	for (int i = 1; i <= numFichas; i++)
	{
		archivo << fichasJugador[i] << endl;
	}
	archivo << endl << numColocadas << endl << numRobadas << endl;
	archivo.close();
}

// Con esta funcion cargamos la partida guardada en un archivo existente
void partidaCargada(string fichasJugador[28], string& tablero, int& numFichas, int& contador, int& numColocadas, int& numRobadas, string& ficha)
{
	ifstream archivo;
	archivo.open("guardado.txt");
	// Si hemos creado el archivo previamente
	if (archivo.is_open())
	{
		archivo >> contador;
		// De esta forma leo las fichas que tengo en la mano
		for (int i = 1; i <= contador; i++)
		{
			archivo >> fichasJugador[i];
			ficha = fichasMazo(fichasJugador, contador);
		}
		archivo >> tablero >> numFichas; 
		// De esta forma leo todas las fichas que tengo, tanto en el mazo como en la mano
		for (int i = 1; i <= numFichas; i++)
		{
			archivo >> fichasJugador[i];
		}
		archivo >> numColocadas >> numRobadas;
		archivo.close();
	}
	else
	{
		cout << "No hay ninguna partida guardada previamente";
		Sleep(2000);
	}
}
