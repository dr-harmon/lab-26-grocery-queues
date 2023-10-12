#pragma once

#include "clock.h"

// Simulates a customer at a grocery store.
class Customer {
public:
    Customer() {
        startTime = 0;
        endTime = 0;
    }

    // Sets the time that the customer began waiting in line.
    void startWaiting(Time time) {
        startTime = time;
    }

    // Sets the time that the customer finished being served.
    void finishCheckout(Time time) {
        endTime = time;
    }

    // Returns the time that the customer spent waiting to be served.
    Time getWaitTime() const {
        return endTime - startTime;
    }

private:
    int startTime;
    int endTime;
};
