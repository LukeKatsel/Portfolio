# CyberApolis Water Company Penetration Test

This project was the capstone final exam for CYBV 480.
The scenario simulated a critical ICS/SCADA attack on the fictional CyberApolis Water Company. A terrorist organization, Carbon Spector, had taken control of the dam’s floodgates, placing the city at risk of flooding. My objective was to identify vulnerabilities, exploit them, and secure the HMI controls to safely close the floodgates.

All reconnaissance, exploitation, and reporting were performed entirely by me. The steps documented reflect the real procedures I carried out in a controlled lab environment.

## Executive Summary

Conducted reconnaissance of the CyberApolis website and associated documents to gather employee profiles and metadata.

Discovered a remote OS command injection vulnerability in the pay-your-bill page.

Exploited this vulnerability to obtain employee usernames and passwords, gaining access to the employee portal.

Using credentials obtained during reconnaissance, accessed the HMI controls and successfully shut the floodgates.


## Recommended mitigations include:

Fixing the input validation vulnerability on the pay-your-bill page.

Enforcing robust, complex password policies.

Requiring reauthentication before accessing email accounts.

Avoiding publicly posting documents containing sensitive information such as usernames.

## Methodology
1. **Reconnaissance**

 Gathered information from the company website, social media, and public documents.

 Developed profiles on eight employees including names, titles, phone numbers, and birthdays.

 Extracted a username from metadata in a publicly posted document.

2. **Scanning**

 Used command-line tools like ping, nslookup, and nmap to map network surfaces.

 Employed GUI tools such as Zenmap and Zed Attack Proxy (ZAP) to identify vulnerabilities in web services.

 Detected the OS command injection vulnerability in the pay-your-bill page.

3. **Exploitation**

 Exploited the vulnerability to retrieve usernames and passwords for seven employees.

 Accessed the employee portal, gaining control of employee email accounts and sensitive information.

 Used an additional reconnaissance-derived username to access the HMI controls and shut the floodgates.

4. **Post-Exploitation**

 Documented findings with screenshots and step-by-step procedures.

 Used tools like John the Ripper for password analysis where applicable.

 Compiled mitigation recommendations to prevent similar breaches in the future.

## Skills Demonstrated

 OSINT & Reconnaissance

 Vulnerability Scanning & Exploitation

 Privilege Escalation & Credential Management

 ICS/SCADA Penetration Testing

 Technical Writing & Executive Reporting


## Academic Integrity Notice
 This project was conducted as part of a controlled academic exercise.
 All work, research, and reporting presented in this repository is my own.
 This portfolio is intended for educational and professional demonstration only.

 Students or others viewing this work should not replicate it for assignments or unauthorized use, but may reference it to learn about penetration testing methodology and best practices.