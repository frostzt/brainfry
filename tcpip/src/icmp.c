#include "tcpip/debug.h"
#include "tcpip/ip.h"
#include "tcpip/icmp.h"
#include "tcpip/algo.h"

ssize_t handle_icmp(uint8_t *buf, ip_packet_t *ip) {
  /* check we're using the right protocol here */
  if (ip->ip_protocol != PROTO_ICMP) return -1;
  /* switch the ip addrs */
  switch_ip_addresses(buf);
  /* create the icmp reply */
  if (icmp_handle_echo(buf + ip->header_len_bytes, ip->payload_len)) return -1;
  return 0;
}

ssize_t icmp_handle_echo(uint8_t *buf, size_t payload_length) {
  if (buf == NULL) return -1;
  if (payload_length < 8) return -1;

  uint8_t type = buf[0];
  if (type != 8) {
    DEBUG_ERROR("Not an echo message");
    return -1;
  }

  uint8_t code = buf[1];
  if (code != 0) {
    DEBUG_ERROR("Malformed echo message");
    return -1;
  }

  DEBUG_INFO("Received an ICMP echo request!");
  if (build_icmp_reply(buf, payload_length)) return -1;
  return 0;
}

ssize_t build_icmp_reply(uint8_t *buf, size_t n) {
  DEBUG_INFO("Received buffer with a total size of %d\n", n);

  buf[0] = buf[1] = 0x00; /* icmp reply and code */
  buf[2] = buf[3] = 0x00; /* zero checksum */

  /* calculate the new checksum */
  uint16_t checksum = ones_complement_checksum(buf, n);
  buf[2] = (uint8_t)(checksum >> 8);
  buf[3] = (uint8_t)(checksum & 0xFF);

  DEBUG_INFO("Generated checksum for the icmp header %d\n", checksum);
  return 0;
}

