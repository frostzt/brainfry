/*
 * icmp.h - Internet Control Message Protocol
 *
 * Author: frostzt
 * Date: 2026-01-24
 */

#ifndef TCPIP_ICMP_H
#define TCPIP_ICMP_H

#include <assert.h>
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>

/* handle ICMP request */
ssize_t handle_icmp(uint8_t *buf, ip_packet_t *ip);

/* handles echo replies to icmp, uses the buffer provided updates everything in-place */
ssize_t icmp_handle_echo(uint8_t *buf, size_t payload_length);

/* builds the icmp reply */
ssize_t build_icmp_reply(uint8_t *buf, size_t n);

#endif // TCPIP_ICMP_H
