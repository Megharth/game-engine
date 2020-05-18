#ifndef EXPLOSION_COMPONENT_HPP
#define EXPLOSION_COMPONENT_HPP

#include "base/GameObject.hpp"
#include "base/GenericComponent.hpp"
#include "base/Level.hpp"
#include <chrono>


class ExplosionComponent : public GenericComponent {
private:
    double timeout;
    bool blast = false;
    bool came = false;
    std::chrono::system_clock::time_point previous, current;

public:
    ExplosionComponent(GameObject &, double, bool);

    void update(Level &, bool);

    void settimeout(double time){timeout = time;}


};

#endif
