# [LeNet] 1998
### time: 2018/01/29
### content: 理解如何合适的利用卷积层以及卷积层的优点

## part1 Introduction
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
6. 尽管自动学习是有益的，但是如果没有任何关于任务的先验知识，任何学习方法都是没有办法成功的。
因此，对于多层NN，利用先验知识的方式是使其体系结构适应该任务（针对不同的任务，设计合适的网络结构）。ex：对于二维的图像识别任务采用conv神经网络。
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
8. 基于梯度的学习：通过评估参数的微小变化对于损失函数的影响来使得评估函数最小化。

        随机梯度下降（online update）：在拥有大量冗余数据样本的情况下，采用噪声版本的平均梯度来更新参数，虽然会使参数的轨迹围绕一个值上下波动，但是这通常比常规的梯度下降要快速。
        
9. 梯度下降广泛应用于复杂的ML系统基于一下三个发现：
    * 损失函数取局部极小值在实践中并没有太大的影响。

            这是一个理论难题。有猜想认为如果神经网络的表达能力超过任务需求的话（通常在实践中确实如此），参数中多余维度的存在使得不可到达的区域的存在的风险降低了。
            > 如果对于一个紧凑的网络是否由此性质？ ex：NeST
    * 出现在非线性多层网络中有效计算梯度的方法，如：反向传播算法。
    * 证实了在神经网络上采用反向传播算法并结合sigmoid单元可以有效解决复杂的学习任务
10. 手写文字识别的一个难点是如何将单个字符从图像中分割出来。
    分割的手段HOS有两种解决方案：
    * 用字符串级别而不是字符级别的训练样本，损失函数是用来衡量分割出错的概率的
    * 用字符识别器扫过整个字符串，利用字符识别器可以识别处在视野中央的字符的属性来实现分割功能。但是开销很大。
    * 现在采用深度学习的方式实现分割，ex：FCN
11. 那时的模式识别系统是由许多模块组成的，现在的类似于目标检测的系统也是由多模块组成的么？
    * 由于系统由多模块组成，所以提出了全局训练的方式。 
    * 通常模块间的数据传输以带权边图的方式传递（成为GTN）。现代的多层神经网络采用矩阵相乘的方式代替图
    * 为了使得全局损失函数可导，整个网络以前向传播的方式构建。并且确保每一层连续可导。
12. 对于GTN，也可以采用梯度下降的方式训练。虽然对于离散的图进行求导看起来很矛盾，但是见后。


