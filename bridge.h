#pragma once

#include <linux/if_bridge.h>
#include <linux/netdevice.h>
#include <linux/if_vlan.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/rtnetlink.h>
#include <linux/errno.h>


struct bridge_ops {
	int initialized;
	int (* create_bridge)(const char* brname);
	int (* del_bridge)(void);
	void (* shutdown)(void);
};


int init_bridge(struct bridge_ops* brops);
