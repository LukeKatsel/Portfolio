# VLAN and Switch Configuration

This document outlines the VLAN assignments and switch configuration used to enforce network segmentation in the homelab. The goal is to separate administrative, general-purpose, guest, and IoT traffic into distinct security zones.

---

## 🧰 Deployment Details

- **Switch Model**: Brocade ICX6450-48P
- **Firmware Version**: 08.0.30pT313
- **Network Role**: VLAN separation, trunk traffic to pfSense, and limit lateral movement

---

## 🌐 VLAN Definitions

| VLAN ID | Name        | Subnet            | Purpose                           |
|---------|-------------|-------------------|-----------------------------------|
| 1       | Default     |                   | Primary Network (Trusted devices) |
| 69      | Primary Wifi| 192.168.69.0/24   | Primary WiFi (Trusted devices)    |
| 70      | Guest WiFi  | 192.168.70.0/24   | Guest network (Isolated)          |
| 71      | IoT WiFi    | 192.168.71.0/24   | IoT network (Untrusted devices)   |

---

## 🔌 Port Configuration

| Port              | Mode       | VLAN Assignment          | Description                               |
|-------------------|------------|--------------------------|-------------------------------------------|
| 1-36, 38-46, 48   | Access     | Untagged                 |                                           |
| 37                | Access     | Dual, Tagged 69,70,71    | Uplink to pfSense                         |
| 47                | Access     | Dual, Tagged 69,70,71    | WiFi AP – Primary, Guest, and IoT WiFi    |

🖼️ _Screenshot: Access Port Configuration  
`![Port Setup](./screenshots/vlan_port_config.png)`

---

## ✅ Rationale for Configuration

- Dual-mode uplink (port 37) ensures all tagged VLAN traffic (69, 70, 71) is sent to pfSense for inter-VLAN routing and firewall policy enforcement.

- WiFi access point (port 47) is configured as a trunk port to carry multiple VLANs, allowing the AP to broadcast separate SSIDs (Primary, Guest, IoT) mapped to their respective VLANs.

- Access ports are untagged for simplicity and device compatibility—each port only allows traffic from its assigned VLAN to reduce misconfiguration risks.

- VLAN separation limits lateral movement between devices in different security zones (e.g., isolating Guest and IoT devices from trusted networks).

- Default VLAN (1) is restricted to trusted wired devices, maintaining administrative control while ensuring that other VLANs are isolated.

- Switch acts as a Layer 2 boundary, pushing all routing and security decisions to pfSense, simplifying switch logic and centralizing control.


---