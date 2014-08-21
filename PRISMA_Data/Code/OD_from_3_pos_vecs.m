function [ elements ] = OD_from_3_pos_vecs( r1,r2,r3,u,eps_cop,eps_spa )
%OD_from_3_pos_vecs computes Keplerian elements from 3 position vectors.
%
%The position vectors must lie in a plane, with 2-3 degrees of out of plane
%error tolerable. The resulting true anomaly (elements.v) is valid at r2.
%
% INPUTS
%   r1: position vector in ECI [km]
%   r2: position vector in ECI [km]
%   r3: position vector in ECI [km]
%   u: gravitational parameter mu for the central body [km^3/s^2]
%   eps_cop: max coplanar error [rad]
%   eps_spa: min spacing between vectors [rad]

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

%compute cross product between input vectors
Z12 = cross(r1,r2);
Z23 = cross(r2,r3);
Z31 = cross(r3,r1);

%check coplanar and spacing constraints
a_cop = asin(dot(Z23,r1)/(norm(Z23)*norm(r1)));
a12 = acos(dot(r1,r2)/(norm(r1)*norm(r2)));
a23 = acos(dot(r2,r3)/(norm(r2)*norm(r3)));

if a_cop > eps_cop
    error('coplanar error too large');
elseif (a12 < eps_spa) || (a23 < eps_spa)
    error('vectors too close');
end

%compute intermediate vectors
N = norm(r1)*Z23 + norm(r2)*Z31 + norm(r3)*Z12;
D = Z23+Z31+Z12;
S = (norm(r2)-norm(r3))*r1 + (norm(r3)-norm(r1))*r2 + ...
    (norm(r1)-norm(r2))*r3;

%solve for velocity at r2
B = cross(D,r2);
Lg = sqrt(u/(norm(N)*norm(D)));
v2 = (Lg/norm(r2))*B + Lg*S;

elements = pos_and_vel_to_elements(r2,v2,u);
end

function [ elements ] = pos_and_vel_to_elements( r,v,mu )
%pos_and_vel_to_elements converts a position and velocity vector into a set
%of Keplerian elements
%
% INPUTS
%   r: position vector in ECI [km]
%   v: velocity vector in ECI [km/s]
%   mu: gravitational parameter mu for the central body [km^3/s^2]
%
% OUTPUTS
%   elements: a struct of Keplerian orbital elements with fields
%       a: semi-major axis [km]
%       e: eccentricity
%       w: argument of perigee [rad], from 0-2pi
%       i: inclination [rad], from 0-pi
%       RAAN: right ascension of the ascending node [rad], from 0-2pi
%       v: true anomaly at epoch t0 [rad], 0-2pi
%
% Writen by:
%   Adam M. Resnick, Stanford University, April 2014
% Reference:
%   AA279A 2014, Lecture 5

%compute angular momentum and then normalize it
H=cross(r,v);
h = H./norm(H);

%calculate i and RAAN and check range of output
elements.i = atan2(sqrt(h(1)^2 + h(2)^2),h(3));
elements.i = atan2checker(elements.i); %should be [0,pi] not [0,2pi]
if elements.i > pi
    error('inclination exceeded range');
end

elements.RAAN = atan2(h(1),-h(2));
elements.RAAN = atan2checker(elements.RAAN);

%calculate semi parameter
p = (dot(H,H))/mu;

%compute a and n from vis-viva
elements.a = 1/((2/norm(r))-(norm(v)^2/mu));
n = sqrt(mu/elements.a^3);

%compute eccentricity from a and p
elements.e = sqrt(1-(p/elements.a));

%find eccentric anomaly and check output range
E = atan2((dot(r,v))/(elements.a^2*n),1-(norm(r)/elements.a));
E = atan2checker(E);


%compute mean and true anomalies from Kepler's equation
M = E - elements.e*sin(E);
elements.v = Ea2ta(elements.e,E);

%compute u, argument of latitude
u = atan2(r(3)/sin(elements.i),r(1)*cos(elements.RAAN)+r(2)*...
    sin(elements.RAAN));
u = atan2checker(u);

%compute w, argument of perigee
elements.w = u-elements.v;
if elements.w < 0
    elements.w = elements.w + (2*pi);
    display('w range changed')
end
end

function [ v ] = Ea2ta( e,E )
%Ea2ta converts the eccentric anomaly to the true anomaly
% INPUTS
%   e: eccentricity
%   E: eccentric anomaly [rad], from 0-2pi
% OUTPUTS
%   v: true anomaly [rad], from 0-2pi
% Written by:
%   Adam M. Resnick, Stanford University, April 2014

c = atan2(sqrt((1+e))*tan(E/2),sqrt(1-e));
c = atan2checker(c);
v = 2*c;
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