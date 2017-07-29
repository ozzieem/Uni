
dth = 0.03;

for rad = 0 : dth : pi/4
    draw_frame(rz(rad),'rgb')
    pause(.05);
end

for rad = 0 : -dth : -pi/18
    draw_frame(rx(rad),'rgb')
    pause(.05);
end