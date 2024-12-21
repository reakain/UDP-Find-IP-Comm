# C# Data Sending
This code was pulled directly from my NAO-pose-mirroring project, [here](https://github.com/shareresearchteam/NAO-Pose-Mirroring), and expects messages after the initial "hello" exchange to be JSON structures. I haven't done a whole lot of clean up, so don't expect this class to run right out of the box.

This would be the "second device" which sends back a "hello!" ping. The "DataTransfer.cs" file includes the "DataTransferManager" class and a static "DataTransfer" class. In your program, you will first start the async task "DiscoverMeProcessAsync()" from the "DataTransferManager" class in order to listen for the first device and send a reply.

The static DataTransfer class holds both the pre-determined communication port, and the function for sending a UDP packet message to the first device.