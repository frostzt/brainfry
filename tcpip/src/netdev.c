#include "tcpip/netdev.h"

struct netdev *netdev_open_tun(const char *dev, int flags) {
  struct ifreq ifr;
  int fd, err;

  /* should be there logically NOT 100% sure on this */
  char *clonedev = "/dev/net/tun";
  if ((fd = open(clonedev, O_RDWR)) < 0) {
    perror("failed to open device");
    return NULL;
  }

  /* prepare for ioctl */
  memset(&ifr, 0, sizeof(ifr));

  ifr.ifr_flags = flags;
  if (*dev) {
    strncpy(ifr.ifr_name, dev, IFNAMSIZ);
  }

  /* forward to ioctl */
  if ((err = ioctl(fd, TUNSETIFF, (void *)&ifr)) < 0) {
    perror("ioctl(TUNSETIFF)");
    close(fd);
    return NULL;
  }

  /* create a new netdev */
  struct netdev *nd = (struct netdev *)malloc(sizeof(struct netdev));
  nd->fd = fd;
  strcpy(nd->dev, dev);
  nd->mtu = 0;

  return nd;
}
