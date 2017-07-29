function R = T4_ABframe()
a = [1; 2; 3];  % Bara som exempel. a är kolinjär med B:s z-axel.
ahelp = [1; 5; 3];

ax = cross(a, ahelp);
ay = cross(a, ax);

Bx = normc(ax);
By = normc(ay);
Bz = normc(a);

% r tar oss från A-frame till B-frame.
r = [Bx By Bz];

R = r * rz(pi/4) * r';


