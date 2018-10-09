%% A2d_D2A_Stream_setup
% Last rev:  29 September - additional comments
%  14 September 2018 
% sets up constants for use with Simulink A2D_D2A_Stream
%% Set up sampling time
Fs = 500;   
% change Fs to see changes in waveforms
% sampling frequency  the faster sampling you see less
% quantization setps
Fs = 1000;  % Alternate faster sampling
Ts = 1/Fs % sampling period
%% two source frequencies for sine waves are hard programmed into simulink
% 25 hz and 50 Hz
%% Notch filter design fir filter - need to run if Ts changes
Fn = 25 % frequency to notch out
% notch in normalized rad - omega_hat see notes for details
fnn = Fn*pi/(Fs/2)
%   FIR coefficients - used in z-transform block in simulink
b1 = -2*cos(fnn)
b0 = 1;
b2 = 1;

