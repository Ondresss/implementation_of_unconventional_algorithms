#include <iostream>
#include <vector>
#include <memory>
#include "Perceptron.h"
#include "Sigmoid.h"
#include "NeuralNetwork.h"

int main() {
    try {
        auto sigmoid = std::make_shared<Sigmoid>("sigmoid");

        std::vector<Point> trainingData = {
            Point({0.0, 0.0}, 0.0),
            Point({1.0, 0.0}, 1.0),
            Point({0.0, 1.0}, 1.0),
            Point({1.0, 1.0}, 0.0)
        };

        std::vector<std::shared_ptr<Perceptron>> hiddenLayer;
        for(int i = 0; i < 2; ++i) {
            hiddenLayer.push_back(std::make_shared<Perceptron>(sigmoid));
        }
        auto outputNeuron = std::make_shared<Perceptron>(sigmoid);
        NeuralNetwork nn(trainingData, hiddenLayer, outputNeuron);
        std::cout << "---------------------------- Before learning phase ----------------------------\n"  << std::endl;
        nn.init();
        std::cout << "-------------------------------------------------------------------------------\n"  << std::endl;
        std::cout << "---------------------------- After learning phase -----------------------------\n"  << std::endl;
        nn.train(100000);
        std::cout << "-------------------------------------------------------------------------------\n"  << std::endl;
        std::cout << "---------------------------- After testing phase-------------------------------\n" << std::endl;
        nn.test(trainingData);
        std::cout << "-------------------------------------------------------------------------------\n"  << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Chyba: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}