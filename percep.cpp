#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

class Perceptron {
private:
    std::vector<double> weights;
    double learningRate;

public:
    Perceptron(int numInputs, double lr) : learningRate(lr) {
        // Initialize weights with random values between -1 and 1
        srand(time(nullptr));
        for (int i = 0; i < numInputs; ++i) {
            double weight = static_cast<double>(rand()) / RAND_MAX * 2 - 1;
            weights.push_back(weight);
        }
    }

    int activate(std::vector<double> inputs) {
        double sum = 0;
        for (int i = 0; i < inputs.size(); ++i) {
            sum += inputs[i] * weights[i];
        }
        if (sum > 0) {
            return 1;
        } else {
            return -1;
        }
    }

    void train(std::vector<std::vector<double>> trainingData, std::vector<int> labels, int numEpochs) {
        for (int epoch = 0; epoch < numEpochs; ++epoch) {
            for (int i = 0; i < trainingData.size(); ++i) {
                std::vector<double> inputs = trainingData[i];
                int predicted = activate(inputs);
                int label = labels[i];
                double error = label - predicted;
                for (int j = 0; j < weights.size(); ++j) {
                    weights[j] += learningRate * error * inputs[j];
                }
            }
        }
    }
};

int main() {
    // Define training data and labels
    std::vector<std::vector<double>> trainingData = {{0, 0}, {0, 1}, {1, 0}, {1, 1}};
    std::vector<int> labels = {-1, -1, -1, 1};

    // Create a perceptron with 2 inputs and a learning rate of 0.1
    Perceptron perceptron(2, 0.1);

    // Train the perceptron for 1000 epochs
    perceptron.train(trainingData, labels, 1000);

    // Test the perceptron
    std::cout << "Testing perceptron:" << std::endl;
    for (int i = 0; i < trainingData.size(); ++i) {
        int predicted = perceptron.activate(trainingData[i]);
        std::cout << "Input: " << trainingData[i][0] << ", " << trainingData[i][1]
                  << " Predicted: " << predicted << std::endl;
    }

    return 0;
}
