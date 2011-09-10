
===================
Vectores y punteros
===================

:Author: Maximiliano Curia
:Date:   2011.08.21

Una particularidad de C, que puede parecer poco intuitiva al principiante,
es que al utilizar el nombre de una variable de un vector en nuestro
código, C (casi siempre)[#]_ usa la dirección de memoria donde está ubicado
el vector.  Es decir, para prácticamente todos los usos, el nombre de un
vector es equivalente a un puntero.

.. [#] Excepto para sizeof, \@ y en el uso en la inicialización de un vector
       en la declaración.

Por ejemplo::

  int a[] = {1, 2, 3, 4, 5};

  printf("%p\n", a);

Imprime la posición de memoria del vector a. También::

  int *p = a; 

Es una intrucción válida, ya que C guarda la dirección de memoria de a en p.
Sin embargo, esto no quiere decir que un vector sea un puntero. ::
 
 |    +----------------+ |
 | +--| dirección de a | | p
 | v  +----------------+ | 
 | +---+---+---+---+---+ |
 | | 1 | 2 | 3 | 4 | 5 | | a
 | +---+---+---+---+---+ |
 |                       |
 | Variables locales     |
 +-----------------------+
 | Parámetros            | Llamado a función actual (f)
 | Dirección de retorno  | 
 +-----------------------+
 | . variables y         |
 | . llamados apilados   |
 | . previo a llamar a f |
 +-----------------------+
     Pila de ejecución

Además de almacenarse de forma distinta en memoria, a un vector no se le puede
cambiar su posición en memoria, por lo que::

  int b[10];
  b = a; // ESTO NO ANDA, no puedo asignarle direcciones de memoria
         // a un vector.

En una función que recibe un arreglo por parámetro, en realidad C le pasa la
dirección de memoria del vector. Por ejemplo::

  [...]
    suma(a, 5); // Al poner el nombre del arreglo, C usa la dirección de
                // memoria del arreglo
  [...]
  long suma(int *datos, int largo) // datos tendrá la dirección de memoria
                                    // del vector recibido, datos es un
                                    // puntero y no un vector
  {
    long res = 0;
    for(int i = 0; i<largo; i++) {
        res += datos[i];
    }
    return res;
  }

Por conveniencia, el "int \*datos" se puede escribir como "int datos[]", que
es la forma usual de recibir un vector en C.

En el código vemos que el puntero se usa exactamente igual que como usaríamos
el vector. Nuevamente, C usá la dirección del arreglo (incluso para el
operador "[ posición ]" ), por lo que el uso es casi identico a utilizar un
puntero.

En particular, el operador "vector[posicion]" es exactamente lo mismo que
escribir "\*(vector+posicion)" y esto funciona ya que al sumar un entero a una
dirección de memoria el entero se multiplica por el "sizeof" del tipo
apuntado (a esto último se lo suele llamar aritmética de punteros).

Parámetros de línea de comandos
-------------------------------

Se le llaman parámetros de línea de comandos a todo lo que se escriba después
del nombre del programa en la invocación de un comando. Por ejemplo::
  
  gcc hola.c -o hola

Es una forma de invocar al compilador *gcc* para que compile *hola.c* y genere el
archivo *hola*. Esto es posible, ya que el sistema operativo le pasa al gcc
los parámetros que escribió el usuario al invocarlo, de forma que::

  "gcc", "hola.c", "-o", "hola"

Son todos parámetros que recibe gcc.

En nuetro código, para recibir estos parámetros. Se utiliza, tradicionalmente,
otra firma de la función main, que es la siguiente::
  
  int main(int argc, char *argv[]);

Anteriormente vimos una firma de main, más reducida, que no recibe parámetros.
es este caso recibimos en main los parámetros de la invocación del programa.
El primer parámetro será la cantidad de parámetros que se reciben y el segundo
parámetros en un vector de punteros a char.

Cada puntero a char, es la dirección de memoria de un vector de chars.
Cómo vimos anteriormente, al recibir un vector por parámetro, en realidad, C
nos está dando una dirección de memoria a un vector, por lo que argv contiene
la dirección a esta estructura. O sea, en memoria, la estructura sería algo así::

  argv
  +-+
  | |----+                 vectores de char
  +-+    |                 terminados en un '\0'
         v                 ("cadenas" de C)
  0      +-+ dirección de  +---+---+---+----+
         | |-------------->|'g'|'c'|'c'|'\0'|
  1      +-+               +---+---+---+----+
         | |---+  +---+---+---+---+---+---+----+
  2      +-+   +->|'h'|'o'|'l'|'a'|'.'|'c'|'\0'|
         | |-+    +---+---+---+---+---+---+----+
  3      +-+ |  +---+---+----+
         ... +->|'-'|'o'|'\0'| 
  argc-1 +-+    +---+---+----+
         | |--+  +---+---+---+---+----+
         +-+  +->|'h'|'o'|'l'|'a'|'\0'|
    vector de    +---+---+---+---+----+
     char *

Notar que el nombre del comando que estamos invocando está referenciado en la
primera posición del vector de char \*.

Consideremos la diferencia con un vector de vectores de char. C requiere que cada posición del vector tenga exactamente el mismo largo (en
bytes), por lo que cada posición debe ser de un tamaño fijo, digamos que
queremos n cadenas de hasta LARGO_MAXIMO bytes. Esto lo podríamos definir
como::
  
  // Vector de n cadenas de hasta LARGO_MAXIMO (sin contar el \0)
  char cadenas[n][LARGO_MAXIMO];

En memoria, esto quedaría::

  0 1 2       LARGO_MAXIMO - 1
  +-+-+-+     +-+ 0
  | | | | ... | | 
  +-+-+-+     +-+ 1
  | | | | ... | |
  +-+-+-+     +-+ 2
  | | | | ... | |
  +-+-+-+     +-+
   . . .       .
  +-+-+-+     +-+ n - 1
  | | | | ... | |
  +-+-+-+     +-+
  cadenas

Se puede apreciar que esta estructura es bastante distinta a la que se usa
para recibir los parámetros de línea de comandos.

Por otro lado, si esta segunda estructura la quisieramos recibir por parámetro
a una función, estaremos recibiendo un puntero al tipo contenido, es decir,
sería: *char (\*datos)[LARGO_MAXIMO]*, que es lo mismo a escribir:
*char datos[][LARGO_MAXIMO]*. Por ejemplo::

  ...
  // largo máximo de cadena a utilizar.
  #define LARGO_MAXIMO 1024
  ...
  void imprimir_cadenas(char datos[][LARGO_MAXIMO], int cantidad)
  {
   ...
  }
  ...
    char cadenas[n][LARGO_MAXIMO];
    ...
    imprimir_cadenas(cadenas, n);
  ...

Notar que para recibir esta *matriz* de char hace falta que el tamaño en
bytes del tipo contenido por el vector externo esté completamente definido.

Ejemplo de recibir parámetros por línea de comandos
---------------------------------------------------

En UNIX existe un comando llamado *echo* cuya única función es imprimir todos
los parámetros que se reciben por línea de comandos. Cada parámetro se imprime
con un espacio entre parámetro y parámetro. Este sencillo programa puede
escribirse como::

  #include <stdio.h>
  
  int main(int argc, char *argv[])
  {
      if (argc > 1) {
          printf("%s", argv[1]);
      }
      for (int i=2; i<argc; i++) {
          printf(" %s", argv[i]);
      }
      printf("\n");
      return 0;
  }

Una vez compilado podría llamarse::
    
    ./echo "primer parámetro"  "segundo parámetro"   etc

Y sin importar la cantidad de espacios entre un parámetro y otro el resultado
sería: *primer parámetro segundo parámetro etc*


