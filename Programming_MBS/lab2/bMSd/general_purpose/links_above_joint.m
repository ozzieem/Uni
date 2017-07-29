function L = links_above_joint(SP,J)
%
% ------------------------------------------------------
% | Basic Multibody Simulator Derived (Matlab toolbox) |
% ------------------------------------------------------
% | General purpose |
% -------------------
%
% links_above_joint
%
% Returns the links that depend on the motion of link J. 
% The indexes are in ascending order.
%
% Syntax:
% -------
% L = links_above_joint(SP,J);
%
% Input:
% ------
% SP    - structure containing system parameters (see struct_def.m)
% J     - joint number (a scalar)
%
% Output:
% -------
% L     - a vector containing link numbers that depend on joint J
%
% SV members changed:
% --------------------
%

%
% Version 1.0 [2009/07]
%
% This toolbox is developed by Dimitar Dimitrov for educational purpose.
% ----------------------------------------------------
%

k = 1;
for i = 1:SP.n+1
  joints = joint_tree(SP,i);
  
  if ~isempty(find(joints == J));
    L(k) = i;
    k = k+1;
  end
end

%%%EOF