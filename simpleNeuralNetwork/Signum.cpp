//
// Created by andrew on 20.02.26.
//

#include "Signum.h"


double Signum::evaluate(double x) {
    if (x < 0) return -1;
    if (x > 0) return 1;
    return 0;
}
