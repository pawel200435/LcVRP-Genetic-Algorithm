#ifndef PROJEKT_LCVRP_IALGORITHMLISTENER_H
#define PROJEKT_LCVRP_IALGORITHMLISTENER_H

class IAlgorithmListener {
public:
    virtual ~IAlgorithmListener() = default;
    //Metoda raportujaca postep
    virtual void vListenProgress(int iIteration, double dElapsedSeconds, double dGlobalFitness, double dCurrentBest) = 0;
};


#endif //PROJEKT_LCVRP_IALGORITHMLISTENER_H