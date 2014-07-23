clear all
close all
clc

fileName = 'GPS_M_20110317.WinMon';
GPS_time = [603,345600];
dt = 1;

sim('WinmonReader');