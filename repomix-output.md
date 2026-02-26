This file is a merged representation of the entire codebase, combined into a single document by Repomix.

# File Summary

## Purpose
This file contains a packed representation of the entire repository's contents.
It is designed to be easily consumable by AI systems for analysis, code review,
or other automated processes.

## File Format
The content is organized as follows:
1. This summary section
2. Repository information
3. Directory structure
4. Repository files (if enabled)
5. Multiple file entries, each consisting of:
  a. A header with the file path (## File: path/to/file)
  b. The full contents of the file in a code block

## Usage Guidelines
- This file should be treated as read-only. Any changes should be made to the
  original repository files, not this packed version.
- When processing this file, use the file path to distinguish
  between different files in the repository.
- Be aware that this file may contain sensitive information. Handle it with
  the same level of security as you would the original repository.

## Notes
- Some files may have been excluded based on .gitignore rules and Repomix's configuration
- Binary files are not included in this packed representation. Please refer to the Repository Structure section for a complete list of file paths, including binary files
- Files matching patterns in .gitignore are excluded
- Files matching default ignore patterns are excluded
- Files are sorted by Git change count (files with more changes are at the bottom)

# Directory Structure
```
__old.txt
.gitignore
check.hpp
doc/chinese.md
dongzhenmao.cpp
draw/gemini.cpp
my_algorithm.hpp
neuron/brain.hpp
neuron/neuron.hpp
overall/const_v.hpp
overall/DA.hpp
overall/overall.hpp
overall/time.hpp
README.md
repomix-output.xml
run.bat
```

# Files

## File: __old.txt
````
void view_DA_v() {
    printf("Time,DA_v\n");
    DA.float_v(1);
    for (int i = 0; i < 2000; ++i) { // 200 ms
        if (i % 10 == 0) {
            printf("%f,%.6f\n", i / 10.0, DA.v());
        }
        DA.t_run();
    }    
}

PN_Neuron a, b, c;

void view_enhance() {
    printf("Time,W\n");
    link_random(&a, &b);
    link_random(&c, &b);

    printf("%lf,%lf,%lf,%lf\n", 0, b.v, b.den.front().Ca_v, b.den.front().w);

    for (int i = 0; i < 6; ++i) {
        c.release();
        b.t_run();
        printf("%lf,%lf,%lf,%lf\n", 0, b.v, b.den.front().Ca_v, b.den.front().w);
    }

    DA.float_v(0.5);
    for (int i = 1; i < 10000; ++i) {
        DA.t_run();
        b.t_run();
        if(i % 10 == 0) printf("%lf,%lf,%lf,%lf\n", i / 10.0, b.v, b.den.front().Ca_v, b.den.front().w);
    }

}
````

## File: .gitignore
````
*.exe
````

## File: check.hpp
````cpp

````

## File: doc/chinese.md
````markdown
结构决定性质，多巴胺发配错误的都已经死完了。

平常的多巴胺浓度：50 umol  
增强的多巴胺浓度：100 umol
削弱的多巴胺浓度：10 umol


洗净平力量。

## 一次发放：

### 自然状态：
由于细胞膜对于 $\text{K}^+$ 有微弱的通透性（存在漏钾通道），正常状态下 $\text{K}^+$ 会不断外溢，直到细胞内相对电压等于 $-67 \, \text{mV}$。如果外有刺激，且小，细胞内的电位会自然下落至 $-67 \,\text{mV}$。

### 神经元达到界限：

但是，一旦超过一定阈值 $-55 \,\text{mV}$，$\text{Na}^+$ 通道会开启，大量的 $\text{Na}^+$ 会内流，电压不断升高，失控，
到 $30 \,\text{mV}$ 时钠离子通道被神秘蛋白质[$^1$]()堵住，
此时 $\text{K}^+$ 通道[$^3$]()完全打开（他们在 $-55 \,\text{mV}$ 时就收到了指令，来自电压，注意不是后文提到的 $\text{Ca}^{2+}$，不过他们反应太慢了），$\text{K}^+$ 疯狂流出，电位开始骤降至 $-85 \,\text{mV}$，然后慢慢回升。

电位的上升让突触小体[$^2$]()进入 $\text{Ca}^{2+}$，这是神经递质发放的开关。

此时分为两种情况：如果这个神经元是兴奋神经元，她会释放`谷氨酸`等兴奋性神经介质；如果这个神经元是抑制神经元，她会释放`γ-氨基丁酸`等抑制性神经介质。

[$1$]()：钠离子通道的一个特殊结构：失活门（球链结构），这是绝对不应期的结构基础基础。  

[$2$]()：位于轴突末梢。

[$3$]()：延迟整流漏钾通道，正因为反应慢，所以给了钠离子机会。

### 后神经元享受（兴奋性介质）：

我们称这种电位上升叫做去极化。

- AMPA 受体反应迅速，开启 $\text{Na}^+$ 通道，让 $\text{Na}^+$ 顺浓度进入细胞，过程快。请注意，$\text{Na}^+$ 是去极化的主力，但不会有招聘的作用。

- 当突触后神经元初步去极化后（$-40 \,\text{mV}$），NMDA 受体通道上 $\text{Mg}^{2+}$ 被弹开，$\text{Ca}^{2+}$ 进入（短时间内电位上升），请详见下文的树突结构详解（必看）。


请注意 $\text{Ca}^{2+}$ 会开启一种特殊的 $\text{K}^{+}$ 通道，会让 $\text{K}^{+}$ 不断外泄，这会导致更难发放。

不过在更长的时间尺度，$\text{Ca}^{2+}$ 也是起到招聘 AMPA 受体的作用，让连接加强，具体请见下文。

### 后神经元受着（抑制性介质）：
我们称这种电位下降叫做超极化。

- GABA_A 受体反应迅速，开启 $\text{Cl}^-$ 通道， 让 $\text{Cl}^-$ 顺浓度进入细胞。

- GABA_B 受体反应较慢，间接开启 $\text{K}^+$ 通道， 让 $\text{K}^+$ 顺浓度流出细胞，较为持久。

### 稳态可塑性

如果有一个神经元长期被压制，那么它的 GABA_A 受体会不断被自己移除来自救，也就是说，变得更加难抑制。当然，如果一个神经元经常兴奋，她也会主动移除 AMPA 受体。这就是我们常说的稳态可塑性。

### 方程描述

这个模型是我最喜欢的，准确率优秀，而且能模拟极大多数的神经元，仅需 $4$ 个参数就能解决电位问题，你说的很对但是我真的不知道该怎么讲清楚这为什么是这样的，建议自己写个代码把玩一下，或者给 [desmos](https://www.desmos.com/) 把玩一下。

$$
\frac{\partial v}{\partial t} = 0.04\cdot v ^ 2 + 5\cdot v + 140 - u + I \\

\frac{\partial u}{\partial t} =  a\cdot (b \cdot v - u)
$$

对于复位，如果 $v \ge 30 \,\text{mV}$：

$$
v \gets c \\
u \gets u + d
$$

对于普通神经元（RS 锥体神经元）来说：

$$
\begin{cases}
a = 0.02 \\
b = 0.2 \\
c = -67.0 \\
d = 8.0
\end{cases}
$$

其中一些神经元的爆发图像长这样，图源来自神经元大手子 Izhikevich，也是这个模型的提出者：

![](https://cdn.luogu.com.cn/upload/image_hosting/t7e2xobb.png)

如果你想自己模拟的话，我也写了一份代码：
```cpp
#include <iostream>
#include <vector>

int main() {
    double a = 0.02;
    double b = 0.2;
    double c = -67.0;
    double d = 8.0;

    double v = -67.0;  
    double u = b * v;  

    double T = 500.0;     // 总时间 500 ms
    double dt = 0.1;       // 步长 0.1 ms
    int steps = (int)(T / dt);

    std::cout << "Time,Voltage" << std::endl;

    for (int i = 0; i < steps; ++i) {
        double t = i * dt;
        double I = (t >= 50.0) ? 50.0 : 0.0; // 过一会再给电流

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
```

使用指南：

```bat
powershell
g++ test.cpp -o test.exe
.\test.exe > data.csv
```

打开 data.csv，选择数据项，选择分隔符为半角逗号，分列。然后选中两列，插入图表，就可以看到你设置的神经元的发放情况啦。




---

## STDP 与 iSTDP[$^1$]()

这两个机制用来调整神经元树突的权重。

这是很精妙的，为什么有的发放能触发增强，有的却不行呢？我们可以从这些方向了解。


有两种受 $\text{Ca}^{2+}$ 影响的酶：

- 磷酸酶反应快，干拆家的活（拆受体），她很敏感，有点 $\text{Ca}^{2+}$ 就被激发，但影响较小，这是 STDP。
- 激酶反应慢，干装修的活（装受体），她比较迟钝，要很多 $\text{Ca}^{2+}$ 才能被激发，影响大，这是 iSTDP。

请注意，由于抑制性神经元与兴奋性神经元的基因表达不同，他们体内激酶和磷酸酶的影响也不一样：在兴奋性神经元中，激酶装 AMPA 受体，磷酸酶拆 AMPA 受体；在抑制性神经元中，激酶装 GABA 受体，磷酸酶拆 GABA 受体。

当然，如果只有这点东西是不够看的，还有大麻素这件东西。她会在 $\text{Ca}^{2+}$ 浓度较高的时候被合成，合成完不往后飘，但是往前飘，无条件地阻止所有连接自己树突的轴突！你会问主播主播，$\text{Ca}^{2+}$ 浓度高不代表这神经元已经放电放爽了吗？根据稳态可塑性，我们应该拆 AMPA 受体才对啊！确实是这样，但是一般短时间的高频放电是要刻录 LTP 了，所以她会想让前面的抑制性神经元先别管她，让她自己敏感些。

怎样，神奇吧。

为什么有的会导致进入的多，有的进入的少呢？请见下文树突的结构。


[$1$]()：小故事，STDP 先被发现，被称为赫布法则。

[$\red 2$]()：~~Gemini 形象的称其为 `awmc` `apgc` `aacc` `artc` `amdc` `azrc` `agtc` `arlc` `apzc`~~。

[$3$]()：这被称为 BCM 曲线。

一些钙浓度参考数值参考：
- 静息：$0.05 \, \text{umol}$。
- 引发 LTD：$0.1 \, \text{umol}$。
- 引发 LTP：$0.8 \, \text{umol}$。
- 单次发放进入：$0.2 \, \text{umol}$。
- 因果进入（见下文树突结构），令 $h$ 为 NMDA 开放率：$ 2 \cdot e^{-0.1\Delta t}\cdot h \, \text{umol}$。

我们考虑使用这样一个函数拟合 STDP 与 iSTDP（注意这是极度简化的版本，真实版本复杂得多！）。

$$
f(x) = \begin{cases}
0 & x \le 0.2 \\
\large\frac{(x \,- \,0.2) \,\cdot \,(x \,- \,0.8)}{ x ^ 2 \,+\, 0.3}  & x > 0.2

\end{cases}
$$


```cpp
double Ca_f(double x) { // min = -0.176, max -> 1, 0.4
    return x < 0.2 ? 0 : (x - 0.2) * (x - 0.8) / (x * x + 0.3);
} 
```

注意到 $f(2) = 0.501$。



---
## 神经元的结构

前言：结构决定性质。

### 树突

你不会以为就一种树突吧？

其实不然。

从空间上看，锥形神经元由上到下，树突分为 3 种：

- 顶树突，长在主干顶端，离细胞核最远，见于 $\text{L}_{1}$。
- 斜树突，长在主干侧。
- 基底树突，长在细胞侧。

她们具有一些相同的特性，每一个树突棘连接到胞体的口（树突棘颈）很小，这保证 $\text{Ca}^{2+}$ 从一个树突棘进入之后，不会乱跑到其他的地方，影响 STDP。这里是 NMDA 受体所在地，也是激酶与磷酸酶等 $\text{Ca}^{2+}$ 感受器所在地。这被称为隔室化，由于口很小，所以 $R$ 很大，由 $U = IR$ 可知即使是很小的 $I$ 也能引起较大的电位变化。

同时，这里也存在 VGCCs（电压控钙门），这个门受电压影响，进入的 $\text{Ca}^{2+}$ 较少。

NMDA 受体有两把锁，第一把是电压，第二把是谷氨酸。

记得上文对 $\text{Ca}^{2+}$ 浓度的讨论吗，我们现在来答疑了（这本来应该放在最顶上的，但是我认为应当在 STDP 后讲）。

我们查看三种场景。

- 突触前神经元释放谷氨酸，激活 AMPA 受体，增加电位。但是没有达到 $-40 \,\text{mV}$，的界限，挡在 NMDA 受体上的 $\text{Mg}^{2+}$ 无法被弹开，$\text{Ca}^{2+}$ 自然也无法通过 NMDA 受体进入。

- 突触后神经元发放，给予了去极化，但是没有谷氨酸结合，NMDA 依然无法打开，只会通过 VGCCs 进入较少（$0.2 \,\text{umol}$）。

- 既有前神经元的发放，也有后神经元的发放，两个锁都打开，$\text{Ca}^{2+}$ 可以通过 NMDA 进入，$ 2 \cdot e^{-0.1\Delta t}\cdot h \, \text{umol}$。

通过上述我们可以发现，时间关系在似乎并非绝对严格（当然还是比较严格的）。即使前神经元后发放，由于后神经元的树突电压下降的较慢[$^1$]()，仍然会出现不小心把 NMDA 受体激活的情况。不过其实也没有关系，因为这不会时间很长，并且，大脑也确实需要一些强行建立关系的情况。

[$1$]()：这里有两个要注意的点。第一有些神经元下降的很快，如 $\text{L}_5$，不过我们忽略她。第二，较慢不是慢，是相较于神经元胞体来说的。


### 轴突

这家伙用来发放动作电位的。

### 细胞核

控制受体制造，稳态可塑性调控者（救救我喵）。


---
## 大脑的皮层：

请注意请注意请注意，下文的 $\text{L}$ 一串代表的是一个皮层之内的东西，和平常说的视觉皮层哪些不是一个东西。



原本这里有 $4k$ 内容，所以我全删了，画个图代替一下。整合一下：
![](https://cdn.luogu.com.cn/upload/image_hosting/h1d72czu.png)  

解释：
- 中间的 $\text{L}_1$ 和 $\text{L}_5$ 中间还有一个 $\text{L}_6$。
- PN 代表主椎体神经元，VIP 和 SST 都是抑制性神经元，其中~~观察图片~~就能知道，SST 神经元只会抑制 PN，VIP 神经元只会抑制 SST。
- $\text{L}_2$ 的 PN 还有一个自环。


### 皮层柱

我为什么要使用这样一个名词呢，因为在大脑中，本质上还是以一个柱为计算单位，大部分的神经元都只连向自己附近的神经元。当然，附近也是有选择性的。比如 PN 就会选择性的连向与自己同味相投的 PN（即使是中间跳过了一些）。SST 神经元则是普遍性的抑制字节周围的神经元。

---

### 不同的皮层

布线规则：
- 远的，$\text{L}_5$ $\to$ 丘脑 $\to$ $\text{L}_4$。
- 近的，$\text{L}_{2/3}$ $\to$ $\text{L}_4$。

#### 感觉皮层：

初级感觉皮层，只处理最基础的“特征”。比如 V1 只看线条的角度，S1 只看哪里的皮肤被扎了一下。

次级感觉皮层，拼凑特征，比如一大堆神秘的角度东西构成了圆。



联合感觉皮层，嗯，黄色圆柱形，香的，卧槽这是个什么，这是个香蕉。

联合感觉皮层的 $\text{L}_1$ 很发达，用来接收 PFC 的预测信息。
$\text{L}_{2/3}$ 也很发达，用于跨模态的整合。

#### 运动皮层：

孩子们我几乎没有 $\text{L}_4$。

你可能会疑惑，不是，那没有 $\text{L}_4$ 处理命令信息我该怎么办？

事实上，请见下文皮层间的联动。


#### 前额叶皮层（PFC）

我们常说的常说的决策就来自这个皮层。

PFC 的 $\text{L}_\text{1...6}$ 发育的都很好。

请注意，这个皮层占据人类大脑的 $\frac{1}{3}$，而在猫这样的生物中只有 $\frac{3}{100}$，我们可以粗略的通过这个比例来判断动物的演化等级和智能程度。

细分可以分为 dlPFC，ACC 和 OFC，这里不做详细展开（因为我没学）。

### 皮层间的联动

感觉皮层直接连向运动皮层，这与很多人想的先交给高层神经元反馈，然后再交给运动皮层实施。但有明显的问题就是：高层的处理是有延时的，你等个 $500\,\text{ms} $ 黄花菜都凉了。真正的逻辑是高层负责给命令，`运动-感觉`皮层负责做和查看对不对。

你可以想象这样一个场景。你在喝水，突然手滑了，那你怎么办，先告诉高层你手滑了吗？肯定不是。
再想象一个场景，黑暗中要摸灯的开关，感觉皮层摸不到，肯定会直接指使运动皮层胡乱摸一摸。

事实上，有研究指出，如果断掉他们间的直接联系，虽然你还能走路。但捡石子这样的运动都无法实现。


### 不同皮层之间的统一性

$\text{L}_{4}$，虽然都叫 $\text{L}_{4}$，但是它们功能上不太相同。

以下是 $\text{L}_{4}$ 非常非常厚的例子：

对于 $\text{V}_{1}$ 来说，她要处理海量的视觉信息。

对于 $\text{S}_{1}$ 来说，她要处理海量的触觉信息。  

对于 $\text{PFC}$ 来说，她要处理丘脑发来的海量的，整合的信息（包括记忆，处境等等）。

$\text{L}_{6}$，对于 PFC 而言，调整丘脑的必要工具。

---






## 学习

请结合连线图和 STDP 与 iSTDP 那一段理解。


### 基因表达

这个真的很神奇，在感觉皮层中，基因让她们发育成了对多巴胺不敏感的样子。但在 PFC 中，她们对多巴胺敏感，基因表达[$^1$]()让她们布满了多巴胺受体，也就是说，她们的 STDP 与 iSTDP 受到了。

同时，由于基因问题 VTA 的轴突根本不往某些区域长。

[$1$]()：这个基因是 COUP-TF1。

---







The Unfinished
````

## File: draw/gemini.cpp
````cpp
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
````

## File: neuron/neuron.hpp
````cpp
#pragma once

#include <stdio.h>
#include <vector> 
#include <math.h>
#include <list>
#include <random>

#include "../my_algorithm.hpp"
#include "../overall/overall.hpp"

struct Neuron;

struct Neuron {

    struct Dendrite;
    struct Axon;

    struct Dendrite {
        static double Ca_f(double x);

        double Ca_rest() { return 0.05; };

        Neuron *from;
        Axon *link;

        double w; 
        double Ca_v;
        double h; // 已激活的 NMDA 受体占比

        // Dendrite() = default;
        Dendrite(double l, double r);

        void get_release();
        void get_bap();
        void t_run();

    };

    struct Axon {
        Neuron *from;
        std::list<Dendrite*> to; // 防止地址变动
        void release();
    };    

    virtual double a() = 0;
    virtual double b() = 0;
    virtual double c() = 0; // 复极化电位
    virtual double d() = 0; // 
    virtual int type() = 0;

    std::list<Dendrite> den;
    Axon ax;

    double v; // 电位
    double u; // 疲劳度
    double I; // 输入电流

    void release();
    void t_run();

    Dendrite *build_a_den(int pre_type);

    Neuron() { 
        ax.from = this; 
    }
    
};

double Neuron::Dendrite::Ca_f(double x) { // 1 ms 为单位
    return x < 0.1 ? 0 : 0.006 * (x - 0.1) * (x - 0.8) / (x * x + 0.3);
}

Neuron::Dendrite::Dendrite(double l, double r) { 
    h = 0, Ca_v = Ca_rest();
    w = rand_double(l, r);
}

void Neuron::Dendrite::get_release() {
    from->I += 100 * w;
    h += (1 - h) * 0.5;
}

void Neuron::Dendrite::get_bap() {
    Ca_v += 4.5 * h + 0.3;
}

void Neuron::Dendrite::t_run() {              // 随时间 min_dt 的自然损失
    // Ca_v = std::max(Ca_rest(), Ca_v + 0.003 * (Ca_rest() - Ca_v) - 0.003); // 前面是树突棘颈流出, 后面是离子泵
    Ca_v = Ca_v + (0.0004 / min_dt) * (Ca_rest() - Ca_v); // 树突棘颈流出

    h *= (0.0994 / min_dt);
    w += (min_dt * Neuron::Dendrite::Ca_f(Ca_v)) * (min_dt * DA.f());

    if (link->from->type() == 1) {            // 突触前神经元是兴奋性
        w = std::max(std::min(w, 2.0), 0.0);
    } else {                                  // 突触前神经元是抑制性
        w = std::max(std::min(w, 0.0), -2.0);
    }
}

Neuron::Dendrite *Neuron::build_a_den(int pre_type) {
    if (pre_type == 1) {
        den.push_back(Neuron::Dendrite(0.2, 0.8));
    } else {
        den.push_back(Neuron::Dendrite(-0.8, 0.2));
    }
    den.back().from = this;
    return &den.back();
}

void link_random(Neuron *pre, Neuron *post) {
    Neuron::Dendrite *den = post->build_a_den(pre->type());
    pre->ax.to.push_back(den);
    den->link = &pre->ax;
}

void Neuron::Axon::release() {
    for (Dendrite *den : to) {
        den->get_release();
    }
}

void Neuron::release() {
    // printf("sp!\n");

    ax.release();
    for (Dendrite &d : den) d.get_bap();
    
    v = c();
    u = u + d();
}

void Neuron::t_run() {
    for (Dendrite &d : den) d.t_run();

    double _v = v;
    v += min_dt * (0.04 * v * v + 5 * v + 140 - u + I);
    u += min_dt * a() * (b() * _v - u);
    I *= (0.01 / min_dt);

    if (v > 30.0) release();
}

struct PN_Neuron : Neuron {
    double a() override { return 0.02; }
    double b() override { return 0.2; }
    double c() override { return -70.0; }
    double d() override { return 8.0; }
    int type() override { return 1; }
    PN_Neuron() : Neuron() {
        v = c();
        u = c() * b();
        I = 0;
    }
};

struct SST_Neuron : Neuron {
    double a() override { return 0.02; }
    double b() override { return 0.2; }
    double c() override { return -70.0; }
    double d() override { return 8.0; }
    int type() override { return -1; }
    SST_Neuron() : Neuron() {
        v = c();
        u = c() * b();
        I = 0;
    }
};
````

## File: overall/const_v.hpp
````cpp
#pragma once

const int max_n = 100; // 神经元数量
````

## File: overall/DA.hpp
````cpp
#pragma once

#include "const_v.hpp"

struct __DA { // umol
    double __v, I;

    double rest() { return 0.05; }

    __DA() : __v(rest()) {}

    void float_v(double k) { 
        I += 0.045 * k;
    }

    double v() { return __v; } // 获取实时多巴胺浓度

    double rare_f() {
        if (v() < 0.045) return v() - 0.045;      // 削弱
        else if (v() > 0.055) return v() - 0.055; // 强化
        else return 0;                            // 不改变
    }

    double f() { // 1 ms 内
        return rare_f() * 100; 
    }

    void t_run() { // 时间步 1 ms
        __v = __v + (rest() - v()) * (0.00011 / min_dt); 
        __v = std::max(0.0, std::min(0.2, __v + I));
        I *= (0.01 / min_dt);
    }

    __DA() {
        __v = rest();
        I = 0;
    }

} DA;
````

## File: overall/overall.hpp
````cpp
#pragma once

#include "const_v.hpp"
#include "DA.hpp"
#include "time.hpp"
````

## File: overall/time.hpp
````cpp
#pragma once

const double min_dt = 0.1; // 时间步

static double __time = 0;

double time() { return __time; }

double next_time() { return ++__time; }
````

## File: README.md
````markdown
你好呀
![](https://github.com/dongzhenmao/photo/blob/main/photo/4ybxo0yq.png?raw=true)
````

## File: repomix-output.xml
````xml
This file is a merged representation of the entire codebase, combined into a single document by Repomix.

<file_summary>
This section contains a summary of this file.

<purpose>
This file contains a packed representation of the entire repository's contents.
It is designed to be easily consumable by AI systems for analysis, code review,
or other automated processes.
</purpose>

<file_format>
The content is organized as follows:
1. This summary section
2. Repository information
3. Directory structure
4. Repository files (if enabled)
5. Multiple file entries, each consisting of:
  - File path as an attribute
  - Full contents of the file
</file_format>

<usage_guidelines>
- This file should be treated as read-only. Any changes should be made to the
  original repository files, not this packed version.
- When processing this file, use the file path to distinguish
  between different files in the repository.
- Be aware that this file may contain sensitive information. Handle it with
  the same level of security as you would the original repository.
</usage_guidelines>

<notes>
- Some files may have been excluded based on .gitignore rules and Repomix's configuration
- Binary files are not included in this packed representation. Please refer to the Repository Structure section for a complete list of file paths, including binary files
- Files matching patterns in .gitignore are excluded
- Files matching default ignore patterns are excluded
- Files are sorted by Git change count (files with more changes are at the bottom)
</notes>

</file_summary>

<directory_structure>
.gitignore
check.hpp
doc/chinese.md
dongzhenmao.cpp
draw/gemini.cpp
my_algorithm.hpp
neuron/brain.hpp
neuron/neuron.hpp
overall/const_v.hpp
overall/DA.hpp
overall/overall.hpp
overall/time.hpp
README.md
run_gemini.bat
run.bat
testA.hpp
time_run.hpp
</directory_structure>

<files>
This section contains the contents of the repository's files.

<file path="neuron/brain.hpp">
#pragma once

#include "neuron.hpp"
#include "overall/overall.hpp"

struct Brain {
    std::list<Neuron> neuron;

    void t_run() {
        for (Neuron &n : neuron) n.t_run();
        DA.t_run();
        next_time();
    }

    void build();

} brain;

void build() {
    
}
</file>

<file path="check.hpp">

</file>

<file path="draw/gemini.cpp">
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
</file>

<file path="my_algorithm.hpp">
#pragma once

#include <random>

static std::mt19937 gen(713);

int rand_int(int l, int r) { // [l, r)
    return std::uniform_int_distribution<int>(l, r - 1)(gen);
}

double rand_double(double l, double r) {
    return std::uniform_real_distribution<double>(l, r)(gen);
}
</file>

<file path="neuron/neuron.hpp">
#pragma once

#include <stdio.h>
#include <vector> 
#include <math.h>
#include <list>
#include <random>

#include "../my_algorithm.hpp"
#include "../overall/overall.hpp"

struct Neuron;

struct Neuron {

    struct Dendrite;
    struct Axon;

    struct Dendrite {
        static double Ca_f(double x);

        double Ca_rest() { return 0.05; };

        Neuron *from;
        Axon *link;

        double w; 
        double Ca_v;
        double h; // 已激活的 NMDA 受体占比

        // Dendrite() = default;
        Dendrite(double l, double r);

        void get_release();
        void get_bap();
        void t_run();

    };

    struct Axon {
        Neuron *from;
        std::list<Dendrite*> to; // 防止地址变动
        void release();
    };    

    virtual double a() = 0;
    virtual double b() = 0;
    virtual double c() = 0; // 复极化电位
    virtual double d() = 0; // 
    virtual int type() = 0;

    std::list<Dendrite> den;
    Axon ax;

    double v; // 电位
    double u; // 疲劳度
    double I; // 输入电流

    void release();
    void t_run();

    Dendrite *build_a_den(int pre_type);

    Neuron() { 
        ax.from = this; 
    }
    
};

double Neuron::Dendrite::Ca_f(double x) { // 1 ms 为单位
    return x < 0.1 ? 0 : 0.006 * (x - 0.1) * (x - 0.8) / (x * x + 0.3);
}

Neuron::Dendrite::Dendrite(double l, double r) { 
    h = 0, Ca_v = Ca_rest();
    w = rand_double(l, r);
}

void Neuron::Dendrite::get_release() {
    from->I += 100 * w;
    h += (1 - h) * 0.5;
}

void Neuron::Dendrite::get_bap() {
    Ca_v += 4.5 * h + 0.3;
}

void Neuron::Dendrite::t_run() {              // 随时间 min_dt 的自然损失
    // Ca_v = std::max(Ca_rest(), Ca_v + 0.003 * (Ca_rest() - Ca_v) - 0.003); // 前面是树突棘颈流出, 后面是离子泵
    Ca_v = Ca_v + (0.0004 / min_dt) * (Ca_rest() - Ca_v); // 树突棘颈流出

    h *= (0.0994 / min_dt);
    w += (min_dt * Neuron::Dendrite::Ca_f(Ca_v)) * (min_dt * DA.f());

    if (link->from->type() == 1) {            // 突触前神经元是兴奋性
        w = std::max(std::min(w, 2.0), 0.0);
    } else {                                  // 突触前神经元是抑制性
        w = std::max(std::min(w, 0.0), -2.0);
    }
}

Neuron::Dendrite *Neuron::build_a_den(int pre_type) {
    if (pre_type == 1) {
        den.push_back(Neuron::Dendrite(0.2, 0.8));
    } else {
        den.push_back(Neuron::Dendrite(-0.8, 0.2));
    }
    den.back().from = this;
    return &den.back();
}

void link_random(Neuron *pre, Neuron *post) {
    Neuron::Dendrite *den = post->build_a_den(pre->type());
    pre->ax.to.push_back(den);
    den->link = &pre->ax;
}

void Neuron::Axon::release() {
    for (Dendrite *den : to) {
        den->get_release();
    }
}

void Neuron::release() {
    // printf("sp!\n");

    ax.release();
    for (Dendrite &d : den) d.get_bap();
    
    v = c();
    u = u + d();
}

void Neuron::t_run() {
    for (Dendrite &d : den) d.t_run();

    double _v = v;
    v += min_dt * (0.04 * v * v + 5 * v + 140 - u + I);
    u += min_dt * a() * (b() * _v - u);
    I *= (0.01 / min_dt);

    if (v > 30.0) release();
}

struct PN_Neuron : Neuron {
    double a() override { return 0.02; }
    double b() override { return 0.2; }
    double c() override { return -70.0; }
    double d() override { return 8.0; }
    int type() override { return 1; }
    PN_Neuron() : Neuron() {
        v = c();
        u = c() * b();
        I = 0;
    }
};

struct SST_Neuron : Neuron {
    double a() override { return 0.02; }
    double b() override { return 0.2; }
    double c() override { return -70.0; }
    double d() override { return 8.0; }
    int type() override { return -1; }
    SST_Neuron() : Neuron() {
        v = c();
        u = c() * b();
        I = 0;
    }
};
</file>

<file path="overall/overall.hpp">
#pragma once

#include "const_v.hpp"
#include "DA.hpp"
#include "time.hpp"
</file>

<file path="run_gemini.bat">
g++ gemini.cpp -o gemini.exe -std=c++14
gemini
pause
</file>

<file path="run.bat">
g++ dongzhenmao.cpp -o dongzhenmao.exe -std=c++14
dongzhenmao
pause
</file>

<file path="testA.hpp">
#pragma once

void solve() {
    
}
</file>

<file path="time_run.hpp">
#pragma once

#include "overall/overall.hpp"
#include "brain.hpp"
</file>

<file path="doc/chinese.md">
结构决定性质，多巴胺发配错误的都已经死完了。

平常的多巴胺浓度：50 umol  
增强的多巴胺浓度：100 umol
削弱的多巴胺浓度：10 umol


洗净平力量。

## 一次发放：

### 自然状态：
由于细胞膜对于 $\text{K}^+$ 有微弱的通透性（存在漏钾通道），正常状态下 $\text{K}^+$ 会不断外溢，直到细胞内相对电压等于 $-67 \, \text{mV}$。如果外有刺激，且小，细胞内的电位会自然下落至 $-67 \,\text{mV}$。

### 神经元达到界限：

但是，一旦超过一定阈值 $-55 \,\text{mV}$，$\text{Na}^+$ 通道会开启，大量的 $\text{Na}^+$ 会内流，电压不断升高，失控，
到 $30 \,\text{mV}$ 时钠离子通道被神秘蛋白质[$^1$]()堵住，
此时 $\text{K}^+$ 通道[$^3$]()完全打开（他们在 $-55 \,\text{mV}$ 时就收到了指令，来自电压，注意不是后文提到的 $\text{Ca}^{2+}$，不过他们反应太慢了），$\text{K}^+$ 疯狂流出，电位开始骤降至 $-85 \,\text{mV}$，然后慢慢回升。

电位的上升让突触小体[$^2$]()进入 $\text{Ca}^{2+}$，这是神经递质发放的开关。

此时分为两种情况：如果这个神经元是兴奋神经元，她会释放`谷氨酸`等兴奋性神经介质；如果这个神经元是抑制神经元，她会释放`γ-氨基丁酸`等抑制性神经介质。

[$1$]()：钠离子通道的一个特殊结构：失活门（球链结构），这是绝对不应期的结构基础基础。  

[$2$]()：位于轴突末梢。

[$3$]()：延迟整流漏钾通道，正因为反应慢，所以给了钠离子机会。

### 后神经元享受（兴奋性介质）：

我们称这种电位上升叫做去极化。

- AMPA 受体反应迅速，开启 $\text{Na}^+$ 通道，让 $\text{Na}^+$ 顺浓度进入细胞，过程快。请注意，$\text{Na}^+$ 是去极化的主力，但不会有招聘的作用。

- 当突触后神经元初步去极化后（$-40 \,\text{mV}$），NMDA 受体通道上 $\text{Mg}^{2+}$ 被弹开，$\text{Ca}^{2+}$ 进入（短时间内电位上升），请详见下文的树突结构详解（必看）。


请注意 $\text{Ca}^{2+}$ 会开启一种特殊的 $\text{K}^{+}$ 通道，会让 $\text{K}^{+}$ 不断外泄，这会导致更难发放。

不过在更长的时间尺度，$\text{Ca}^{2+}$ 也是起到招聘 AMPA 受体的作用，让连接加强，具体请见下文。

### 后神经元受着（抑制性介质）：
我们称这种电位下降叫做超极化。

- GABA_A 受体反应迅速，开启 $\text{Cl}^-$ 通道， 让 $\text{Cl}^-$ 顺浓度进入细胞。

- GABA_B 受体反应较慢，间接开启 $\text{K}^+$ 通道， 让 $\text{K}^+$ 顺浓度流出细胞，较为持久。

### 稳态可塑性

如果有一个神经元长期被压制，那么它的 GABA_A 受体会不断被自己移除来自救，也就是说，变得更加难抑制。当然，如果一个神经元经常兴奋，她也会主动移除 AMPA 受体。这就是我们常说的稳态可塑性。

### 方程描述

这个模型是我最喜欢的，准确率优秀，而且能模拟极大多数的神经元，仅需 $4$ 个参数就能解决电位问题，你说的很对但是我真的不知道该怎么讲清楚这为什么是这样的，建议自己写个代码把玩一下，或者给 [desmos](https://www.desmos.com/) 把玩一下。

$$
\frac{\partial v}{\partial t} = 0.04\cdot v ^ 2 + 5\cdot v + 140 - u + I \\

\frac{\partial u}{\partial t} =  a\cdot (b \cdot v - u)
$$

对于复位，如果 $v \ge 30 \,\text{mV}$：

$$
v \gets c \\
u \gets u + d
$$

对于普通神经元（RS 锥体神经元）来说：

$$
\begin{cases}
a = 0.02 \\
b = 0.2 \\
c = -67.0 \\
d = 8.0
\end{cases}
$$

其中一些神经元的爆发图像长这样，图源来自神经元大手子 Izhikevich，也是这个模型的提出者：

![](https://cdn.luogu.com.cn/upload/image_hosting/t7e2xobb.png)

如果你想自己模拟的话，我也写了一份代码：
```cpp
#include <iostream>
#include <vector>

int main() {
    double a = 0.02;
    double b = 0.2;
    double c = -67.0;
    double d = 8.0;

    double v = -67.0;  
    double u = b * v;  

    double T = 500.0;     // 总时间 500 ms
    double dt = 0.1;       // 步长 0.1 ms
    int steps = (int)(T / dt);

    std::cout << "Time,Voltage" << std::endl;

    for (int i = 0; i < steps; ++i) {
        double t = i * dt;
        double I = (t >= 50.0) ? 50.0 : 0.0; // 过一会再给电流

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
```

使用指南：

```bat
powershell
g++ test.cpp -o test.exe
.\test.exe > data.csv
```

打开 data.csv，选择数据项，选择分隔符为半角逗号，分列。然后选中两列，插入图表，就可以看到你设置的神经元的发放情况啦。




---

## STDP 与 iSTDP[$^1$]()

这两个机制用来调整神经元树突的权重。

这是很精妙的，为什么有的发放能触发增强，有的却不行呢？我们可以从这些方向了解。


有两种受 $\text{Ca}^{2+}$ 影响的酶：

- 磷酸酶反应快，干拆家的活（拆受体），她很敏感，有点 $\text{Ca}^{2+}$ 就被激发，但影响较小，这是 STDP。
- 激酶反应慢，干装修的活（装受体），她比较迟钝，要很多 $\text{Ca}^{2+}$ 才能被激发，影响大，这是 iSTDP。

请注意，由于抑制性神经元与兴奋性神经元的基因表达不同，他们体内激酶和磷酸酶的影响也不一样：在兴奋性神经元中，激酶装 AMPA 受体，磷酸酶拆 AMPA 受体；在抑制性神经元中，激酶装 GABA 受体，磷酸酶拆 GABA 受体。

当然，如果只有这点东西是不够看的，还有大麻素这件东西。她会在 $\text{Ca}^{2+}$ 浓度较高的时候被合成，合成完不往后飘，但是往前飘，无条件地阻止所有连接自己树突的轴突！你会问主播主播，$\text{Ca}^{2+}$ 浓度高不代表这神经元已经放电放爽了吗？根据稳态可塑性，我们应该拆 AMPA 受体才对啊！确实是这样，但是一般短时间的高频放电是要刻录 LTP 了，所以她会想让前面的抑制性神经元先别管她，让她自己敏感些。

怎样，神奇吧。

为什么有的会导致进入的多，有的进入的少呢？请见下文树突的结构。


[$1$]()：小故事，STDP 先被发现，被称为赫布法则。

[$\red 2$]()：~~Gemini 形象的称其为 `awmc` `apgc` `aacc` `artc` `amdc` `azrc` `agtc` `arlc` `apzc`~~。

[$3$]()：这被称为 BCM 曲线。

一些钙浓度参考数值参考：
- 静息：$0.05 \, \text{umol}$。
- 引发 LTD：$0.1 \, \text{umol}$。
- 引发 LTP：$0.8 \, \text{umol}$。
- 单次发放进入：$0.2 \, \text{umol}$。
- 因果进入（见下文树突结构），令 $h$ 为 NMDA 开放率：$ 2 \cdot e^{-0.1\Delta t}\cdot h \, \text{umol}$。

我们考虑使用这样一个函数拟合 STDP 与 iSTDP（注意这是极度简化的版本，真实版本复杂得多！）。

$$
f(x) = \begin{cases}
0 & x \le 0.2 \\
\large\frac{(x \,- \,0.2) \,\cdot \,(x \,- \,0.8)}{ x ^ 2 \,+\, 0.3}  & x > 0.2

\end{cases}
$$


```cpp
double Ca_f(double x) { // min = -0.176, max -> 1, 0.4
    return x < 0.2 ? 0 : (x - 0.2) * (x - 0.8) / (x * x + 0.3);
} 
```

注意到 $f(2) = 0.501$。



---
## 神经元的结构

前言：结构决定性质。

### 树突

你不会以为就一种树突吧？

其实不然。

从空间上看，锥形神经元由上到下，树突分为 3 种：

- 顶树突，长在主干顶端，离细胞核最远，见于 $\text{L}_{1}$。
- 斜树突，长在主干侧。
- 基底树突，长在细胞侧。

她们具有一些相同的特性，每一个树突棘连接到胞体的口（树突棘颈）很小，这保证 $\text{Ca}^{2+}$ 从一个树突棘进入之后，不会乱跑到其他的地方，影响 STDP。这里是 NMDA 受体所在地，也是激酶与磷酸酶等 $\text{Ca}^{2+}$ 感受器所在地。这被称为隔室化，由于口很小，所以 $R$ 很大，由 $U = IR$ 可知即使是很小的 $I$ 也能引起较大的电位变化。

同时，这里也存在 VGCCs（电压控钙门），这个门受电压影响，进入的 $\text{Ca}^{2+}$ 较少。

NMDA 受体有两把锁，第一把是电压，第二把是谷氨酸。

记得上文对 $\text{Ca}^{2+}$ 浓度的讨论吗，我们现在来答疑了（这本来应该放在最顶上的，但是我认为应当在 STDP 后讲）。

我们查看三种场景。

- 突触前神经元释放谷氨酸，激活 AMPA 受体，增加电位。但是没有达到 $-40 \,\text{mV}$，的界限，挡在 NMDA 受体上的 $\text{Mg}^{2+}$ 无法被弹开，$\text{Ca}^{2+}$ 自然也无法通过 NMDA 受体进入。

- 突触后神经元发放，给予了去极化，但是没有谷氨酸结合，NMDA 依然无法打开，只会通过 VGCCs 进入较少（$0.2 \,\text{umol}$）。

- 既有前神经元的发放，也有后神经元的发放，两个锁都打开，$\text{Ca}^{2+}$ 可以通过 NMDA 进入，$ 2 \cdot e^{-0.1\Delta t}\cdot h \, \text{umol}$。

通过上述我们可以发现，时间关系在似乎并非绝对严格（当然还是比较严格的）。即使前神经元后发放，由于后神经元的树突电压下降的较慢[$^1$]()，仍然会出现不小心把 NMDA 受体激活的情况。不过其实也没有关系，因为这不会时间很长，并且，大脑也确实需要一些强行建立关系的情况。

[$1$]()：这里有两个要注意的点。第一有些神经元下降的很快，如 $\text{L}_5$，不过我们忽略她。第二，较慢不是慢，是相较于神经元胞体来说的。


### 轴突

这家伙用来发放动作电位的。

### 细胞核

控制受体制造，稳态可塑性调控者（救救我喵）。


---
## 大脑的皮层：

请注意请注意请注意，下文的 $\text{L}$ 一串代表的是一个皮层之内的东西，和平常说的视觉皮层哪些不是一个东西。



原本这里有 $4k$ 内容，所以我全删了，画个图代替一下。整合一下：
![](https://cdn.luogu.com.cn/upload/image_hosting/h1d72czu.png)  

解释：
- 中间的 $\text{L}_1$ 和 $\text{L}_5$ 中间还有一个 $\text{L}_6$。
- PN 代表主椎体神经元，VIP 和 SST 都是抑制性神经元，其中~~观察图片~~就能知道，SST 神经元只会抑制 PN，VIP 神经元只会抑制 SST。
- $\text{L}_2$ 的 PN 还有一个自环。


### 皮层柱

我为什么要使用这样一个名词呢，因为在大脑中，本质上还是以一个柱为计算单位，大部分的神经元都只连向自己附近的神经元。当然，附近也是有选择性的。比如 PN 就会选择性的连向与自己同味相投的 PN（即使是中间跳过了一些）。SST 神经元则是普遍性的抑制字节周围的神经元。

---

### 不同的皮层

布线规则：
- 远的，$\text{L}_5$ $\to$ 丘脑 $\to$ $\text{L}_4$。
- 近的，$\text{L}_{2/3}$ $\to$ $\text{L}_4$。

#### 感觉皮层：

初级感觉皮层，只处理最基础的“特征”。比如 V1 只看线条的角度，S1 只看哪里的皮肤被扎了一下。

次级感觉皮层，拼凑特征，比如一大堆神秘的角度东西构成了圆。



联合感觉皮层，嗯，黄色圆柱形，香的，卧槽这是个什么，这是个香蕉。

联合感觉皮层的 $\text{L}_1$ 很发达，用来接收 PFC 的预测信息。
$\text{L}_{2/3}$ 也很发达，用于跨模态的整合。

#### 运动皮层：

孩子们我几乎没有 $\text{L}_4$。

你可能会疑惑，不是，那没有 $\text{L}_4$ 处理命令信息我该怎么办？

事实上，请见下文皮层间的联动。


#### 前额叶皮层（PFC）

我们常说的常说的决策就来自这个皮层。

PFC 的 $\text{L}_\text{1...6}$ 发育的都很好。

请注意，这个皮层占据人类大脑的 $\frac{1}{3}$，而在猫这样的生物中只有 $\frac{3}{100}$，我们可以粗略的通过这个比例来判断动物的演化等级和智能程度。

细分可以分为 dlPFC，ACC 和 OFC，这里不做详细展开（因为我没学）。

### 皮层间的联动

感觉皮层直接连向运动皮层，这与很多人想的先交给高层神经元反馈，然后再交给运动皮层实施。但有明显的问题就是：高层的处理是有延时的，你等个 $500\,\text{ms} $ 黄花菜都凉了。真正的逻辑是高层负责给命令，`运动-感觉`皮层负责做和查看对不对。

你可以想象这样一个场景。你在喝水，突然手滑了，那你怎么办，先告诉高层你手滑了吗？肯定不是。
再想象一个场景，黑暗中要摸灯的开关，感觉皮层摸不到，肯定会直接指使运动皮层胡乱摸一摸。

事实上，有研究指出，如果断掉他们间的直接联系，虽然你还能走路。但捡石子这样的运动都无法实现。


### 不同皮层之间的统一性

$\text{L}_{4}$，虽然都叫 $\text{L}_{4}$，但是它们功能上不太相同。

以下是 $\text{L}_{4}$ 非常非常厚的例子：

对于 $\text{V}_{1}$ 来说，她要处理海量的视觉信息。

对于 $\text{S}_{1}$ 来说，她要处理海量的触觉信息。  

对于 $\text{PFC}$ 来说，她要处理丘脑发来的海量的，整合的信息（包括记忆，处境等等）。

$\text{L}_{6}$，对于 PFC 而言，调整丘脑的必要工具。

---






## 学习

请结合连线图和 STDP 与 iSTDP 那一段理解。


### 基因表达

这个真的很神奇，在感觉皮层中，基因让她们发育成了对多巴胺不敏感的样子。但在 PFC 中，她们对多巴胺敏感，基因表达[$^1$]()让她们布满了多巴胺受体，也就是说，她们的 STDP 与 iSTDP 受到了。

同时，由于基因问题 VTA 的轴突根本不往某些区域长。

[$1$]()：这个基因是 COUP-TF1。

---







The Unfinished
</file>

<file path="overall/time.hpp">
#pragma once

const double min_dt = 0.1; // 时间步

static double __time = 0;

double time() { return __time; }

double next_time() { return ++__time; }
</file>

<file path=".gitignore">
*.exe
</file>

<file path="overall/const_v.hpp">
#pragma once

const int max_n = 100; // 神经元数量
</file>

<file path="README.md">
你好呀
![](https://github.com/dongzhenmao/photo/blob/main/photo/4ybxo0yq.png?raw=true)
</file>

<file path="overall/DA.hpp">
#pragma once

#include "const_v.hpp"

struct __DA { // umol
    double __v, I;

    double rest() { return 0.05; }

    __DA() : __v(rest()) {}

    void float_v(double k) { 
        I += 0.045 * k;
    }

    double v() { return __v; } // 获取实时多巴胺浓度

    double rare_f() {
        if (v() < 0.045) return v() - 0.045;      // 削弱
        else if (v() > 0.055) return v() - 0.055; // 强化
        else return 0;                            // 不改变
    }

    double f() { // 1 ms 内
        return rare_f() * 100; 
    }

    void t_run() { // 时间步 1 ms
        __v = __v + (rest() - v()) * (0.00011 / min_dt); 
        __v = std::max(0.0, std::min(0.2, __v + I));
        I *= (0.01 / min_dt);
    }

    __DA() {
        __v = rest();
        I = 0;
    }

} DA;
</file>

<file path="dongzhenmao.cpp">
#include <stdio.h>
#include <vector> 
#include <math.h>

#include "neuron.hpp"

void view_DA_v() {
    printf("Time,DA_v\n");
    DA.float_v(1);
    for (int i = 0; i < 2000; ++i) { // 200 ms
        if (i % 10 == 0) {
            printf("%f,%.6f\n", i / 10.0, DA.v());
        }
        DA.t_run();
    }    
}

PN_Neuron a, b, c;

void view_enhance() {
    printf("Time,W\n");
    link_random(&a, &b);
    link_random(&c, &b);

    printf("%lf,%lf,%lf,%lf\n", 0, b.v, b.den.front().Ca_v, b.den.front().w);

    for (int i = 0; i < 6; ++i) {
        c.release();
        b.t_run();
        printf("%lf,%lf,%lf,%lf\n", 0, b.v, b.den.front().Ca_v, b.den.front().w);
    }

    DA.float_v(0.5);
    for (int i = 1; i < 10000; ++i) {
        DA.t_run();
        b.t_run();
        if(i % 10 == 0) printf("%lf,%lf,%lf,%lf\n", i / 10.0, b.v, b.den.front().Ca_v, b.den.front().w);
    }

}

int main() {
    view_enhance();
    
    return 0;
}

/*


*/
</file>

</files>
````

## File: run.bat
````batch
g++ dongzhenmao.cpp -o dongzhenmao.exe -std=c++14
dongzhenmao
pause
````

## File: dongzhenmao.cpp
````cpp
#include <stdio.h>
#include <vector> 
#include <math.h>

#include "neuron/brain.hpp"

Brain brain;

int main() {
    brain.build();
    for ( ; ; ) {
        
        brain.t_run();
    }

    
    return 0;
}

/*


*/
````

## File: my_algorithm.hpp
````cpp
#pragma once

#include <random>

static std::mt19937 gen(713);

int rand_int(int l, int r) { // [l, r)
    return std::uniform_int_distribution<int>(l, r - 1)(gen);
}

double rand_double(double l, double r) {
    return std::uniform_real_distribution<double>(l, r)(gen);
}

int rand_bool(double k) {
    return std::bernoulli_distribution(k)(gen);
}
````

## File: neuron/brain.hpp
````cpp
#pragma once

#include "neuron.hpp"
#include "overall/overall.hpp"
#include "../my_algorithm.hpp"

struct Brain {
    std::list<Neuron*> neuron; // 纯虚类不能实例化
    std::list<Neuron*> input_ly;
    std::list<Neuron*> hide_ly;
    std::list<Neuron*> output_ly;

    void give_DA(double k) {
        DA.float_v(k);
    }

    void t_run() {
        for (Neuron *n : neuron) n->t_run();
        DA.t_run();
        next_time();
    }

    void build();

};

void Brain::build() { // 累了, 皮层等会再实现
    for (int i = 0; i < 2; ++i) { // input
        Neuron *p = new PN_Neuron;
        neuron.push_back(p), output_ly.push_back(p);
    }

    for (int i = 0; i < 40; ++i) { // hide
        Neuron *p = new PN_Neuron;
        neuron.push_back(p), hide_ly.push_back(p);
    }
    for (int i = 0; i < 10; ++i) { // hide
        Neuron *p = new SST_Neuron;
        neuron.push_back(p), hide_ly.push_back(p);
    }

    for (int i = 0; i < 1; ++i) { // output
        Neuron *p = new PN_Neuron;
        neuron.push_back(p), output_ly.push_back(p);
    }

    for (Neuron *pre : input_ly) {
        for (Neuron *post : hide_ly) {
            if (!rand_bool(0.3) || pre == post) continue;
            link_random(pre, post);
        }
    }

    for (Neuron *pre : hide_ly) {
        for (Neuron *post : hide_ly) {
            if (!rand_bool(0.1) || pre == post) continue;
            link_random(pre, post);
        }
    }

    for (Neuron *pre : hide_ly) {
        for (Neuron *post : output_ly) {
            if (!rand_bool(0.3) || pre == post) continue;
            link_random(pre, post);
        }
    }

}
````
