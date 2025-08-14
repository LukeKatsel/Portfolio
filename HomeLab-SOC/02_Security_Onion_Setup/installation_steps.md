# 🛠️ Security Onion Installation (Standalone Mode)

This document outlines the process of installing Security Onion in Standalone mode on a dedicated server in the homelab environment.

---

## 🧰 Deployment Environment

- **Host Hardware**: Bare metal Installation (Dell OptiPlex 7040)
- **Network Mode**: Standalone
- **Security Onion Version**: 2.4.141
- **Interfaces Used**: 
  - `enp0s31f6` – Management
  - `enp2s0f0` – Monitored (SPAN/mirrored port from switch)

---

## 📦 Installation Steps

1. **Download & Boot ISO**
   - Downloaded the Security Onion ISO from [securityonion.net](https://securityonion.net).
   - Verified SHA256 hash before flashing to USB.

2. **Initial Setup**
   - Selected "Install Security Onion" from the GRUB menu.
   - Partitioned disk manually (1TB SSD).
   - Configured hostname: `securityonion`.

3. **Network Configuration**
   - Management Interface: `enp0s31f6` (static IP 192.168.55.4)
   - Monitor Interface: `enp2s0f0` (no IP, receives mirrored traffic)

4. **Setup Wizard**
   - Selected **Standalone** deployment.
   - Enabled **Suricata**, **Zeek**, **PCAP**, and **Elastic Stack**.
   - Chose **PF_RING** for high-performance packet capture.
   - Set up local user credentials.

5. **Reboot and Services Check**
   - Rebooted system.
   - Verified `so-status` shows all green services.

---

## 🧩 Challenges Encountered

- ❗ Initial network misconfiguration: Management and Monitor interfaces were flipped — resolved by reassigning in `nmtui`.
- ❗ Slow interface discovery: Needed to manually rename NICs via `udev` rules.
- ❗ Time drift warnings: Fixed by enabling NTP via `timedatectl`.

---

## 📸 Screenshots

- `so-status` Output  
  `![Status Check](./screenshots/so_status.png)`

---

## ✅ Summary

Security Onion was successfully deployed in standalone mode. It is configured to:
- Capture and analyze mirrored network traffic.
- Serve as a central log aggregation and detection point.
- Integrate with external log sources such as pfSense.

