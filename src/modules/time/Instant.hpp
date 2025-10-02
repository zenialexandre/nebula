#pragma once

#include <chrono>

namespace nebula {
    namespace time {

enum Duration {
    SECONDS,
    MILLISECONDS,
    MICROSECONDS,
    NANOSECONDS
};

class Instant {
public:
    static double now(Duration timeDur = MILLISECONDS) {
        auto now = std::chrono::high_resolution_clock::now();
        auto duration = now.time_since_epoch();
        double returnValue;
        switch (timeDur) {
        case SECONDS:
            returnValue = std::chrono::duration_cast<std::chrono::seconds>(duration).count();
            break;
        case MILLISECONDS:
            returnValue = std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();
            break;
        case MICROSECONDS:
            returnValue = std::chrono::duration_cast<std::chrono::microseconds>(duration).count();
            break;
        case NANOSECONDS:
            returnValue = std::chrono::duration_cast<std::chrono::nanoseconds>(duration).count();
            break;
        }
        return returnValue;
    }
};
} // time
} // nebula
