function T = S2T(S)
%
% forms a homogeneous matrix T given
%
% S - struct as given in the lab description
%

R = rx(S.alpha)*ry(S.beta)*rz(S.gamma);
t = [S.x S.y S.z]';
T = [         R, t;
    zeros(1,3),   1];

%%%EOF form_T
% -------------------------------------------------------------------------
