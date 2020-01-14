#include <stdio.h>
#include "matrix.h"
#include "csv.h"
#include "mlp.h"

static void forward_pass(MLPClassifier * model);
static Matrix * compute_dW(Matrix * dZ, Matrix * Aprev);
static Matrix * compute_db(Matrix * dZ);
static Matrix * sigmoid_dZ(Matrix * A, Matrix * Y);
static Matrix * relu_dZ(Matrix * nextW, Matrix * nextdZ, Matrix * Z, float alpha);
static void backward_pass(MLPClassifier * model);
void update_params(MLPClassifier * model);

MLPClassifier * new_mlp_classifier(
    int features,
    int batch_size,
    int epochs,
    float learning_rate,
    float training_ratio,
    FILE * training_data,
    FILE * test_data
) {
    MLPClassifier * model = malloc(sizeof(MLPClassifier));

    model->layers = 0;
    model->epochs = epochs;
    model->learning_rate = learning_rate;
    model->batch_size = batch_size;
    model->training_ratio = training_ratio;
    model->training_data = training_data;
    model->test_data = test_data;

    MLPLayer * input_layer = malloc(sizeof(MLPLayer));
    input_layer->units = features;
    input_layer->A = matrix(features, batch_size);
    
    model->data = malloc(sizeof(MLPLayer *));
    model->data[0] = input_layer;

    return model;
}

MLPLayer * new_mlp_layer(
    int units,
    enum Activation act,
    float * params,
    MLPLayer * prev_layer
) {
    MLPLayer * layer = malloc(sizeof(MLPLayer));

    layer->units = units;
    layer->act = act;
    layer->params = params;

    layer->W = matrix(units, prev_layer->units);
    layer->b = matrix(units, 1);

    init_matrix_random(layer->W);
    init_matrix(layer->b, 0.0);

    return layer;
}

void add_mlp_layer(MLPClassifier * model, MLPLayer * layer) {
    model->layers++;
    model->data = realloc(model->data, (model->layers + 1) * sizeof(MLPLayer *));
    model->data[model->layers] = layer;
}

void forward_pass(MLPClassifier * model) {
    for (int i = 1; i <= model->layers; i ++) {
        //printf("layer: %d\n", i);
        MLPLayer * layer = model->data[i];

        Matrix * X = model->data[i - 1]->A; // (features, examples)
        Matrix * W = layer->W;              // (units, features)
        Matrix * b = layer->b;              // (units, 1)

        //print_matrix(W, "W:\n");
        //print_matrix(b, "b: \n");

        Matrix * Z = product(W, X);         // (units, examples)
        bump_column(Z, b);
        //print_matrix(Z, "Z:\n");

        layer->Z = Z;

        Matrix * A = matrix_copy(Z);

        if (layer->act == ACT_RELU) relu(A, layer->params[RELU_ALPHA]);
        else if (layer->act == ACT_SIGMOID) sigmoid(A);
        layer->A = A;
        
        //print_matrix(A, "A: \n");
    }
}

Matrix * compute_dW(Matrix * dZ, Matrix * Aprev) {
    Matrix * AprevT = transpose(Aprev);
    Matrix * dW = product(dZ, AprevT);

    for (int i = 0; i < dW->n; i ++)
        for (int j = 0; j < dW->m; j ++)
            dW->d[i][j] /= (float) dZ->m;

    return dW;
}

Matrix * compute_db(Matrix * dZ) {
    Matrix * db = matrix(dZ->n, 1);
    init_matrix(db, 0.0);

    for (int i = 0; i < dZ->n; i ++)
        for (int j = 0; j < dZ->m; j ++)
            db->d[i][0] += dZ->d[i][j];

    for (int i = 0; i < db->n; i ++)
        db->d[i][0] /= (float) dZ->m;

    return db;
}

Matrix * sigmoid_dZ(Matrix * A, Matrix * Y) {
    Matrix * dZ = matrix(Y->n, Y->m);

    for (int i = 0; i < Y->n; i ++)
        for (int j = 0; j < Y->m; j ++)
            dZ->d[i][j] = A->d[i][j] - Y->d[i][j];

    return dZ;
}

Matrix * relu_dZ(Matrix * nextW, Matrix * nextdZ, Matrix * Z, float alpha) {
    Matrix * nextWT = transpose(nextW);
    Matrix * dZ = product(nextWT, nextdZ);

    for (int i = 0; i < dZ->n; i ++)
        for (int j = 0; j < dZ->m; j ++)
            dZ->d[i][j] *= Z->d[i][j] > 0 ? 1 : alpha;

    return dZ;
}

