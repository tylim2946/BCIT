% Model equation: y(t) = V(t) * P(D) / Q(D)
% Plot the unit step response of the second order circuit system

% system parameters
L = 10 * 10^-3; % unit: H
C = 10 * 10^-9; % unit: F
R = 1.2 * 10^3; % unit: Ohms
Rcoil = 24; % unit: Ohms
Rgen = 50;  % unit: Ohms

% transfer function
Q = [L*C (R+Rcoil+Rgen)*C 1];
P = [1];
sys = tf(P, Q);

% characteristic value
p = roots(Q);

% plot the unit step response
step(sys);