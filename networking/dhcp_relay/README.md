# DHCP relay agent Lab

```yaml
LAN1:
  Network: '192.168.1.0/24'
  Gateway: '192.168.1.1'

LAN2:
  Network: '192.168.2.0/24'
  Gateway: '192.168.2.1'

LAN3:
  Network: '192.168.3.0/24'
  Gateway: '192.168.3.1'

R1:
  interfaces:
    - g0/0: '192.168.1.1/24'
    - g0/1: '192.168.2.1/24'
    - g0/2: '192.168.3.1/24'

DhcpServer:
  interfaces:
    - fe0: '192.168.1.2/24'

DnsServer:
  interfaces:
    - fe0: '192.168.1.3/24'

DuckduckgoServer:
  interfaces:
    - fe0: '192.168.1.4/24'

PC1:
  interfaces:
    - fe0: DHCP

PC2:
  interfaces:
    - fe0: DHCP
```

## Objectives

* perform basic configuration on `R1`
* configure `R1` as a DHCP relay agent for `LAN2` & `LAN3`
* configure `PC1` & `PC2` to use DHCP and test connectivity

## perform basic configuration on `R1`

### configure the interfaces of `R1` as stated above

    R1> enable
    R1# configure terminal
    R1(config)# interface g0/0
    R1(config-if)#ip address 192.168.1.1 255.255.255.0
    R1(config-if)#no shutdown
    R1(config-if)#interface g0/1
    R1(config-if)#ip address 192.168.2.1 255.255.255.0
    R1(config-if)#no shutdown
    R1(config-if)#interface g0/2
    R1(config-if)#ip address 192.168.3.1 255.255.255.0
    R1(config-if)#no shutdown

## configure `R1` as a DHCP relay agent for `LAN2` & `LAN3`

### configure `G0/1` interface

    R1>enable
    R1#configure terminal
    R1(config)#interface G0/1
    R1(config)#ip helper-address 192.168.1.2
    R1(config)#end

### configure `G0/2` interface

Follow the previous steps.

## configure `PC1` & `PC2` to use DHCP and test connectivity

Now configure PC1 and PC2 to use DHCP and make sure the addresses are
assigned from the LAN2 & LAN3 pools.

From PC1:

* ping the default gateway (192.168.2.1)
* open `duckduckgo.com` webpage

From PC2:

* ping the default gateway (192.168.3.1)
* open `duckduckgo.com` webpage
