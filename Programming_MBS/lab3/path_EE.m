%
% Generation of a Cartesian path (exercise 3)
%

clear;clc;cla

hold on
axis([-1 1 -1 1]);grid on

[x,y] = ginput % press RETURN to stop
z = zeros(length(x),1);
P = [x';y';z']

pe = trajC(P(1,:),P(2,:),P(3,:),1,0.01);
plot(pe(1,:),pe(2,:),'b')

%%%EOF