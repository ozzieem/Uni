function plot_T(T)
%
% plot the corresponding frame to a homogeneous matrix T
%
% T - homogeneous matrix
%
p = T(1:3,4);
r1 = T(1:3,1);
r2 = T(1:3,2);
r3 = T(1:3,3);
plot3([p(1) p(1)+r1(1)], [p(2) p(2)+r1(2)], [p(3) p(3)+r1(3)], 'r')
plot3([p(1) p(1)+r2(1)], [p(2) p(2)+r2(2)], [p(3) p(3)+r2(3)], 'g')
plot3([p(1) p(1)+r3(1)], [p(2) p(2)+r3(2)], [p(3) p(3)+r3(3)], 'b')
%%%EOF plot_T
% -------------------------------------------------------------------------