## part2 Convolutional Neural Network
1. 那时候的一个发展趋势是更多的依赖于特征提取器的自动学习而不是人工设计。而卷积层可以认为是自动合成特征提取器。
2. 卷积神经网络相对于全连接网络的优势在于：
    * 对于全连接神经网络，一张图片在输入的时候需要对应像素个数的神经元输入点。由于图像一般很大，所以会导致网络的参数很多，导致网络的表达能力h变大。根据公式，这样就需要更多的训练样本和时间，占用的内存也大。
    * 采用卷积作为第一层网络或者中间层网络可以通过卷积操作提取特征图减小图片大小从而有效减小参数规模。
    -------
    * 对于全连接神经网络，输入必须先进行归一化并且把数据放在输入野的中间。但是这样的处理不可能是完美的，总换对于样本产生偏差和变形。为了保持网络对于输入变形的不变性，全连接神经网络可以采用扩大网络规模的方式实现。但是从训练结果来看，这样子会使各层网络的不同神经元的参数存在模式相似的问题。
    * 卷积网络通过在图片上以滑动的方式来将同一种参数配置应用在图片的不同位置来代替全连接网络中参数重复的问题，从而以更小的代价达到实现对于输入变形不变性。（比如：对于图像的偏移，卷积窗口滑动方式就可以很好地克服）
    （idea：卷积网络的发现一部分可以归功于对于全连接神经网络训练后各层参数观察的结果。最近几年类似的研究方式还发现了全链接层权重剪枝以及DorefaNet）
    -------
    * 全连接神经网络二维输入的拓扑结构被忽略。
    * 卷积层通过控制每次对于图片的局部进行卷积操作从而提取出局部特征。卷积操作会将图片的拓扑结构加入计算，从而根据局部的相对位置关系提取特征，具有更好的输入变形不变性。
    * 局部相关性是在识别空间或时间对象之前，提取和结合局部特征的著名优势的原因，因为相邻变量的关系组合可以划分为少量的类别(例如:边缘,角落,等等）。
3.  卷积不仅仅适合于图像的处理，对于其他的2-D数据也有很好的效果，比如：带有时序信息的音频识别，语音识别。
4.  卷积层结合了三种结构性的方案来解决一定程度上的变形：
    * 局部接受域：此处指卷积窗口一次只处理输入图像的一部分。（受到猫的视觉系统中对于局部敏感神经元的启发）
    * 共享权重：指一个卷积核会在图片上滑动。
    * 空间或者时间降采样：pooling，用于减少数据规模，否则数据量会越来越大。同时也弱化特征的绝对位置的影响。
5. 同一个卷积层中的不同卷积核，由于被训练出了不同的权重和偏置，因此可以提取出不同的特征。
6. 卷积层可以提取出图片的基本特征（边缘、端点、转角等）用于后续的层产生更加高级的特征。
7. 对于卷积来说，一旦一个特征被提取出来，其绝对位置就变得不重要，应当关注该特征与其他特征的相对位置关系。这种思想也正是CNN逐层提取特征的设计理念。在CNN中，采用池化的方式进行降采样，从而以降低特征图分辨率的方式来达到弱化特诊绝对位置的影响，突出相对位置关系。
8. 为什么网络中常常会出现卷积之后立刻跟着一个池化层？

    因为卷积通过增加特征图数目使得数据的表达丰富性增加，从而补偿池化为了弱化特征的绝对关系而降低了特征图的清晰度。
9. 在LeNet5中，池化层2->卷积层3的链接不是完全的，只有部分链接：
    * 使得连接保持在合理的数目之内。
    * 打破网络中的对称性，希望提取出互补的完全不同的特征。
10. RBF作为输出层，每一个RBF对应一个类。
11. RBF
    * RBF(Radial Basis Function)径向核函数，核函数的一种。（关于核函数见https://www.zhihu.com/question/24627666）
    * 核函数：可以使用核函数，将原始输入空间映射到新的特征空间，从而使得原本线性不可分的样本可在核空间可分。
    * RBF在概率论中可以描述为未正则化负指数型高斯分布。
    * 此处用于描述输入与目标模式的匹配程度。
    * 在分类类似字符的场景，RBF的参数应该在选择-1或者1时，应当根据特定的输出图像以对于相似的字符（ex: I、i、O、o、0）得到好的效果。（见论文Fig. 3）
    * RBF的参数代表了一种特定的图像模式，初始值需要手动根据不同的图片特殊设计。参数可以不变，也可以训练，但是初始值应当手动设计。
    * Page8 输出层RBF的设计并不是很清楚，需要补充背景知识（SVM）
12. 在该模型中，损失函数的设计应当结合RBF层输出函数的设计。
13. 如果损失函数是计算全连接层F6的输出与RBF设定的参数的平均欧氏距离的话，存在几个缺陷：
    * 如果RBF的参数允许训练的话，存在一个不合理解：网络忽略输入，F6输出常量=参数。loss=0
    * 由于要区分一个图像是否是字符，因此需要一个非字符分类标签，而这个标签与其他的标签不是同等地位的。因此此处缺少分类之间的竞争（没有完全了解Page9右侧）
    * 解决方案：采用MAP（极大后验概率）代替之前的平均欧氏距离以及与其等价的MSE（极大似然估计）（原理未理解，需要数学背景知识）
14. 反向传播算法：由于在CNN中存在权重共享，所以对于传统的BP算法要进行调整。
    首先假设这是一个没有权重共享的卷积网络，求出各个连接的偏导。然后对于共享的参数，将所有共享这个参数的连接的偏导加起来构成关于该参数的偏导。（理解不够深入，需要具体代码实践）

## part3 实验结果
1. 尽管单个数字识别是设计识别系统的众多难点之一，但这仍然是一个很好的比较不同形状识别模型的标准。
2. 在LeNet5 on MNIST当中消除了过拟合的现象。
    * 由于learning rate保持相对比较大（该实验采用变化的学习率），所以权重不会停留在局部最小值，而是在这周围随机震荡。
    * 由于权重的震荡，cost function的平均值会在一个更大的权重局部最小值域内搜索，从而使得cost均值更小。
    * 因此，保持学习率相对较大以及采用随机梯度下降的方式，可以起到和正则化类似的效果。即在更广泛的最小值域内选择，缓解过拟合问题。
    * 在更广泛的最小值域内搜索，可以使得权重参数的分布熵值更大，这对于减少全局错误率有利。
3. 更大的训练集可以提高准确率。
    *  同随机扭曲原始图像可以获得更大的训练集。
    *  图像扭曲包括：平面仿射变换、压缩、水平裁剪。
4. 对于网络分类错误的样本：
    * 有一些样本确实模棱两可。
    * 有一些样本可以被人类完美识别出来，尽管它们的书写风格在训练样本中没有代表性。
    * 对于第二类样本，进一步扩大训练集的规模可以带来更高的准确率。

## need to learn
1. details of conv operation
2. pooling的具体实现，是否要进行参数训练或者是激活函数以及具体的滑动方式 （in paper page7，is seems so）
如果要的话，重新阅读page7左下方的1/4  （可以通过阅读code解决）
3. CNN是受语音信号处理中时延神经网络（TDNN）影响而发明的
4. Page8 输出层RBF的设计并不是很清楚，需要补充背景知识
5. 结构分险最小化：可以参考感知机与SVM的区别。
6. broader minimum确切地指什么？
