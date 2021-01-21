#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
    int size;
    float* weight;
    float (*normalizeFunc)(float);
    float (*adderFunc)(float*, float*, int);
} neuron;

typedef struct {
    int a;
    int b;
    neuron* layer;
    neuron** layers;
} net;

float sigmoid(float x);
float NET(float* weigth, float* feaches, int size);
float useNeu(neuron N, float* features);
float useNet(net Net, float* features);

neuron createNeu(
    int size, float (*normalizeFunc)(float), 
    float (*adderFunc)(float*, float*, int)
);

net createNet(neuron N, int a, int b);

//----------------POINTERS_OF_FUNCTIONS---------------

float (*normilizeFunc)(float);
float (*adderFunc)(float*, float*, int);

//----------------------------------------------------

int main(int argc, char* argv[]) {
    int size = 3;
    float features[] = {1.0, 1.0, 1.0};
    
    normilizeFunc = &sigmoid;
    adderFunc = &NET;

    neuron N = createNeu(size, normilizeFunc, NET);
    net Net = createNet(N, 3, 3);

    printf("%f\n", Net.layers[0][0].weight[0]);

    return 0;
}

//----------------------------------------------------

float sigmoid(float x) {
    if (x > 0.5) {
        return 1.0;
    } else return 0.0;
}

float NET(float* weigth, float* feaches, int size) {
    float net = 0;
    
    for (int i = 0; i < size; i++) {
        net += weigth[i] * feaches[i];
    }

    printf("%f\n", net);
    return net;
}

neuron createNeu(
    int size, float (*normalizeFunc)(float), 
    float (*adderFunc)(float*, float*, int)
) {
    float* weight = (float*)malloc(size*sizeof(float));
    for (int i = 0; i < size; i++) {
        weight[i] = ((float)(rand()%10))/10;
    }

    neuron N = {size, weight, normalizeFunc, adderFunc};
    return N;
}

float useNeu(neuron N, float* features) {
    float net = N.adderFunc(N.weight, features, N.size);
    printf("%f\n", net);

    return(N.normalizeFunc(net));
}

net createNet(neuron N, int a, int b) {
    neuron* layer = (neuron*)malloc(a*sizeof(neuron));
    neuron** layers = (neuron**)malloc(b*sizeof(neuron*));
    for (int i = 0; i < a; i++) {
        layer[i] = N;
    }
    for (int i = 0; i < b; i++) {
        layers[i] = layer;
    }

    net Net = {a, b, layer, layers};
    return Net;
}

float useNet(net Net, float* features) {
    
}