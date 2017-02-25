#include "img.h"

extern unsigned char _binary_bgra_os5_ss_bgra_start;
extern unsigned char _binary_bgra_yux_bgra_start;

struct IMG img[NUM_IMGS] = {
	{640, 356, &_binary_bgra_os5_ss_bgra_start},
	{640, 480, &_binary_bgra_yux_bgra_start}
};
