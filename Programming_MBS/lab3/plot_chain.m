function [pe, Re] = plot_chain(pos,rot,e,q)
%
% plots a chain of frames defined by
%
% pos(:,i)  - position of frame i as seen from frame i-1
%             (frame 0 is the world frame)
%
% rot(:,i)  - frame i is rotated w.r.t. frame i-1 using
%             x->y->z Euler angles (current axis)
%
% e.pos     - position of the end-effector in last frame
% e.pos     - x->y->z Euler angles (current frame) w.r.t last frame
%
% q(i)      - angles around the local z-axis
%

Tp = eye(4); % world frame (the parent frame of the first frame)

hold on;

% plot the world frame
plot_line([0;0;0],Tp(1:3,1),'b',2);
plot_line([0;0;0],Tp(1:3,2),'g',2);
plot_line([0;0;0],Tp(1:3,3),'r',2);

% Plot all frames
for i = 1:length(q)
    Tc = Tp*form_T(pos(:,i),rot(:,i),q(i)); % forward geometric model
    plot_T(Tp,Tc);
    Tp = Tc;
end
% handle the end-effector
Tc = Tp*form_T(e.pos,e.rot,0);
plot_T(Tp,Tc);
pe = Tc(1:3,4);
Re = Tc(1:3,1:3);
plot3(pe(1),pe(2),pe(3),'ro','MarkerFaceColor','r','markerSize',6)

%%%EOF plot_chain
% -------------------------------------------------------------------------

function T = form_T(pos,rot,q)
%
% forms a homogeneous matrix T given
%
% pos - 3D position
% rot - Euler angles x->y->z (current axis)
% q   - joint angle around the local z-axis
%

R = rx(rot(1))*ry(rot(2))*rz(rot(3)+q);
T = [         R, pos;
    zeros(1,3),   1];

%%%EOF form_T
% -------------------------------------------------------------------------

function plot_T(Tp,Tc)
%
% Tp and Tc are two homogeneous matrices defining the posture of two
% consecutive frames with respect to the world frame.
%
% This function plots the frame associated with the homogeneous matrix Tc
% as well as the vector from the origin of Tp to the origin of Tc
%

% position of the origin (in the world frame) of the frame associated with Tp
p1 = Tp(1:3,4);

% position of the origin (in the world frame) of the frame associated with Tc
p2 = Tc(1:3,4);

% rotation matrix (w.r.t the world frame) associated with Tc
R = Tc(1:3,1:3);

% plot vector from the origin of Tp to the origin of Tc
plot_line(p1,p2,'k');

scale = 0.5; % plot shorter coordinate axis (for better view)
plot_line(p2,p2+R(:,1)*scale,'b',2);
plot_line(p2,p2+R(:,2)*scale,'g',2);
plot_line(p2,p2+R(:,3)*scale,'r',2);

%%%EOF plot_T
% -------------------------------------------------------------------------

function plot_line(p1,p2,color,lw)
%
% plots a line (in 3D) from point p1 to point p2 with
% color - color
% lw    - line width
%
% Example:
% ---------
% plot_line([0;0;0],[1;1;1],'b',2)
%

if nargin < 4
    lw = 1;
end

plot3([p1(1) p2(1)], [p1(2) p2(2)], [p1(3) p2(3)], color, 'LineWidth',lw)

%%%EOF plot_line
% -------------------------------------------------------------------------

%%%EOF