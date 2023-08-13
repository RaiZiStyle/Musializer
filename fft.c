#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <math.h>

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
    float out_sin[n];
    float out_cos[n];


    // Mixing two frequencies 1Hz frequence (sinf(2*pi*t*1)) with 3Hz frequence (sinf(2*pi*t*3))
    for (size_t i = 0; i < n; i++){
        float t = (float)i/n; 
        // in[i] = sinf(2*pi*t); // We add frequencie here. This is just a basic period
        // in[i] = sinf(2*pi*t*1) + cosf(2*pi*t*2); // We add other frequencies of 3Hz here
        in[i] = cosf(2*pi*t*1) + cosf(2*pi*t*2); // QUESTION : What is the diff here if we use cos ?
        in[i] = sinf(2*pi*t*1) + cosf(2*pi*t*2); // Here we mix with Cos & Sin signal
    }

    // We unmix it here.
    for (size_t f=0; f< n ; f++){
        printf("value of sample : %f\n" , in[f]);
        out_cos[f] = 0;
        out_sin[f] = 0;
        for (size_t i = 0; i < n; i++){
            float t = (float)i/n;
            out_sin[f] += in[i]*sinf(2*pi*f*t);
            out_cos[f] += in[i]*cosf(2*pi*f*t);
        }

    }
    for (size_t f=0; f< n ; f++){
        printf("%02zu : %.2f, %.2f\n" , f, out_sin[f], out_cos[f]);
    }

    return 0;
}
