# AmPOSIX Porting Lab

The Porting Lab validates AmPOSIX against real, small portable-C programs. The goal is to measure practical source-change cost, not just synthetic API compatibility.

Initial progression: hello, cat, grep, wc, date, sleep, netcat, then a small IRC client.

Each port records upstream source, required changes, AmPOSIX level, build result, runtime qualification and known semantic differences.
