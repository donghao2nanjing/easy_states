clear; 
close all ; 

input_wave = dlmread('sinewave.txt') ; 
state = dlmread('state.txt'); 

t = input_wave(:, 1); 
y1 = input_wave(:, 2);
y2 = input_wave(:, 3); 

s1 = state(:, 1);
s2 = state(:, 2); 
s3 = state(:, 3); 
s4 = state(:, 4); 
s5 = state(:, 5); 

plot(t, y1); 
hold on ; 
plot(t, y2); 
plot(t, s1 * 9, '-x'); 
plot(t, s2 * 10, '-.'); 
plot(t, s3 * 11, '-*'); 
plot(t, -s4 * 10); 
plot(t, -s5 * 11); 
legend('y1', 'y2', '1', '2', '3', '4', '5'); 
