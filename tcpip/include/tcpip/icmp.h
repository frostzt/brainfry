/*
 * icmp.h - Internet Control Message Protocol
 *
 * Author: frostzt
 * Date: 2026-01-24
 */

#ifndef TCPIP_ICMP_H
#define TCPIP_ICMP_H

#include <stdint.h>

/* handle ICMP request */
void handle_icmp(uint8_t *buf, ip_packet_t *ip);

void icmp_handle_echo(uint8_t *buf, int payload_length);

/*
  -- FROM RFC 792
  Checksum
  The checksum is the 16-bit ones's complement of the one's
  complement sum of the ICMP message starting with the ICMP Type.
  For computing the checksum , the checksum field should be zero.
  If the total length is odd, the received data is padded with one
  octet of zeros for computing the checksum.  This checksum may be
  replaced in the future.
  -- FROM RFC 792
*/
void compute_icmp_checksum(uint8_t *buf, int n);

void build_icmp_reply(uint8_t *buf_in, uint8_t *buf_out, size_t n);

#endif // TCPIP_ICMP_H
