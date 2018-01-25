# PathNet
### time : 2018/01/23
### code : https://github/xjtuwyd/pathnet

## Overview
1. artificial general intelligence (AGI) it would be efficient if multiple users trained the same giant neural network, per-mitting parameter reuse, without catastrophic forgetting.
2. uses agents embedded in the neural net-work whose task is to discover which parts of the network to re-use for new tasks. 
3. Agents are pathways (views) through the network which determine the subset of parameters that are used and updated by the forwards and backwards passes of the backpropogation algorithm.
4. 对于fix的模块，path和模块内的参数(weight & biases)都不会修改

## code
file binary_mnist_pathnet_with_conv.py
### read date
1. 数据分为a、b是针对两个不同的task
2. 数据分为a1与a2是因为这只是一个二分类任务，而mnist是一个十分类任务。因此要提取出两中样本并且把标签也修改为二分类的形式
### variables
x                   # input images
y_                  # input labels
y                   # reference labels

geopath             M*L=1       #
fixed_list          M*L=0       # mark fixed path and modules
weight_list         M*L=normal  # record weights in every module
biases_list         M*L=0.1     # record biases in every module
layer_modules_list  M  =None    # store output of each module in a layer for calc sum average.

var_list_to_learn               # record all the variables need to learn, ex: weights, biases
accuracy            1*1         # accuracy of current batch
train_step          op          # ops to minimizs cross_entropy on var_list_to_learn
geopath_set         candi*L*M   # store all candiants

var_update_ops          len(var_list_to_learn)  # ops of assigning var_update_placeholders[i] to var_list_to_learn[i]
var_update_placeholders len(var_list_to_learn)  # shape of var_list_to_learn[i]
geopath_update_ops          M*L # ops of assigning geopath_update_placeholders[i][j] to geopath[i][j]
geopath_update_placeholders M*L # shape of geopath[i][j]

var_fix_ops                 len(var_list_to_fix) # 同上
var_fix_placeholders        len(var_list_to_fix) # 同上
var_list_to_fix                 # a list record fixed weights and biases
var_list_fix                    # packup the value of weights and biases in var_list_to_fix


##　pipline
1. 遗传算法
2. fix task1
### net struct
如果fixed_list == 0, 则将该处的weights和biases加入var_list_to_learn
### 遗传算法
1. 随机生成20种候选的path
2. 从20个候选中随机选出2个竞争者
3. 将一个候选的路径插入到geopath变量中
4. 训练FLAGS.T个epoch后计算每个epoch的准确率平均值acc_geo
5. 根据acc_geo来判断哪个竞争
6. 用获胜者的geopath覆盖其他竞争者的geopath并且变异（获胜者本身不变异,变异是指把某条路径转移到同一层的其他路径上，可能会重叠）
### train task1
循环执行遗传算法，将胜利者的accuary与阈值比较，如果超过，则训练结束。胜利者的path就是task１的最优路径。
### fix net of task1
将task1的最优路径标记在fixed_list中，防止被修改。
### train task2
1. 初始化variables　
1. 根据fix选择没有fix的要训练的值加入var_list_to_learn
2. 重新载入之前fix的值
3. 重新设置与var_list_to_learn相关的ops
4. 同task1

### evaluate

# tensorflow
1. 定义网络结构和tensor维度（执行流程与网络结构分离，执行中不能改变网络结构）
2. 定义所需要的变量的计算流程及其维度
2. 设置初始值
3. 定义执行流程
4. 开始训练

* sess.run(ops,feed={placeholder:feed_var})
    1. feed_dict的作用是给使用placeholder创建出来的tensor赋值。
    2. 其实，他的作用更加广泛：feed 使用一个值临时替换一个 op 的输出结果。
    3. 你可以提供 feed 数据作为 run() 调用的参数。
    4. feed 只在调用它的方法内有效, 方法结束, feed 就会消失。
* sess.run(tf.global_variables_initializer()) 
    就是 run了 所有global Variable 的 assign op，这就是初始化参数的本来面目。

# Need to learn 
1. A3C
异步的优势行动者评论家算法（Asynchronous Advantage Actor-Critic，A3C）是Mnih等人根据异步强化学习（Asynchronous Reinforcement Learning， ARL） 的思想，提出的一种轻量级的 DRL(Deep reinforcement learning) 框架，该框架可以使用异步的梯度下降法来优化网络控制器的参数，并可以结合多种RL算法。
Q学习是一种model-free（不用学习环境模型）的基于off-policy（学习过程中执行的策略与值估计使用的策略不一样）的temporal difference（TD）方法，也是RL中流传最为广泛的一种学习方法。
其实深度学习本身也正是把更多注意力拉回到特征学习上来。
深度学习前的神经网络功能上只用于分类或回归，没有无监督学习提取特征的功能，因此难以直接处理裸数据，比如像素级数据（raw pixels）。

2. In A3C : a value function readout and a policy readout

2. tournament selection algorithm

# Question
1. 把变量定义部分放入module会不会导致在执行task2时，变量会被重新初始化？（task2重新载入过值->tf的具体执行原理）
    不会。tensorflow中的变量定义只会被执行一遍，然后就变成了静态的流程图进行运算了，初始化不会被重复执行。
2. 加入卷积层后，是否要将卷积核也加入var_list_need_to_learn以及fix？
    要。源代码只考虑了weights和biases，没有考虑卷积核的训练与固定。
3. task2新加入的path是否会影响task1的ｍodule的输出结果？
    不会。在应用中，每一个task对应一个path矩阵，根据矩阵选择路径。
4. 为什么要用占位符写入值？不可以直接赋值么？这是tf的特定机制决定的么？
    是由于tensorflow仅仅支持静态流程图所决定的。
5. 为什么task2要重新global_variables_initializer()？
    因为那些没有被task1激活的modules也被task1训练了，所以需要把这些module里面的参数还原为初始值。