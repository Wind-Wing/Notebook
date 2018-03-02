# Bugs I meet in Tensorflow and Solutions

## valueError
1. get_variable 与 variable
    get_variable 不能自动解决在同一个namescope内的变量名冲突问题，要手动设置reuse。而variable可以。
2. session与namescope
* sess用来给固定的图灌入数据，但是当sess关闭的时候图结构仍然标记在显存中。这时候如果一个程序中有要重复运行多次sess时（ex：在DetaNet中）在重新修改图的时候，就有可能导致变量重复定义的问题（valueError：variable already exist）。
* 解决方案：

  1.给每一次运行sess时都在不同的namescope中定义图结构。
  
  2.将变量定义的函数从get_variable改为Variable
