daq.getDevices

s = daq.createSession('ni')

s.Rate = 200e3;


s.DurationInSeconds = 5;

ch = s.addAnalogInputChannel('myDAQ1', 'ai0', 'Voltage')

[data, timestamps, triggerTime] = s.startForeground;

plot(timestamps, smooth(data));xlabel('Time/sec'); ylabel('Voltage/V');
title(['Clocked Data Triggered on: ' datestr(triggerTime)])
