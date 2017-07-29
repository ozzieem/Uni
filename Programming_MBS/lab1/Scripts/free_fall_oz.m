function [] = free_fall_oz(y0, t0, v0)

yt = y0;
t = t0;
while(yt >= 0)
    vt = -9.82*t + v0;
    yt = -(1/2)*9.82*t^2 + v0*t + y0;
    t = t + 0.001;
    
    disp('Velocity    Altitude   Time');
    disp([vt, yt, t]);
    
    u = [0, y0]-[0, y0-yt];
    plot(u(1),u(2), 'o');
    axis([-y0 y0 -10 y0+100]);
    pause(.0001);
end
end