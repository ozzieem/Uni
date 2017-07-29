% Inverse Geometric Model

function q = igm(pe, l, up_down)

c2 = (pe(1)^2 + pe(2)^2 - l(1)^2 - l(2)^2) / (2 * l(1) * l(2));

if up_down == 0
    s2 = -sqrt(1 - c2^2);
else
    s2 = sqrt(1 - c2^2);
end

if c2 < -1 | c2 > 1
    q = NaN;    
else
    alfa = atan2(pe(2), pe(1));
    beta = atan2(l(2) * s2, l(1) + l(2) * c2); 
   
    q(1) = alfa - beta;
    q(2) = atan2(s2, c2);
end
end

%input: pe - desired Cartesian coordinates of the end-effector
%input: l - lengths of the two links
%input: up_down - a flag for choosing up-elbow or down-elbow
%output: q - joints angles
