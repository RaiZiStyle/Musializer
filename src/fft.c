#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <math.h>
#include <complex.h>

float pi;



/*
Scholar implementation of the Fourier transform.

If I get it right, it used to extract specific frequencie from a base signal.
*/
int main(int argc, char const *argv[]) {

    pi = atan2f(1,1)*4;
    printf("Pi : %0f\n" , pi);
    size_t n = 8;
    float in[n];
    float complex out[n];


    // Mixing two frequencies 1Hz frequence (sinf(2*pi*t*1)) with 3Hz frequence (sinf(2*pi*t*3))
    for (size_t i = 0; i < n; i++){
        float t = (float)i/n; 
        // in[i] = sinf(2*pi*t); // We add frequencie here. This is just a basic period
        // in[i] = sinf(2*pi*t*1) + cosf(2*pi*t*2); // We add other frequencies of 3Hz here
        // in[i] = cosf(2*pi*t*1) + cosf(2*pi*t*2); // QUESTION : What is the diff here if we use cos ?
        in[i] = cosf(2*pi*t*1)  + sinf(2*pi*t*2); // Here we mix with Cos & Sin signal
    }

    // We unmix it here.
    for (size_t f=0; f< n ; f++){
        printf("value of sample : %f\n" , in[f]);
        printf("%02zu: " ,f);
        out[f] = 0;
        for (size_t i = 0; i < n; i++){
            float t = (float)i/n;
            printf(" %0.2f", sinf(2*pi*t*f));
        }
        printf("\n");

        // for (size_t i = 0; i < n; i++){
        //     float t = (float)i/n;
        //     // This is the same as  line under it
        //     out[f] += in[i]*cexp(2*I*pi*f*t);
        //     // out[f] += in[i]*sinf(2*pi*f*t);
        //     // out[f] += in[i]*cosf(2*pi*f*t);
        // }

    }
    printf("Unmixed value :\n");
    // for (size_t f=0; f< n ; f++){
    //     printf("%02zu : %.2f, %.2f\n" , f, creal(out[f]), cimag(out[f]));
    // }

    return 0;
}
