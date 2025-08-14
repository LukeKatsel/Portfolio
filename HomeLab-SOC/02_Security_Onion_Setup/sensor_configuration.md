# 🛰️ Sensor Configuration – Security Onion

This document outlines the configuration of network sensors in Security Onion, focusing on interface assignments, monitored traffic, and sensor validation for proper data ingestion.

---

## 🌐 Interface Assignments

| Interface | Role           | Description                                      |
|-----------|----------------|--------------------------------------------------|
| enp0s31f6 | Management     | Static IP from LAN 192.168.55.4                  |
| enp2s0f0  | Monitor        | Connected to mirrored switch port (port 17)      |

📝 _The monitor interface receives all mirrored packets from pfSense uplink via a SPAN port on the switch._

---

## 🔧 Configuration Steps

1. **Interface Selection (During Setup Wizard)**
   - Selected `en0` as management interface.
   - Selected `enp2s0f0` as monitor (sensor) interface.
   - Ensured monitor interface was left unconfigured (no IP address).

2. **PF_RING Setup**
   - Enabled PF_RING for performance optimization during setup.
   - Verified correct NICs were assigned for sniffing in `/opt/so/conf/pfring`.

3. **Service Validation**
   - Ran `so-status` to confirm Suricata, Zeek, and Stenographer were active.
   - Checked that `enp2s0f0` showed packet activity using `tcpdump -i enp2s0f0`.

4. **Monitor Interface Test**
   - Verified live mirrored traffic using:
     ```bash
     tcpdump -i enp2s0f0 -n
     ```
   - Saw DHCP, ARP, and general web traffic as expected from VLANs 69–71.

---

## 🧪 Verification

| Service     | Command                  | Expected Output                    |
|-------------|--------------------------|------------------------------------|
| Suricata    | `so-suricata-status`     | Green – running                    |
| Zeek        | `so-zeek-status`         | Green – running                    |
| Traffic     | `tcpdump -i enp2s0f0`    | Mirrored VLAN traffic              |

📸 _Screenshot: tcpdump of mirror traffic_  
`![tcpdump enp2s0f0](./screenshots/tcpdump_enp2s0f0.png)`

---

## 🛡️ Summary

The sensor interface (`enp2s0f0`) is successfully ingesting mirrored traffic from the Brocade ICX6450 switch, allowing Suricata and Zeek to process live packets for analysis and detection. The management interface (`enp0s31f6`) remains isolated for administrative tasks, enhancing the realism of this SOC simulation.

