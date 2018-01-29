# [LeNet] 1998
### time: 2018/01/29
1. 主旨：更好的模式识别系统可以通过更多地依赖于自动学习而不是手工设计启发式信息来完成。
1. convolution neural network is specifically designed to deal with the variability of 2-D shapes.
2. 传统的模式识别系统可以分为两部分：

    a. 特征提取模型（手动特殊设计）

    * 要求提取的特征容易匹配或者区分
    * 要求提取的特征不会随着输入的变形而改变

    b. 可训练分类模型（通用可训练）
3. 由于传统系统的特征提取部分依赖于人工设计，所以十分低效。
    
        idea：现在的ML模型也专注与模型的设计，是否应该把精力放在设计可以自组织模型的通用模型上面。
5. 需要手工设计特征提取器的原因是分类器使用的技术限制在低维空间。而现在，三个因素改变了这种状况：
    * 计算机计算能力的增强使得允许依赖于更加暴力的神经元模型而不是算法改进型神经元。
    * 市场上的巨大利润使得巨大的训练数据集得以产生。
    * 可用性。强大的ML技术可以使用这些巨大的数据集来做出复杂的决策。
6. 在多层NN的情况下，结合知识的好方法是使其体系结构适应该任务。ex：对于二维的图像识别任务采用conv神经网络。
7. 描述现代ML梯度下降训练流程
    * E(test) - E(train) = k*(h/P)^a
    E: Prediction error rate
    k: A constant
    h: a measure of “effective capacity” or complexity of the machine
    P: the number of training examples
    a: a number between 0.5-1.0
    * inference:为了使得模型收敛，就需要提高模型的信息容量h。但是这样会使得E(test)与E(train)之间的gap变大，所以需要更多的样本P使得gap变小。
    * structural risk minimization:希望在减小训练集误差的同时减小gap，即找到最合适的h

        设定一组拥有递增的权重参数空间的h递增的训练模型，使得后一个模型是前一个的超集。然后选着合适的训练模型对于表达式
        min E(train) + b*H(W)进行优化。

        b:      A constant
        H(w):   measure h
8. 

        
