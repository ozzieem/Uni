function angles = T3P3_geteulers(R)

d = R(8)^2 + R(9)^2;

angles = [-atan2(R(4), R(1));       %gamma
          -atan2(R(8), R(9));       %alfa
          atan2(R(7), sqrt(d))];    %beta
end
