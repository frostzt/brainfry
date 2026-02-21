/*
 * algo.h - Checksums and everythings
 *
 * Author: frostzt
 * Date: 2026-02-21
 *
 * This files contains algorithms that can be common across
 * ip and others was not sure where to put them so keeping
 * them here.
 */

#ifndef TCPIP_ALGO_H
#define TCPIP_ALGO_H

static inline uint16_t ones_complement_checksum(uint8_t *buf, size_t n) {
  uint32_t sum = 0;
  size_t i = 0;
  for (; i + 1 < n; i += 2) {
    sum += ((uint16_t)buf[i] << 8) | ((uint16_t)buf[i + 1]);
  }
  if (i < n) { // last byte is odd
    sum += ((uint16_t)buf[i] << 8);
  }

  while (sum >> 16) {
    sum = (sum & 0xFFFFu) + (sum >> 16);
  }

  return (uint16_t)~sum;
}

#endif // TCPIP_ALGO_H
