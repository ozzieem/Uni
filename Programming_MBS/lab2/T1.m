
A = eye(3);
B = A;

dth = 0.03;

draw_frame(B)

for rad = 0 + dth : dth : 2 * pi
    B = B * rx(dth)
    draw_frame(B,'rgb')
    pause(.05);
end
