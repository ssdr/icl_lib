#include <stdio.h>
#include <string.h>
#include <libmemcached/memcached.h>
#include <libmemcached/memcached.h>
#include <icl_random.h>
#include <time.h>

//#define ACCESS_TIME  10000

static unsigned int ACCESS_TIME;

int test_main(const char *config_string)
{
	memcached_st *memc = memcached(config_string, strlen(config_string));
	int i;
	int start = time(NULL);
	printf("start:%d\n", start);
	for (i = ACCESS_TIME; i < ACCESS_TIME + ACCESS_TIME * 2; i++) {
		char *key= get_char128_random(i);
		char *value= get_char128_random(i);
		//char key[16];
		//char value[16];
		//snprintf(key, 16, "%d", i);
		//snprintf(value, 16, "%d", i);
		//printf("key: %s, value: %s\n", key, value);
		memcached_return_t rc = memcached_set(memc, key, strlen(key), value, strlen(value), (time_t)0, (uint32_t)0);
		if (rc != MEMCACHED_SUCCESS)
		{
			printf("(%d)\n", rc);
		}
		free(key);
		free(value);
	}
	int end = time(NULL);
	printf("end:%d\n", end);
	int divisor = end - start;
	if (divisor != 0) {
		printf("tps: %d\n", ACCESS_TIME/divisor);
	}
	else {
		printf("divisor: %d\n", divisor);
	}
	memcached_success(memcached_flush(memc, 0));
	memcached_free(memc);
	return 0;

}

int test_mem() 
{
	//const char *config_string = "--server=imcp.ifeng.com:12121";
	//const char *config_string = "--server=127.0.0.1:11211";
	const char *config_string = "--server=imcp.ifeng.com:1340";
	printf("config_string: %s\n", config_string);
	test_main(config_string);
}

int test_tts() 
{
	const char *config_string = "--server=imcp.ifeng.com:1978";
	printf("config_string: %s\n", config_string);
	test_main(config_string);
}

int main(int argc, char *argv[])
{
	if (argc == 2) {
		ACCESS_TIME = atoi(argv[1]);
	}
	else {
		return 0;
	}
	//test_tts();
	test_mem();
}
