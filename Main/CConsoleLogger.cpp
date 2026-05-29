#include "CConsoleLogger.h"

#include <iostream>
#include <ostream>

void CConsoleLogger::vListenProgress(int iIteration, double dElapsedSeconds, double dBestFitness, double dCurrentBest) {
    std::cout
        << "[LOG] Iteracja: " << iIteration
        << " | Czas: " << (int)dElapsedSeconds << "s"
        << " | Rekord: " << dBestFitness
        << " | Obecna populacja: " << dCurrentBest
        <<std::endl;
}
