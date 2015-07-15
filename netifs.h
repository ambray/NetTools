#pragma once

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/netdevice.h>
#include <linux/rtnetlink.h>
#include <linux/errno.h>


struct netifs_ops {
	int initialized;
	int (* find_dev)(struct net_device** ndev, char* devname);
	int (* set_promisc)(struct net_device* ndev);
	int (* unset_promisc)(struct net_device* ndev);
	void (* shutdown)(void);
};

int init_netifs(struct netifs_ops* netops);
