function[proj_ans] = proj(A,B)

proj_ans = (dot(A,B)/norm(B,1)^2)*B;

end