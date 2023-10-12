#pragma once

#include "clock.h"
#include "customer.h"
#include "queue.h"

#include <cmath>

// Simulates a checkout line at a grocery store.
class CheckoutLine {
public:
    // Initializes the checkout line.
    // maxLineSize: total number of customers that can wait in line
    // avgServiceTime: time, in seconds, that the cashier spends serving each customer
    CheckoutLine(int maxLineSize, int avgServiceTime) : queue(maxLineSize) {
        this->avgServiceTime = avgServiceTime;
        isServingCustomer = false;
        serviceTime = 0;
        customersServed = 0;
    }

    // Invoked to indicate a clock tick. Serves the next customer if the current customer
    // has been fully served, or if no customer is being served and a customer is in line.
    void tick(Time time) {
        if (isServingCustomer) {
            serviceTime++;
            if (serviceTime > avgServiceTime) {
                customersServed++;
                serveNextCustomer(time);
            }
        } else {
            serveNextCustomer(time);
        }
    }

    // Adds a new customer to the line.
    void addCustomer(Time time) {
        Customer customer;
        customer.startWaiting(time);
        queue.enqueue(customer);
    }

    // Returns the number of customers waiting (including the one being served).
    int getLength() const {
        return queue.getSize();
    }

    // Returns the total number of customers that have been served.
    int getCustomersServed() const {
        return servedCustomers.size();
    }

    // Returns the average time, in seconds, that served customers spent waiting
    // to be served.
    int getAverageWaitTime() const {
        int totalWaitTime = 0;
        for (auto& customer : servedCustomers) {
            totalWaitTime += customer.getWaitTime();
        }
        return round((float)totalWaitTime / servedCustomers.size());
    }

private:
    // Finishes serving the current customer, if any, and moves it from the line
    // to the list of served customers.
    void serveNextCustomer(Time time) {
        if (queue.isEmpty()) {
            isServingCustomer = false;
        } else {
            isServingCustomer = true;
            Customer servedCustomer = queue.dequeue();
            servedCustomer.finishCheckout(time);
            servedCustomers.push_back(servedCustomer);
            serviceTime = 0;
        }
    }

    Queue<Customer> queue;
    std::vector<Customer> servedCustomers;
    Time avgServiceTime;
    bool isServingCustomer;
    Time serviceTime;
    int customersServed;
};
