% Model Equation: T(s) = K*omega^2 / (s^2 + 2*zeta*omega*s + omega^2)
% Approximate the angular velocity as second order system
% using a sample input-output data

load closed-loop_ang-vel;

% Array indices
idxStart = 1;
idxEnd = 1001;

% Calculate zero means
Input = x(idxStart:idxEnd);
Output = out(idxStart:idxEnd);

% Find best fit K and tau
K = 0; %0.125;
zeta = 0; %2.1;
omega = 0; %1318;
minSSE = -1;

for kTest = 0.1:0.01:0.2
    for zetaTest = 0:1:10
        for omegaTest = 0:100:2000
            sys = tf([kTest*omegaTest^2], [1 2*zetaTest*omegaTest omegaTest^2]);
            OutputSim = lsim(sys, Input, t(idxStart:idxEnd));
            SSE = sum((Output - OutputSim) .^ 2);
        
            if minSSE == -1
                minSSE = SSE;
                K = kTest;
                zeta = zetaTest;
                omega = omegaTest;
            elseif SSE < minSSE
                minSSE = SSE;
                K = kTest;
                zeta = zetaTest;
                omega = omegaTest;
            end
        end
    end
end

% Calculated internal temperature
sys = tf([K*omega^2], [1 2*zeta*omega omega^2]);
OutputSim = lsim(sys,Input, t(idxStart:idxEnd));

% Plot the data
figure(3);
t = t(idxStart:idxEnd);
plot(t, Input, '-', t, Output, '-.', t, OutputSim, '--');
ylabel('Amplitude');
xlabel('Time (seconds)');
title('Angular Velocity vs. Time');
legend('Rated Voltage [V]', 'Angular Velocity [rad/s]', 'Approximated Angular Velocity [rad/s]');
grid on;