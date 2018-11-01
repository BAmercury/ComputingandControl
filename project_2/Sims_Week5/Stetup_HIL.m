%% file:  Setup_HIL
% Dr. Tom Chmielewski
% 20 October 2018
%% System Parameters
% a = 1/(RC)
a = 25; % radians
Fs = 500;% Hz
T = 1/Fs;

K = 20;
% try K = 10 you get an overshot with time dealy approx
% K sets pole of analog system to
pa = -a-K*a

%%
Tsim = 0.0001 % for Simulink fixed point solver

%% z transform model G(z) 
zp=exp(-a*T)
zg=K*(1-exp(-a*T))
