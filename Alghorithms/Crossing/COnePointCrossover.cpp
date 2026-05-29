#include "COnePointCrossover.h"

COnePointCrossover::COnePointCrossover() {
    // rd() wywołuje operator() klasy random_device, który pobiera ziarno (seed)
    // std::mt19937(seed) tworzy nowy, zainicjalizowany silnik
    this->gen = std::mt19937(this->rd());
}

void COnePointCrossover::vCrossover(const std::vector<int> &vParentA,
    const std::vector<int> &vParentB,
    std::vector<int> &vChild1,
    std::vector<int> &vChild2) {

    size_t iSize = vParentA.size();
    if (iSize == 0) return;

    //Losowanie punktu przeciecia
    std::uniform_int_distribution<int> distribution(1, iSize - 1);
    int iPivot = distribution(this->gen);

    vChild1.clear();
    vChild2.clear();
    vChild1.resize(iSize);
    vChild2.resize(iSize);

    //Budujemy Child 1: fragment A + fragment B
    for (int i = 0; i < iPivot; ++i) {
        vChild1[i] = vParentA[i];
    }
    for (size_t i = iPivot; i < iSize; ++i) {
        vChild1[i] = vParentB[i];
    }

    //Budujemy Child 2: fragment B + fragment A
    for (int i = 0; i < iPivot; ++i) {
        vChild2[i] = vParentB[i];
    }
    for (size_t i = iPivot; i < iSize; ++i) {
        vChild2[i] = vParentA[i];
    }


}
