function [ output ] = rotate2D(point_, rad )

R = [ cos(rad) -sin(rad); sin(rad) cos(rad) ];
output = R*point_;
            
end

