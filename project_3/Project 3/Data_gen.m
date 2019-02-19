
n = 9

kf_data = xlsread('kf_data.xlsx');

normal_track = [1,2,3,4,5,7,8,9,10]';
ground_truth = kf_data(:,2);
measured_data = kf_data(:,4);
samples = (1:1:9);

% Compute error between ground truth and measured data
diff = ground_truth - measured_data;
variance_ground_v_measured = var(diff)

% Compute error between the ideal track data and measured data
diff = normal_track - measured_data;
variance_normal_v_measured = var(diff)

% Compute error between the ideal track data and the ground truth data
diff = normal_track - ground_truth;
variance_ground_v_normal = var(diff)
% Results here we see that the measured data has the more variance with the
% ideal track. There is variance between the ground truth and ideal data.
% The error was induced to simulate possible noise


%%  display track data
figure
plot(samples,ground_truth,'g',samples,ground_truth,'g.' )
hold on
plot(samples,measured_data,'r',samples,measured_data, 'r.')
hold on
plot(samples,normal_track,'b',samples,normal_track, 'b.')
legend('actual state','actual state','measured state','measured state', ...
    'ideal track', 'ideal track', 'location', 'best')
title('Ground Truth, Measured, and Ideal Data for a 1st order system')



%% Attempt to build a KF
clean_data = [];
clean_data(1) = 1;
a = 0.7;
for k = 1:1:n-1
    clean_data(k+1) = clean_data(k) + a*(measured_data(k+1)-clean_data(k)); 
end

figure
plot(samples,ground_truth,'g',samples,ground_truth,'g.' )
hold on
plot(samples,measured_data,'r', samples,measured_data, 'r.')
hold on
plot(samples,clean_data,'b', samples,clean_data, 'b.')
hold on
plot(samples,normal_track,'c', samples,normal_track, 'c.')
legend('actual state','actual state','measured state','measured state', ...
    'clean data', 'clean data', 'normal track' , 'normal track', 'location', 'best','filtered')
title('state and measurement data 1st order system')

%% Compute error between clean data and other data sets
diff = normal_track - clean_data';
% compute variance
variance_normal_v_clean = var(diff)