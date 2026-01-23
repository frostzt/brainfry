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
 * Made this through RFC-791
 */
struct IpPacket {
  int ip_version; /* ip version */
  int ip_ihl; /* Internet header length */
  int ip_total_length; /* total length of this buffer */
  int ip_protocol; /* protocol */
  int ip_src_addr;
  int ip_dst_addr;
};

/* parses an ip packet buffer and sets it to the passed buffer */
struct IpPacket *ip_parse(uint8_t *buf);

/* prints a provided ip packet */
void print_ip_packet(struct IpPacket *packet);

#endif // TCPIP_IP_H
