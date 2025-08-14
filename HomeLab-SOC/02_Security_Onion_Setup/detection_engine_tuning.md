# 🛠️ Detection Engine Tuning in Security Onion

This document details the process of tuning Security Onion’s primary detection engines — Suricata and Zeek — to improve alert quality by reducing false positives and noise, and enhancing detection accuracy in a homelab environment.

---

## 🧰 Environment Details

- **Security Onion Version**: 2.4.141 (Standalone Mode)
- **Detection Engines**: Suricata (IDS/IPS), Zeek (Network Security Monitoring)
- **Data Sources**: Mirrored network traffic (SPAN port), pfSense logs (syslog)
- **Objective**: Optimize detection rules for accurate, actionable alerts

---

## 📦 Tuning Steps

1. **Baseline Alert Collection**

- Allow the system to run with default detection rules for a period (e.g., 1 week) to gather baseline alert data.
- Collect logs from Suricata and Zeek for analysis.

2. **Analyze Alert Volume and Types**

- Use Kibana dashboards to review the types and frequency of alerts generated.
- Identify common false positives or benign events triggering alerts.

3. **Rule Suppression and Customization (Suricata)**

- Use the suricata.yaml configuration to disable or suppress noisy rules.
- Leverage the threshold.config file to set thresholds on alerts to reduce repetitive alerts from the same source.
- Create local rules to fine-tune detection, e.g., whitelist known safe IPs or adjust rule parameters.

4. **Zeek Script Customization**

- Review Zeek logs to identify false positives or unnecessary events.
- Customize Zeek scripts (written in Zeek scripting language) to filter out benign events or add custom detection logic.

5. **Detection Engine Integration and Correlation**

- Tune Elasticsearch queries in Kibana to correlate Suricata and Zeek alerts for higher fidelity.
- Adjust dashboards to focus on prioritized alerts.

6. **Continuous Monitoring and Feedback Loop**

- Regularly review alert trends and update tuning rules accordingly.
- Document changes for reproducibility and audit.

---

## 🧩 Challenges Encountered
❗ Initial high volume of irrelevant alerts due to broad default signatures.

❗ Difficulty balancing detection sensitivity vs. noise in a small homelab environment.

---

## ✅ Summary

Tuning Security Onion’s detection engines is crucial for actionable threat detection. Through systematic analysis, rule suppression, and customization, the homelab environment now generates higher-quality alerts aligned with simulated threats and realistic network behaviors.