<<<<<<< HEAD
# ecs
=======
>>>>>>> def39e1c2339f3da0058b389ed8bdc8d61fe7a91
# 2018华为软件经验挑战赛-
    这个程序来自于我今年4月份参加的华为软件经验挑战赛，这里记录一下我的关于这个比赛的一些经验于学习历程。
*这个程序来自于我今年4月份参加的华为软件经验挑战塞，当时刚刚参加这个比赛的时候，也真的是一头雾水，不知道任何关于机器学习的知识，什么线性回归，逻辑回归，梯度下降发就跟不要说了。


*赛题介绍：这个比赛乍看真的任何想法，但是仔细想一下，加上官方的提示，就是一个拿之前的历史虚拟机数量，然后训练模型，实现对给定时间段的虚拟机出现数量的预测。

 
*当时看到了这个比赛，下定了决心，想在比赛中拿一个名次，于是没日没夜的去学习机器学习算法，尝试和失败了n多次后，终于我的第一个机器学习的模型成功生成了。这个模型基于一元的线性回归模型，将不同虚拟机根据时间的关系分别生成各自对应的预测模型，在根据这个模型分别预测，汇总，输出。

 
 
*而这个赛题的另一个考察点，就是对于预测出来结果的一个分配问题，给定物理机的实际内存和cpu的数量，问将这些虚拟机布置到物理机上，如何才能使物理机的利用率最高，（内存或者cpu其中一个最高即可，由input文件内指定），这个问题其实是一个多重背包的问题，我在这里实现了，但是没有使用，具体原因是当时我时间很赶了，可是上传到评分系统后一直无法正常运行，可是我在本地环境和其他运行系统的环境试过都可以，我还尝试了各种评测数据，发现还是ok的，最后我没办法，提交效率并不高的，按顺序优先填充的算法。



*这次的比赛最后的成绩是80名左右，这里需要反省一下，本来这个比赛前72名就能进决赛的，而我在比赛的最后三四个小时还能保持在60名左右，可是越到后面我的排名一名名的往下掉，最后掉出了72名，我不应该在自己进了决赛就大意的，还是有许多大神在比赛的最后一段时间才提交的代码，以后要需要时刻保存警惕，不能睡死在温柔乡里。


*最后说一下这段代码如何编译执行，linux下，进入主文件夹，`执行目录下的build.sh，./build.sh`,等待执行编译完成，显示100%就是编译完成，然后`执行bin目录下的esc可执行文件给进训练数据的文件名，预测的要求文件，和最终的输出文件名`，就可以开始训练数据，完成预测，输出到最后那个文件中。
# 2018huawei-
