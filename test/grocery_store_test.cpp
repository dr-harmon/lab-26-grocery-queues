#include <catch2/catch_test_macros.hpp>
#include <catch2/benchmark/catch_benchmark_all.hpp>

#include "grocery_store.h"

using namespace std;

TEST_CASE("Single line: No customers lost")
{
	const int NUM_CHECKOUT_LINES = 1;
	const int MAX_LINE_SIZE = 3;
	const int CUSTOMER_ARRIVAL_PERIOD = 6;
	const int AVG_SERVICE_TIME = 2;
	const int SIMULATION_TIME = 20;
	GroceryStore store(NUM_CHECKOUT_LINES, MAX_LINE_SIZE, CUSTOMER_ARRIVAL_PERIOD, AVG_SERVICE_TIME);
	store.runSimulation(SIMULATION_TIME);
    REQUIRE(store.getCustomersLost() == 0);
    REQUIRE(store.getCustomersServed() == 3);
    REQUIRE(store.getAverageWaitTime() == 1);
}

TEST_CASE("Single line: Some customers lost")
{
	const int NUM_CHECKOUT_LINES = 1;
	const int MAX_LINE_SIZE = 3;
	const int CUSTOMER_ARRIVAL_PERIOD = 3;
	const int AVG_SERVICE_TIME = 8;
	const int SIMULATION_TIME = 20;
	GroceryStore store(NUM_CHECKOUT_LINES, MAX_LINE_SIZE, CUSTOMER_ARRIVAL_PERIOD, AVG_SERVICE_TIME);
	store.runSimulation(SIMULATION_TIME);
    REQUIRE(store.getCustomersLost() == 1);
    REQUIRE(store.getCustomersServed() == 2);
    REQUIRE(store.getAverageWaitTime() == 4);
}

TEST_CASE("Multiple lines: No customers lost")
{
	const int NUM_CHECKOUT_LINES = 2;
	const int MAX_LINE_SIZE = 3;
	const int CUSTOMER_ARRIVAL_PERIOD = 3;
	const int AVG_SERVICE_TIME = 8;
	const int SIMULATION_TIME = 20;
	GroceryStore store(NUM_CHECKOUT_LINES, MAX_LINE_SIZE, CUSTOMER_ARRIVAL_PERIOD, AVG_SERVICE_TIME);
	store.runSimulation(SIMULATION_TIME);
    REQUIRE(store.getCustomersLost() == 0);
    REQUIRE(store.getCustomersServed() == 4);
    REQUIRE(store.getAverageWaitTime() == 4);
}

TEST_CASE("Multiple lines: Some customers lost")
{
	const int NUM_CHECKOUT_LINES = 2;
	const int MAX_LINE_SIZE = 3;
	const int CUSTOMER_ARRIVAL_PERIOD = 2;
	const int AVG_SERVICE_TIME = 9;
	const int SIMULATION_TIME = 20;
	GroceryStore store(NUM_CHECKOUT_LINES, MAX_LINE_SIZE, CUSTOMER_ARRIVAL_PERIOD, AVG_SERVICE_TIME);
	store.runSimulation(SIMULATION_TIME);
    REQUIRE(store.getCustomersLost() == 2);
    REQUIRE(store.getCustomersServed() == 4);
    REQUIRE(store.getAverageWaitTime() == 5);
}
