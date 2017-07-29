function [abT] = T5_abT(th, r_vect)

I = eye(4,4)

p1 = rx(th)
p2 = ry(th)
p3 = rz(th)

p4 = [1 0 r_vect(1); 0 1 0; 0 0 1]
p5 = [1 0 0; 0 1 r_vect(2); 0 0 1]
p6 = [1 0 0; 0 1 0; 0 0 r_vect(3)]


% abT expressed as a product of 6 homogenous matrices
abT = p1*p2*p3*p4*p5*p6


end

