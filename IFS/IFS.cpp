//
// Created by andrew on 4/8/26.
//

#include "IFS.h"

IFS::IFS(Point point) : point(std::move(point)),rng(std::random_device()())
{
    this->transformations.resize(4,Transformation{IFSUTILS::Matrix<double>(3,3,0.0f),Point{}});
    this->transformations.at(0).transformation = IFSUTILS::Matrix<double>(3,3,{0.00,0.00,0.01,0.00,0.26,0.00,0.00,0.00,0.05});
    this->transformations.at(1).transformation = IFSUTILS::Matrix<double>(3,3,{0.20,-0.26,-0.01,0.23,0.22,-0.07,0.07,0.00,0.24});
    this->transformations.at(2).transformation = IFSUTILS::Matrix<double>(3,3,{-0.25,0.28,0.01,0.26,0.24,-0.07,0.07,0.00,0.24});
    this->transformations.at(3).transformation = IFSUTILS::Matrix<double>(3,3,{0.85,0.04,-0.01,-0.04,0.85,0.09,0.00,0.08,0.84});

    this->transformations.at(0).translation = Point(std::vector<double>({0.00,0.00,0.00}));
    this->transformations.at(1).translation = Point(std::vector<double>({0.00,0.80,0.00}));
    this->transformations.at(2).translation = Point(std::vector<double>({0.00,0.22,0.00}));
    this->transformations.at(3).translation = Point(std::vector<double>({0.00,0.80,0.00}));

}


void IFS::run(int no_iter) {
    std::uniform_int_distribution<> dist(0,3);
    for (int i = 0; i < no_iter; i++) {
        auto& transformation = this->transformations.at(dist(rng));
        Point resPoint;
        resPoint.coords.resize(3,0);
        for (int r = 0; r < transformation.transformation.rows; ++r) {
            double res = 0.0f;
            for (int c = 0; c < transformation.transformation.cols; ++c) {
                res += transformation.transformation.at(r,c) * this->point.coords.at(c);
            }
            resPoint.coords.at(r) = res;
        }

        for (int r = 0; r < transformation.translation.coords.size(); ++r) {
            resPoint.coords.at(r) += transformation.translation.coords.at(r);
        }
        this->points.push_back(resPoint);
        this->point = resPoint;
    }
}

void IFS::visualize() {
    std::vector<double> x, y, z;
    x.reserve(this->points.size());
    y.reserve(this->points.size());
    z.reserve(this->points.size());

    for (const auto& p : this->points) {
        if (p.coords.size() >= 3) {
            x.push_back(p.coords.at(0));
            y.push_back(p.coords.at(1));
            z.push_back(p.coords.at(2));
        }
    }

    auto plt = matplot::scatter3(x, y, z);

    plt->marker_size(4.5);

    plt->marker_style(matplot::line_spec::marker_style::point);

    plt->marker_color({0.1, 0.1, 0.4});


    matplot::xlabel("X");
    matplot::ylabel("Y");
    matplot::zlabel("Z");
    matplot::title("3D IFS Fractal (25% Probabilities)");

    matplot::grid(matplot::on);
    matplot::show();
}