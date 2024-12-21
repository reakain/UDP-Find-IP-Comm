# UDP Find Device and Communicate Starting Functions
Starting scripts for UDP communication across different programming environments. These scripts include first "calling out" to find a remote system, and then managing the communication between the two systems.

I've been the "system networking" person in my lab for a while, primarily because I worked previously in a team that did remote-operated robots in locations with unstable connections, so I just... Know some bits. I keep rebuilding UDP connections for my own systems, as well as needing to yank out code and offer it up as a starting point for my lab mates. It's happened enough times I decided I'd just keep a repo of the communication scripts for different operating systems for easy reference.

## Communication Structure
The communication process is:
 1. First device broadcasts "hello?" on the network
 2. Second device listens for the "hello?" ping, then stores the IP address of the first device.
 3. Second device sends a "hello!" ping directly back to the first device, who then saves the IP address of the second device.
 4. Then UDP communication continues as normal. Current structure is largely one directional, with the second device sending data to the first device.

It requires predefining the communication port IDs for the two devices, and if using an ESP microcontroller, pre-defining the network name and password.

## Supported Programming Languages & Systems
Currently I have some starting code for this process for:
 - C# (Specifically tested on Windows 10, with VS 2019/2022, and version 4.8 of the .NET Framework)
 - Python 2.7 (Designed for use with the Softbank NAO, and can be seen in the system [here](https://github.com/shareresearchteam/NAO-Pose-Mirroring))
 - Arduino (For an ESP8266, or more specifically, a Wemos D1 Mini)

## Other Notes
My original mentor and dear friend, [blink the things](https://github.com/BlinkTheThings), is the one who originally taught me all about system networking, and also the one who walked me through this communication process and structure to "auto-find" the IP address of another system.