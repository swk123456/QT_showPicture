# QT多线程显示图片

![UI图片](UI.jpg)

这个应用将图片显示在两个QLabel里\
两个线程读取图片在picture文件夹\
exe文件夹内showPicture.exe可运行\
\
\
两个线程同时按指定顺序读取文件（图片）\
读取的文件显示在主窗口的两个QLabel当中\
开始按钮 实现启动线程，开始更新图片\
暂停按钮 实现图片暂停刷新\
结束按钮 实现停止刷新图片，退出线程\