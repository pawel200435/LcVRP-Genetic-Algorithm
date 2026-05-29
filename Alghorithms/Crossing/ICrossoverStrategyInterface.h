#ifndef PROJEKT_LCVRP_ICROSSOVERSTRATEGYINTERFACE_H
#define PROJEKT_LCVRP_ICROSSOVERSTRATEGYINTERFACE_H
#include <vector>

class ICrossoverStrategyInterface {
public:
    virtual ~ICrossoverStrategyInterface() = default;
    virtual void vCrossover(const std::vector<int>& vParentA,
        const std::vector<int>& vParentB,
        std::vector<int>& vChildA,
        std::vector<int>& vChiledB) = 0;

};


#endif //PROJEKT_LCVRP_ICROSSOVERSTRATEGYINTERFACE_H