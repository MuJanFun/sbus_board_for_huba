# sbus_board_for_huba
the code for sbus board base on stm3f100c8 using the MDK 4.70A

2016-4-21
sbus board:v0.1.1
提交请求：clear project - v0.1.1
说明：相对干净的工程空间，忽略掉了一些output文件，目前的工程不改工程文件只编译不会产生新的更新请求，只有更改了.c等文件才可以。以后就在这个版本上进行开发。
功能说明：此版本程序可以正常使用，可以将sbus数据转换为huba可以识别的串行数据，并解决了第0通道在遥控器关闭时输出不正确的bug,这个bug的原因是当遥控控关闭时各通道输出失控保护值为0，这个时候0通道是0,输出又是0，就会有一个全是0的字节产生，这个时候huba认为没有收到数据，所以通道0才没有输出，这个版本程序将遥控器通道由从0开始改为从1开始，这个问题就解决了。