#define NUM_IMGS	2

struct IMG {
	unsigned int width;
	unsigned int height;
	unsigned char *addr;
};

extern struct IMG img[NUM_IMGS];
