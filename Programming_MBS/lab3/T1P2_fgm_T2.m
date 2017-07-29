function result = T1P2_fgm_T2(q, l)
p01 = [0; 0; 0];
p12 = [l(1); 0; 0];
p2e = [l(2); 0; 0];

T01 = [rz(q(1)) p01;
       0 0 0 1];

T12 = [rz(q(2)) p12;
       0 0 0 1];
   
T2e = [rz(0) p2e;
       0 0 0 1];

T02 = T01 * T12;

T0e = T01 * T12 * T2e;

result = [T02(13) T0e(13) q(1) q(2); 
          T02(14) T0e(14) 0 0];
   
end
