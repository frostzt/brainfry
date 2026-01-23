#include <stdio.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>

#include "tcpip/debug.h"
#include "tcpip/netdev.h"

int main() {
  DEBUG_LOG("TCP/IP stack starting...");

  char dev[IFNAMSIZ] = "tun0";

  /* open a new tun device */
  struct netdev *nd = netdev_open(dev, IFF_TUN | IFF_NO_PI);
  if (nd == NULL) {
    perror("netdev_open()");
    exit(1);
  }

  /* allocate a buffer to read into */
  uint8_t buf[nd->mtu];
  while (1) {
    if (netdev_read(nd, buf, nd->mtu) < 0) {
      DEBUG_ERROR("Failed to read from TUN device");
      exit(1);
    }
  }

  /* close the netdev device */
  netdev_close(nd);
  DEBUG_LOG("TCP/IP stack shutting down...");
  return 0;
}
