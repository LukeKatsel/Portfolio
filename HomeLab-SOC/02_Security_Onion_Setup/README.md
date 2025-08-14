# 02_Security_Onion_Setup

This section of the portfolio documents the deployment and configuration of **Security Onion**, a powerful open-source platform for enterprise-grade security monitoring, threat hunting, and log management. The goal of this setup is to simulate a real-world Security Operations Center (SOC) environment within a home lab.

By integrating full-packet capture, log aggregation, and signature-based detection, this setup enables comprehensive monitoring and analysis of emulated threats across a segmented network.

## Contents

- **`installation_steps.md`** – Step-by-step guide to installing Security Onion in Standalone mode, including challenges encountered and resolved.
- **`sensor_configuration.md`** – Documentation of interface selection, traffic flow setup, and sensor status verification.
- **`log_forwarding.md`** – Configuration of external log sources (e.g., pfSense firewall) and their integration into Security Onion via syslog.
- **`detection_engine_tuning.md`** – Notes on tuning Suricata and Zeek for optimal alerting, including rule customization and noise reduction strategies.
- **`screenshots/`** – Visual evidence of setup and analysis workflows, including active alerts, log dashboards, and sensor status.

## Tools & Technologies

- Security Onion 2.x
- Suricata IDS/IPS
- Zeek (formerly Bro)
- Elasticsearch, Logstash, and Kibana (ELK stack)
- Syslog forwarding (from pfSense)
- Linux command-line tools

## Purpose

This deployment demonstrates practical skills in:

- Deploying and managing a distributed security monitoring system
- Ingesting and correlating multi-source logs
- Understanding network traffic behaviors and anomalies
- Tuning detection engines for operational efficiency

This setup supports adversary emulation and PCAP analysis documented in later sections of the portfolio.
