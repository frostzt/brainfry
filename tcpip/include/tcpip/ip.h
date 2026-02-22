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
#include <stddef.h>
#include <stdlib.h>

#include <tcpip/netdev.h>

/* A struct depicting IP Packet only the stuff I need though
 * Made this through RFC-791 */
typedef struct {
  int ip_version; /* ip version */
  int ip_ihl; /* Internet header length, this guys tells us how long the ip header is */
  int ip_total_length; /* total length of this buffer */
  int ip_protocol; /* protocol */
  int ip_src_addr; /* src address */
  int ip_dst_addr; /* destination address */

  const uint8_t* payload; /* whatever is in the payload */
  uint16_t payload_len;
  uint8_t header_len_bytes; /* bytes that are just ip header */
} ip_packet_t;

/* Protocol numbers
 * Note: do not use IPPROTO_ prefix as that collides netinet */
typedef enum {
  PROTO_ICMP = 1,
  PROTO_TCP = 6,
  PROTO_UDP = 17,
} ip_proto_t;

/* parses an ip packet buffer and sets it to the passed buffer
 * if success the returned number is 1 otherwise its less than 1
 *
 * ERR_PACKET_TOO_SHORT = -11
 * ERR_PACKET_TRUNCATED = -12
 * ERR_PACKET_MALFORMED = -13
 * ERR_INVALID_IP_VERSION = -14
 */
ssize_t ip_parse(uint8_t *buf, size_t n, ip_packet_t *out);

/* prints a provided ip packet */
void print_ip_packet(ip_packet_t *packet);

/* switches src address and dst address in a buffer */
ssize_t switch_ip_addresses(uint8_t *buf);

/* computes ip checksum */
void ip_compute_checksum(uint8_t *buf, size_t n);

/* converts a uint32_t ipv4 address to its native representation */
char *ipv4_to_string(uint32_t ipv_number);

/* replies back */
ssize_t ip_send_reply(uint8_t *buf, size_t header_length, size_t total_length, struct netdev *nd);

#endif // TCPIP_IP_H
