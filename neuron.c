#include <math.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int dimension;
    float* weight;
    float (*normalizeFunc)(float);
    float (*adderFunc)(float*, float*, int);
} neuron;

neuron createNeu(int dimension, float (*normalizeFunc)(float), float (*adderFunc)(float*, float*, int));
float unitJump(float x);
float adderfunc(float* weight, float* features, int dimension);

//--------------------POINTERS_TO_FUNCTIONS------------------

float (*sigm_pointer)(float);
float (*add_pointer)(float*, float*, int);

//-----------------------------------------------------------

int main(int argc, char* argv[]) {
    int dimension = 10;
    sigm_pointer = &unitJump;
    add_pointer = &adderfunc;

    neuron N;
    N = createNeu(dimension, sigm_pointer, add_pointer);

    for (int i = 0; i < dimension; i++) {
        printf("%f\n", N.weight[i]);
    }
}

//-----------------------------------------------------------

neuron createNeu(int dimension, float (*normalizeFunc)(float), float (*adderFunc)(float*, float*, int)) {
    float* weight = (float*)malloc(dimension*sizeof(float));
    for (int i = 0; i < dimension; i++){
        weight[i] = ((float)(rand()%10))/10;
    }
    neuron N = {dimension, weight, normalizeFunc, adderFunc};
    return N;
}

float unitJump(float x) {
    if (x > 0.5) {
        return 1;
    } else return 0;
}

float adderfunc(float* weight, float* features, int dimension) {
    float net = 0;

    for (int i = 0; i < dimension; i++) {
        net += weight[i] * features[i];
    }

    return net;
}