#include <iostream>


#include "Perceptron.h"
#include  "PointLoader.h"
#include "Signum.h"
int main(void) {
    try {
        PointLoader loader("../trainingSet.txt");
        loader.loadPoints();
        auto trainingSet = loader.getPoints();
        loader.setPath("../testingSet.txt");
        auto testingSet = loader.getPoints();
        std::shared_ptr<IFunction> signumF = std::make_shared<Signum>("Signum");
        Perceptron perceptron(trainingSet,signumF);
        perceptron.train();
        perceptron.predict(testingSet);
        perceptron.setSeparationFunction([](double x){ return 3 * x + 2; });
        perceptron.visualize();
    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
        std::exit(EXIT_FAILURE);
    }
    std::exit(EXIT_SUCCESS);
}