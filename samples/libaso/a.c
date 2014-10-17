#include <stdio.h>
#include "b.h"
extern "C" {
#include "c.h"
}
int main(int argc, char *argv[])
{
	boo();
	coo();
	return 0;
}
