# rblos
A very tiny RTOS since 1996

Why did I write a RTOS?
Back to 1996, there was no RTOS available, and I worked for a PSTN switch and was resiponsible for software develempent for all peripheral boards.
There were many boards with 386EX as CPU such as DT(Digital trunk), SLC, MFC, all wolud be communicated with the main control board.
Since there were no RTOS, for every board, we needed to start from the ground, it was very inconvenient.

Another reason was for debugging and trouble shooting.

Our main control board had a 486 CPU with intel iRMX.
The iRMX is a multitask OS, when you stop a task to debug, other tasks still are running include timer task, so you will recieve a lot of time out event which makes debug work very hard.

The other reason was related to list structure
Our OS engineer designed a event system which was implemented with list structure.
When we met a GP, we need to know which event made the GP error, but list structure made it very hard to locate the right event.
In command line debug mode, it's nightmare to browse all nodes in list structure.

So rblos is a sigle task OS and use array to replace link table.

The last reason is that RBLOS makes our team work very easy.

The team member can develop and debug software in RBLOS, then smothly move their software to iRMX without any change.

Since RBLOS has a same set of user API as it is implemented in iRMX.


