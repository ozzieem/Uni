function [ output ] = myPlot3Vectors(vects)
%% Make dynamic
starts = zeros(3,3);
hold on
output = quiver3(starts(:,1),starts(:,2),starts(:,3),vects(:,1),vects(:,2),vects(:,3));
hold off
axis equal
end

