#pragma once

#include "Instant.hpp"

namespace nebula {
    namespace time {
        
class DeltaTime {
public:
    DeltaTime();
    ~DeltaTime();

    double tick();

    double get() const;

    int getFPS() const;

private:
    double currTime;
    double prevTime;
    double prevFpsTime;

    int fps;
    int frames;
    double delta;
};

} // time
} // nebula
