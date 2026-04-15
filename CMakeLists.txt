cmake_minimum_required(VERSION 4.3)
project(neuron)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)
include_directories(neuron)
include_directories(overall)

add_executable(neuron
        draw/gemini.cpp
        neuron/brain.hpp
        neuron/neuron.hpp
        overall/const_v.hpp
        overall/DA.hpp
        overall/overall.hpp
        overall/time.hpp
        dongzhenmao.cpp
)
