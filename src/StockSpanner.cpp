//
// Created by cchau on 12/29/2024.
//

#include "StockSpanner.h"

StockSpanner::StockSpanner() {

}

int StockSpanner::next(int price) {
    int span = 1;
    // Pop elements from the stack while the current price is higher or equal
    while (!s.empty() && s.top().first <= price) {
        span += s.top().second;
        s.pop();
    }
    // Push the current price and its span onto the stack
    s.emplace(price, span);
    return span;
}
