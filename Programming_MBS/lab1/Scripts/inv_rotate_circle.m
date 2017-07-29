for v = 0 : 0.1 : (2 * pi) * 1
    u = inv_rotate2D([1,1]', v);
    plot(u(1),u(2), 'go')
    axis([-3 3 -3 3]);
    pause(.05);
end