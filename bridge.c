#include "bridge.h"

static volatile long unsigned int bitlock;

static int create_bridge(const char* brname)
{
	int status = 0;

	return status;
}

static void shutdown(void)
{
	clear_bit(0, &bitlock);

}

int init_bridge(struct bridge_ops* brops)
{
	int status = 0;
	
	if(NULL == brops)
		return -EINVAL;
	
	if(test_and_set_bit(0, &bitlock))
		return -EALREADY;		

	memset(brops, 0, sizeof(*brops));
	brops->create_bridge = create_bridge;
	brops->shutdown = shutdown;
	brops->initialized = 1;
		
	return status;
}
