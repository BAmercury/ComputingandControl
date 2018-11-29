%% System Parameters
% a = 1/(RC)
a = 25.1133; % radians
Fs = 500;% Hz
T = 1/Fs;
% Output Signal Period
U = 1/Fs;
% Delay induced on hardware to see unstable response
delay = 0;
%delay = .10;
computation_time = 0.000870; % computations and sampling incorporated measured on arduino
IRQ_DELAY = computation_time + delay; % Interrupt service routine delay
% try K = 10 you get an overshot with time dealy approx
K = 1;




%% z transform model G(z) 

% K sets pole of analog system to
pa = -a-K*a

%%
Tsim = 0.0001 % for Simulink fixed point solver


zp=exp(-a*T)
zg=K*(1-exp(-a*T))
