function [ MJD ] = calendar_to_mjd( yr,mo,d,h,min,s,leap_second )
%calendar_to_mjd computes the Modified Julian Date from the typical
%calendar day format
%
%Julian Date usually implies UT1, unless specifically stated otherwise.
%Assumes no leap seconds have been added this day.
%
% Usage: MJD = calendar_to_mjd(yr,mo,d,h,min,s,leap_second)
% INPUTS
%   yr: full calendar year (ex. 1996)
%   mo: number of month (ex. 1 = Jan., 2 = Feb. etc)
%   d: day of the month
%   h: hour, in 24-hour format (ex. 2pm = 14)
%   min: minute
%   s: second (typically in UT1)
%   leap_second: 1 if day d contains a leap second, otherwise can be any
%                value
%
%
% OUTPUTS
%   MJD: Modified Julian Date
%
% Writen by:
%   Adam M. Resnick, Stanford University, August 2014
% Reference:
%   Adapted from Vallado, 4th Ed., 3.5.1

% Treat Jan. and Feb. as months 13 and 14
if (mo == 1) || (mo ==2)
    yr = yr - 1;
    mo = mo + 12;
end

if leap_second
    C = ((((s/61)+min)/60) + h)/24;
else
    C = ((((s/60)+min)/60) + h)/24;
end

B = 2 - floor(yr/100) + floor(floor(yr/100)/4);
JD = floor(365.25*(yr+4716)) + floor(30.6001*(mo+1)) + d + B - 1524.5 + C;
MJD = JD - 2400000.5;
end

