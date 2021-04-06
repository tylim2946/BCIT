% Model Equation: T(s) = K / (τ*s + 1)
% Approximate the angular velocity as first order system
% using a sample input-output data

load open-loop_ang-vel;

% Array indices
idxStart = 1;
idxEnd = 1001;

% Calculate zero means
Input = x(idxStart:idxEnd);
Output = out(idxStart:idxEnd);

% Find best fit K and tau
K = 0;
tau = 0;
minSSE = -1;

for kTest = 0.12:0.001:0.14
    for tauTest = 0.0018:0.00001:0.0020
        sys = tf([kTest], [tauTest 1]);
        OutputSim = lsim(sys, Input, t(idxStart:idxEnd));
        SSE = sum((Output - OutputSim) .^ 2);
        
        if minSSE == -1
            minSSE = SSE;
            K = kTest;
            tau = tauTest;
        elseif SSE < minSSE
            minSSE = SSE;
            K = kTest;
            tau = tauTest;
        end
    end
end

% Calculated internal temperature
sys = tf([K], [tau 1]);
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