#include <iostream>
#include <vector>

int main() {
    double a = 0.02;
    double b = 0.2;
    double c = -67.0;
    double d = 8.0;

    double v = -67.0;  
    double u = b * v;  

    double T = 350.0;     // 总时间 500 ms
    double dt = 0.1;       // 步长 0.1 ms
    int steps = (int)(T / dt);

    std::cout << "Time,Voltage" << std::endl;

    for (int i = 0; i < steps; ++i) {
        double t = i * dt;
        double I = (t >= 50.0 && t <= 200) ? 10.0 : 0.0; // 过一会再给电流

        double v_prev = v;
        v = v + dt * (0.04 * v * v + 5 * v + 140 - u + I);
        u = u + dt * (a * (b * v_prev - u));

        if (v >= 30.0) {
            std::cout << t << "," << 30.0 << std::endl;
            v = c;     
            u = u + d; 
            std::cout << t << "," << v << std::endl;
        } else {
            std::cout << t << "," << v << std::endl;
        }

    }

    return 0;
}

/*
powershell
g++ gemini.cpp -o gemini.exe
.\gemini.exe > data.csv


*/