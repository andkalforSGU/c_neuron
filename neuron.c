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
    int layers_count;
    neuron** layers;
    neuron out_neu;
} net;

float sigmoid(float x);
float NET(float* weigth, float* feaches, int size);
float useNeu(neuron N, float* features);
float useNet(net Net, float* features);

neuron createNeu(
    int size, float (*normalizeFunc)(float), 
    float (*adderFunc)(float*, float*, int)
);

net createNet(
    neuron (*createNeu)(int size, float (*normalizeFunc)(float), 
    float (*adderFunc)(float*, float*, int)),
    int layers_count,
    int feacheres_count,
    float (*normilizeFunc)(float),
    float (*adderFunc)(float*, float*, int)
);

//----------------POINTERS_OF_FUNCTIONS---------------

float (*normilizeFunc)(float);
float (*adderFunc)(float*, float*, int);
neuron (*createNeuPoi)(
    int size, float (*normalizeFunc)(float), 
    float (*adderFunc)(float*, float*, int)
);
//----------------------------------------------------

int main(int argc, char* argv[]) {
    int size = 3;
    float features[] = {0.0, 0.0, 0.0};
    
    normilizeFunc = &sigmoid;
    adderFunc = &NET;
    createNeuPoi = &createNeu;

    net N = createNet(createNeuPoi, 3, size, normilizeFunc, adderFunc);

    float out = useNet(N, features);
    printf("%f\n", out);

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

net createNet(
    neuron (*createNeuPoi)(int size, float (*normalizeFunc)(float), 
    float (*adderFunc)(float*, float*, int)),
    int layers_count,
    int feacheres_count,
    float (*normilizeFunc)(float),
    float (*adderFunc)(float*, float*, int)
    ) {
    neuron** layers = (neuron**)malloc(layers_count*sizeof(neuron*));
    for (int i = 0; i < layers_count; i++) {
        layers[i] = (neuron*)malloc(feacheres_count*sizeof(neuron));
    }

    for (int i = 0; i < layers_count; i++) {
        for (int j = 0; j < feacheres_count; j++) {
            layers[j][i] = createNeu(feacheres_count, normilizeFunc, adderFunc);
        }
    }

    neuron out_neu = createNeu(feacheres_count, normilizeFunc, adderFunc);

    net Net = {layers_count, layers, out_neu};
    return Net;
}

float useNeu(neuron N, float* features) {
    float net = N.adderFunc(N.weight, features, N.size);

    return(N.normalizeFunc(net));
}

float useNet(net Net, float* features) {
    int marker;
    float* out_a = (float*)malloc(Net.layers[0][0].size*sizeof(float));
    float* out_b = (float*)malloc(Net.layers[0][0].size*sizeof(float));
    for (int i = 0; i < Net.layers[0][0].size; i++) {
        out_a[i] = useNeu(Net.layers[i][0], features);
    }

    for (int i = 1; i < Net.layers_count; i++) {
        for (int j = 0; j < Net.layers[0][0].size; j++) {
            if (i % 2 == 1) {
                out_b[j] = useNeu(Net.layers[j][i], out_a);
                marker = 0;
            } else if (i % 2 == 0) {
                out_a[j] = useNeu(Net.layers[j][i], out_b);
                marker = 1;
            }
        }
    }

    if (marker == 0) {
        return(useNeu(Net.out_neu, out_b));
    } else if (marker == 1) {
        return(useNeu(Net.out_neu, out_a));
    } else return 1.1;
}