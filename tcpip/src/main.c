#include <stdio.h>
#include "tcpip/netdev.h"

int main() {
  char dev[IFNAMSIZ] = "";
  struct netdev *nd = netdev_open_tun(dev, IFF_TUN | IFF_NO_PI);

  printf("%d\n", nd->fd);

  close(nd->fd);
  free(nd);

  return 0;
}
