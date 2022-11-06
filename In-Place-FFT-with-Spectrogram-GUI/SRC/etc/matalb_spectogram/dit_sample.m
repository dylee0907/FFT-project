function Xk = dit_sample(x)

p = nextpow2(length(x));
x = [x zeros(1,(2^p)-length(x))];
N = length(x);
S = log2(N);
x = bitrevorder(x);
Half = 1;
for stage=1:S                                                               % stages of transformation
    for index=0:(2^stage):(N-1)                                             % series of "butterflies" for each stage
        for n=0:(Half-1)                                                    % creating "butterfly" and saving the results
            pos=n+index+1;                                                  % index of the data sample
            pow=(2^(S-stage))*n;                                            % part of power of the complex multiplier
            w=exp((-1i)*(2*pi)*pow/N);                                      % complex multiplier
            a=x(pos)+x(pos+Half).*w;                                        % 1-st part of the "butterfly" creating operation
            b=x(pos)-x(pos+Half).*w;                                        % 2-nd part of the "butterfly" creating operation
            x(pos)=a;                                                       % saving computation of the 1-st part
            x(pos+Half)=b;                                                  % saving computation of the 2-nd part
        end
    end
Half=2*Half;                                                                % computing the next "Half" value
end
Xk(1:N/2+1) = x(1:N/2+1);