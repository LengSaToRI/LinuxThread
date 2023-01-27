# LinuxThread
Linux下的经典进程同步问题和银行家算法/Classic Process Synchronization question and Banker's Algorithm under Linux
使用说明：本程序基于Linux下的Qt编译器开发，使用语言为c++，包含了生产者—消费者问题、读-写者问题、哲学家问题和银行家算法的实现，并通过Qt GUI设计了相应的UI界面。

由于代码优化问题，运行哲学家问题时可能会出现吞字问题，作者的解决方法是在输出字符前加空格缓冲（摆烂）
