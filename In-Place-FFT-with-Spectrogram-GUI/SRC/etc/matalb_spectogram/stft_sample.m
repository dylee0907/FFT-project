function Xk = stft_sample(x,w,N,H,M)
Xk = zeros(M+1,N/2+1);

for m = 0:M
    x_win = x(m*H+1:m*H+N).*w;
    Xk(m+1,(1:N/2+1)) = dit_sample(x_win);
end