#ifndef UBERMAN_MATH_MLP_H_
#define UBERMAN_MATH_MLP_H_

#include <stdio.h>
#include "matrix.h"

typedef enum Activation {
    ACT_SIGMOID,
    ACT_RELU
} Activation;

typedef enum ACT_RELU_PARAMS {
    RELU_ALPHA
} ACT_RELU_PARAMS;

typedef struct MLPLayer {
    int units;
    Matrix * W;
    Matrix * b;
    Matrix * Z;
    Matrix * A;
    Matrix * dZ;
    Matrix * dW;
    Matrix * db;
    Matrix * Y;
    enum Activation act;
    float * params;
} MLPLayer;

typedef struct MLPClassifier {
    int batch_size;
    int epochs;
    float learning_rate;
    float training_ratio;
    float cost_cutoff;
    int layers;
    FILE * training_data;
    FILE * test_data;
    MLPLayer ** data;
} MLPClassifier;

extern MLPClassifier * new_mlp_classifier(
    int features,
    int batch_size,
    int epochs,
    float learning_rate,
    float training_ratio,
    FILE * training_data,
    FILE * test_data
);
MLPLayer * new_mlp_layer(int units, Activation act, float * params, MLPLayer * prev_layer);
extern void add_mlp_layer(MLPClassifier * model, MLPLayer * layer);
extern void train(MLPClassifier * model);
extern float validate(MLPClassifier * model);

#endif