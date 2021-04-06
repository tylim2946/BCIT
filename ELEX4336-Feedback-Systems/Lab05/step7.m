% Step 7
% Model Equation: E(t) = DeltaIntTemp(t) - DeltaIntTempSim(t)
% Calculate and plot the residual errors

load temps;

% System Parameters
K = 0.72;
tau = 145300;
sys = tf([K], [tau 1]);

% Array indices
idxStart = 1;
idxEnd = 10744;  % approx. 24 days (full data)

% Calculate zero means
DeltaExtTemp = ExtTemp(idxStart:idxEnd) - mean(ExtTemp(idxStart:idxEnd));
DeltaIntTemp = IntTemp(idxStart:idxEnd) - mean(IntTemp(idxStart:idxEnd));

% Calculated internal temperature
DeltaIntTempSim = lsim(sys, DeltaExtTemp, t(idxStart:idxEnd));

% Calculate Residual Error
E = DeltaIntTemp - DeltaIntTempSim;

% Plot the data
figure(5);
t = t(idxStart:idxEnd);
plot(t/60/60/24, E, '-');
ylabel('Temperature (Celcius)');
xlabel('Time (days)');
title('Residual Error for Straw Bale House for 24 Days');
legend('Error');
grid on;