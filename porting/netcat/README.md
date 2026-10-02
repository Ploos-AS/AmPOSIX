# netcat

First integrated networking Porting Lab target. It exercises the AmPOSIX resolver + socket/connect layers. The initial target resolves IPv4, connects to TCP, sends stdin, and exits.

The client now sends stdin and reads the server response through AmPOSIX send/recv.
