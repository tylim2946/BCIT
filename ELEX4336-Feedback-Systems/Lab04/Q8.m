% compute the closed-loop transfer function then compute and plot the step
% response to a 10 degree step input. Finally compare the step response
% when J is reduced by 20% and 50%.

% spacecraft parameters
J = 10.8E8; % moment of inertia

% controller parameters
k = 10.8E8;
a = 1;
b = 8;

% define blocks
sysg = tf([k k*a], [1 b]);  % controller
sysh1 = tf([1], [J 0 0]);   % spacecraft
sysh2 = tf([1], [(1 - 0.2)*J 0 0]); % spacecraft (J reduced by 20%)
sysh3 = tf([1], [(1 - 0.5)*J 0 0]); % spacecraft (J reduced by 50%)

% construct closed loop transfer function
sys1 = feedback(series(sysg, sysh1), 1, -1);
sys2 = feedback(series(sysg, sysh2), 1, -1);
sys3 = feedback(series(sysg, sysh3), 1, -1);

% plot step response of 10 degree step input
opt = stepDataOptions('StepAmplitude', 10); % 10 degree step input
step(sys1, sys2, sys3, opt);