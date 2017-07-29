%
% Example (Lab_03)
%

clear;clc;cla

% constant parameters (system definition)
% -------------------------------------------------------------------------
pos(:,1) = [1; 0; 0]; % position of frame 1 in frame 0
pos(:,2) = [1; 0; 0]; % position of frame 2 in frame 1
pos(:,3) = [1; 0; 0]; % position of frame 3 in frame 2
pos(:,4) = [0; 1; 0]; % position of frame 4 in frame 3
pos(:,4) = [0; 0; 1]; % position of frame 5 in frame 4
% .

% frame i is rotated w.r.t. frame i-1 using x->y->z Euler angles (current axis)
rot(:,1) = [0;pi/4;0]; % frame 1 in world frame
rot(:,2) = [0;0;pi/4]; % frame 2 in frame 1
rot(:,3) = [0;0;0]; % frame 3 in frame 2
rot(:,4) = [0;0;0]; % frame 4 in frame 3
rot(:,5) = [0;0;0]; % frame 5 in frame 4
% ...

e.pos = [1;1;1]; % position in last frame
e.rot = [0;0;0]; % x->y->z Euler angles (current frame) w.r.t last frame

n = size(pos,2);

% just testing
%pos = randn(3,n);
%rot = randn(3,n);
%e.pos = randn(3,1);
%e.rot = randn(3,1);

% variable parameters: q(i) is the angle around the local z-axis of frame i
% -------------------------------------------------------------------------
q = zeros(n,1);

% visualization
% -------------------------------------------------------------------------
% [pe, Re] = plot_chain(pos,rot,e,q); % plots one configuration

%plot 3 configuration
if 1
    for i = 1:n
        %plot_chain(pos,rot,e,q+[0.2*i;0;0]);
        %plot_chain(pos,rot,e,q+[0;0.2*i;0]);
        plot_chain(pos,rot,e,q);
    end
end

% the same system using the bMSd toolbox
% -------------------------------------------------------------------------
if 0
    SP = model_bMSd(pos,rot,e);
    SV = System_Variables(SP);
    SV.q = q;
    
    % positions of CoM of links
    SV = calc_pos(SP,SV);
    
    % Position of the joints in the world frame
    pJ = fk_j(SP,SV,1:SP.n);
    
    % Position of the end-effector in the world frame
    [pe1,Re1] = fk_e(SP,SV,SP.bN,SP.bP,SP.bR);
    
    % visualize
    Draw_System(SP, SV, SP.bN, SP.bP,1:SP.n);
    
    disp('compare')
    pe-pe1
    Re-Re1
end

grid on; axis equal
%%%EOF