function [ elements ] = OD_from_2_pos_vecs( r1,r2,dt,mu )
%OD_from_2_pos_vecs computes Keplerian elements from 2 position vectors and
%a time of flight between them. 
%
%It is assumed that r1 and r2 are less than 180 degrees
%apart. The resulting true anomaly (elements.v) is valid at r1.
%
% INPUTS
%   r1: position vector in ECI [km]
%   r2: position vector in ECI [km]
%   dt: time of flight between r1 and r2 [s]
%   mu: gravitational parameter mu for the central body [km^3/s^2]
%
%
% OUTPUTS
%   elements: a struct of Keplerian orbital elements with fields
%       a: semi-major axis [km]
%       e: eccentricity
%       w: argument of perigee [rad], from 0-2pi
%       i: inclination [rad], from 0-pi
%       RAAN: right ascention of the ascending node [rad], from 0-2pi
%       v: true anomaly at epoch t0 [rad], 0-2pi
%
% Writen by:
%   Adam M. Resnick, Stanford University, August 2014
% Reference:
%   AA279A 2014, Lecture 13
%   Adapted from Montenbruck, 2.4.1

%compute aux variables
m = (mu*dt^2)/((2*(norm(r1)*norm(r2)+dot(r1,r2)))^(3/2));
l = ((norm(r1)+norm(r2))/(2*sqrt(2*(norm(r1)*norm(r2)+dot(r1,r2)))))-.5;

%set start values
eta = zeros(1,3);
a = eta;
f = eta;
cnt = 3;
eta(1) = (12/22) + (10/22)*sqrt(1+(44/9)*(m/(l+(5/6))));
eta(2) = eta(1) + 0.1;
eta(3) = eta(1);
a(2) = (m/(eta(2)^2))-l;
f(2) = 1 - eta(2) + (m/(eta(2)^2))*((a(2)-sin(a(2)))/(sin(a(2)*.5)^3));


%find root of second Gauss equation
while abs(eta(cnt)-eta(cnt-1)) > (1e4)*eps %start at cnt=3
    a(cnt) = (m/(eta(cnt)^2))-l;
    f(cnt) = 1 - eta(cnt) + ...
        (m/(eta(cnt)^2))*((a(cnt)-sin(a(cnt)))/(sin(a(cnt)*.5)^3));
    eta(cnt+1) = eta(cnt)-f(cnt)*((eta(cnt)-eta(cnt-1))/(f(cnt)-f(cnt-1)));
    cnt = cnt+1;
end

%begin computing elements
A = .5*norm(r1)*norm(r2)*sin(acos(dot(r1,r2)/(norm(r1)*norm(r2))));
p = ((2*A*eta(end))/(sqrt(mu)*dt))^2;

%normalized aux variables
e1 = r1/norm(r1);
r0 = r2 - (dot(r2,e1))*e1;
e0 = r0/norm(r0);
h = cross(r1,r2)/norm(cross(r1,r2));

%more aux variables
b = ((p/norm(r1)-1)*(dot(r2,e1)/norm(r2))-(p/norm(r2)-1));
c = norm(r0)/norm(r2);

%compute eccentricity and semi-major axis
elements.e = sqrt((p/norm(r1)-1)^2 + (b/c)^2);
elements.a = p/(1-elements.e^2);

%calculate inclination, RAAN and true anomaly and modify their range
elements.i = atan2(sqrt(h(1)^2 + h(2)^2),h(3));
elements.i = atan2checker(elements.i); %should be [0,pi] not [0,2pi]
if elements.i > pi
    error('inclination exceeded range');
end

elements.RAAN = atan2(h(1),-h(2)); %wrong range
elements.RAAN = atan2checker(elements.RAAN); %corrected range

elements.v = atan2(b/c, p/norm(r1) - 1); %wrong range
elements.v = atan2checker(elements.v); %corrected range

%TODO: finish computing elements 

end

function [ a ] = atan2checker(a)
%atan2checker ensures angular output of atan2 is in [0,2pi] instead of
%[-pi,pi]
%
% INPUTS
%   a: angle computed with atan2 [rad]
%
% OUTPUTS
%   a: angle computed with atan2 now in [0,2pi] [rad]
%
% Writen by:
%   Adam M. Resnick, Stanford University, August 2014

if a < 0
    a = a + (2*pi);
    display('atan2checker called');
end

end
