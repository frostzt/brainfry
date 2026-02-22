#include <stdio.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>

#include "tcpip/debug.h"
#include "tcpip/netdev.h"
#include "tcpip/ip.h"
#include "tcpip/icmp.h"

int main() {
  DEBUG_LOG("TCP/IP stack starting...");

  char dev[IFNAMSIZ] = "tun0";

  /* open a new tun device */
  struct netdev *nd = netdev_open(dev, IFF_TUN | IFF_NO_PI);
  if (nd == NULL) {
    perror("netdev_open()");
    exit(1);
  }

  /* allocate a buffer to read into and output with */
  uint8_t buf[nd->mtu];
  uint8_t output[nd->mtu];
  while (1) {
    ssize_t bytes_read = netdev_read(nd, buf, nd->mtu);
    if (bytes_read < 0) {
      DEBUG_ERROR("Failed to read from TUN device");
      exit(1);
    }

    /* parse the ip packet */
    ip_packet_t ip;
    if (ip_parse(buf, bytes_read, &ip) != 0) continue;

#ifdef DEBUG
    /* DEBUG: Print the ip header */
    print_ip_packet(&ip);
#endif

    /* copy buffer from buf to output buffer the output
     * buffer will be modified in place */
    memcpy(output, buf, ip.ip_total_length);

    ssize_t reply = 0;
    switch (ip.ip_protocol) {
      case PROTO_ICMP: reply = handle_icmp(output, &ip); break;
      default: continue;
    }

    if (reply != 0) {
      DEBUG_ERROR("failed to build protocol: %d message\n", ip.ip_protocol);
      continue;
    }

#ifdef DEBUG
    /* DEBUG: Parse ip source address */
    char* ipvstr = ipv4_to_string(ip.ip_src_addr);
    DEBUG_INFO("Writing back to %s", ipvstr);
    free(ipvstr);
#endif

    if (ip_send_reply(output, ip.header_len_bytes, ip.ip_total_length, nd) < 0) {
      fprintf(stderr, "failed to reply back...");
    }
  }

  /* close the netdev device */
  netdev_close(nd);
  DEBUG_LOG("TCP/IP stack shutting down...");
  return 0;
}
