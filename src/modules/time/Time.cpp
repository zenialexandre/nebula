#include "Time.hpp"

namespace nebula {
    namespace time {

    Time::Time()
        : Module(TIME, "time") 
        , dt(nullptr) {
        dt = new DeltaTime();
    }

    Time::~Time() {
        delete dt;
    }

    double Time::now() {
        return Instant::now();
    }

    double Time::tick() {
        return dt->tick();
    }

    double Time::getDeltaTime() const {
        return dt->get();
    }

    double Time::getFPS() const {
        return dt->getFPS();
    }
} // time
} // nebula
