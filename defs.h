#pragma once

#ifdef _DEBUG
#define kDbg(x, ...) printk(KERN_INFO "[-] Debug: %s | %d :" #x " \n",  __FUNCTION__, __LINE__, ##__VA_ARGS__)
#else
#define kDbg(x, ...) (void*)0
#endif


#define MOD_AUTH "Aaron Bray <aaron.m.bray@gmail.com>"
