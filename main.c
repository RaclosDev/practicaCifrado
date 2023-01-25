#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

const int MAX_LENGTH = 80; // tamaño máximo permitido
// Matriz clave inicial
char matrizClave[6][6] = {
        {'A', 'B', 'C', 'D', 'E', 'F'},
        {'G', 'H', 'I', 'J', 'K', 'L'},
        {'M', 'N', 'O', 'P', 'Q', 'R'},
        {'S', 'T', 'U', 'V', 'W', 'X'},
        {'Y', 'Z', ' ', '1', '2', '3'},
        {'4', '5', '6', '7', '8', '9'}
};
char matrizCifrado[7][7];

//Funcion para resetear la matriz entre ejecucuciones
void resetMatrix() {
    char originalMatrix[6][6] = {
            {'A', 'B', 'C', 'D', 'E', 'F'},
            {'G', 'H', 'I', 'J', 'K', 'L'},
            {'M', 'N', 'O', 'P', 'Q', 'R'},
            {'S', 'T', 'U', 'V', 'W', 'X'},
            {'Y', 'Z', ' ', '1', '2', '3'},
            {'4', '5', '6', '7', '8', '9'}
    };

    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 6; j++) {
            matrizClave[i][j] = originalMatrix[i][j];
        }
    }
}

//Generamos una matriz nueva y le añadimos el cifrado
void generarMatrizClave(int clave) {
    resetMatrix();
    int i, j, k;
    //Crea matriz actual
    char matrizClaveFinal[6][6];
//Movemos todos
    for (k = 0; k < clave; ++k) {
        for (i = 0; i < 6; i++) {
            for (j = 0; j < 6; j++) {

                if (j == 5) {
                    matrizClaveFinal[i][j] = matrizClave[i + 1][0];
                } else {
                    matrizClaveFinal[i][j] = matrizClave[i][j + 1];
                }
            }

        }
        //asignamos el ultimo
        matrizClaveFinal[i - 1][j - 1] = matrizClave[0][0];
        //Copiamos la nueva en la clave
        for (int i = 0; i < 6; i++) {
            for (int j = 0; j < 6; j++) {
                matrizClave[i][j] = matrizClaveFinal[i][j];
            }
        }
    }

    // Crear matriz de cifrado
    for (i = 0; i < 6; i++) {
        for (j = 0; j < 6; j++) {
            matrizCifrado[i][j] = matrizClave[i][j];
        }
    }
    matrizCifrado[6][0] = 'X';
    matrizCifrado[6][1] = 'I';
    matrizCifrado[6][2] = 'F';
    matrizCifrado[6][3] = 'R';
    matrizCifrado[6][4] = 'A';
    matrizCifrado[6][5] = 'T';

    matrizCifrado[0][6] = 'N';
    matrizCifrado[1][6] = 'O';
    matrizCifrado[2][6] = 'R';
    matrizCifrado[3][6] = 'M';
    matrizCifrado[4][6] = 'A';
    matrizCifrado[5][6] = 'L';
    matrizCifrado[6][6] = ' ';
}

//Funcion para contar longitudes de textos propia
int contarLongitud(char texto[]) {
    int longitud = 0;

    for (int i = 0; texto[i] != '\0' && texto[i] != '\n'; i++) {
        longitud++;
    }
    return longitud;
}
//Funcion para pasar a mayusculas un texto mediante
void toMayus(char* texto) {
    int i = 0;
    while (texto[i]) {
        texto[i] = toupper(texto[i]);
        i++;
    }
}

//Busca las coordenadas en la matriz clave
int *buscarCoordenadas(char caracter, char matriz[6][6]) {

    int i, j;
    static int posiciones[2] = {-1, -1};

    for (i = 0; i < 6; i++) {
        for (j = 0; j < 6; j++) {
            if (matriz[i][j] == caracter) {
                posiciones[0] = i;
                posiciones[1] = j;
                return posiciones;
            }
        }
    }
    return posiciones;
}
//Busca coordenadas en la matriz con el cifrado
int *buscarCoordenadasDescifrar(char fila, char columna, char matriz[7][7]) {

    int i, j;
    static int posiciones[2] = {-1, -1};

    for (i = 0; i < 7; i++) {
        for (j = 0; j < 7; j++) {
            if (matriz[i][6] == fila && matriz[6][j] == columna) {
                posiciones[0] = i;
                posiciones[1] = j;
                return posiciones;
            }
        }
    }
    return posiciones;
}

void cifrarTexto(char texto[], char textoCifrado[]) {
    int i, j = 0;
    int longitud = contarLongitud(texto);
    for (i = 0; i < longitud; i++) {
        char caracter = texto[i];
        int *coordenadas = buscarCoordenadas(caracter, matrizClave);

        textoCifrado[j] = matrizCifrado[coordenadas[0]][6];
        j++;
        textoCifrado[j] = matrizCifrado[6][coordenadas[1]];
        j++;
    }
    textoCifrado[j] = '\0';
}

void descifrarTexto(char textoCifrado[], char textoDescifrado[]) {
    int i, j = 0;
    int longitud = contarLongitud(textoCifrado);
    for (i = 0; i < longitud; i += 2) {
        char fila = textoCifrado[i];
        char columna = textoCifrado[i + 1];
        int *coordenadas = buscarCoordenadasDescifrar(fila, columna, matrizCifrado);
        textoDescifrado[j] = matrizCifrado[coordenadas[0]][coordenadas[1]];
        j++;
    }
    for (j; j < MAX_LENGTH; j++) {
        textoCifrado[j] = '\0';
    }
}

