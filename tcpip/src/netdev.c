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
    /* figured this out the hard way if you're using OS default this would be
     * empty and the logs you'll get will be empty */
    strncpy(nd->dev, dev, IFNAMSIZ);
  }
  nd->mtu = 0;

  DEBUG_INFO("Successfully created netdev '%s' (fd=%d)", ifr.ifr_name, fd);
  return nd;
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
