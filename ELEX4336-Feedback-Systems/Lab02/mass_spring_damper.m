% Model equation: y(t) = f(t) * P(D) / Q(D)
% Plot the unit step response of the mass spring damper system over [0, 10]

% system parameters
m = 1;  % unit: kg
k = 40; % unit: N/m
b = 22; % unit: N/m-sec

% transfer function
Q = [m b k];
P = [1];
sys = tf(P, Q);

% characteristic values
p = roots(Q);

% plot range
t = 0:0.001:10;

% plot the unit step response
step(sys, t);



