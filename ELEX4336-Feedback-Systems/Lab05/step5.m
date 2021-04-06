% Step 5
% Model Equation: T(s) = K / (τ*s + 1)
% Approximate the gain relationship between mean internal temperature and
% mean external temperature by assuming that K = 1 in your input output model

load temps;

% Array indices
idxStart = 1;
idxEnd = 5372;  % approx. 12 days

% Calculate zero means
DeltaExtTemp = ExtTemp(idxStart:idxEnd) - mean(ExtTemp(idxStart:idxEnd));
DeltaIntTemp = IntTemp(idxStart:idxEnd) - mean(IntTemp(idxStart:idxEnd));

% Find best fit K and tau
K = 0;
tau = 0;
minSSE = -1;

for kTest = 2:0.1:5
    for tauTest = 145300:1:145301
        sys = tf([kTest], [tauTest 1]);
        DeltaIntTempSim = lsim(sys, DeltaExtTemp, t(idxStart:idxEnd));
        SSE = sum((DeltaIntTemp - DeltaIntTempSim) .^ 2);
        
        if minSSE == -1
            minSSE = SSE;
        elseif SSE < minSSE
            minSSE = SSE;
            K = kTest;
            tau = tauTest;
        end
    end
end

% Calculated internal temperature
sys = tf([K], [tau 1]);
DeltaIntTempSim = lsim(sys, DeltaExtTemp, t(idxStart:idxEnd));

% Plot the data
figure(3);
t = t(idxStart:idxEnd);
plot(t/60/60/24, DeltaExtTemp, '-', t/60/60/24, DeltaIntTemp, '-.', t/60/60/24, DeltaIntTempSim, '--');
ylabel('Temperature (Celcius)');
xlabel('Time (days)');
title('Zero Mean Temperature vs. Time for Straw Bale House for 12 Days');
legend('Zero Mean External Temperature', 'Zero Mean Internal Temperature', 'Simulated Zero Mean Internal Temperature');
grid on;