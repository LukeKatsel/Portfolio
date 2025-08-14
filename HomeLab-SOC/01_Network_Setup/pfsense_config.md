# pfSense Firewall Configuration

This document outlines the pfSense configuration used to segment and secure the virtual lab environment. This setup supports multiple VLANs with different security contexts and is designed to simulate realistic SOC monitoring scenarios.

---

## 🧰 Deployment Details

- **pfSense Version**: 2.7.2 CE
- **Deployment Mode**: Bare metal Installation (Dell OptiPlex 7040)
- **Network Role**: Core firewall/router, DHCP/DNS server, VLAN gateway

---

## 🌐 Interface Assignments

| Interface | Name     | Type     | IP Address        | Description             |
|-----------|----------|----------|-------------------|-------------------------|
| em0       | WAN      | Physical | DHCP (from ISP)   | Internet uplink         |
| igb0      | LAN      | Physical | 192.168.55.1/24   | Admin/Trusted network   |
| igb0.69   | VLAN 69  | VLAN     | 192.168.69.1/24   | Primary WiFi VLAN       |
| igb0.70   | VLAN 70  | VLAN     | 192.168.70.1/24   | Guest WiFi VLAN         |
| igb0.71   | VLAN 71  | VLAN     | 192.168.71.1/24   | IOT WiFi VLAN           |

🖼️ _Screenshot: Interface Assignments Page_  
`![Interfaces](./screenshots/pfsense_interfaces.png)`

---

## 🔥 Firewall Rules

### LAN (Admin/Trusted network - 192.168.55.1/24)

- Anti-Lockout Rule
- Allow full outbound access (for homelab management)

### VLAN 69 (Primary WiFi VLAN - 192.168.69.1/24)

- Allow DNS to pfsense
- Block DNS
- Allow full outbound access

### VLAN 70 (Guest WiFi VLAN - 192.168.70.1/24)

- Allow DNS to pfsense
- Block DNS
- Block all traffic to private networks (LAN & VLAN 69)
- Block web traffic to pfsense web interface
- Allow full outbound access

### VLAN 71 (IOT WiFi VLAN - 192.168.71.1/24)

- Allow DNS to pfsense
- Block DNS
- Block all traffic to private networks (LAN & VLAN 69)
- Block web traffic to pfsense web interface
- Allow full outbound access

🖼️ _Screenshot: Example VLAN Rule_  
`![VLAN71 Firewall Rules](./screenshots/vlan71_rules.png)`

---

## 🔁 NAT Configuration

- **Outbound NAT**: Set to "Automatic"
---

## 📦 DHCP Configuration

| Interface | Range              | DNS              | Notes                       |
|-----------|--------------------|------------------|-----------------------------|
| LAN       | 192.168.55.1–254   | 192.168.55.1     |                             |
| VLAN 69   | 192.168.69.1–254   | 192.168.69.1     |                             |
| VLAN 70   | 192.168.70.1–254   | 192.168.70.1     |                             |
| VLAN 71   | 192.168.71.1–254   | 192.168.71.1     |                             |

🖼️ _Screenshot: DHCP for VLAN 71_  
`![DHCP VLAN 71](./screenshots/dhcp_vlan71.png)`

---

## 🔐 Inter-VLAN Routing Restrictions

Routing between Guest/IoT VLANs and trusted networks is **explicitly restricted** via firewall rules. For example:

- VLAN 70 cannot access LAN or VLAN 69.

---

## ✅ Rationale for Rules

This segmentation and rule structure simulates a real-world environment where:

- IoT and Guest VLANs are isolated from Trusted Networks
To prevent lateral movement and protect critical systems, devices on VLANs 70 (Guest) and 71 (IoT) are explicitly blocked from accessing the LAN (Admin) and other VLANs. This mirrors real-world practices where untrusted devices are quarantined to prevent internal threats.

- Access to the pfSense web interface is restricted
Guest and IoT devices are blocked from accessing the pfSense admin interface to prevent unauthorized configuration attempts or exploitation of management services.

- Internal DNS enforcement
All VLANs are allowed to query only the pfSense DNS resolver. This prevents devices from bypassing DNS-based filtering and enables centralized logging of DNS queries for visibility and threat hunting.

- Outbound internet access is allowed where appropriate
Full outbound access is granted to most VLANs to allow for software updates, cloud communication, and internet functionality. However, internal segmentation ensures that compromise of an endpoint doesn’t provide access to sensitive systems.

- LAN is unrestricted for management and monitoring
The Admin/Trusted LAN is granted full access to manage and monitor all systems in the environment. It acts as the control plane for the homelab.

---