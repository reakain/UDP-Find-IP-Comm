# Python 2.7 Data Reciever
This code was pulled directly from my NAO-pose-mirroring project, [here](https://github.com/shareresearchteam/NAO-Pose-Mirroring), and originally it expected messages after the initial "hello" exchange to be JSON structures. The JSON structures were removed, however, and some additional comments added, and some port tweaks made, when I grabbed it to use with the D1 Mini to support my lab mate's project.

This code would be the "first" device, which sends the initial "hello?" message out, then waits for a "hello!" message back.