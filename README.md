# car
 	rt-thread小车
	无线控制小车
## 作品基本思路

        小车分为车和控制器两个部分，由两个esp8266模块进行通信，控制器发送控制信息来控制小车行走，并且可以通过相关的模块收集环境
    信息，发送回控制器，目前小车只实现了最基本的控制、显示功能。
        小车通过控制器的按键扫描程序得到按键信息，通过控制器的esp8266模块发送数据。车的esp8266模块接送数据，AT client以URC数据
    处理的方式获取数据中包含的控制信息，并保存在变量CARDATA中。
        小车运行线程通过getCARDATA函数得到小车的控制信息，与小车行走状态相匹配，从而控制小车的速度与方向。
        串口屏显示线程通过getCARDATA函数得到小车的控制信息，并且打印相应的信息。
        小车还可以添加不同的模块与相应的程序来实现不同的功能。
##  软件部分

	Rt-thread操作系统。
##  硬件部分

###  硬件清单

    单片机STM32F103ZE    X2
    ESP8266模块          X2
    串口屏               X1
    按键模块(自己焊接)    X1
    三轮小车             X1
    L298N模块            X1
    5V直流电源           X2
#### 按键图片
![image](https://github.com/catHhui/files/blob/master/images/key.JPG)
###  关于 ESP8266模块：
#### 车上的ESP8266:
  	    已经设置为AP模式，创建WIFI热点：RTT-CAR  密码：12345678（模块断电后重启此设置不失效）
	    程序设置ESP为服务器（模块断电重启此设置失效）
#### 控制器上的ESP8266:
  	    已经设置为AP模式，创建WIFI热点：RTT-CAR  密码：12345678（模块断电后重启此设置不失效）
	    程序设置ESP为客户端，开启透传模式（模块断电重启此设置失效）
	也可以使用程序初始化ESP（直接使用esp8266模块，一开始不需要对esp设置）
### 关于串口屏TJC3224T022:

	已经设置文本 t0 为：OFF，t1为：方向，t2为：速度，t3为：NULL, t4为：NULL（即上电显示此内容）
	程序改变文本t0、t3、t4内容（串口屏断电重启此设置失效）
### 关于小车控制信息：

        车上单片机的 uart3 为AT client，eap8266模块为AT server，控制信息为AT server下发的以字符‘d’结尾的URC数据（可自定义
    URC数据处理方式），其中第10个字符为控制信息，保存在全局变量 CARDATA 中，其他 .C 文件可以使用外部函数 getCARDATA() 获取
    小车的控制信息。
### 其他

    小车可以外加其他模块。
    
## 实物图

#### 小车图片
![image](https://github.com/catHhui/files/blob/master/images/xc.JPG)

![image](https://github.com/catHhui/files/blob/master/images/xiaoche.JPG)
#### 控制器图片
![image](https://github.com/catHhui/files/blob/master/images/control.JPG)
      
## 演示视频
    
![video](https://github.com/catHhui/files/raw/blob/master/videos/video_20190307_193038.mp4)
