% Plot the step response of the closed-loop system in MATLAB

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

% optical encoder feedback
H = 3.11 * km;                      % kg*m^2/A/s^3; 3.11 V/rad

% transfer functions
sys1 = tf([km], [n*J*Lf n*(J*Rf+b*Lf) n*b*Rf]);     
sys1 = feedback(sys1, H, -1);                       % angular velocity output
sys2 = tf([km], [n*J*Lf n*(J*Rf+b*Lf) n*b*Rf 0]);
sys2 = feedback(sys2, H, -1);                       % angular position output

% calculate and save step response for angular velocity output
t = 0:7E-6:7E-3;
x = step(tf(Vrated, 1), t); % step input
[out, t] = lsim(sys1, x, t);
save('closed-loop_ang-vel.mat', 't', 'x', 'out');

% calculate and save step response for angular position output
t = 0:0.001:1;
x = step(tf(Vrated, 1), t); % step input
[out, t] = lsim(sys2, x, t);
save('closed-loop_pos.mat', 't', 'x', 'out');

% plot the step response for angular velocity output
figure(1);
load closed-loop_ang-vel;
plot(t, x, '-', t, out, '-.');
ylabel('Amplitude');
xlabel('Time (seconds)');
title('Angular Velocity vs. Rated Voltage');
legend('Rated Voltage [V]', 'Angular Velocity [rad/s]');
grid on;

% plot the step response for position output
figure(2);
load closed-loop_pos;
plot(t, x, '-', t, out, '-.');
ylabel('Amplitude');
xlabel('Time (seconds)');
title('Position vs. Rated Voltage');
legend('Rated Voltage [V]', 'Position [rad]');
grid on;