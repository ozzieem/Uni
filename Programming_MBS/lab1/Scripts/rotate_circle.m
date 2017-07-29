for v = 0 : 0.01 : (2 * pi) * 1
    u = rotate2D([1,0]', v)
    plot(u(1),u(2), 'go')
    axis([-1.5 1.5 -1.5 1.5]);
    pause(.05);
    
end