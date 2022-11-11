#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

bool get_bytes(int n, void *bytes_out)
{
	FILE *fp;
	size_t nread;
	bool b;

	fp = fopen("/dev/urandom", "r");

	if(!fp) {
		b = false;
		goto out;
	}

	nread = fread(bytes_out, 1, n, fp);

	if(nread != n) {
		b = false;
		goto out;
	}

	b = true;

out:
	return b;
}

uint32_t get_random_u32(void)
{
	bool b;
	uint32_t val;

	b = get_bytes(4, &val);

	if(!b) {
		fprintf(stderr, "Error: Failed to get random bytes\n");
		exit(1);
	}

	return val;
}

int main(int argc, char **argv)
{
	uint32_t val;

	val = get_random_u32();

	printf("%u\n", val);

	return 0;
}
