function qi = quat_inv(q)
%
% ------------------------------------------------------
% | Basic Multibody Simulator Derived (Matlab toolbox) |
% ------------------------------------------------------
% | Rotations |
% -------------
%
% quat_inv
%
% Computes an inverse of a quaternion q
%
% Syntax:
% -------
% qi = quat_inv(q)
%
% Input:
% ------
% quaternion q of the form
% 
% q = [s x y z] - unit quaternion 
%     [s]       - scalar part
%     [x y z]   - vector part
%
% Output: 
% -------
% qi - inverse of q 
%

% Algorithm:
% ----------
% 
% qi = [s -x -y -z]
%

%
% Version 1.0 [2009/07]
%
% This toolbox is developed by Dimitar Dimitrov for educational purpose.
% ----------------------------------------------------

qi = zeros(1,4);
qi(1) = q(1);
qi(2:4) = -q(2:4);

%%%EOF