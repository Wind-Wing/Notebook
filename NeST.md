# NeST: NN synthesis tool
一个基于数据自动生成紧凑网络的方法，特别是在大数据集上。
### time: 2018/02/05

## Introduction
1. NeST 从一个种子网络开始，通过基于梯度的增长和基于尺度的对于神经元与连接进行剪枝，来迭代的调整网络结构。最终生成一个紧凑的网络结构。（手工设计的网络往往存在很多的冗余参数）
2. 传统的网络生成方法遍历结构的参数并且训练相应的网络结构直到其分类的收益递减点。（guess：传统方法对于一个极其冗余的网络进行剪枝，直到该任务的收益递减点？是一种剪切算法而不是生成算法。）这种方法有以下的缺陷:

    * 结构固定：多数BP模型训练参数而不是结构。
    * 时间冗长：通过试错的方式找到合适的网络结构十分低效，特别是针对大数据集。
    * 大量冗余：多数网络存在参数冗余的情况。
3. NeST根据人脑发育的过程同时训练参数和结构，来解决传统方式的缺陷。

    * 从一个种子网络开始。
    * 基于梯度信息（gradient information - baby brain)来增加神经元以及连接。这使得生成的网络可以适用于不同的任务。
    * 基于尺度信息（magnitude information - adult brain)来减少神经元以及连接。这使得生成的网络不会冗余。

## Traditional method
1. 传统的自动生成网络结构策略可以分为两种：
> 进化算法（EA，evolutionary algorithm）
>
* 一种在离散复杂的结构空间中进行搜索的方式
* 十分低效所以不适合大数据集
* pathNet采用模块化以及每一层sum的方式有效的减少了遗传算法的搜索空间，因此可以应用到更大的数据集上，ex：imageNet

> 结构适应型算法（SA，structure adaptation）
>
* 利用网络的状态特性（ex：权重的分布情况）来调整网络结构。
* 可以分为：  
    > constructive approach
    >
    * 对于深度大型神经网络十分低效
    * 存在不可忽视的网络冗余情况
    > destructive approach
    >
    * 依赖于一个大型的训练好的网络作为裁剪的起始状态
    * 然而训练一个大型网络到收敛是一个十分耗时的是错过程
2. SA到现在为止发展的并不是很成熟。

## 合成方法（Synthesis Methodology）
* NeST结合了SA中的construction和destruction方法
### pipeline
1. 初始拥有一个种子网络，拥有部分稀疏的连接
1. 设置最大网络尺寸S和期望的准确率A
2. s = sizeof(Net), a = test(Net), train(Net)
3. Construction

    if s <= S and a < A :

    迭代地 [增加连接神经元、连接、特征图并训练], 直到s >= S or a >= A
4. Destruction

    迭代地 [剪枝并训练], 直到a < A

### Construction ( Gradient-based Growth )
> 增加连接
* 

> 增加神经元

> 增加特征图
### Destruction ( Magnitude-based Pruning )