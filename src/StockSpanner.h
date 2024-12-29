//
// Created by cchau on 12/29/2024.
//

#ifndef PLAYGROUND_STOCKSPANNER_H
#define PLAYGROUND_STOCKSPANNER_H


#include <stack>
#include <utility>

class StockSpanner {
public:
    StockSpanner();
    int next(int price);

private:
    std::stack<std::pair<int, int>> s;
};


#endif //PLAYGROUND_STOCKSPANNER_H
