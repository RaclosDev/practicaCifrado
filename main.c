#include <stdio.h>
#include <string.h>
#include <malloc.h>

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

void generarMatrizClave(int clave) {
    int i;
    // Desplazar elementos de la matriz clave según la clave
    for (i = 0; i < clave; i++) {
        char ultimo = matrizClave[5][5];
        int j;
        for (j = 0; j < 5; j++) {
            matrizClave[5][j] = matrizClave[5][j + 1];
        }
        for (j = 0; j < 5; j++) {
            int k;
            for (k = 5; k > 0; k--) {
                matrizClave[k][5] = matrizClave[k - 1][5];
            }
            for (k = 0; k < 5; k++) {
                matrizClave[0][k] = matrizClave[0][k + 1];
            }
            for (k = 0; k < 5; k++) {
                matrizClave[k][0] = matrizClave[k + 1][0];
            }
        }
        matrizClave[5][5] = ultimo;
    }

    // Crear matriz de cifrado
    for (i = 0; i < 6; i++) {
        int j;
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

int contarLongitud(char texto[]) {
    int longitud = 0;

    for (int i = 0; texto[i] != '\0'; i++) {
        longitud++;
    }
    return longitud;
}

void toMayus(char texto[]) {
    int i;

    for (i = 0; texto[i] != '\0'; i++) {
        if (texto[i] >= 'a' && texto[i] <= 'z') {
            texto[i] -= 32;
        }
    }
}

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
    for (j; j < 80; j++) {
        textoCifrado[j] = '\0';
    }
}

void encripta() {
    int clave;
    char temp;
    char texto[80];
    char textoCifrado[160];
    printf("Introduce una clave (numero entre 0 y 35):\n");
    scanf("%d", &clave);
    generarMatrizClave(clave);

    printf("Introduce el texto a cifrar:\n");
    scanf("%c", &temp); //Limpiamos buffer
    scanf("%[^\n]", texto);
    toMayus(&texto);

    cifrarTexto(texto, &textoCifrado);
    printf("Texto cifrado: %s\n", textoCifrado);
}

void desencripta() {
    int clave;
    char temp;
    char textoCifrado[160];
    char textoDescifrado[80];
    printf("Introduce una clave (numero entre 0 y 35):\n");
    scanf("%d", &clave);
    generarMatrizClave(clave);

    printf("Introduce el texto a desencriptar:\n");
    scanf("%c", &temp); //Limpiamos buffer
    scanf("%[^\n]", textoCifrado);
    toMayus(&textoCifrado);


    descifrarTexto(textoCifrado, &textoDescifrado);
    printf("Texto descifrarOut: %s\n", textoDescifrado);
}

void encriptaArchivo() {
    int clave;
    char textoSinCifrar[160];
    char textoCifrado[80];
    printf("Introduce una clave (numero entre 0 y 35):\n");
    scanf("%d", &clave);
    generarMatrizClave(clave);

    toMayus(&textoSinCifrar);
    FILE *archivo;

    archivo = fopen("C:\\Users\\Carlos\\CLionProjects\\untitled5\\encriptarIn.txt", "r");

    if (archivo == NULL) {
        perror("Error al abrir el archivo\n");
    }

    while (fgets(textoSinCifrar, sizeof(textoSinCifrar), archivo) != NULL);

    fclose(archivo);
    toMayus(&textoSinCifrar);

    archivo = fopen("C:\\Users\\Carlos\\CLionProjects\\untitled5\\encriptarOut.txt", "w");

    if (archivo == NULL) {
        perror("Error al abrir el archivo\n");
    }
    cifrarTexto(textoSinCifrar, &textoCifrado);
    fprintf(archivo, "%s", textoCifrado);
    fclose(archivo);
}


void desencriptaArchivo() {
    int clave;
    char textoCifrado[160];
    char textoDescifrado[80];
    printf("Introduce una clave (numero entre 0 y 35):\n");
    scanf("%d", &clave);
    generarMatrizClave(clave);

    toMayus(&textoCifrado);
    FILE *archivo;

    archivo = fopen("C:\\Users\\Carlos\\CLionProjects\\untitled5\\descifrarIn.txt", "r");

    if (archivo == NULL) {
        perror("Error al abrir el archivo\n");
    }

    while (fgets(textoCifrado, sizeof(textoCifrado), archivo) != NULL);

    fclose(archivo);
    toMayus(&textoCifrado);

    archivo = fopen("C:\\Users\\Carlos\\CLionProjects\\untitled5\\descifrarOut.txt", "w");

    if (archivo == NULL) {
        perror("Error al abrir el archivo\n");
    }
    descifrarTexto(textoCifrado, &textoDescifrado);
    fprintf(archivo, "%s", textoDescifrado);
    fclose(archivo);
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
        printf("Selecciona una opcion: ");
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