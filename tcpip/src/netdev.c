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

  DEBUG_INFO("Successfully created netdev '%s' (fd=%d)", ifr.ifr_name, fd);
  DEBUG_INFO("MTU set to: %d\n", nd->mtu);
  return nd;
}

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
