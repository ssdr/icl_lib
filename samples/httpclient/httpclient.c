#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

int main(int argc, char *argv[])
{
	/*
	 * struct tm *localtime(const time_t *timep);
	 */
	char test_url[] = "http://172.30.204.122/index.html";
	CURL *curl;
	CURLcode res;

	int i;
	for (i = 0; i < 1025; i++) {
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
	}

	return 0;
}
