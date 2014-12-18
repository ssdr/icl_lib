#include <stdio.h>
#include <string.h>
#include <libmemcached/memcached.h>


#include <libmemcached/memcached.h>
int main(int argc, char *argv[])
{
	const char *config_string = "--server=localhost:11211";
	memcached_st *memc = memcached(config_string, strlen(config_string));
	char *key= "foo";
	char *value= "value";
	memcached_return_t rc= memcached_set(memc, key, strlen(key), value, strlen(value), (time_t)0, (uint32_t)0);
	if (rc != MEMCACHED_SUCCESS)
	{
		printf("(%d)\n", rc);
	}
	memcached_free(memc);
	return 0;
}
