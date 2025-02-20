cmake_minimum_required(VERSION 3.29)
project(tp1_ordonnancement_CerberusX21)

set(CMAKE_CXX_STANDARD 14)

set(SOURCES
        Processus.cpp
        simulateur.cpp
        Ordonnanceur.cpp
        ContratException.cpp
)

set(HEADERS
        Processus.h
        File.h
        Ordonnanceur.h
        ContratException.h
)

add_executable(tp1_ordonnancement_CerberusX21 ${SOURCES} ${HEADERS})

include(FetchContent)
FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG v1.12.x
)

FetchContent_MakeAvailable(googletest)

enable_testing()

add_subdirectory(tests)

# Copy Simulation files from SimulationFiles directory to the build directory
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/SimulationFiles/FCFS_FJS_Round
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/SimulationFiles/Multiniveaux
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/SimulationFiles/Priorite
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
