#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include "netifs.h"
#include "bridge.h"
#include "defs.h"

struct netifs_ops netops;
struct bridge_ops briops;

static int __init init_func(void)
{
	int status = 0;
	struct net_device* nd;

	kDbg("Loaded.");
	
	if(0 != (status = init_netifs(&netops))) {
		kDbg("Failed to initialized netops! Error: %d", status);
		return status;
	}

	if(0 != (status = netops.find_dev(&nd, "eth0"))) {
		kDbg("Failed to find the requested device! Error: %d", status);
		return status;
	}	

	if(0 != (status = netops.set_promisc(nd))) {
		kDbg("Failed to put device into promiscuous mode! Error: %d", status);
	}
	
	return status;
}


static void __exit exit_func(void)
{
	int status = 0;
	struct net_device* nd;

	kDbg("Unloading.");
	if(1 != netops.initialized)
		return;

	if(0 != (status = netops.find_dev(&nd, "eth0")) || NULL == nd) {
		goto Exit;
	}	

   	netops.unset_promisc(nd);

Exit:
	netops.shutdown();
	
}


MODULE_LICENSE("Dual MIT/GPL");
MODULE_AUTHOR(MOD_AUTH);

module_init(init_func);
module_exit(exit_func);
