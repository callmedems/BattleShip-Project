// directivas de procesamiento
#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Constantes para la representación de las celdas
const char BARCO = 'X';
const char AGUA = ' ';

// Clase que representa un tablero de batalla
class Tablero {
private:
  // mapa que contendrá las posiciones de los barcos
  vector<vector<char>> mapa;

  // mapa de #, que verá el usuario para no ver los barcos
  vector<vector<char>> mapaVisible;
  int contador = 0; // contador para saber el ganador

public:
  // se inicializa constructor de tablero
  Tablero(int filas, int columnas) {
    mapa.resize(
        filas, vector<char>(columnas,
                            AGUA)); // se llena de las constantes de agua el mapa
    mapaVisible.resize(filas, vector<char>(columnas, '#')); // se llena con #
  }

  // método para crear los Barcos de los jugadores
  void ubicarBarco(int fila, int columna, char tipoBarco) {
    mapa[fila][columna] = tipoBarco;
  }

  // método para saber si el jugador adivinó la coordenada de un barco
  void disparar(int fila, int columna) {
    if (mapaVisible[fila][columna] == '#') {
      mapaVisible[fila][columna] = mapa[fila][columna];

      // si la 'celda' es un barco, se imprime hit y se suma al contador del
      // jugador
      if (mapa[fila][columna] == BARCO) {
        cout << "\n¡Hit!" << endl;
        contador++;
      }

      // si el usuario ingresó una coordenada no posible, o ya disparó a esa
      // posición
    } else {
      cout << "No se pudo hacer daño. " << endl;
    }
  }

  // para mostrar el mapa
  void mostrarMapa() {
    cout << "\n";
    for (int i = 0; i < mapa.size(); i++) {
      for (int j = 0; j < mapa[i].size(); j++) {
        cout << mapaVisible[i][j] << " ";
      }
      cout << endl;
    }
    cout << "\n";
  }

  // por si un jugador hunde todos los barcos enemigos, el bucle del juego se
  // rompe porque ahora es true
  bool todoHundido() { return (contador == 3); }
};

// clase de Jugadores para obtener sus nombres
class Jugadores {
public:
  string nombre1;
  string nombre2;

  // Constructor
  Jugadores() {
    cout << "Ingrese el nombre del jugador 1: ";
    cin >> nombre1;
    cout << "Ingrese el nombre del jugador 2: ";
    cin >> nombre2;
  }
};

// clase de Naves, para obtener las coordenadas de los barcos
class Naves {
public:
  int x;
  int y;
  int b;
  int a;

  // Constructor
  Naves() {
    x = 0;
    y = 0;
    b = 0;
    a = 0;
  }
  // para el ingreso de las coordenadas
  void ingresarCoordenadas() {
    cout << "Ingrese la posición x: ";
    cin >> x;
    cout << "Ingrese la posición y: ";
    cin >> y;
    // se le resta -1 a las variables debido a que en c++ se contabiliza desde
    // el 0, y se le pide al usuario ingresar datos de 1 al 5 en un tablero que
    // va de 0 a 4.
    a = x - 1;
    b = y - 1;
    x = a;
    y = b;
  }
};

// clase referi para anunciar al jugador ganador
class Referi {
public:
  // función que anuncia al ganador
  void anunciarGanador(string jugador) {
    cout << "¡Felicidades, " << jugador << " ha ganado el juego!" << endl;
  }
};

// clase juego para explicar las reglas a los jugadores
class Juego {
public:
  // bienvenida
  void bienvenida() {
    cout << "\nBienvenido al juego de Batalla Naval.\nEl juego consiste en "
            "adivinar la ubicación de los barcos enemigos en un tablero de "
            "5x5. ¡Buena suerte!\n"
         << endl;
  }
  // las reglas
  void explicarReglas() {
    cout << "Las reglas del juego son las siguientes:" << endl;
    cout << "1. Cada jugador tiene un turno para adivinar la ubicación de un "
            "barco enemigo."
         << endl;
    cout << "2. Si el jugador adivina correctamente la ubicación de un barco "
            "enemigo, ese barco será destruido."
         << endl;
    cout << "3. El juego continúa hasta que un jugador haya destruido todos "
            "los barcos enemigos."
         << endl;
    cout << "4. El jugador que destruya primero todos los barcos enemigos es "
            "declarado ganador."
         << endl;
    cout << "5. Como ya se mencionó, los tableros son de 5x5, por lo que al "
            "ingresar coordenadas, son del 1 al 5, ejemplo (2,3) No ingresar "
            "números menores a 1 o mayores a 5.\n"
         << endl;
  }
};

// función principal
int main() {

  // se crean objetos
  Jugadores jugadores; // se piden los nombres a los jugadores
  Referi referi;
  Juego juego;

  // se explica el juego al usuario
  juego.bienvenida();
  juego.explicarReglas();

  // se inicia el juego, y se crean los tableros de los jugadores
  Tablero tableroJugador1(5, 5);
  Tablero tableroJugador2(5, 5);

  // Se piden las coordenadas de los barcos al jugador 1
  for (int i = 0; i < 3; i++) {
    cout << jugadores.nombre1 << ", ingresa las coordenadas del barco " << i + 1
         << endl;
    Naves naves1;                 // se crea un objeto de la clase de Naves
    naves1.ingresarCoordenadas(); // se llama a la función
    tableroJugador1.ubicarBarco(naves1.x, naves1.y, BARCO);
  }

  cout << "\n";

  // Se piden las coordenadas de los barcos al jugador 2
  for (int i = 0; i < 3; i++) {
    cout << jugadores.nombre2 << ", ingresa las coordenadas del barco " << i + 1
         << endl;
    Naves naves2; //
    naves2.ingresarCoordenadas();
    tableroJugador2.ubicarBarco(naves2.x, naves2.y, BARCO);
  }

  bool partidaFinalizada = false; // no se ha finalizado la partida
  while (!partidaFinalizada) { // mientras partidaFinalizada sea falsa, el bucle
                               // sigue
    tableroJugador1.mostrarMapa();
    cout << jugadores.nombre1 << ", ingresa la posición para disparar: " << endl;
    int fila, columna;
    cin >> fila >> columna;
    // se le resta -1 a las variables debido a que en c++ se contabiliza desde
    // el 0, y se le pide al usuario ingresar datos de 1 al 5 en un tablero que
    // va de 0 a 4.
    int a, b;
    a = fila - 1;
    b = columna - 1;
    fila = a;
    columna = b;
    tableroJugador2.disparar(
        fila, columna); // se llama a la función disparar de Tablero

    if (tableroJugador2.todoHundido()) {
      partidaFinalizada = true;
      referi.anunciarGanador(
          jugadores.nombre1); // se llama a la función anunciarGanador de la
                              // clase Referi
    } else {
      tableroJugador2.mostrarMapa();
      cout << jugadores.nombre2 << ", ingresa la posición para disparar: " << endl;
      cin >> fila >> columna;
      int a, b;
      a = fila - 1;
      b = columna - 1;
      fila = a;
      columna = b;
      tableroJugador1.disparar(fila, columna);

      if (tableroJugador1.todoHundido()) {
        partidaFinalizada = true;
        referi.anunciarGanador(jugadores.nombre2);
      }
    }
  }

  return 0;
}