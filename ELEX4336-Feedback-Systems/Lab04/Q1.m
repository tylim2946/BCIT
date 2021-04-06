% parallel configuration of two transfer functions
% Obtain the overall transfer function when the two blocks are in parallel

% G(s)
numg = [1];
deng = [500 0 0];
sysg = tf(numg, deng);

% H(s)
numh = [1 1];
denh = [1 2];
sysh = tf(numh, denh);

% H(s) + G(s)
sys = parallel(sysg, sysh);

