function [] = free_fall_deltat(r0, vf)

rf = r0;
dt = 0.01;
a = 9.82;
t = 0;
while(rf >= 0)
    vf = vf + -a*dt;
    rf = rf + vf*dt + (1/2)*a*dt^2;
    t = t + dt; % Display Time
    
    disp('Velocity        Altitude       Time');
    disp([vf, rf, t]);
    
    plot(0,rf, 'o');
    axis([-r0 r0 -10 r0+100]);
    pause(dt);
end
end