void backward_pass(MLPClassifier * model) {
    for (int i = model->layers; i > 0; i --) {
        //printf("\nLayer: %d\n", i);
        MLPLayer * layer = model->data[i];
        MLPLayer * prev_layer = model->data[i - 1];

        Matrix * dZ;
        Matrix * dW;
        Matrix * db;

        if (layer->act == ACT_SIGMOID) {
           dZ = sigmoid_dZ(layer->A, layer->Y); 
        }
        else {
            MLPLayer * next_layer = model->data[i + 1];
            dZ = relu_dZ(next_layer->W, next_layer->dZ, layer->Z, layer->params[RELU_ALPHA]);
        }

        //print_matrix(dZ, "\ndZ: \n");
        dW = compute_dW(dZ, prev_layer->A);
        //print_matrix(dW, "\ndW: \n");
        db = compute_db(dZ);
        //print_matrix(db, "\ndb: \n");
        layer->dZ = dZ;
        layer->dW = dW;
        layer->db = db;
    }
}
void update_params(MLPClassifier * model) {
    for (int i = 1; i <= model->layers; i ++) {
        MLPLayer * layer = model->data[i];

        Matrix * W = layer->W;
        //print_matrix(W, "Old W: \n");
        Matrix * b = layer->b;
        Matrix * dW = layer->dW;
        Matrix * db = layer->db;

        for (int j = 0; j < W->n; j ++)
            for (int k = 0; k < W->m; k ++)
                W->d[j][k] -= model->learning_rate * dW->d[j][k];

        for (int j = 0; j < b->n; j ++)
            for (int k = 0; k < b->m; k ++)
                b->d[j][k] -= model->learning_rate * db->d[j][k];

        //print_matrix(W, "New W: \n");
    }
}

void train(MLPClassifier * model) {
    MLPLayer * input_layer = model->data[0];
    MLPLayer * output_layer = model->data[model->layers];
    output_layer->Y = matrix(output_layer->units, model->batch_size);

    float training_ratio = model->training_ratio;

    for (int e = 0; e < model->epochs; e ++) {
        printf("epoch: %d\r", e);
        csvgetline(model->training_data);

        int examples = 0;
        int batches = 1;

        while(csvgetline(model->training_data) != NULL) {
            int full_batch = (examples + 1) % model->batch_size == 0;
            int runnable_batch = batches && batches % (int)(1 / (1 - training_ratio)) != 0;

            if (runnable_batch) {
                output_layer->Y->d[0][examples] = atof(csvfield(0));

                for (int d = 1; d < csvnfield(); d ++) {
                    input_layer->A->d[d-1][examples] = atof(csvfield(d));
                }

                if (full_batch) {
                    //print_matrix(input_layer->A, "X: \n");
                    //print_matrix(output_layer->Y, "Y: \n");
                    forward_pass(model);
                    backward_pass(model);
                    update_params(model);
                }
            }
            if (full_batch) {
                batches ++;
                examples = 0;
            }
            else examples ++;
        }

        rewind(model->training_data);
    }
}

float validate(MLPClassifier * model) {
    MLPLayer * input_layer = model->data[0];
    float training_ratio = model->training_ratio;
    MLPLayer * output_layer = model->data[model->layers];

    float accuracy = 0.0;
    int samples = 0;

    int examples = 0;
    int batches = 1;

    while(csvgetline(model->training_data) != NULL) {
        int full_batch = (examples + 1) % model->batch_size == 0;
        int runnable_batch = batches && batches % (int)(1 / (1 - training_ratio)) != 0;

        if (runnable_batch) {
            output_layer->Y->d[0][examples] = atof(csvfield(0));

            for (int d = 1; d < csvnfield(); d ++) {
                input_layer->A->d[d-1][examples] = atof(csvfield(d));
            }

            if (full_batch) {
                forward_pass(model);
                for (int i = 0; i < model->batch_size; i ++) {
                    int prediction = output_layer->A->d[0][i] > 0.5;
                    int label = output_layer->Y->d[0][i] > 0.5;

                    accuracy += prediction == label;
                }
            }
        }
        if (full_batch) {
            batches ++;
            examples = 0;
        }
        else examples ++;

        samples ++;
    }

    return accuracy / (float) samples;
}

//Matrix * test(MLPClassifier * model, FILE * save_path) {
//    forward_pass(model);
//    return model->data[model->layers]->A;
//}