clear; 
close all ; 

ts = 0.01 ; % 10 ms 
t = 0:ts:10; 
y1 = 10 * sin( 2 * pi * 0.1 * t);
y2 = 10 * sin( 2 * pi * 0.2 * t);
plot(t, y1);
hold on;
plot(t, y2) 
hold off ; 

dlmwrite('sinewave.txt', [t; y1; y2]')