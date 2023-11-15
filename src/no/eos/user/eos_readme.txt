EOS(Embedded OS )
The idea comes from the WIN32 API to implement a simple event-driven state machine foe embended system. 

The EOS also has more better modulization and can support 5 types of process:

1.Message-driven process which will be scheduled according to message
2.Time-slot process which is scheduled by time slot.this feature can be added in the future according to requirement
3.Real time process which will be scheduled in every main loop.
4.Routine process which will be called every 1 ms or 10 ms
5.Idle process which will be called when there is no 1,2,4 process called in every main loop

The EOS has more presice timer and doesn't accumulate time error.

Please note, even you have a RTOS or Linus for your embeded system, EOS or similar system is still badly needed.
EOS can goes with any RTOS.