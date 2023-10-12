#pragma once

#include <functional>
#include <vector>

typedef int Time;  // Seconds

typedef std::function<void(Time)> ClockWatcher;

// Simulates the passage of time in seconds.
class Clock {
public:
    Clock() {
        time = 0;
    }

    // Returns the current time in seconds.
    Time getTime() {
        return time;
    }

    // Adds a watcher to be notified when time advances each second.
    void addWatcher(ClockWatcher watcher) {
        watchers.push_back(watcher);
    }

    // Advances the clock by one second.
    void tick() {
        time++;
        for (auto& watcher : watchers) {
            watcher(time);
        }
    }

private:
    Time time;
    std::vector<ClockWatcher> watchers;
};
