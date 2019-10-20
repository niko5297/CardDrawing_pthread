This program is a card drawing game. The game uses 4 threads to draw (2 threads), check (1 thread)
and read (1 thread) the random selected card - therefore it uses multithreading.




Hvis man fjerner sleep så får man hele tiden samme kort, hvilket indikere at multithreading fungere, da det kræver lidt sleep??



When the game is about to end, there are few cards left, its going to take some time. I tried to come up with a fix
for this but without the luck. If you can think of one solution, please describe it in the giving feedback.