#include "tcpip/debug.h"
#include "tcpip/netdev.h"

struct netdev *netdev_open(const char *dev, int flags) {
  struct ifreq ifr;
  int fd, err;

  DEBUG_INFO("Opening netdev with flags: 0x%x", flags);

  /* should be there logically NOT 100% sure on this */
  char *clonedev = "/dev/net/tun";
  if ((fd = open(clonedev, O_RDWR)) < 0) {
    DEBUG_ERROR("Failed to open %s: %s", clonedev, strerror(errno));
    perror("failed to open device");
    return NULL;
  }
  DEBUG_LOG("Opened %s with fd=%d", clonedev, fd);

  /* prepare for ioctl */
  memset(&ifr, 0, sizeof(ifr));

  ifr.ifr_flags = flags;
  if (*dev) {
    strncpy(ifr.ifr_name, dev, IFNAMSIZ);
  }

  /* forward to ioctl */
  if ((err = ioctl(fd, TUNSETIFF, (void *)&ifr)) < 0) {
    DEBUG_ERROR("ioctl(TUNSETIFF) failed: %s", strerror(errno));
    perror("ioctl(TUNSETIFF)");
    close(fd);
    return NULL;
  }

  /* create a new netdev */
  struct netdev *nd = (struct netdev *)malloc(sizeof(struct netdev));
  nd->fd = fd;
  if (*dev) {
    strncpy(nd->dev, ifr.ifr_name, IFNAMSIZ);
    nd->dev[IFNAMSIZ - 1] = '\0';
  }

  int socket_fd = socket(AF_INET, SOCK_DGRAM, 0);
  if ((err = ioctl(socket_fd, SIOCGIFMTU, (void *)&ifr)) < 0) {
    DEBUG_ERROR("ioctl(SIOCGIFMTU) failed: %s", strerror(errno));
    perror("ioctl(SIOCGIFMTU)");
    close(fd);
    return NULL;
  }

  nd->mtu = ifr.ifr_mtu;

  close(socket_fd);
  DEBUG_INFO("Successfully created netdev '%s' (fd=%d)", ifr.ifr_name, fd);
  DEBUG_INFO("MTU set to: %d\n", nd->mtu);
  return nd;
}

// Raw Hexdump from NetDev
// PING 10.0.0.2 (10.0.0.2) 56(84) bytes of data.
// [2026-01-23 15:48:30] [DEBUG] [netdev.c:74] Received packet: (84 bytes):
//
// 0000:  45 00 00 54 7d e8 40 00  40 01 a8 be 0a 00 00 01  E..T}.@.@.......
//                    *
// 0010:  0a 00 00 02 08 00 f0 34  00 04 00 01 4e 98 73 69  .......4....N.si
//
// 0020:  00 00 00 00 83 f1 03 00  00 00 00 00 10 11 12 13  ................
//
// 0030:  14 15 16 17 18 19 1a 1b  1c 1d 1e 1f 20 21 22 23  ............ !"#
//
// 0040:  24 25 26 27 28 29 2a 2b  2c 2d 2e 2f 30 31 32 33  $%&'()*+,-./0123
//
// 0050:  34 35 36 37                                       4567

/* Version: 4 , IHL: 5
 * TOS: 00
 * Total Length: 0x0054 ==> 84
 * Identification: 0x07de8 ==> 32,232
 * -----------------------------------
 * FLAGS | F R A G M E N T O F F S E T
 * 0 1 0 | 0 0 0 0 0 0 0 0 0 0 0 0 0
 * -----------------------------------
 * Flags: 0 1 0 : Don't Fragment
 * Fragment Offset: 0 0 0 0 0 0 0 0 0 0 0 0 0
 * TTL: 0x40 ==> 64
 * Protocol: 0x01 ==> 1 -- ICMP
 * Checksum: 0xa8be
 * Source Address: 0a 00 00 01
 *                 10. 0. 0. 1
 * Destination Addresss: 0a 00 00 02
 *                       10. 0. 0. 2
 * Options: starts from 0x08 ...
 */

ssize_t netdev_read(struct netdev *dev, uint8_t *buf, size_t len) {
  if (dev == NULL) {
    DEBUG_ERROR("Attempted to read from an NULL netdev");
    perror("netdev_read()");
    return -1;
  }

  ssize_t nread = read(dev->fd, buf, len);
  if (nread < 0) {
    DEBUG_ERROR("Failed to read from interface");
    perror("reading from interface()");
    return nread;
  }

  if (nread > 0) {
    DEBUG_HEXDUMP(buf, nread, "Received packet:");
  }

  DEBUG_INFO("Read %d bytes from %s\n", nread, dev->dev);
  return nread;
}

void netdev_close(struct netdev *dev) {
  if (dev == NULL) {
    DEBUG_WARN("Attempted to close NULL netdev");
    return;
  }

  DEBUG_INFO("Closing netdev '%s' (fd=%d)", dev->dev, dev->fd);
  close(dev->fd);
  free(dev);
}
