% Lab 3 task 3.

close all;
clear all;

S(1).x = 0;
S(1).y = 0;
S(1).z = 0;
S(1).alpha = 0;
S(1).beta = pi/6;
S(1).gamma = 0;

S(2).x = 2;
S(2).y = 0;
S(2).z = 0;
S(2).alpha = 0;
S(2).beta = 0;
S(2).gamma = 0;

% Plot the frames
plot_S(S)

% Function that rotates round the x-axis.
S(1) = rotx_S(S(1), pi/8);
plot_S(S)

% Rotate around S(2) 
S(2) = rotx_S(S(2), pi/8);
plot_S(S)

%  Translate along z-axis in S(1)
S(1) = translz_S(S(1), 0.2);
plot_S(S)

%  Translate along z-axis in S(2)
S(2) = translz_S(S(2), 0.2);
plot_S(S)



% New plotting window
figure(2)
% Use the keys

stop=0; inc=0.01;
while ~stop
    clf;
    plot_S(S)
    waitforbuttonpress;
    if strcmp(get(gcf,'currentcharacter'),'a');
        S(1) = rotx_S(S(1), inc);
    elseif strcmp(get(gcf,'currentcharacter'),'z');
        S(1) = rotx_S(S(1), -inc);
    elseif strcmp(get(gcf,'currentcharacter'),'s');
        S(2) = rotx_S(S(2), inc);
    elseif strcmp(get(gcf,'currentcharacter'),'x');
        S(2) = rotx_S(S(2), -inc);
    elseif strcmp(get(gcf,'currentcharacter'),'d');
        S(1) = translz_S(S(1), inc);
    elseif strcmp(get(gcf,'currentcharacter'),'c');
        S(1) = translz_S(S(1), -inc);
    elseif strcmp(get(gcf,'currentcharacter'),'f');
        S(2) = translz_S(S(2), inc);
    elseif strcmp(get(gcf,'currentcharacter'),'v');
        S(2) = translz_S(S(2), -inc);

    elseif strcmp(get(gcf,'currentcharacter'),'q');
    stop=1; disp('quit');
    end
    
end
