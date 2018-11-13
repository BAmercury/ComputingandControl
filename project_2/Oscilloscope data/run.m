%% Gain k = 1
clc;
clear all;

M1 = csvread('tek0000.csv');
time = M1(1000:end,1);
time_offset = 0 - time(1);
for i = 1:length(time)
    time(i) = time(i) + time_offset;
end
voltage = M1(1000:end,2);
plot(time, voltage)
xlabel("Time")
ylabel("V")
title("Arduino feedback with k = 1")
%% Gain k = 1.333
clc;
clear all;

M1 = csvread('tek0001.csv');
time = M1(2000:end,1);
time_offset = 0 - time(1);
for i = 1:length(time)
    time(i) = time(i) + time_offset;
end
voltage = M1(2000:end,2);
plot(time, voltage)
xlabel("Time")
ylabel("V")
title("Arduino feedback with k = 1.333")
%% Gain k = 2
clc;
clear all;

M1 = csvread('tek0002.csv');
time = M1(2000:end,1);
time_offset = 0 - time(1);
for i = 1:length(time)
    time(i) = time(i) + time_offset;
end
voltage = M1(2000:end,2);
plot(time, voltage)
xlabel("Time")
ylabel("V")
title("Arduino feedback with k = 2")
%% Gain k = 2.666
clc;
clear all;

M1 = csvread('tek0003.csv');
time = M1(2000:end,1);
time_offset = 0 - time(1);
for i = 1:length(time)
    time(i) = time(i) + time_offset;
end
voltage = M1(2000:end,2);
plot(time, voltage)
xlabel("Time")
ylabel("V")
title("Arduino feedback with k = 2.666")
%% Gain k = 5
clc;
clear all;

M1 = csvread('tek0004.csv');
time = M1(2000:end,1);
time_offset = 0 - time(1);
for i = 1:length(time)
    time(i) = time(i) + time_offset;
end
voltage = M1(2000:end,2);
plot(time, voltage)
xlabel("Time")
ylabel("V")
title("Arduino feedback with k = 5")
%% Gain k = 5.333
clc;
clear all;

M1 = csvread('tek0006.csv');
time = M1(2000:end,1);
time_offset = 0 - time(1);
for i = 1:length(time)
    time(i) = time(i) + time_offset;
end
voltage = M1(2000:end,2);
plot(time, voltage)
xlabel("Time")
ylabel("V")
title("Arduino feedback with k = 5.333")
%% Gain k = 10
clc;
clear all;

M1 = csvread('tek0007.csv');
time = M1(2000:end,1);
time_offset = 0 - time(1);
for i = 1:length(time)
    time(i) = time(i) + time_offset;
end
voltage = M1(2000:end,2);
plot(time, voltage)
xlabel("Time")
ylabel("V")
title("Arduino feedback with k = 10")