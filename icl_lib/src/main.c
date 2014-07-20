/*
* main.c
*
*  Created on: 2014年3月1日
*      Author: peterxiemin
*/


#include <stdio.h>
#include "wyf_log.h"
#include "wyf_array.h"
#include "net/wyf_wrapi.h"


int main (int argc, char* argv[])
{

///////////////////////////////////////////////////////////////
//   这部分主要为log的测试
//	int ret = wyf_open_file("./log");
//	if (ret == -1)
//		wyf_log_error("%s(%d)", __FILE__, __LINE__);
//	wyf_log_info("%s(%d) xiemin shi :%s\n", __FILE__, __LINE__, "tiancai");
//	wyf_close_file();
///////////////////////////////////////////////////////////////
//    int i;
//    WYF_ARRAY *p;
//    WYF_ARRAY *sample = wyf_array_init();
//
//    //i 是一个临时变量， 保存它的地址没有意义
//    for (i = 0; i < 5; i++) {
//        int *j = (int*) malloc(sizeof(int));
//        *j = i;
//        wyf_array_push_front(sample, j);
//    }
//   
//    wyf_log_stdout("my array size is %d\n", wyf_array_size(sample) );
//   
//    while (wyf_array_empty(sample)) {
//        p = wyf_array_pop_back(sample);
//        //多重指针问题
//        wyf_log_stdout("%d\n", *(int*) p->data);
//        free(p);
//    }
//    
//    //如何仍然未清理干净， 则使用下列函数再次清理
//    while (wyf_array_empty(sample)) {
//        wyf_array_clear(sample);
//    }
//   
//    wyf_log_stdout("the end\n");
///////////////////////////////////////////////////////////////

	char *ip = "192.168.124.144";
	int port = 80;
	int ret = wyf_net_connect(ip, port);
	if (ret != 0) 
		return (-1);
}
