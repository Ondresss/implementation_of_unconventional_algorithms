//
// Created by andrew on 20.02.26.
//

#include "Perceptron.h"
void Perceptron::visualize() {
    if (!this->separationFunction) throw std::runtime_error("Perceptron::Separation function wasnt set");

    using namespace matplot;

    std::vector<double> x_pos, y_pos;
    std::vector<double> x_neg, y_neg;

    for (const auto& p : this->predictedSet->points) {
        if (p.belongs == 1) {
            x_pos.push_back(p.coordinates[0]);
            y_pos.push_back(p.coordinates[1]);
        } else {
            x_neg.push_back(p.coordinates[0]);
            y_neg.push_back(p.coordinates[1]);
        }
    }

    auto s1 = scatter(x_pos, y_pos);
    s1->marker_face_color("blue");
    s1->display_name("Trida 1");

    hold(on);

    auto s2 = scatter(x_neg, y_neg);
    s2->marker_face_color("red");
    s2->display_name("Trida -1");


    std::vector<double> lx = linspace(-10, 10);
    std::vector<double> ly_ideal;
    for(double x : lx) {
        ly_ideal.push_back(this->separationFunction(x));
    }

    auto ideal_line = plot(lx, ly_ideal, "g--");
    ideal_line->line_width(2);
    ideal_line->display_name("Idealni separace (Lambda)");

    std::vector<double> ly_learned;
    double w1 = this->pointSet->weights[0];
    double w2 = this->pointSet->weights[1];
    double b = this->pointSet->offset;

    for(double x : lx) {
        ly_learned.push_back(-(w1 * x + b) / w2);
    }

    auto learned_line = plot(lx, ly_learned, "k-");
    learned_line->line_width(2);
    learned_line->display_name("Nauceny model");

    title("Porovnani: Skutecna separace vs. Perceptron");
    xlabel("Souradnice x");
    ylabel("Souradnice y");

    legend();

    show();
}

void Perceptron::train() {
    const double learningRate = 0.1f;
    bool change = false;
    do {
        change = false;
        for (auto& point : this->pointSet->points) {
            double sum = 0.0;
            for (int i = 0; i  < point.coordinates.size(); ++i) {
                sum += point.coordinates.at(i) * this->pointSet->weights.at(i);
            }
            sum += this->pointSet->offset;
            const double res = this->f->evaluate(sum);
            double error = point.belongs - res;
            for (int i = 0; i < this->pointSet->weights.size(); ++i) {
                double lastWeight = this->pointSet->weights.at(i);
                this->pointSet->weights.at(i) = this->pointSet->weights.at(i) + error * point.coordinates.at(i) * learningRate;
                if (lastWeight != this->pointSet->weights.at(i)) {
                    change = true;
                }
            }
            double lastOffset = this->pointSet->offset;
            this->pointSet->offset += error * 1.0 * learningRate;
            if (lastOffset != this->pointSet->offset) {
                change = true;
            }
        }
    } while (change);
}

void Perceptron::predict(std::shared_ptr<PointSet> pointSet_) {
    auto points = pointSet_->points;
    for (auto point : points) {
        double sum = 0.0f;
        for (int i = 0; i < point.coordinates.size(); ++i) {
            sum += point.coordinates.at(i) * this->pointSet->weights.at(i);
        }
        sum += this->pointSet->offset;
        const double res = this->f->evaluate(sum);
        point.belongs = static_cast<int>(res);
    }
    this->predictedSet = pointSet_;
}
