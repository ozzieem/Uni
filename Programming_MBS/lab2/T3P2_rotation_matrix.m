% Task 3 Problem 2

function [] = T3P2_rotation_matrix(p1, p2, p3)

p1 = [0.268245951374788   0.168626454467227  -0.103539072508682]';
p2 = [-0.155308608763023   0.402368927062183   0.252939681700840]';
p3 = [0.168626454467227  -0.103539072508682   0.268245951374788]';

p1n = normc(p1);
p2n = normc(p2);
p3n = normc(p3);

R = [p1n p2n p3n];

control_m = [R'*p1n R'*p2n R'*p3n];

display(R)
display(control_m);

end

