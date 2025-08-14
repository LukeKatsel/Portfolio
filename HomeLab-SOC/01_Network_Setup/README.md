# Network Setup

This folder contains documentation and configurations for setting up the segmented virtual network that supports SOC functionality within the homelab.

## Contents

* **pfSense Firewall Configuration**: NAT rules, firewall rules, and routing setup
* **VLAN and Switch Configuration**: VLAN IDs, switch port tagging/trunking strategy
* **Network Architecture Diagram**: High-level topology showing segmentation, SSID mapping, and monitoring points

## Goals

* Emulate a small enterprise environment with multiple subnets and access controls
* Enable Security Onion to monitor inter-VLAN traffic effectively
* Apply best practices in segmentation to reduce lateral movement and increase visibility

## Key Features

* Isolated IoT, Guest, and primary WiFi VLANs
* Controlled inter-VLAN access through pfSense
* SPAN/mirror port setup for feeding traffic to Security Onion

## Files in this Directory

* `pfsense_config.md`: Overview of pfsense configuration
* `vlan_switch_config.md`: Overview of VLAN strategy and switch config
* `network_diagram.png`: Diagram showing network layout
* `screenshots/`: Folder holding screenshots for network configuration examples.

## Notes

All network components are configured to simulate enterprise segmentation and monitoring conditions. The switch config includes working examples of access port settings. pfSense rules enforce segmentation and forward logs to Security Onion for analysis.

---

For questions or walkthroughs, refer to the README in `02_Security_Onion_Setup/`.
