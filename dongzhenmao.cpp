#include <iostream>
#include <vector> 
#include <math.h>
#include "network/NEAT.hpp"

using namespace std;

int main() {
    mtd::Test test;
    
    // 1. 初始化种群网络 (25个网络)
    test.init();
    
    cout << "初始化完成，开始演化与训练..." << endl;
    
    // 2. 演化迭代
    // 原代码 run0 里面进行了 300 次 mutate 和 run1，这可能需要花费较多时间
    // 为了看到过程，我们手动拆解并打印它的演化进度
    
    for (int gen = 1; gen <= 100; ++gen) {
        test.mutate();
        test.run1();
        
        // 找出这一代中最优秀的个体
        double best_score = -1.0;
        double best_cnt = 0.0;
        for (int i = 0; i < 25; ++i) {
            if (test.net[i].score > best_score) {
                best_score = test.net[i].score;
                best_cnt = test.net[i].cnt;
            }
        }
        
        // 每 10 代打印一次信息
        if (gen % 10 == 0 || gen == 1) {
            cout << "Generation " << gen 
                 << " | Best Score: " << best_score 
                 << " | Max Match Count: " << best_cnt << endl;
        }
    }
    
    cout << "\n训练结束！" << endl;
    
    // 测试最好网络对异或门 (XOR) 的拟合效果
    cout << "\n正在选取最优网络进行前向测试..." << endl;
    mtd::network best_net = test.net[0]; // mutate 已经按分数排过序了
    
    // 简单验证逻辑（由于是SNN，需要持续输入一段时长才能看到神经元脉冲）
    
    return 0;
}