
%
% data file used in exercise 2
%

% homogeneous matrix that transforms vectors from frame {B} to frame {A}
A_T_B = [0.572061402817684  -0.415626937777453   0.707106781186547   1;
         0.789312333510914   0.044565010575065  -0.612372435695795   1;
         0.223006259046285   0.908442738110763   0.353553390593274   1;
         0                   0                   0                   1];

% homogeneous matrix that transforms vectors from frame {C} to frame {B}
B_T_C = [ 0   1   0   2;
         -1   0   0   0;
          0   0   1   0;
          0   0   0   1];

% homogeneous matrix that transforms vectors from frame {D} to frame {C}
C_T_D = [ 0   0   1   0;
          0   1   0   2;
         -1   0   0   0;
          0   0   0   1];


A_T_D = A_T_B * B_T_C * C_T_D

D_T_B = inv(B_T_C * C_T_D)

geteulers([A_T_B(1:3); A_T_B(5:7); A_T_B(9:11)])


%%%EOF