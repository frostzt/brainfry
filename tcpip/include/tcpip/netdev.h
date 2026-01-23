#ifndef TCPIP_NETDEV_H
#define TCPIP_NETDEV_H

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

/* allocates a new tun device and opens it */
struct netdev *netdev_open(const char *dev, int flags);

/* reads into buffer from the net device */
ssize_t netdev_read(struct netdev *dev, uint8_t *buf, size_t len);

ssize_t netdev_write(struct netdev *dev, const uint8_t *buf, size_t len);

void netdev_close(struct netdev *dev);

#endif // TCPIP_NETDEV_H
