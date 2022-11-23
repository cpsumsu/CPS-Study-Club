# Why Active Directory?

Active Directory (AD) is a directory service for Windows network environments. It is a distributed, hierarchical structure that allows for **centralized management** of an organization's resources, including **users, computers, groups, network devices, file shares, group policies, devices, and trusts**

- Many features are arguably not "secure by default,"

- AD is essentially a sizeable read-only database accessible to all users within the domain, regardless of their privilege level

- A basic AD user account with no added privileges can enumerate most objects within AD
- importance of a defense-in-depth strategy and careful planning focusing on security and hardening AD, network segmentation, and least privilege

Example: [noPac](https://www.secureworks.com/blog/nopac-a-tale-of-two-vulnerabilities-that-could-end-in-ransomware) attack

![image](https://academy.hackthebox.com/storage/modules/74/whyad5.png)

A successful attack such as a phish that lands an attacker within the AD environment as a standard domain user would give them enough access to begin mapping out the domain and looking for avenues of attack

> The [Conti Ransomware](https://www.cisa.gov/uscert/ncas/alerts/aa21-265a) which has been used in more than 400 attacks around the world has been shown to leverage recent critical Active Directory flaws such as [PrintNightmare (CVE-2021-34527)](https://msrc.microsoft.com/update-guide/vulnerability/CVE-2021-34527) and [Zerologon (CVE-2020-1472)](https://msrc.microsoft.com/update-guide/vulnerability/CVE-2020-1472) to escalate privileges and move laterally in a target network.

*Tools are only as effective as their operator is knowledgeable*

## History of Active Directory

LDAP, the foundation of Active Directory