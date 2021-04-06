% Step 1
% Plot the zero mean adjusted data for 12 days as shown as in Figure 1

load temps;

% Array indices
idxStart = 1;
idxEnd = 5372;  % approx. 12 days

% Calculate zero means
DeltaExtTemp = ExtTemp(idxStart:idxEnd) - mean(ExtTemp(idxStart:idxEnd));
DeltaIntTemp = IntTemp(idxStart:idxEnd) - mean(IntTemp(idxStart:idxEnd));

% Plot the data
figure(2);
t = t(idxStart:idxEnd);
plot(t/60/60/24, DeltaExtTemp, '-', t/60/60/24, DeltaIntTemp, '-.');
ylabel('Temperature (Celcius)');
xlabel('Time (days)');
title('Zero Mean Temperature vs. Time for Straw Bale House for 12 Days');
legend('Zero Mean External Temperature', 'Zero Mean Internal Temperature');
grid on;