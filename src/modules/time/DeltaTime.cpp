#include "DeltaTime.hpp"

namespace nebula {
    namespace time {

    DeltaTime::DeltaTime()
        : fps(0)
        , frames(0)
        , delta(0) {
        currTime = Instant::now(MILLISECONDS)/1000;
        prevFpsTime = currTime;
    }

    DeltaTime::~DeltaTime() {}

    double DeltaTime::tick() {
        frames++;
        
        prevTime = currTime;
        currTime = Instant::now(MILLISECONDS)/1000;

        delta = currTime - prevTime;

        double deltaFps = currTime - prevFpsTime;
        // FPS update time is 1 second
        if (deltaFps > 1) {
            fps = int(frames/deltaFps);
            prevFpsTime = currTime;
            frames = 0;
        }

        return delta;
    }

    double DeltaTime::get() const {
        return delta;
    }

    int DeltaTime::getFPS() const {
        return fps;
    }
} // time
} // nebula
