function pd = powerDistribution(X,N,M)
pd = zeros(N/2+1,M+1);
mu = mean(X);
sigma = std(X);
X = sort(X);
for m = 0:M
    pd(:,m+1) = exp(-(X(:,m+1)-mu(m+1)).^2./(2*sigma(m+1)^2))./(sigma(m+1)*sqrt(2*pi));
end
pd = 100 * pd;