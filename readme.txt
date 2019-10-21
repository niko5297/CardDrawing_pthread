This program is a card drawing game. The game uses 4 threads to draw (2 threads), check (1 thread)
and read (1 thread) the random selected card - therefore it uses multithreading.
The program achives mutual exclusion by using pthread_mutex.


To use the application, simply run it on either your IDEA or using a terminal.

If you are using a terminal, remember to compiler it first, or it won't run.


To check if the threads are working properly, you can try remove the sleep function. If you do so, the program will keep
printing "The selected card has been drawn before, drawing a new one", which means that the system can't reconize which
cards have been drawn and which not.
You can also try to remove one mutex_unlock function, and the program will not continue running, because one of the threads are
locked, and the main thread is waiting for the thread to unlock.
By multithreading the program will run faster, and by using mutal exclusing, the chances of a deadlock is enormously decreased.



CHANGES THAT COULD HAVE BEEN MADE WITH MORE TIME:

When the game is about to end, there are few cards left, its going to take some time. I tried to come up with a fix
for this but without the luck. If you can think of one solution, please describe it in the giving feedback.