g = 9.81; 
l = 0.8048; % Length of arm, approximation
m = 1; % kg, approxmation

A = [0 1; g/l 0];
B = [0; l/m];
C = [1 0];
D = 0;

sys = ss(A,B,C,D)

%%
% Test controllability
result = rank(ctrb(A,B))

%%
% Test observability
result2 = rank(obsv(A,C))

%%
% Both are full rank so we are able to move eig to any point

%%
% Transfer function representation
[NUM, DEN] = ss2tf(A,B,C,D)
tf_sys = tf(NUM, DEN)

%%
% Eigenvalues/Poles
e = eig(A)
% One pole in RHP and one in LHP

%%
% Open loop impulse response
impulse(sys)
%%
% Notice response trails off to infinity
%%
% Open loop step resposne
grid on
step(sys)
title('Step Response of open loop system')

%%
% Likewise the step response trails to infinity. Implement state feedback
% to have system regulate to desired angle
P = [-5, -3] % Arbitrary poles
K = place(A,B,P)


%%
% Update the state feedback model with the new K values
t = 0:0.01:5; % Simulation time span
sys_fdbk = ss(A-B*K, B, C, D)
[NUM, DEN] = ss2tf(A-B*K, B, C, D);
tf_sys_fdbk = tf(NUM, DEN)
step(sys_fdbk, t)
grid on
title('Step Response with Feedback')

