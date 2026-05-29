cmake_minimum_required(VERSION 4.0)
project(PROJEKT_LcVRP)

set(CMAKE_CXX_STANDARD 20)

add_executable(PROJEKT_LcVRP Main/main.cpp
        "Helpers Classes/CResult.h"
        Evaluator/CEvaluator.cpp
        Evaluator/CEvaluator.h
        "Helpers Classes/CLoadedData.cpp"
        "Helpers Classes/CLoadedData.h"
        "Helpers Classes/CFileDataLoader.cpp"
        "Helpers Classes/CFileDataLoader.h"
        Individual/CIndividual.cpp
        Individual/CIndividual.h
        Alghorithms/Crossing/ICrossoverStrategyInterface.cpp
        Alghorithms/Crossing/ICrossoverStrategyInterface.h
        Alghorithms/Crossing/COnePointCrossover.cpp
        Alghorithms/Crossing/COnePointCrossover.h
        Alghorithms/Mutation/IMutationStrategyInterface.cpp
        Alghorithms/Mutation/IMutationStrategyInterface.h
        Alghorithms/Mutation/CEveryGenRandomMutation.cpp
        Alghorithms/Mutation/CEveryGenRandomMutation.h
        GeneticAlgorithm/CGeneticAlgorithm.cpp
        GeneticAlgorithm/CGeneticAlgorithm.h
        Individual/SBestIndividualSnapshot.h
        Main/IAlgorithmListener.h
        Main/CConsoleLogger.cpp
        Main/CConsoleLogger.h
        GeneticAlgorithm/ConstantsGeneticAlgorithm.h
        Alghorithms/Mutation/CReversedGenMutation.cpp
        Alghorithms/Mutation/CReversedGenMutation.h)
