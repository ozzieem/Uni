function T2P2_plottraj(l, up_down)

axis([-(l(1)+l(2)) (l(1)+l(2)) -(l(1)+l(2)) (l(1)+l(2))]);grid on
[x,y] = ginput;

z = zeros(length(x),1);
P = [x';y';z'];

pe = trajC(P(1,:),P(2,:),P(3,:),1,0.01);

for i = 1 : 1 : length(pe)
    
    % Calculate angle with IGM from coords
    q = T2P1_igm([pe(1, i) pe(2, i)], l, up_down);
    
    % Calculate coords from angles
    FGM = T1P2_fgm_T2([q(1) q(2)], l);
    
    clc;cla;
    hold on;
    plot([0 FGM(1) FGM(3)], [0 FGM(2) FGM(4)]);
    plot(FGM(1), FGM(2), 'o');
    plot(FGM(3), FGM(4), 'o');
    
    axis([-(l(1)+l(2)) (l(1)+l(2)) -(l(1)+l(2)) (l(1)+l(2))]);
    
    % Plot the profile
    plot(pe(1,:),pe(2,:),'b');
    pause(0.03);
end
