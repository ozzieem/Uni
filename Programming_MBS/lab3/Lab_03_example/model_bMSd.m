function SP = model_bMSd(pos,rot,e)
%
% this file is used in the example in Lab_03
%
% a system is defined using:
% --------------------------
% pos(:,i)  - position of frame i as seen from frame i-1
%             (frame 0 is the world frame)
%
% rot(:,i)  - frame i is rotated w.r.t. frame i-1 using
%             x->y->z Euler angles (current axis)
%
% e.pos     - position of the end-effector in last frame
% e.pos     - x->y->z Euler angles (current frame) w.r.t last frame
%

% definition of system structure
% ----------------------------------------
SP.n = size(pos,2);
SP.C = 0:SP.n+1;
SP.mode = 1; % fixed base

% definition of joints
% I assume that the CoM of link i coincides with the input joint of link i
% ----------------------------------------
for i = 1:SP.n
    SP.J(i).t    = pos(:,i);
    SP.J(i).f    = zeros(3,1); % CoM coincides with the joint
    SP.J(i).rpy  = rot(:,i);
    SP.J(i).type = 'R';
end

% definition of links
% I use trivial values here
% ----------------------------------------
for i = 1:SP.n+1
    SP.L(i).m = 1;
    SP.L(i).I = eye(3);
end

% definition of end-effectors
% (only one end-effector)
% ----------------------------------------
SP.bN = SP.n+1;
SP.bP = e.pos;
SP.bR = rpy2R(e.rot);

%%%EOF