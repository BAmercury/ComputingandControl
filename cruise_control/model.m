m = 1000; %kg
damp = 50; % Ns/m

% State Space Model
A = -damp/m;
B = 1/m
C = 1;
D = 0;

ss_model = ss(A,B,C,D);

% Transfer function model
s = tf('s')
tf_model = 1/(m*s + damp);

% Open Loop Resposne
u = 500 % Newtons
step(u*tf_model)

% Open Loop Zeros and Poles
pzmap(tf_model)
axis([-1 1 -1 1])

% Open loop frequency response: Bode plot
bode(tf_model)

% PID Controller
Kp = 1;
Ki = 1;
Kd = 1;

s = tf('s');
C = Kp + Ki/s + Kd*s

C = pid(Kp,Ki,Kd)

T = feedback(C*tf_model,1);
r = 10; % Reference input
t = 0:0.1:20;
step(r*T,t)
axis([0 20 0 10])

% Root locus method
rlocus(tf_model)
axis([-0.6 0 -0.6 0.6]);
sgrid(0.6, 0.36)

[Kp,poles]=rlocfind(tf_model) %(~ -0.4)

sys_cl = feedback(Kp*P_cruise,1);
t = 0:0.1:20;
step(r*sys_cl,t)

% Implement lag compensator to fix steady state error
zo = 0.3;
po = 0.03;

s = tf('s');
C_lag = (s+zo)/(s+po);

rlocus(C_lag*P_cruise);
axis([-0.6 0 -0.4 0.4])
sgrid(0.6,0.36);
[Kp,poles]=rlocfind(C_lag*tf_model) %(~ -0.4)

% State space approach
x0 = [0];

p1 = -1.5;

K = place(A,B,[p1])

sys_cl = ss(A-B*K,B,C,D);
lsim(sys_cl,u,t,x0);
axis([0 10 0 0.35])

Nbar = rscale(sys,K)*10/500;
sys_cl = ss(A-B*K,B*Nbar,C,D);

lsim(sys_cl,u,t,x0);
axis([0 10 0 11])


% Discrete time approach
Ts = 1/50;

dP_cruise = c2d(P_cruise,Ts,'zoh')

Wn = 0.0072;
zeta = 0.6;

rlocus(dP_cruise)
zgrid(zeta, Wn)
axis ([-1 1 -1 1])
axis ([0.95 1 -.1 .1])

[K,poles] = rlocfind(dP_cruise) 

K = 451.1104;
sys_cl = feedback(K*dP_cruise,1);
r = 10;
figure
step(r*sys_cl,10);

% employ a digital lag compensator to reduce sserror
m = 1000;
b = 50;
u = 500;

s = tf('s');
P_cruise = 1/(m*s+b);
Ts = 1/50;
dP_cruise = c2d(P_cruise,Ts,'zoh');

z = tf('z',Ts);
C = 0.2*(z - 0.999)/(z - 0.9998);

Wn = 0.0072;
zeta = 0.6;

rlocus(C*dP_cruise)
zgrid(zeta, Wn)
axis([0.98 1 -0.01 0.01])


[K,poles] = rlocfind(C*dP_cruis (~-0.99)

K = 2.4454e+03;
sys_cl = feedback(K*C*dP_cruise,1);
r = 10;
step(r*sys_cl,10);