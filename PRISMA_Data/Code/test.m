clear all
close all
clc

filename_main = 'GPS_M_20110317.WinMon';
filename_target = 'GPS_T_20110317.WinMon';
initial_epoch = [1627,349200]; %3/17/2011 at 09:00:00UTC
dt = 10;
VERBOSE = 0;
t_f = 6120; %17 hours later

sim('gif_model');
%% Number of commonly tracked SVs
figure(1);
plot(tout,DLR_TM_GIF(:,5));
%,tout,DLR_TM_GIF(:,3),tout,DLR_TM_GIF(:,4));
grid on;
xlabel('Time since 09:00:00UTC [s]');
ylabel('Number of Tracked SVs');
title('Number of Commonly Tracked SVs on 20110317, Starting at 09:00:00UTC');
%legend('Common','Main','Target','location','southeast');

%% CNR as function of time
%Use Ch. 1 on Main. Break into separate chunks corresponding to each PRN to
%plot in different color
figure(2);
hold on
for i = 1:1
    CNR = DLR_GPS_MAIN_OBS(:,(i-1)*4+25);
end
PRNs = DLR_GPS_MAIN_OBS(:,4);

plot(tout(1:21),CNR(1:21),'rx',tout(37:179),CNR(37:179),'kx',...
    tout(195:390),CNR(195:390),'bx',tout(417:613),CNR(417:613),'gx')
legend('PRN25','PRN6','PRN17','PRN29','location','southeast');
grid on;
hold off
% CNR_plot = [];
% k = 0;
% temp = 1;
% for j = 2:length(CNR)
%     if PRNs(j)~=PRNs(j-1) 
%         k = k+1;
%         CNR_plot{k} = CNR(temp:j-1);
%         time{k} = tout(temp:j-1);
%         temp = j;
%     end
% end
% CNR_plot{k+1} = CNR(temp:end);
% 
% color = ['b','k','m','c','g','r','y'];
% for i=1:length(CNR_plot)
%     plot(time{i},CNR_plot{i},color(i))
% end
xlabel('Time since 09:00:00UTC on 20110317 [s]');
ylabel('dBHz');
title('CNR as a Function of Time for Mango, Ch. 1 on 20110317');
%legend('PRN

%% Plot Main and Target orbits in ECI

R_E = 6378.1370; % Earths equitorial radius from wiki [km]
ticki = 4; % tick interval-one tickmark every 'ticki' datapoints

% Setup earth plotting data
load('topo.mat', 'topo'); % MATLAB-provided earth data
topoplot = [topo(:,181:360) topo(:,1:180)]; %-180 to +180 longitude
[xeplot, yeplot, zeplot] = ellipsoid(0.0, 0.0, 0.0, ... % earth sphere
R_E, R_E, R_E, 10);

% Plot view from inertial observer
figure(3);
clf;

% Draw earth sphere for reference
hold on;
plot3(main_state(:,1)/1000,main_state(:,2)/1000,main_state(:,3)/1000,'r', 'LineStyle', ...
    '-', 'LineWidth', 3);
plot3(target_state(:,1)/1000,target_state(:,2)/1000,target_state(:,3)/1000,'k', 'LineStyle', ...
    '-', 'LineWidth', 3);
title('Orbit of Mango and Tango (ECI) Over 17 Hours, Starting 09:00:00UTC on 20110317');
grid on;
legend('Mango','Tango');

surface(xeplot, yeplot, zeplot, 'FaceColor', 'blue', 'EdgeColor', 'black');
axis equal;
view(3);
grid on;
set(gca,'XLim', [-10000 +10000], ...'YLim', [-50000 +50000], ...
'ZLim',[-10000 +10000], ...
'XTick', [-10000:5000:+10000], ...
'YTick', [-10000:5000:+10000], ...
'ZTick', [-10000:5000:+10000]);

xlabel('X [km]');
ylabel('Y [km]');
zlabel('Z [km]');

%% Plot ECI velocities
figure(4);
plot(tout,main_state(:,4),'rx',tout,main_state(:,5),'kx',tout,main_state(:,6),'bx');
hold on;
%plot3(target_state(:,4),target_state(:,5),target_state(:,6),'kx');
title('Orbital Velocities of Mango, ECI');
grid on;
xlabel('Time since 09:00:00UTC on 20110317 [s]');
ylabel('[m/s]');
legend('x','y','z');

figure(5);
plot(tout,target_state(:,4),'rx',tout,target_state(:,5),'kx',tout,target_state(:,6),'bx');
hold on;
title('Orbital Velocities of Tango, ECI');
grid on;
xlabel('Time since 09:00:00UTC on 20110317 [s]');
ylabel('[m/s]');
legend('x','y','z');

%% Eliminate spurious RTN points
i = 1;
while i < length(RTN)
    if norm(RTN(i,:)) > 1e4
        RTN(i,:) = [];
        i = i-1;
    end
    i = i+1;
end
%% Plot RTN motion
figure(6);
plot3(RTN(:,1),RTN(:,2),RTN(:,3),'x');
grid on;
xlabel('R [m]');
ylabel('T [m]');
zlabel('N [m]');
title('Relative Distance Between Mango and Tango in RTN Frame Over 17 Hours on 20110317 Starting at 09:00:00UTC')