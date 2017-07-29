function lab2Task1(ang)

R = eye(3);
delta = 0.05;
draw_frame(eye(3));

for i = 0 + delta: delta : 1
    R = R * rz(delta*ang);
    draw_frame(R, 'rgb');
    pause(0.1);
end
end
    