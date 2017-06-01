PCShare是一款强大的远程控制软件，可以监视目标机器屏幕、注册表、文件系统等。

一、软件使用方法介绍：

1. 启动PcShare.exe，这是控制端主程序，该程序会在8080端口上监听被控制端的连接。

2. 生成被控制端宿主程序，点击控制端主界面上的“生成客户按钮”：

3. 生成一个新的宿主程序，这个程序的名称叫ps.exe，然后将ps.exe与PcStat.exe一起发给要被控制的机器上。在被控制的机器上启动PcStat.exe，过一会儿被控制端就连接上控制终端了，控制终端就可以对被控制终端进行各种控制了。


二、原理介绍

控制端生成的宿主程序ps.exe实际上是一个后台程序，该程序先由PcStat.exe启动，ps.exe被启动后，释放自己二进制文件尾部的节，该节实际上是一个dll文件，这个dll可以根据生成时的配置信息以三种方式运行：1、独立进程运行 2、注入到ie浏览器中运行 3、注入到windows资源管理中运行（explorer.exe）。dll运行以后会hook操作系统的各种消息，以实现对该机器的监控；并通过socket连接控制终端PcShare.exe，将获得的各种信息以http协议发给PcShare.exe。PcShare.exe对目标机器的控制也是通过http协议发回给dll程序。


三、程序编译：

程序使用mfc框架开发，用VS2015打开PcShare目录下PcShare.sln，运行编译即可。如果需要调试控制端或者被控制端，你可以先在外部启动一个，再在VS里面调试另外一个。具体详情参见：http://blog.csdn.net/analogous_love/article/details/72835754

四、问题反馈
  QQ: 906106643   email: balloonwj@qq.com  QQ群：49114021
