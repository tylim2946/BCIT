% unity feedback system
% compute and plot unit step response of closed-loop transfer function

% define blocks
sysg = tf([1], [1 1]);  % controller
sysh = tf([1 2], [1 3]);    % plant

% construct closed loop transfer function
sys = feedback(series(sysg, sysh), 1, -1);

% plot unit step response
step(sys);