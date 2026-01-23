#include "tcpip/debug.h"
#include "tcpip/ip.h"

struct IpPacket *ip_parse(uint8_t *buf) {
  if (buf == NULL) {
    return NULL;
  }

  uint8_t fbyte = buf[0];

  /* 1st byte: version and ihl */
  uint8_t v = fbyte >> 4;
  uint8_t ihl = fbyte & 0x0F;

  /* 3rd + 4th byte: total length */
  uint16_t total_length = ((uint16_t)buf[2] << 8) | buf[3];

  /* 10th byte: protocol */
  uint8_t protocol = buf[9];

  /* 13th + 14th + 15th + 16th byte: src addr */
  uint32_t src_addr = ((uint32_t)buf[12] << 24) |
    ((uint32_t)buf[13] << 16) |
    ((uint32_t)buf[14] << 8) | buf[15];

  /* 17th + 18th + 19th + 20th byte: dst addr */
  uint32_t dst_addr = ((uint32_t)buf[16] << 24) |
    ((uint32_t)buf[17] << 16) |
    ((uint32_t)buf[18] << 8) | buf[19];

  /* allocate space for ip_packet */
  struct IpPacket *ip_packet = (struct IpPacket *)malloc(sizeof(struct IpPacket));
  if (ip_packet == NULL) {
    DEBUG_ERROR("Failed to allocate ip_packet");
    exit(1);
  }

  ip_packet->ip_version = v;
  ip_packet->ip_ihl = ihl;
  ip_packet->ip_total_length = total_length;
  ip_packet->ip_protocol = protocol;
  ip_packet->ip_src_addr = src_addr;
  ip_packet->ip_dst_addr = dst_addr;

  return ip_packet;
}

/* Converts a possible ipv4 number to ipv4 string
 * DO NOT FORGET TO CALL FREE */
char *ipv4_to_string(int ipv_number) {
  int a = (ipv_number >> 24) & 0xFF;
  int b = (ipv_number >> 16) & 0xFF;
  int c = (ipv_number >> 8) & 0xFF;
  int d = ipv_number & 0xFF;

  char *src_addr = (char *)malloc(16);
  if (src_addr == NULL) {
    DEBUG_ERROR("Error while allocating ipv4 string");
    return NULL;
  }

  snprintf(src_addr, 16, "%d.%d.%d.%d", a, b, c, d);
  return src_addr;
}

void print_ip_packet(struct IpPacket *packet) {
  if (packet == NULL) {
    return;
  }

  printf("IP Packet ----------------------\n");
  printf("Version: %d\n", packet->ip_version);
  printf("IHL: %d\n", packet->ip_ihl);
  printf("Total Length: %d\n", packet->ip_total_length);
  printf("Protocol: %d\n", packet->ip_protocol);
  char *src_addr = ipv4_to_string(packet->ip_src_addr);
  printf("Src Addr: %s\n", src_addr);
  char *dst_addr = ipv4_to_string(packet->ip_dst_addr);
  printf("Dst Addr: %s\n", dst_addr);
  printf("IP Packet xxxxxxxxxxxxxxxxxxxxxx\n\n");
  free(src_addr);
  free(dst_addr);
}
