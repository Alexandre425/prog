#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//definição da frequência de diferentes tipos de onda

#define rad 3000000000
#define mic 3000000000000
#define inf 430000000000000
#define vis 750000000000000
#define ult 300000000000000000
#define xra 30000000000000000000


int main( void )
{

    long long int freq = 0; //variável de entrada

    //leitura da variável de entrada

    printf ("\nThis program classifies frequencies into categories.\n");
    printf ("Insert a frequency in Hz: " );
    scanf ("%lli" , &freq );

    //escolha de fazer print a um tipo de onda correspondente à frequência introduzida

    if (freq <= rad && freq < 0) {
        printf ("\nThat frequency is in the range of Radio waves.\n");
        }

    else if (freq > rad && freq <= mic) {
        printf ("\nThat frequency is in the range of Microwaves.\n");
        }

    else if (freq > mic && freq <= inf) {
        printf ("\nThat frequency is in the range of Infrared light.\n");
        }

    else if (freq > inf && freq <= vis) {
        printf ("\nThat frequency is in the range of Visible light.\n");
        }

    else if (freq > vis && freq <= ult) {
        printf ("\nThat frequency is in the range of Ultraviolet light.\n");
        }

    else if (freq > ult && freq <= xra) {
        printf ("\nThat frequency is in the range of X-rays.\n");
        }

    else if (freq > xra) {
        printf ("\nThat frequency is in the range of Gamma rays.\n");
        }
    else {
        printf("\nERROR! Value is out of bounds!\n -Make sure the frequency is a positive integer!");
    }

    return EXIT_SUCCESS;
    
}
