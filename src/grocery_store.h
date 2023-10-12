#pragma once

#include "clock.h"
#include "checkout_line.h"

#include <cmath>
#include <vector>

// Simulates a grocery store.
class GroceryStore {
public:
    // Initializes the grocery store.
    // numCheckoutLines: total number of lines with cashiers where customers can wait for service
    // maxLineSize: maximum number of customers that can wait in each line
    // customerArrivalTime: average period, in seconds, that customers arrive in the checkout area
    // avgServiceTime: average time, in seconds, that the cashier spends serving each customer
    GroceryStore(int numCheckoutLines, int maxLineSize, int customerArrivalTime, int avgServiceTime) {
        customersLost = 0;
        this->numCheckoutLines = numCheckoutLines;
        this->maxLineSize = maxLineSize;
        this->customerArrivalTime = customerArrivalTime;
        addCheckoutLines(avgServiceTime);
        addClockWatchers();
    }

    // Runs the simulation for the given number of seconds.
    void runSimulation(Time simulationTime) {
        while (clock.getTime() < simulationTime) {
            clock.tick();
        }
    }

    // Returns the total number of customers who were ready to checkout but left the
    // store because all lines were full.
    int getCustomersLost() {
        return customersLost;
    }

    // Returns the total number of customers who were successfully served by a cashier.
    int getCustomersServed() {
        int customersServed = 0;
        for (auto& line : checkoutLines) {
            customersServed += line.getCustomersServed();
        }
        return customersServed;
    }

    // Returns the average time that customers spent waiting to be served.
    int getAverageWaitTime() {
        int totalAverage = 0;
        for (auto& line : checkoutLines) {
            totalAverage += line.getAverageWaitTime();
        }
        return round((float)totalAverage / checkoutLines.size());
    }

private:

    // Initializes the checkout line objects.
    void addCheckoutLines(int avgServiceTime) {
        for (int i = 0; i < numCheckoutLines; i++) {
            checkoutLines.emplace_back(maxLineSize, avgServiceTime);
        }
    }

    // Configures callbacks so that actors in the simulation can be
    // notified of each clock tick.
    void addClockWatchers() {
        for (auto& line : checkoutLines) {
            clock.addWatcher( [&line](Time time){ line.tick(time); });
        }
        clock.addWatcher([this](Time time) {
            tick(time);
        });
    }

    // Indicates that a clock tick (second) has occurred. If a new customer has
    // arrived, it is added to a checkout line if poassible, otherwise it is lost.
    void tick(Time time) {
        if (customerArrived(time)) {
            if (canAddCustomer()) {
                checkoutLines[getShortestLine()].addCustomer(time);
            } else {
                customersLost++;
            }
        }
    }

    // Returns true if there is at least one line with capacity for a customer to wait.
    bool canAddCustomer() const {
        return checkoutLines[getShortestLine()].getLength() < maxLineSize;
    }

    // Returns the index (0 being the first) of the line with the shortest length.
    // Returns the first shortest line if there is more than one.
    int getShortestLine() const {
        // TODO
        return 0;
    }

    // Returns true if a customer has arrived at the given time.
    bool customerArrived(Time time) const {
        return time % customerArrivalTime == 0;
    }

    std::vector<CheckoutLine> checkoutLines;
    Clock clock;
    int customersLost;
    int numCheckoutLines;
    int maxLineSize;
    int customerArrivalTime;
};