void encripta() {
    int clave;
    char temp;
    char texto[MAX_LENGTH];
    char textoCifrado[MAX_LENGTH*2];
    printf("Introduce una clave (numero entre 0 y 35):\n");
    scanf("%d", &clave);

    generarMatrizClave(clave);

    printf("Introduce el texto a cifrar:\n");
    scanf("%*c%[^\n]", texto);
    toMayus(texto);

    cifrarTexto(texto, &textoCifrado);
    printf("Texto cifrado: %s\n", textoCifrado);
}

void desencripta() {
    int clave;
    char temp;
    char textoCifrado[MAX_LENGTH*2];
    char textoDescifrado[MAX_LENGTH];
    printf("Introduce una clave (numero entre 0 y 35):\n");
    scanf("%d", &clave);
    generarMatrizClave(clave);

    printf("Introduce el texto a cifrar:\n");
    scanf("%*c%[^\n]", textoCifrado);
    toMayus(&textoCifrado);

    descifrarTexto(textoCifrado, &textoDescifrado);
    printf("Texto descifrado: %s\n", textoDescifrado);
}

void encriptaArchivo() {
    int clave;
    char textoSinCifrar[MAX_LENGTH*2];
    char textoCifrado[MAX_LENGTH];
    char *rutaArchivoIn = "C:\\Users\\Carlos\\CLionProjects\\practicaEncriptacion\\encriptarIn.txt";
    char *rutaArchivoOut = "C:\\Users\\Carlos\\CLionProjects\\practicaEncriptacion\\encriptarOut.txt";

    printf("Introduce una clave (numero entre 0 y 35):\n");
    scanf("%d", &clave);
    generarMatrizClave(clave);

    FILE *archivoRead;
    FILE *archivoWrite;
    archivoRead = fopen(rutaArchivoIn, "r");

    if (archivoRead == NULL) {
        perror("Error al abrir el archivo\n");
    }

    bool append = false;
    while (fgets(textoSinCifrar, sizeof(textoSinCifrar), archivoRead) != NULL) {

        toMayus(&textoSinCifrar);

        if (append) {
            archivoWrite = fopen(rutaArchivoOut, "a");
        } else {
            archivoWrite = fopen(rutaArchivoOut, "w");
            append = true;
        }

        if (archivoWrite == NULL) {
            perror("Error al abrir el archivo\n");
        }
        cifrarTexto(textoSinCifrar, &textoCifrado);
        fprintf(archivoWrite, "%s", textoCifrado);
        fprintf(archivoWrite, "\n");
        fclose(archivoWrite);
    }
    fclose(archivoRead);
}

void desencriptaArchivo() {
    int clave;
    char textoSinCifrar[MAX_LENGTH*2];
    char *rutaArchivoIn = "C:\\Users\\Carlos\\CLionProjects\\practicaEncriptacion\\descifrarIn.txt";
    char *rutaArchivoOut = "C:\\Users\\Carlos\\CLionProjects\\practicaEncriptacion\\descifrarOut.txt";

    printf("Introduce una clave (numero entre 0 y 35):\n");
    scanf("%d", &clave);
    generarMatrizClave(clave);

    FILE *archivoRead;
    FILE *archivoWrite;
    archivoRead = fopen(rutaArchivoIn, "r");

    if (archivoRead == NULL) {
        perror("Error al abrir el archivo\n");
    }

    bool append = false;
    while (fgets(textoSinCifrar, sizeof(textoSinCifrar), archivoRead) != NULL) {

        toMayus(&textoSinCifrar);

        if (append) {
            archivoWrite = fopen(rutaArchivoOut, "a");
        } else {
            archivoWrite = fopen(rutaArchivoOut, "w");
            append = true;
        }

        if (archivoWrite == NULL) {
            perror("Error al abrir el archivo\n");
        }
        char textoCifrado[MAX_LENGTH];
        descifrarTexto(textoSinCifrar, &textoCifrado);
        fprintf(archivoWrite, "%s", textoCifrado);
        fprintf(archivoWrite, "\n");
        fclose(archivoWrite);
    }
    fclose(archivoRead);
}

int main() {

    int opcion;

    do {
        printf("Menu:\n");
        printf("1. Encriptar un texto que se introduce por teclado\n");
        printf("2. Desencriptar un texto que se introduce por teclado\n");
        printf("3. Encriptar un texto incluido en un archivo de texto\n");
        printf("4. Desencriptar un texto incluido en un archivo de texto\n");
        printf("5. Salir\n");
        printf("Selecciona una opcion:\n");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                printf("Has seleccionado la opcion 1: Encriptar un texto que se introduce por teclado\n");
                encripta();
                break;
            case 2:
                printf("Has seleccionado la opcion 2: Desencriptar un texto que se introduce por teclado\n");
                desencripta();
                break;
            case 3:
                printf("Has seleccionado la opcion 3: Encriptar un texto incluido en un archivo de texto\n");
                encriptaArchivo();
                break;
            case 4:
                printf("Has seleccionado la opcion 4: Desencriptar un texto incluido en un archivo de texto\n");
                desencriptaArchivo();
                break;
            case 5:
                printf("Has seleccionado la opcion 5: Salir\n");
                break;
            default:
                printf("Opcion no valida, intenta de nuevo\n");

        }
    } while (opcion != 5);

    return 1;
}
