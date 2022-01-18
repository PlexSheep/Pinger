# Pinger
This is a small command line tool for use with linux systems.
It's purpose is to keep the user informed, if a target is connected.
The tools accepts multiple targets as argument and will continously ping the targets
with a predetermined delay of 5 seconds.
Valid targets are (full) domains such as sub.example.com or IP Adresses (IPv4 and IPv6) such as 1.1.1.1 or ::1

## The tool makes use of the system() combined with user input, if you use this tool on a platform where any user could add userinput for the program to execute, you will be vulnerable to ###Remote Code Execution### You have been warned!