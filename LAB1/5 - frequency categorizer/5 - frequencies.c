#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define rad 3000000000
#define mic 3000000000000
#define inf 430000000000000
#define vis 750000000000000
#define ult 300000000000000000
#define xra 30000000000000000000


int main( void )
{

    long long int freq = 0;

    printf ("This program classifies frequencies into categories.");
    printf ("Insert a frequency in Hz:" );
    scanf ("%lli" , &freq );

    if (freq <= rad){
        printf ("That frequency is in the range of Radio waves.");
        }

    else if (freq > rad && freq <= mic) {
        printf ("That frequency is in the rande of Microwaves.");
        }

    else if (freq > mic && freq <= inf) {
        printf ("That frequency is in the range of Infrared light.");
        }

    else if (freq > inf && freq <= vis) {
        printf ("That frequency is in the range of Visible light.");
        }

    else if (freq > vis && freq <= ult) {
        printf ("That frequency is in the range of Ultraviolet light.");
        }

    else if (freq > ult && freq <= xra) {
        printf ("That frequency is in the range of X-rays.");
        }

    else if (freq > xra) {
        printf ("That frequency is in the range of Gamma rays.");
        };



    return EXIT_SUCCESS;
}
