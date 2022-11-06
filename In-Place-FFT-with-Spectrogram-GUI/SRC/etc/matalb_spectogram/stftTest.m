clear;
clc;
close all;

filename = "chopin_etude_op25_no11.mp3";
[y, Fs] = audioread(filename);
y = y(20*Fs:30*Fs);
x = resample(y,8192,44100);
Fs = 8192;
sound(x,Fs);

N = 1024;
H = N/2;
L = length(x);
M = floor((L-N)/H);
w = window(@hann,N);
w = transpose(w);
Xk = stft_sample(x,w,N,H,M);
X = transpose(Xk);
X = abs(X);
X = X.^2;
X = 10*log10(X);
dx = 0:H/Fs:M*H/Fs;
dy = 0:Fs/N:Fs/2;
pmax = powermax(X);
pmin = powermin(X);
dp = [pmin pmax];
PD = powerDistribution(X,N,M);

fig = figure;
fig.Position = [400 100 650 650];
subplot(2,2,3)
image(dx,dy,X,'Cdatamapping','scaled')
ax = gca;
ax.YDir = 'normal';
c = colorbar;
c.Label.String = 'Power(dB)';
xlabel('Time(sec)')
ylabel('Frequency(Hz)')

subplot(2,2,4)
image(dx,dp,PD,'Cdatamapping','scaled')
ax = gca;
ax.YDir = 'normal';
c = colorbar;
c.Label.String = 'Density(%)';
xlabel('Time(sec)')
ylabel('Power(dB)')

subplot(2,2,1:2)
stftplot(Xk,M);