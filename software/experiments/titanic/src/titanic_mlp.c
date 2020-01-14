#include "mlp.h"
#include <stdio.h>
#include <time.h>

int main() {
    FILE * training_data = fopen("experiments/titanic/output/train_cleaned.csv", "r");
    FILE * test_data = fopen("experiments/titanic/output/test_cleaned.csv", "r");

    int features = 6;
    int batch_size = 14;
    int epochs = 100000;
    float learning_rate = 0.01;
    float training_ratio = 0.8;

    MLPClassifier * model = new_mlp_classifier(
        features,
        batch_size,
        epochs,
        learning_rate,
        training_ratio,
        training_data,
        test_data
    );

    float alpha = 0.01;
    float params[1];
    params[RELU_ALPHA] = alpha;

    MLPLayer * layer_1 = new_mlp_layer(1, ACT_RELU, params, model->data[0]);
    add_mlp_layer(model, layer_1);
 
    //MLPLayer * layer_2 = new_mlp_layer(4, ACT_RELU, params, layer_1);
    //add_mlp_layer(model, layer_2);

    MLPLayer * output_layer = new_mlp_layer(1, ACT_SIGMOID, NULL, layer_1);
    add_mlp_layer(model, output_layer);

    train(model);
    float accuracy = validate(model);
    print_matrix(model->data[model->layers]->A, "Predictions: \n");
    print_matrix(model->data[1]->W, "W of first layer: \n");
    printf("Accuracy on dev data: %f\n", accuracy);
}