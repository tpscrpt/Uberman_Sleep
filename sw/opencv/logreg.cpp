#include <opencv2/ml.hpp>

using namespace cv;
using namespace ml;
using namespace std;

static float calculateAccuracyPercent(const Mat &original, const Mat &predicted)
{
    return 100 * (float)countNonZero(original == predicted) / predicted.rows;
}

Ptr<LogisticRegression> model(float learningRate, int iterations, int miniBatchSize) {
    Ptr<LogisticRegression> logreg = LogisticRegression::create();
    
    logreg->setLearningRate(learningRate);
    logreg->setIterations(iterations);
    logreg->setMiniBatchSize(miniBatchSize);
    logreg->setTrainMethod(LogisticRegression::BATCH);
    logreg->setRegularization(LogisticRegression::REG_L2);

    return logreg;
}

int main(int, char**)
{   
    const Ptr<TrainData> trainData = TrainData::loadFromCSV("data/train_cleaned.csv",
        1, // lines to skip
        0, // index of label
        -1 // 1 response per line
    );

    trainData->setTrainTestSplitRatio(0.95);
    trainData->shuffleTrainTest();

    Ptr<LogisticRegression> logreg = model(0.0001, 100000, 100);

    logreg->train(trainData->getTrainSamples(), ROW_SAMPLE, trainData->getTrainResponses());

    logreg->predict(trainData->getTestSamples());

    return 0;
}