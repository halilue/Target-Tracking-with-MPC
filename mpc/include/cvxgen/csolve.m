% csolve  Solves a custom quadratic program very rapidly.
%
% [vars, status] = csolve(params, settings)
%
% solves the convex optimization problem
%
%   minimize(quad_form(x_1 - xD_1, Q) + quad_form(x_2 - xD_2, Q) + quad_form(x_3 - xD_3, Q) + quad_form(x_4 - xD_4, Q) + quad_form(x_5 - xD_5, Q) + quad_form(x_6 - xD_6, Q) + quad_form(x_7 - xD_7, Q) + quad_form(x_8 - xD_8, Q) + quad_form(x_9 - xD_9, Q) + quad_form(x_10 - xD_10, Q) + quad_form(x_11 - xD_11, Q) + quad_form(x_12 - xD_12, Q) + quad_form(x_13 - xD_13, Q) + quad_form(x_14 - xD_14, Q) + quad_form(x_15 - xD_15, Q) + quad_form(x_16 - xD_16, Q) + quad_form(x_17 - xD_17, Q) + quad_form(x_18 - xD_18, Q) + quad_form(x_19 - xD_19, Q) + quad_form(x_20 - xD_20, Q) + quad_form(x_21 - xD_21, P))
%   subject to
%     x_1 == A*x_0 + B*u_0
%     x_2 == A*x_1 + B*u_1
%     x_3 == A*x_2 + B*u_2
%     x_4 == A*x_3 + B*u_3
%     x_5 == A*x_4 + B*u_4
%     x_6 == A*x_5 + B*u_5
%     x_7 == A*x_6 + B*u_6
%     x_8 == A*x_7 + B*u_7
%     x_9 == A*x_8 + B*u_8
%     x_10 == A*x_9 + B*u_9
%     x_11 == A*x_10 + B*u_10
%     x_12 == A*x_11 + B*u_11
%     x_13 == A*x_12 + B*u_12
%     x_14 == A*x_13 + B*u_13
%     x_15 == A*x_14 + B*u_14
%     x_16 == A*x_15 + B*u_15
%     x_17 == A*x_16 + B*u_16
%     x_18 == A*x_17 + B*u_17
%     x_19 == A*x_18 + B*u_18
%     x_20 == A*x_19 + B*u_19
%     x_21 == A*x_20 + B*u_20
%
% with variables
%      u_0   3 x 1
%      u_1   3 x 1
%      u_2   3 x 1
%      u_3   3 x 1
%      u_4   3 x 1
%      u_5   3 x 1
%      u_6   3 x 1
%      u_7   3 x 1
%      u_8   3 x 1
%      u_9   3 x 1
%     u_10   3 x 1
%     u_11   3 x 1
%     u_12   3 x 1
%     u_13   3 x 1
%     u_14   3 x 1
%     u_15   3 x 1
%     u_16   3 x 1
%     u_17   3 x 1
%     u_18   3 x 1
%     u_19   3 x 1
%     u_20   3 x 1
%      x_1   6 x 1
%      x_2   6 x 1
%      x_3   6 x 1
%      x_4   6 x 1
%      x_5   6 x 1
%      x_6   6 x 1
%      x_7   6 x 1
%      x_8   6 x 1
%      x_9   6 x 1
%     x_10   6 x 1
%     x_11   6 x 1
%     x_12   6 x 1
%     x_13   6 x 1
%     x_14   6 x 1
%     x_15   6 x 1
%     x_16   6 x 1
%     x_17   6 x 1
%     x_18   6 x 1
%     x_19   6 x 1
%     x_20   6 x 1
%     x_21   6 x 1
%
% and parameters
%        A   6 x 6
%        B   6 x 3
%        P   6 x 6    PSD, diagonal
%        Q   6 x 6    PSD, diagonal
%     xD_1   6 x 1
%     xD_2   6 x 1
%     xD_3   6 x 1
%     xD_4   6 x 1
%     xD_5   6 x 1
%     xD_6   6 x 1
%     xD_7   6 x 1
%     xD_8   6 x 1
%     xD_9   6 x 1
%    xD_10   6 x 1
%    xD_11   6 x 1
%    xD_12   6 x 1
%    xD_13   6 x 1
%    xD_14   6 x 1
%    xD_15   6 x 1
%    xD_16   6 x 1
%    xD_17   6 x 1
%    xD_18   6 x 1
%    xD_19   6 x 1
%    xD_20   6 x 1
%    xD_21   6 x 1
%      x_0   6 x 1
%
% Note:
%   - Check status.converged, which will be 1 if optimization succeeded.
%   - You don't have to specify settings if you don't want to.
%   - To hide output, use settings.verbose = 0.
%   - To change iterations, use settings.max_iters = 20.
%   - You may wish to compare with cvxsolve to check the solver is correct.
%
% Specify params.A, ..., params.x_0, then run
%   [vars, status] = csolve(params, settings)
% Produced by CVXGEN, 2021-06-20 16:41:19 -0400.
% CVXGEN is Copyright (C) 2006-2017 Jacob Mattingley, jem@cvxgen.com.
% The code in this file is Copyright (C) 2006-2017 Jacob Mattingley.
% CVXGEN, or solvers produced by CVXGEN, cannot be used for commercial
% applications without prior written permission from Jacob Mattingley.

% Filename: csolve.m.
% Description: Help file for the Matlab solver interface.
