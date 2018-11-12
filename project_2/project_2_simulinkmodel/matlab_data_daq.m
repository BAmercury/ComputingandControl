daq.getDevices

s = daq.createSession('ni')

s.Rate = 200e3;


s.DurationInSeconds = 10;

ch = s.addAnalogInputChannel('myDAQ1', 'ai1', 'Voltage')

[data, timestamps, triggerTime] = s.startForeground;

plot(timestamps, data);xlabel('Time/sec'); ylabel('Voltage/V');
title(['Clocked Data Triggered on: ' datestr(triggerTime)])
