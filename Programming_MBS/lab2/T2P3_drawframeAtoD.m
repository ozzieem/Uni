
A = eye(3);
B = A;
C = rx(pi/4)*B;
D = ry(pi/4)*A;

draw_frame(B)

dth = 0.03;

% fixed frame = Rz*Ry*Rx
% current frame = Rx*Ry*Rz

% C
for rad = 0 + dth : dth : pi/4
    m = B*rx(rad)
    draw_frame(m,'rgb')
    pause(.05);
end

draw_frame(C)

% D
for rad = 0 + dth : dth : pi/4
    m = C*ry(rad)
    draw_frame(m,'rgb')
    pause(.05);
end
