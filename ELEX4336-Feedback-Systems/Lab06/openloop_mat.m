% Plot the step response of the open-loop system in MATLAB

% system parameters
Vrated = 24;                        % V
Trated = 0.5;                       % N*m
Wrated = 366;                       % rpm
km = 0.0458;                        % N*m/A
Rf = 2.49;                          % Ohms
Lf = 2.63E-3;                       % H
J = 0.0000071;                      % kg*m^2
b = Trated / (Wrated * 2*pi / 60);  % N*m*s
n = 11.5;                           % dimensionless

% transfer functions
sys1 = tf([km], [n*J*Lf n*(J*Rf+b*Lf) n*b*Rf]);     % angular velocity output
sys2 = tf([km], [n*J*Lf n*(J*Rf+b*Lf) n*b*Rf 0]);   % position output

% calculate and save step response for angular velocity output
t = 0:7E-6:7E-3;
x = step(tf(Vrated, 1), t); % step input
[out, t] = lsim(sys1, x, t);
save('open-loop_ang-vel.mat', 't', 'x', 'out');

% calculate and save step response for position output
t = 0:0.001:1;
x = step(tf(Vrated, 1), t); % step input
[out, t] = lsim(sys2, x, t);
save('open-loop_pos.mat', 't', 'x', 'out');

% plot the step response for angular velocity output
figure(1);
load open-loop_ang-vel;
plot(t, x, '-', t, out, '-.');
ylabel('Amplitude');
xlabel('Time (seconds)');
title('Angular Velocity vs. Rated Voltage');
legend('Rated Voltage [V]', 'Angular Velocity [rad/s]');
grid on;

% plot the step response for position output
figure(2);
load open-loop_pos;
plot(t, x, '-', t, out, '-.');
ylabel('Amplitude');
xlabel('Time (seconds)');
title('Position vs. Rated Voltage');
legend('Rated Voltage [V]', 'Position [rad]');
grid on;