#include <stdio.h>

#include "tcpip/debug.h"
#include "tcpip/ip.h"
#include "tcpip/icmp.h"

void handle_icmp(uint8_t *buf, ip_packet_t *ip) {
  if (ip->ip_protocol != PROTO_ICMP) {
    return;
  }

  icmp_handle_echo(buf, ip->payload_len);
}

void icmp_handle_echo(uint8_t *buf, int payload_length) {
  DEBUG_INFO("Recieved an ICMP echo request!");
  if (buf == NULL) {
    return;
  }

  uint8_t type = buf[0];
  if (type != 8) {
    DEBUG_ERROR("Not an echo message");
    return;
  }

  uint8_t code = buf[1];
  if (code != 0) {
    DEBUG_ERROR("Malformed echo message");
    return;
  }

  uint8_t buf_out[payload_length];
  build_icmp_reply(buf, buf_out, payload_length);
}

void compute_icmp_checksum(uint8_t *buf, int n) {
  uint16_t intermediate = 0;
  for (int i = 0; i < n; i++) {
    intermediate = intermediate | (~buf[i]);
  }

  printf("%x\n", intermediate);
}

void build_icmp_reply(uint8_t *buf_in, uint8_t *buf_out, size_t n) {
  DEBUG_INFO("Received buffer with a total size of %d\n", n);

  buf_out[0] = (uint8_t)0; /* icmp reply type */
  buf_out[1] = (uint8_t)0; /* icmp code */

  /* checksum */
  buf_out[2] = (uint8_t)0;
  buf_out[3] = (uint8_t)0;

  /* identifier */
  buf_out[4] = (uint8_t)0;
  buf_out[5] = (uint8_t)0;

  /* sequence number */
  buf_out[6] = (uint8_t)0;
  buf_out[7] = (uint8_t)0;

  /* copy description/data */
  memcpy(buf_out + 8, buf_in + 8, n - 8);
  compute_icmp_checksum(buf_out, n);
}
