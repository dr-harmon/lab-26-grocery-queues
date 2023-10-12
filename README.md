# Lab 26: Grocery Queues

[Queuing theory](https://en.wikipedia.org/wiki/Queueing_theory) is the science of queues. By modeling the behavior of queues mathematically, engineers are able to predict and optimize the behavior of:

* customer service call centers
* vehicle traffic
* orders in a warehouse
* computer data networks

and many other applications.

Sometimes it is helpful to simulate a queuing system in order to understand its behavior and make predictions about it. In this lab, we will simulate the behavior of a well-known queuing system: the grocery store. We will assume the following:

* The store has multiple checkout lines (cashiers).
* Each line can have some maximum number of customers waiting for service.
* If all lines are full, any new customer that arrives will give up and leave the store without waiting in line. ("Customer arrival" means a customer has arrived in the checkout area with items to purchase, not that the customer has just entered the store.)
* Customers who enter a line wait until the cashier is free and never leave their line or switch lines.
* Cashiers never stop serving customers. When a cashier finishes serving one customer, the next customer in line (if any) is served immediately.

A virtual clock will drive the simulation and notify all components when a "tick" occurs. The tick indicates that another second has passed and allows the simulation to operate at speeds much faster than real time.

To further simplify the lab, we will not simulate discrete events and will instead assume a fixed average rate for all events. This leads to the following assumptions:

* Customers arrive at a fixed rate (e.g. one per 30 seconds).
* Cashiers serve customers at a fixed rate (e.g. one per 90 seconds).

After running the simulation, we should be able to query it for the following:

* Total number of customers served
* Total number of customers lost (all lines full on customer arrival)
* Average time that the customers spent waiting in line

## Part 1: Queue Implementation

Instead of using the STL `std::queue`, let's write our own. It should be identical to the "informal Queue interface" of Example 5.15 in the textbook with the following exceptions:

* Custom constructor with `capacity` parameter that limits the queue size
* Change `size` to `getSize`
* Change `empty` to `isEmpty`
* Change `front` to `getFront`
* `dequeue` returns a copy of the element that was removed
* No `throw` clauses, as this grammar was removed from the C++ standard after the book was written

The underlying implementation can be anything you like. Choose your own data structure (e.g., array, vector, linked list) and private variables as you see fit.

Some unit tests have been provided for you in `queue_test.cpp`. Make sure all of them pass before continuing.

## Part 2: Completing the Simulation

Most of the simulation project has been written already, but there some key pieces missing that you must fill in.

* `CheckoutLine::addCustomer`: Creates a new customer, set its start time to `time`, and adds it to the queue.
* `CheckoutLine::serveNextCustomer`: If the queue is empty, it sets `isServingCustomer` to false. Otherwise, it should set `isServingCustomer` to true and `serviceTime` to zero, then pull a customer out of the queue, set its finish time to `time`, and add it to the `servedCustomers` list.
* `GroceryStore::getShortestLine`: Finds the index of the checkout line with the fewest number of customers waiting. (If there is more than one shortest line, the index can be any one of them.)

When you are finished, make sure all unit tests in `grocery_store_test.cpp` pass.
