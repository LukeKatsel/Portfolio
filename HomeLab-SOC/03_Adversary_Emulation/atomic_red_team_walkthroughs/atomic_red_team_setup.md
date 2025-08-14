# 🛠️ Atomic Red Team Set up
This document outlines the step-by-step process for executing Atomic Red Team adversary simulation tests in the homelab environment. These tests replicate real-world MITRE ATT&CK techniques, allowing for validation and tuning of Security Onion’s detection capabilities.

Link to MITRE ATT&CK: https://attack.mitre.org/

---

## 🧰 Environment Details

- **Test Framework**: Atomic Red Team (PowerShell module: Invoke-AtomicRedTeam)
- **Target System**: Windows 11 lab machine
- **Detection Platform**: Security Onion 2.4.141 (Standalone Mode)
- **Objective**: Simulate adversary techniques to generate observable behaviors and validate SOC monitoring

---

## 📦 Walkthrough Steps

1. **Prepare PowerShell Environment**

- Open PowerShell as Administrator.
- Check current execution policy
- Set the execution policy to allow running scripts, if needed:
'Set-ExecutionPolicy -ExecutionPolicy RemoteSigned -Scope CurrentUser'

- Import the Atomic Red Team module:
'Import-Module Invoke-AtomicRedTeam'

2. **Explore Available Tests for a Technique**

- To view brief details about technique T1003 (Credential Dumping):
'Invoke-AtomicTest T1003 -ShowDetailsBrief'


3. **Run a Specific Test**

- Execute test number 1 of T1003 with detailed output:
'Invoke-AtomicTest T1003 -TestNumbers 1 -ShowDetails'

- Run multiple tests under a technique:
'Invoke-AtomicTest T1003 -TestNumbers 1,2'

- Run all tests for a technique:
'Invoke-AtomicTest T1003 -All'

4. **Capture and Analyze Output**

- Save command output for review:
'Invoke-AtomicTest T1003 -TestNumbers 1 -ShowDetails | Out-File C:\temp\T1003_test_output.txt'

- Monitor Security Onion dashboards for alerts triggered by the test.
- Review Suricata and Zeek logs to validate detection.

5. **Revert back to the original policy after test completion**

- If you want to revert back to the original policy later, run:
'Set-ExecutionPolicy -ExecutionPolicy Restricted -Scope CurrentUser'

---

## ✅ Summary

Executing Atomic Red Team tests within the homelab allows realistic adversary behavior simulation. This hands-on approach validates and strengthens Security Onion’s detection setup by correlating simulated attacks with alerts and logs, providing a robust SOC training environment.