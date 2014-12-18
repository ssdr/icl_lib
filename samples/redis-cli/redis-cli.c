#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <hiredis.h>
#include <icl_random.h>

int domain(redisContext *c, int seed) 
{
    unsigned int j;
    //redisContext *c;
    redisReply *reply;
    
    /* PING server */
    //reply = redisCommand(c,"PING");
    //printf("PING: %s\n", reply->str);
    //freeReplyObject(reply);

    /* Set a key */
	char *p = get_char128_random(seed);
	//printf("seed: %d \t key: %s \t value : %s\n", p, p);
    reply = redisCommand(c,"SET %s %s", p, p);
	free(p);
    //reply = redisCommand(c,"SET %s %s", "foo", "hello world");
    //printf("SET: %s\n", reply->str);
    freeReplyObject(reply);

    ///* Set a key using binary safe API */
    //reply = redisCommand(c,"SET %b %b", "bar", (size_t) 3, "hello", (size_t) 5);
    //printf("SET (binary API): %s\n", reply->str);
    //freeReplyObject(reply);

    ///* Try a GET and two INCR */
    //reply = redisCommand(c,"GET foo");
    //printf("GET foo: %s\n", reply->str);
    //freeReplyObject(reply);

    //reply = redisCommand(c,"INCR counter");
    //printf("INCR counter: %lld\n", reply->integer);
    //freeReplyObject(reply);
    ///* again ... */
    //reply = redisCommand(c,"INCR counter");
    //printf("INCR counter: %lld\n", reply->integer);
    //freeReplyObject(reply);

    ///* Create a list of numbers, from 0 to 9 */
    //reply = redisCommand(c,"DEL mylist");
    //freeReplyObject(reply);
    //for (j = 0; j < 10; j++) {
    //    char buf[64];

    //    snprintf(buf,64,"%d",j);
    //    reply = redisCommand(c,"LPUSH mylist element-%s", buf);
    //    freeReplyObject(reply);
    //}

    ///* Let's check what we have inside the list */
    //reply = redisCommand(c,"LRANGE mylist 0 -1");
    //if (reply->type == REDIS_REPLY_ARRAY) {
    //    for (j = 0; j < reply->elements; j++) {
    //        printf("%u) %s\n", j, reply->element[j]->str);
    //    }
    //}
    //freeReplyObject(reply);

    /* Disconnects and frees the context */

    return 0;
}



int main(int argc, char *argv[])
{
	/* init */
    redisContext *c;
	const char *hostname = (argc > 1) ? argv[1] : "127.0.0.1";
	int port = (argc > 2) ? atoi(argv[2]) : 9998;

	struct timeval timeout = { 1, 500000 }; // 1.5 seconds
	c = redisConnectWithTimeout(hostname, port, timeout);
	if (c == NULL || c->err) {
		if (c) {
			printf("Connection error: %s\n", c->errstr);
			redisFree(c);
		} else {
			printf("Connection error: can't allocate redis context\n");
		}
		exit(1);
	}

	/* test */
	int i;
	for (i=100000001; i < 800000000; i++) {
		domain(c, i);
	}
	redisFree(c);
	return 0;
}
