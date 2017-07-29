clear

Gravity = [0;0;0]; % acceleration due to gravity 
d_time = 0.01; % numerical integration step

% system definition 
SP = model_system_2();
%SP = model_ABB();
%SP = model_7dof();

SV = System_Variables(SP);

% generate random joint angles
SV.q = rand(SP.n,1); 

% updates positions of links
SV = calc_pos(SP,SV); 

% Jacobian of the end-effector defined by SP.bN,SP.bP
Je = calc_Je(SP,SV,SP.bN,SP.bP); 

% Position of the end-effector in the world frame 
[pE,RE] = fk_e(SP,SV,SP.bN,SP.bP);

% Position of the joints in the world frame
pJ = fk_j(SP,SV,[1:SP.n]);

% manipulator inertia matrix
HH = calc_hh(SP,SV); 
H = HH(7:end,7:end);

% nonlinear term
C = r_ne(SP,SV,Gravity);

% some general purpose functions 
jt = joint_tree(SP,SP.bN);

% Some conventions for rotations
ea = [pi/2 ; -pi/4 ; pi/3]; % Euler angles (X-Y-Z current axis)
R = rpy2R(ea); % rotation matrix
Qn = R2q(R); % quaternion
ea1 = q2rpy(Qn);

% visualize
Draw_System(SP, SV, SP.bN, SP.bP,[1:SP.n]);
axis equal
grid on
axis off
cameratoolbar
drawnow

return

SV.dq = rand(SP.n,1);
SV.tau = rand(SP.n,1);
SV.L(1).F=rand(3,1);
SV.L(1).T=rand(3,1);

i=1;
for time=0:d_time:5
  
  outQ(:,i) = SV.q; % output joint angles
  outT(i) = time;

  %visualizing in the loop is very slow
  %--------------------------------------------
  if 0
    cla
    Draw_System(SP, SV, SP.bN, SP.bP,[1:SP.n]);
    axis equal
    grid on
  end
  %--------------------------------------------
  
  % perform a simulation step using Euler
  SV = f_dyn(SP,SV,Gravity); % forward dynamics
  SV = int_euler(SV,d_time); % numerical integration
  
  % RK4 integration
  %SV = int_rk4(SP,SV,d_time,Gravity); % forward dynamics & numerical integration
  
  i=i+1;
end

figure(2);hold on;
for i=1:SP.n
  plot(outQ(i,:),'b')
end

%%%EOF