function [ R ] = rotation_matrix( rad )

R = [ cos(rad) -sin(rad); sin(rad) cos(rad) ];
end

