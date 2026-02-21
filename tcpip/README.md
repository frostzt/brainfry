# TCP/IP

## Setup

Quick setup.

```shell
ip addr add 10.0.0.1/24 dev tun0
ip link set tun0 up
ping -c 1 10.0.0.2
```
