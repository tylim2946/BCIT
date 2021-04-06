% multi-loop feedback system
% find closed loop transfer function and plot pole-zero map of the system

% define blocks
sysg1 = tf([1], [1 10]);
sysg2 = tf([1], [1 1]);
sysg3 = tf([1 0 1], [1 4 4]);
sysg4 = tf([1 1], [1 6]);
sysh1 = tf([1 1], [1 2]);
sysh2 = tf([2], [1]);
sysh3 = tf([1], [1]);

% construct closed loop transfer function
L1 = feedback(series(sysg3, sysg4), sysh1, +1);
L2 = feedback(series(sysg2, L1), sysh2/sysg4, -1);
sys = feedback(series(sysg1, L2), sysh3, -1);

% plot pole-zero map
pzmap(sys);