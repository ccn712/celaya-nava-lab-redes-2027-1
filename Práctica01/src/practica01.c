// Redes de computadoras - Práctica 01
// Celaya Nava Carlos Adrián
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Simula la codificación de un bit a una señal física (Voltaje)
void transmitir_bit_nrz(int bit) {
    if (bit == 1) {
        printf("[+5V]"); // Bit 1 representado por voltaje alto
    } else {
        printf("[-5V]"); // Bit 0 representado por voltaje alto
    }
}

// Conversión de caracteres
int main() {
    //Arreglo destinado a almacenar el texto proporcionado por el usario
    char texto[100];

    // Obtención del texto dado por el usuario
    printf("Introduce un texto para transmitir:");
    fgets(texto, sizeof(texto), stdin);

    // Inicializa el generador de números "aleatorios"
    srand(time(NULL));

    // Probabilidad de ruido
    // Se dividió entre 10 ya que, de no hacerlo, la mayoría de las veces el mensaje se distorsionaba.
    // Tras la división, se logró un mayor balance entre transmisiones favorables y distorsionadas. 
    double prob_ruido = ((double)rand() / RAND_MAX) / 10;
    printf("Probabilidad de ruido en el canal: %f\n", prob_ruido);

    printf("1. Procesamiento de bits y voltajes.\n");

    for (int i = 0; texto[i] != '\0'; i++) {
        // Caracter actual del texto
        unsigned char c = texto[i];
        // Variable utilizada para recorrer los bits de cada caracter
        int bit_actual = -1;

        //Se ignora el caracter final indepentiente del texto
        if (c == '\n')
            continue;

        // Caracter actual mostrado literalmente y como su número ASCII
        printf("Caracter '%c' (ASCII %d):\n", c, c);

        // Desglose en bits
        printf("Bits originales:");
        for (int j = 7; j >= 0; j--) {
            bit_actual = (c >> j) & 1; // Sacamos el bit j
            printf("%d", bit_actual); // Se muestra cada bit de forma continua
        }
        
        printf("\n");

        // Representación de los bits en forma de voltaje
        printf("Señal física: ");
        for (int k = 7; k >= 0; k--) {
            bit_actual = (c >> k) & 1; // Sacamos el bit k
            transmitir_bit_nrz(bit_actual); // Se aplica la función facilitada en el PDF para representar los voltajes de forma continua
        }
        printf("\n\n");

        // Posibilidad de que ocurra un bit-flip dada la probabilidad de ruido
        for (int l = 7; l >= 0; l--) {
            // Ruido "real"
            double ruido = (double)rand() / RAND_MAX;
            // Si el "ruido real" coincide con la probabilidad, se produce un bit-flip
            if (ruido <= prob_ruido)
                texto[i] ^= (1 << l); // Bit-flip emulado mediante la operación XOR sobre un corrimiento de 'l' bits
        }

    }

    printf("2. Simulación de transmisión con ruido\n");
    printf("Texto recibido: %s\n", texto);

    return 0;
}