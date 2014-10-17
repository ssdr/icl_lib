#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>


#define AUTH_SYNC_LEN 2
#define AUTH_LENGTH_LEN sizeof(unsigned int)
#define AUTH_CRC_LEN 2
#define AUTH_EXTRA_LEN AUTH_SYNC_LEN + AUTH_LENGTH_LEN + AUTH_CRC_LEN

#define AUTH_SYNC1_POS 0
#define AUTH_SYNC2_POS 1
#define AUTH_LENGTH_START_POS 2
#define AUTH_CONTENT_POS 6



	static unsigned short
auth_crc(unsigned char *msg, unsigned int len)
{
	if(msg==NULL || !len ) return 0;
	unsigned int i, j;
	unsigned short crc_reg = 0, current;
	for (i = 0; i<len; i++) {
		current = msg[i] << 8;
		for (j = 0; j < 8; j++) {
			if ((short)(crc_reg ^ current) < 0)
				crc_reg = (crc_reg<< 1) ^ 0x1021;
			else
				crc_reg<<= 1;
			current<<= 1;
		}
	}
	return crc_reg;
}

	static unsigned int
auth_get_random_seed(void)
{
	struct timeval tv;
	memset(&tv, 0, sizeof(tv));
	if (gettimeofday(&tv, NULL) < 0) {
		unsigned long ret = (unsigned long)(&tv);
		return ret;
	}
	return tv.tv_sec*1000000 + tv.tv_usec;
}


int auth_encode(void *buf, unsigned int len, void **retbuf, unsigned int *retlen)
{
	if (buf == NULL || !len || retbuf == NULL || retlen == NULL)
		return -1;
	unsigned char sync1 = 0, sync2, auth_rand = 0, xxor;
	unsigned char **ret = (unsigned char **)retbuf;
	unsigned int i;
	int rand_num;

	/*get two randomized numbers which first one is not zero*/
	do {
		srandom(auth_get_random_seed());
		rand_num = rand();
		for(i = 0; i<sizeof(int); i++) {
			auth_rand += ((rand_num>> (i * 8)) & 0xff);
		}
		if (!auth_rand) continue;
		sync1 = ((unsigned long)(&sync1)) % auth_rand;
	} while (!sync1);
	sync2 = ((unsigned long)(&sync2)) % sync1;

	*ret = (unsigned char *)calloc(1, AUTH_EXTRA_LEN + len + 1);
	if (*ret == NULL) return -1;

	/*
	 *      * Format of the encode buffer:
	 *           * [sync1 | sync2 | length ( 4 bytes ) | content | crc ( 2 bytes )]
	 *                */
	(*ret)[AUTH_SYNC1_POS] = sync1;
	(*ret)[AUTH_SYNC2_POS] = sync2;
	unsigned char *p = &(*ret)[AUTH_LENGTH_START_POS];
	unsigned int l = len + AUTH_EXTRA_LEN;
	for (i = 0; i<sizeof(l); i++) {
		*p++ = ((l >>i*8) & 0xff);
	}
	memcpy(&(*ret)[AUTH_CONTENT_POS], buf, len);

	xxor = sync1;
	p = &(*ret)[AUTH_LENGTH_START_POS];
	for ( ;\
			p <&(*ret)[AUTH_LENGTH_START_POS]+len+AUTH_LENGTH_LEN; \
			p++)
	{
		*p ^= xxor;
		xxor = *p;
	}
	xxor = sync2;
	p = &(*ret)[AUTH_LENGTH_START_POS];
	for ( ; \
			p <&(*ret)[AUTH_LENGTH_START_POS]+len+AUTH_LENGTH_LEN; \
			p++) {
		*p ^= xxor;
		xxor = *p;
	}

	unsigned short crc= auth_crc(&(*ret)[AUTH_LENGTH_START_POS], len+AUTH_LENGTH_LEN);
	(*ret)[AUTH_SYNC_LEN + AUTH_LENGTH_LEN + len] = crc& 0xff;
	(*ret)[AUTH_SYNC_LEN + AUTH_LENGTH_LEN + len + 1] = (crc>> 8) & 0xff;

	*retlen = len + AUTH_EXTRA_LEN;
	return 0;
}


int main(int argc, char *argv[])
{
	char input[1024];
	/*
	 * struct tm *localtime(const time_t *timep);
	 */
	time_t tm = time(NULL);
	snprintf(input, 1024, "2283644-102-1513_H.mp4??%lu", (unsigned long)tm);
	//snprintf(input, 1024, "2283644-102-1513_H?i.?10-15-122");
	unsigned char *retbuf;
	int retlen = 0;
	int ret = auth_encode(input, strlen(input), (void **)(&retbuf), &retlen);
	if (ret < 0 || retlen == 0) {
		printf("auth_encode error \n");
	}
	printf("retlen :%d\n", retlen);
	retbuf[retlen] = '\0';
	//printf("%s\n", retbuf);
	char test_url[512];
	snprintf(test_url, 512, "http://114.80.177.156/data2/video05/2014/09/18/2283644-102-1513_H.mp4?encode_seq=");
	char *p = &test_url[strlen(test_url)];// point to '\0';
	int i = 0;
	if (retlen >= 512 - strlen(test_url)) return -1; // 剩余空间不能完成下面的赋值操作
	for (i; i < retlen; i++, p+=2) {
		//*p = retbuf[i];
		sprintf(p, "%02x", retbuf[i]);
	}
	*p = '\0';
	printf("test_url: %s\n", test_url);
	CURL *curl;
	CURLcode res;

	curl = curl_easy_init();
	if(curl) {
		curl_easy_setopt(curl, CURLOPT_URL, test_url);
		curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);

		res = curl_easy_perform(curl);
		if(res != CURLE_OK)
			fprintf(stderr, "curl_easy_perform() failed: %s\n",
					curl_easy_strerror(res));
		//curl_easy_strerror(res);
		curl_easy_cleanup(curl);
	}
	free(retbuf);

	return 0;
}
