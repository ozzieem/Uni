function [ output ] = inv_rotate2D(point_, rad )

%R = inv([ cos(rad) -sin(rad); sin(rad) cos(rad) ]);
R = [cos(rad) sin(rad); -sin(rad) cos(rad)];
output = R * point_;
            
end

