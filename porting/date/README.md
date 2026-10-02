# date

First Level-2 Porting Lab target. The program uses the AmPOSIX realtime clock API while keeping the application logic ordinary portable C.

The AmigaOS backend maps realtime to `timer.device` system time and converts the 1978 Amiga epoch to Unix epoch.
