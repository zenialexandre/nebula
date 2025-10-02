#pragma once

#include "../common/Module.hpp"
#include "DeltaTime.hpp"

namespace nebula {
    namespace time {

class Time : public Module {
public:
    Time();
    ~Time();

    double now();

    double tick();

    double getDeltaTime() const;

    double getFPS() const;
private:
    DeltaTime *dt;
};
} // time
} // nebula
