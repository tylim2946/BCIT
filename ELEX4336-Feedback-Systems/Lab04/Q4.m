% plot the location of the system zeros and poles

% H(s)
numh = [1 1];
denh = [1 2];
sysh = tf(numh, denh);

% find poles and zero
p = pole(sysh);
z = zero(sysh);

% plot pole-zero map
pzmap(sysh);