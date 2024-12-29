//
// Created by cchau on 12/29/2024.
//

#include "MovingAverage.h"

MovingAverage::MovingAverage(int size) : windowSize(size) {}

double MovingAverage::next(int val) {
    queue.push_back(val);
    if (queue.size() > windowSize) {
        sum -= queue.front();
        queue.pop_front();
    }
    sum += val;

    return static_cast<double>(sum) / (int)queue.size();
}


