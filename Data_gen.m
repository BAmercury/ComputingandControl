%% Program to genenerate ground truth and measurement data
% for Alpha Kalman filter 
%  Data_gen
%  author  Tom Chmielewski   
%  last revision 22 May 2018  
%
%  Program Description
%
%  This mfile generates state and measurement data for 
%  a system of the form
%       x(k+1) = phi*x(k) + w(k)
%       z(k) = x(k) + v(k)
%  where phi = 1 
close all
clear all
clc
format short;

% Key parameters follow
%  overall parameters
    T = 1;  %  sampling time
    n = 100;  %  number of discrete time steps
    max_time = T*n; ;  %  maximum time

% ground truth parameters
    x_ic = [100];  %  IC for state vector
    phi = 1.0;  % paramter for simulation
   
%  measurement noise parameters
    R  = 0.4^2;  %  Gaussian, normal variance of R and  mean v_mean
    v_mean = 0;
% state noise parameters
    Q = 0; % if we didnt have any state noise, notice how kf data still thinks there is noise in the system
    %Q = 0.05; %  Gaussian normal variance of Q with mean z_mean
    w_mean = 0;
% --------------------------------------   
 
%  create noise vectors

randn('seed',2345);  %  set a seed so we can repeat experiment
v = v_mean + sqrt(R).*randn(1,n); % create gaussian noise with bias v_mean
%  check noise
v_m= mean(v);
%  remove bias noise due to finite length

v = v-(v_m);


randn('seed',5432);  %  set a seed so we can repeat experiment
w = w_mean + sqrt(Q).*randn(1,n); % create gaussian noise with bias v_mean
w_m= mean(w);
% remove bias noise
w = w-(w_m);

% check simulation of noise
v_m= mean(v);
v_m= mean(v);
vn_act = cov(v);
fprintf('measurement noise mean %6.4f  cov %6.2f\n\n', v_m, vn_act)

w_m= mean(w);
wn_act = cov(w);
fprintf('state noise mean %6.4f  cov %6.2f\n\n', w_m, wn_act)

x_hist = []; %  accumulator for state 
z_hist = []; %  accumulator for measurements
t_hist = []; % accumulator for update time

x_old = x_ic;

% generate trajectories
delt = 100;
for k = 1:n

    %if k>50
    %    delt = 100; % change later 
    %end

        
     x_new = phi*x_old + ((T^2)/2)*w(k);
    %x_new = delt;  % constant
     z = x_old + v(k); % gives us the measurement
    
     % Save the data
     x_hist = [x_hist, x_old];  % so time 0 is IC
     z_hist = [z_hist, z];
     t_hist = [t_hist, k-1];
    
     % restart
     x_old = x_new;
    
end


%%  display track data
figure
plot(t_hist,x_hist,'g',t_hist,x_hist,'g.' )
hold on
plot(t_hist,z_hist,'r', t_hist,z_hist, 'r.')
legend('actual state','actual state','measured state','measured state', ...
    'location', 'best')
title('state and measurement data 1st order system')


clean_data = [];
clean_data(1) = 100;
a = 0.24316/4;
%% Attempt to build a KF
for k = 1:1:n-1
    clean_data(k+1) = clean_data(k) + a*(z_hist(k+1)-clean_data(k)); 
end

figure
plot(t_hist,x_hist,'g',t_hist,x_hist,'g.' )
hold on
plot(t_hist,z_hist,'r', t_hist,z_hist, 'r.')
hold on
plot(clean_data)
legend('actual state','actual state','measured state','measured state', ...
    'location', 'best','filtered')
title('state and measurement data 1st order system')

%% X tilde compute the error
x_t = x_hist - clean_data;
% compute variance
var(x_t);




