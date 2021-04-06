% multi-loop feedback system
% simplify and calculate the transfer function of the system

% define symbols
syms s;

% define blocks
g1 = 1/(s + 10);
g2 = 1/(s + 1);
g3 = (s^2 + 1)/(s^2 + 4*s + 4);
g4 = (s + 1)/(s + 6);
h1 = (s + 1)/(s + 2);
h2 = 2;
h3 = 1;

% calculate overall transfer function
sys = (g1*g2*g3*g4)/(1 - (g3*g4*h1) + (g2*g3*h2) + (g1*g2*g3*g4*h3));

% simplify and display transfer equation
sys = simplifyFraction(sys, 'Expand', true);
pretty(sys);

% simplify the transfer function from Question 5
sys2 = (s^5 + 4*s^4 + 6*s^3 + 6*s^2 + 5*s + 2) / (12*s^6 + 205*s^5 + 1066*s^4 + 2517*s^3 + 3128*s^2 + 2196*s + 712);
sys2 = simplifyFraction(sys2, 'Expand', true);
pretty(sys2);