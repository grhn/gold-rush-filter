clear all;

fs = 88200;
t = linspace(0,2,2*fs);
x = dirac(t);
x(x > 1) = 1;

%number of samples
xsize = size(x);
n = xsize(2);

% filter parameters
cutoff = 1000;
resonance = 1.0;

% frequencies
f = (1:n) / (n / fs);

% impulse responses
for poles = 1:8
    y(poles, :) = x;
    tau = 1.0 / (2 * pi * cutoff) * fs * sqrt(2 ^ (1/poles) - 1);
    voltage = zeros([poles 1]);
    for k = 1:n
        for p = 1:poles
            voltage(p) = voltage(p) + (y(poles, k) - voltage(p)) / (1.0 + tau);
            y(poles, k) = voltage(p);
        end
    end
end

% amplitude plot
subplot(2,1,1);
hold on;
grid on;
plot(f, 20*log10(abs(fft(y'))));
axis([10 22e3 -96 6]);
set(gca,'xscale','log')

title('Amplitude responses of 1st - 8th order RC low-pass filter (relative to unity gain)')
xlabel('Frequency [Hz]')
ylabel('Amplitude [dB]')
l = legend('1st', '2nd', '3rd', '4th', '5th', '6th', '7th', '8th');
set(l, 'Location', 'southwest');
set(gca, 'FontSize', 14);


% phase plots
subplot(2,1,2);
hold on;
grid on;
plot(f, angle(fft(y')) / pi * 180);    
axis([10 22e3 -180 180]);
set(gca,'xscale','log');

xlabel('Frequency [Hz]')
ylabel('Phase [deg]')
title('Phase responses (wrapped between -180 and 180 degrees)')
l = legend('1st', '2nd', '3rd', '4th', '5th', '6th', '7th', '8th');
set(l, 'Location', 'southwest');
set(gca, 'FontSize', 14);

