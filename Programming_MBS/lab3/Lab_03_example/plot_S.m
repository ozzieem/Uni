function plot_S(S)
%
% plot the struct S from the lab description
%
% S - struct as given in the lab description
% for simplicity this is hard coded to be of length 2.
%
% Compute the T matrices
T1_local = S2T(S(1));
T2_local = S2T(S(2));

T1_global = T1_local;
T2_global = T1_global*T2_local;

% Plot the frames
hold on
plot_T(T1_global)
plot_T(T2_global)
%%%EOF plot_S
% -------------------------------------------------------------------------
