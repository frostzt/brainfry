#ifndef TCPIP_NETDEV_HPP
#define TCPIP_NETDEV_HPP

/*
 * netdev.h - TUN/TAP Abstraction
 *
 * Author: frostzt
 * Date: 2026-01-04
 */

/*
 * Logic here is mostly implemented with help of official Linux Kernal docs
 * @see https://www.kernel.org/doc/Documentation/networking/tuntap.txt
 *
 * I hope this works out lol
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/* https://stackoverflow.com/questions/20082433/what-is-the-difference-between-linux-if-h-and-net-if-h */
#include <net/if.h>
#include <linux/if.h>

#include <linux/if_tun.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <arpa/inet.h> 
#include <sys/select.h>
#include <sys/time.h>
#include <errno.h>
#include <stdarg.h>

struct netdev {
  int fd;
  char dev[IFNAMSIZ];
  int mtu;
};

/* allocates a new tun device */
struct netdev *netdev_open_tun(const char *dev, int flags);

#endif // TCPIP_NETDEV_HPP
