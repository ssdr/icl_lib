#include <stdio.h>

// libevent头文件
#include <event.h>

// 定时事件回调函数
void ontime(int sock, short event, void *arg)
{
	printf("time over!\n");

    struct timeval tv;
    tv.tv_sec = 1;
    tv.tv_usec = 0;
	// 重新添加定时事件（定时事件触发后默认自动删除）
    event_add((struct event*)arg, &tv);
}

int test_timeout()
{
	// 初始化
    event_init();

    struct event evtime;
	// 设置定时事件
    evtimer_set(&evtime, ontime, &evtime);

    struct timeval tv;
    tv.tv_sec = 1;
    tv.tv_usec = 0;
	// 添加定时事件
    event_add(&evtime, &tv);

	// 事件循环
    event_dispatch();

    return 0;
}
