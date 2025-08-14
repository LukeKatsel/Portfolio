# 03_Adversary_Emulation

This section documents adversary simulation efforts within the home lab using tools and methodologies inspired by real-world threat actors. The objective is to generate realistic network activity and system behaviors for detection and analysis using Security Onion.

## Tools & Frameworks

- **Atomic Red Team**  
  Used to simulate MITRE ATT&CK techniques in a controlled environment. Executed selected atomic tests to produce observable behaviors and validate detection capabilities.

- **Custom YAML Tests**  
  Modified and created new Atomic Red Team test cases to tailor adversary activity to the local network configuration and specific SOC goals.


## Contents

- **`atomic_red_team_walkthroughs/`**  
  Step-by-step executions of Atomic Red Team tests, including commands run, expected outcomes, and observed network/system behavior.

- **`custom_tests.yaml`**  
  Locally developed atomic test definitions with notes on MITRE technique mapping and use cases.

- **`screenshots/`**  
  Supporting visual evidence of emulated activity, alert logs, and console output.

## Emulated Techniques

Examples of simulated techniques include:

- Credential dumping via LSASS access
- PowerShell-based command and control
- DNS tunneling
- HTTP beaconing
- Lateral movement using SMB

## Purpose

This project demonstrates the ability to:

- Execute controlled adversary behavior aligned with MITRE ATT&CK
- Understand and anticipate how attacks manifest in logs and alerts
- Evaluate and improve SOC detection coverage
- Build repeatable, testable adversary simulation playbooks

This emulation activity supports the incident response and detection tuning documented in later sections of the portfolio.
