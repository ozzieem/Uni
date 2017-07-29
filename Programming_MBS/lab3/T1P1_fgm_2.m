function pe = T1P1_fgm_2(q, l1, l2)

pe = [l1 * cos(q(1)) + l2 * cos(q(1) + q(2));
      l1 * sin(q(1)) + l2 * sin(q(1) + q(2))];
  
end
