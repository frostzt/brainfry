/*
 * ip.h - Internet Protocol
 *
 * Author: frostzt
 * Date: 2026-01-23
 *
 * A rather simple implementation of IP
 * might not be full. So don't use bruh
 */

#ifndef TCPIP_IP_H
#define TCPIP_IP_H

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

/* A struct depicting IP Packet only the stuff I need though
 * Made this through RFC-791 */
typedef struct {
  int ip_version; /* ip version */
  int ip_ihl; /* Internet header length, this guys tells us how long the ip header is */
  int ip_total_length; /* total length of this buffer */
  int ip_protocol; /* protocol */
  int ip_src_addr;
  int ip_dst_addr;

  const uint8_t* payload;
  uint16_t payload_len;
  uint8_t header_len_bytes;
} ip_packet_t;

/* parses an ip packet buffer and sets it to the passed buffer
 * if success the returned number is 1 otherwise its less than 1
 *
 * ERR_PACKET_TOO_SHORT = -11
 * ERR_PACKET_TRUNCATED = -12
 * ERR_PACKET_MALFORMED = -13
 * ERR_INVALID_IP_VERSION = -14
 */
int ip_parse(uint8_t *buf, size_t n, ip_packet_t *out);

/* prints a provided ip packet */
void print_ip_packet(ip_packet_t *packet);

#endif // TCPIP_IP_H
