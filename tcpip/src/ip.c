#include "tcpip/debug.h"
#include "tcpip/ip.h"

int ip_parse(uint8_t *buf, size_t n, ip_packet_t *out) {
  if (buf == NULL) {
    return -1;
  }

  if (n < 20) {
    DEBUG_ERROR("Error packet too short");
    return -11;
  }

  /* 1st byte: version and ihl */
  uint8_t v = buf[0] >> 4;
  uint8_t ihl = buf[0] & 0x0F;
  uint8_t header_len_bytes = ihl * 4;

  /* 3rd + 4th byte: total length */
  uint16_t total_length = ((uint16_t)buf[2] << 8) | buf[3];
  if (total_length > n) {
    DEBUG_ERROR("Error packet truncated");
    return -12;
  }

  if (header_len_bytes > total_length) {
    DEBUG_ERROR("Error malformed or malicious packet");
    return -13;
  }

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

  if (v != 4) {
    DEBUG_ERROR("Error invalid IP version");
    return -14;
  }

  out->ip_version = v;
  out->ip_ihl = ihl;
  out->ip_total_length = total_length;
  out->ip_protocol = protocol;
  out->ip_src_addr = src_addr;
  out->ip_dst_addr = dst_addr;
  out->header_len_bytes = header_len_bytes;
  out->payload = buf + header_len_bytes;
  out->payload_len = total_length - header_len_bytes;

  return 0;
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

void print_ip_packet(ip_packet_t *packet) {
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
