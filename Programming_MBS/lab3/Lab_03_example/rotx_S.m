function S=rotx_S(S, angle)
%
% update S with rotation angle around it's local X coordinate
%
% S - struct as given in the lab description
% angle - angle to be rotated
%

R = rx(S.alpha)*ry(S.beta)*rz(S.gamma)*rx(angle);
rpy = R2rpy(R);
S.alpha = rpy(1);
S.beta = rpy(2);
S.gamma = rpy(3);

% This will not guarantee that we rotate around the x-axis only since the
% rotation could be dependent on S.beta and S.gamma.
%S.alpha = S.alpha + angle;

%%%EOF plot_S
% -------------------------------------------------------------------------
