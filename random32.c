#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <inttypes.h>
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

static uint32_t string_to_u32(const char *s)
{
	int n;
	uint32_t v;

	n = sscanf(s, "%"PRIu32, &v);

	if(n != 1) {
		fprintf(stderr, "Error: Invalid number: %s\n", s);
		exit(1);
	}

	return v;
}

uint32_t get_random_u32_range(uint32_t range_min, uint32_t range_max)
{
	uint32_t range_size;
	uint32_t val;

	range_size = range_max - range_min + 1;

	val = range_min + (get_random_u32() % range_size);

	return val;
}

int main(int argc, char **argv)
{
	uint32_t val;

	if(argc == 1) {
		val = get_random_u32();
	} else {
		uint32_t range_min;
		uint32_t range_max;

		if(argc == 2) {
			range_min = 0;
			range_max = string_to_u32(argv[1]);
		} else if(argc == 3) {
			range_min = string_to_u32(argv[1]);
			range_max = string_to_u32(argv[2]);
		} else {
			fprintf(stderr, "Error: Invalid args\n");
			exit(1);
		}

		val = get_random_u32_range(range_min, range_max);
	}

	printf("%u\n", val);

	return 0;
}
