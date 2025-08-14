# IoT Camera Research Project

Luke D. L. Katsel
University of Arizona – CYBV 498: Senior Capstone (Engineering)
Professor: Jordan VanHoy
April 7, 2024

## Overview

This project demonstrates the security risks inherent to Internet of Things (IoT) devices through a penetration test of a commercially available IoT camera. The goal was to exploit vulnerabilities in the device to gain unauthorized root access, showcasing potential real-world risks associated with IoT devices in home and networked environments. All research, testing, and reporting were conducted solely by me.

## Context & Motivation

IoT devices, including smart cameras and baby monitors, provide convenience and connectivity but often lack robust security measures. Poor design practices and insufficient security standards leave these devices vulnerable to unauthorized access, putting users and their data at risk.

An illustrative case involved a baby monitor where an unauthorized party gained access to a live stream and microphone, demonstrating the real-world consequences of IoT vulnerabilities. This project emphasizes the importance of secure design, responsible usage, and regulatory compliance for IoT devices.

## Objectives

Identify security weaknesses in an IoT camera.

Exploit vulnerabilities to gain root access to the device.

Document the penetration testing methodology, findings, and remediation recommendations.

Highlight the broader security implications of IoT devices in homes and enterprises.

## Methodology
1. **Reconnaissance**

Collected publicly available information about the camera and manufacturer.

Analyzed documentation, manuals, and device behavior.

Reviewed industry standards for IoT security from NIST publications.


2. **Vulnerability Analysis**

Evaluated firmware, configuration, and update mechanisms.

Assessed network interfaces for unauthorized access vectors.

Tested for weak access controls, unencrypted data transmission, and exploitable features.


3. **Exploitation**

Exploited the manual firmware update mechanism to gain unauthorized root access.

Verified access to the device terminal and critical configuration files.

Ensured controlled testing environment to avoid impact on real users or networks.


4. **Post-Exploitation & Reporting**

Documented step-by-step procedures, screenshots, and proof of exploit.

Developed mitigation recommendations to prevent unauthorized access.

Analyzed compliance gaps relative to NIST IoT security guidelines.


## Key Findings

The camera’s manual firmware update mechanism could be exploited to gain root access.

Network interfaces allowed for potential unauthorized access when not properly secured.

Device lacked robust authentication and encryption features.

Publicly available documentation revealed sensitive metadata, including default usernames and device identifiers.


## Recommended Mitigations

Enforce secure firmware update mechanisms with authentication and integrity checks.

Implement strong password policies and two-factor authentication for device access.

Encrypt all communication between the device and network services.

Limit exposure of sensitive metadata in publicly shared documents.

Educate consumers on proper IoT device configuration and security hygiene.


## Relevant Standards & Literature

NISTIR 8259A: IoT Device Cybersecurity Capability Core Baseline – outlines minimum-security requirements for IoT devices.

NISTIR 8259: Foundational Cybersecurity Activities for IoT Device Manufacturers – provides a framework for developing secure IoT devices pre- and post-market.

NIST SP 800-213: Guidance on IoT security and risk management.

These standards were used as a reference to evaluate device security posture and provide mitigation guidance.


## Skills Demonstrated

IoT Device Security Assessment & Risk Analysis

Firmware and Network Exploitation

OSINT and Reconnaissance Techniques

Security Reporting & Technical Documentation

Application of NIST IoT Security Standards