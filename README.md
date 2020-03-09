本例子主要演示如何通过qt dbus发送自动的数据结构。

Student讲自己注册到dbus,通过needHelp信号发送Letter到parent,parent收到回复后
调用student的reciveParcel发送Parcel对象，Student收到数据之后，发送parcelRecived信号通知已经收到包。

使用方法，本代码需要puppy编译工程支持
git clone https://gitee.com/qq2820/puppy.git 

cd puppy 

git clone https://github.com/onier/QDBus.git

mkdir build
cd build 
cmake -DCMAKE_BUILD_TYPE=debug ..
make 
