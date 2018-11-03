%% System Parameters
% a = 1/(RC)
a = 25; % radians
Fs = 500;% Hz
T = 1/Fs;
% Output Signal Period
U = 1/Fs;
computation_time = 0.01;
IRQ_DELAY = T + computation_time; % Interrupt service routine delay + sampling period
% try K = 10 you get an overshot with time dealy approx
K = 1;




%% z transform model G(z) 

% K sets pole of analog system to
pa = -a-K*a

%%
Tsim = 0.0001 % for Simulink fixed point solver


zp=exp(-a*T)
zg=K*(1-exp(-a*T))
