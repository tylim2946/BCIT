% non-unity feedback system
% obtain the overall transfer function of the system as shown in the figure

% G(s)
numg = [1];
deng = [500 0 0];
sysg = tf(numg, deng);

% H(s)
numh = [1 1];
denh = [1 2];
sysh = tf(numh, denh);

% overall transfer function
sys = feedback(sysg, sysh, -1);