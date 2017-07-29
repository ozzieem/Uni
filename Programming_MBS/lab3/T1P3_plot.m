function T1P3_plot(q, l, q_start)

q1 = poly3(q_start(1), q(1), 0, 0, [0:0.01:1]);
q2 = poly3(q_start(2), q(2), 0, 0, [0:0.01:1]);


for i = 1 : 1 : length(q1)
    FGM = T1P2_fgm_T2([q1(i) q2(i)], l); % evaluate the FGM
    
    clc;cla;
    hold on;
    plot([0 FGM(1) FGM(3)], [0 FGM(2) FGM(4)]);
    plot(FGM(1), FGM(2), 'o');
    plot(FGM(3), FGM(4), 'o');
    
    axis([-(l(1)+l(2)) (l(1)+l(2)) -(l(1)+l(2)) (l(1)+l(2))]);
    pause(0.01);
    
end
