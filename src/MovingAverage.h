//
// Created by cchau on 12/29/2024.
//

#ifndef PLAYGROUND_MOVINGAVERAGE_H
#define PLAYGROUND_MOVINGAVERAGE_H

#include <deque>

class MovingAverage {
private:
    int windowSize;
    std::deque<int> queue;
    int sum = 0;
public:
    MovingAverage(int size);
    double next(int val);

};


#endif //PLAYGROUND_MOVINGAVERAGE_H
