#include "netifs.h"
#include "defs.h"

static int find_netdev(struct net_device** ndev, char* devname)
{
	int status = 0;
	int found = 0;
	struct net_device* nd;

	if(NULL == ndev || NULL == devname)
		return -EINVAL;

	read_lock(&dev_base_lock);
	// Search the init_net namespace...
	// Assuming a standard physical network device,
	// this should be where it's located.
	for_each_netdev(&init_net, nd) {
		if(0 == strcmp(nd->name, devname)) {
			kDbg("Found our device, %s", devname);
			found = 1;
			*ndev = nd;
			break;
		}
	}

	if(!found) {
		kDbg("Unable to find the device, %s", devname);
		*ndev = NULL;
		status = -ENXIO;
	}

	return status;
}

// Increment the promiscuity ref counter on the net device.
static int set_promisc_mode(struct net_device* ndev)
{
	int status = 0;
	
	if(NULL == ndev)
		return -EINVAL;

	rtnl_lock();
	status = dev_set_promiscuity(ndev, 1);
	rtnl_unlock();

	return status;
}

// Decrement the promiscuity ref counter on the net device.
static int unset_promisc_mode(struct net_device* ndev)
{
	int status = 0;

	if(NULL == ndev)
		return -EINVAL;

	rtnl_lock();
	status = dev_set_promiscuity(ndev, -1);
	rtnl_unlock();

	return status;
}

static void shutdown(void)
{
	kDbg("Shutting down netifs");
}

int init_netifs(struct netifs_ops* netops)
{
	int status = 0;

	if(NULL == netops)
		return -EINVAL;	

	memset(netops, 0, sizeof(*netops));
	
	netops->find_dev = find_netdev;
	netops->set_promisc = set_promisc_mode;
	netops->unset_promisc = unset_promisc_mode;
	netops->shutdown = shutdown;
	netops->initialized = 1;
	
	return status;
}

