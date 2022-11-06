function stftplot(Xk,M)
Xk = abs(Xk);
col = length(Xk(1,:));
Xk = Xk/col;
ymin = min(min(Xk));
ymax = max(max(Xk));
h = animatedline;
for m = 0:M
    Xk(m+1,2:col) = Xk(m+1,2:col)*2;
    axis([m*col (m+1)*col-1 min(Xk(m+1,:)) max(Xk(m+1,:))])
    addpoints(h,m*col:(m+1)*col-1,Xk(m+1,:));
    drawnow
end

axis([0 col*(M+1)-1 ymin ymax]);
for m = 0:M
    addpoints(h,m*col:(m+1)*col-1,Xk(m+1,:));
    drawnow limitrate
end
title('\fontsize{12}Chopin Etude Op.25 No.11','Short Time Fourier Transform');
xlabel('Sample(#)');
ylabel('Amplitude');