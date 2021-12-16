/* Produced by CVXGEN, 2021-06-20 16:41:20 -0400.  */
/* CVXGEN is Copyright (C) 2006-2017 Jacob Mattingley, jem@cvxgen.com. */
/* The code in this file is Copyright (C) 2006-2017 Jacob Mattingley. */
/* CVXGEN, or solvers produced by CVXGEN, cannot be used for commercial */
/* applications without prior written permission from Jacob Mattingley. */

/* Filename: testsolver.c. */
/* Description: Basic test harness for solver.c. */
#include "solver.h"
Vars vars;
Params params;
Workspace work;
Settings settings;
#define NUMTESTS 0
int main(int argc, char **argv) {
  int num_iters;
#if (NUMTESTS > 0)
  int i;
  double time;
  double time_per;
#endif
  set_defaults();
  setup_indexing();
  load_default_data();
  /* Solve problem instance for the record. */
  settings.verbose = 1;
  num_iters = solve();
#ifndef ZERO_LIBRARY_MODE
#if (NUMTESTS > 0)
  /* Now solve multiple problem instances for timing purposes. */
  settings.verbose = 0;
  tic();
  for (i = 0; i < NUMTESTS; i++) {
    solve();
  }
  time = tocq();
  printf("Timed %d solves over %.3f seconds.\n", NUMTESTS, time);
  time_per = time / NUMTESTS;
  if (time_per > 1) {
    printf("Actual time taken per solve: %.3g s.\n", time_per);
  } else if (time_per > 1e-3) {
    printf("Actual time taken per solve: %.3g ms.\n", 1e3*time_per);
  } else {
    printf("Actual time taken per solve: %.3g us.\n", 1e6*time_per);
  }
#endif
#endif
  return 0;
}
void load_default_data(void) {
  params.xD_1[0] = 0.20319161029830202;
  params.xD_1[1] = 0.8325912904724193;
  params.xD_1[2] = -0.8363810443482227;
  params.xD_1[3] = 0.04331042079065206;
  params.xD_1[4] = 1.5717878173906188;
  params.xD_1[5] = 1.5851723557337523;
  params.Q[0] = 1.1255853104638363;
  params.Q[1] = 1.2072428781381868;
  params.Q[2] = 1.0514672033008299;
  params.Q[3] = 1.4408098436506365;
  params.Q[4] = 1.0298762108785668;
  params.Q[5] = 1.456833224394711;
  params.xD_2[0] = 0.596576190459043;
  params.xD_2[1] = -0.8860508694080989;
  params.xD_2[2] = 0.7050196079205251;
  params.xD_2[3] = 0.3634512696654033;
  params.xD_2[4] = -1.9040724704913385;
  params.xD_2[5] = 0.23541635196352795;
  params.xD_3[0] = -0.9629902123701384;
  params.xD_3[1] = -0.3395952119597214;
  params.xD_3[2] = -0.865899672914725;
  params.xD_3[3] = 0.7725516732519853;
  params.xD_3[4] = -0.23818512931704205;
  params.xD_3[5] = -1.372529046100147;
  params.xD_4[0] = 0.17859607212737894;
  params.xD_4[1] = 1.1212590580454682;
  params.xD_4[2] = -0.774545870495281;
  params.xD_4[3] = -1.1121684642712744;
  params.xD_4[4] = -0.44811496977740495;
  params.xD_4[5] = 1.7455345994417217;
  params.xD_5[0] = 1.9039816898917352;
  params.xD_5[1] = 0.6895347036512547;
  params.xD_5[2] = 1.6113364341535923;
  params.xD_5[3] = 1.383003485172717;
  params.xD_5[4] = -0.48802383468444344;
  params.xD_5[5] = -1.631131964513103;
  params.xD_6[0] = 0.6136436100941447;
  params.xD_6[1] = 0.2313630495538037;
  params.xD_6[2] = -0.5537409477496875;
  params.xD_6[3] = -1.0997819806406723;
  params.xD_6[4] = -0.3739203344950055;
  params.xD_6[5] = -0.12423900520332376;
  params.xD_7[0] = -0.923057686995755;
  params.xD_7[1] = -0.8328289030982696;
  params.xD_7[2] = -0.16925440270808823;
  params.xD_7[3] = 1.442135651787706;
  params.xD_7[4] = 0.34501161787128565;
  params.xD_7[5] = -0.8660485502711608;
  params.xD_8[0] = -0.8880899735055947;
  params.xD_8[1] = -0.1815116979122129;
  params.xD_8[2] = -1.17835862158005;
  params.xD_8[3] = -1.1944851558277074;
  params.xD_8[4] = 0.05614023926976763;
  params.xD_8[5] = -1.6510825248767813;
  params.xD_9[0] = -0.06565787059365391;
  params.xD_9[1] = -0.5512951504486665;
  params.xD_9[2] = 0.8307464872626844;
  params.xD_9[3] = 0.9869848924080182;
  params.xD_9[4] = 0.7643716874230573;
  params.xD_9[5] = 0.7567216550196565;
  params.xD_10[0] = -0.5055995034042868;
  params.xD_10[1] = 0.6725392189410702;
  params.xD_10[2] = -0.6406053441727284;
  params.xD_10[3] = 0.29117547947550015;
  params.xD_10[4] = -0.6967713677405021;
  params.xD_10[5] = -0.21941980294587182;
  params.xD_11[0] = -1.753884276680243;
  params.xD_11[1] = -1.0292983112626475;
  params.xD_11[2] = 1.8864104246942706;
  params.xD_11[3] = -1.077663182579704;
  params.xD_11[4] = 0.7659100437893209;
  params.xD_11[5] = 0.6019074328549583;
  params.xD_12[0] = 0.8957565577499285;
  params.xD_12[1] = -0.09964555746227477;
  params.xD_12[2] = 0.38665509840745127;
  params.xD_12[3] = -1.7321223042686946;
  params.xD_12[4] = -1.7097514487110663;
  params.xD_12[5] = -1.2040958948116867;
  params.xD_13[0] = -1.3925560119658358;
  params.xD_13[1] = -1.5995826216742213;
  params.xD_13[2] = -1.4828245415645833;
  params.xD_13[3] = 0.21311092723061398;
  params.xD_13[4] = -1.248740700304487;
  params.xD_13[5] = 1.808404972124833;
  params.xD_14[0] = 0.7264471152297065;
  params.xD_14[1] = 0.16407869343908477;
  params.xD_14[2] = 0.8287224032315907;
  params.xD_14[3] = -0.9444533161899464;
  params.xD_14[4] = 1.7069027370149112;
  params.xD_14[5] = 1.3567722311998827;
  params.xD_15[0] = 0.9052779937121489;
  params.xD_15[1] = -0.07904017565835986;
  params.xD_15[2] = 1.3684127435065871;
  params.xD_15[3] = 0.979009293697437;
  params.xD_15[4] = 0.6413036255984501;
  params.xD_15[5] = 1.6559010680237511;
  params.xD_16[0] = 0.5346622551502991;
  params.xD_16[1] = -0.5362376605895625;
  params.xD_16[2] = 0.2113782926017822;
  params.xD_16[3] = -1.2144776931994525;
  params.xD_16[4] = -1.2317108144255875;
  params.xD_16[5] = 0.9026784957312834;
  params.xD_17[0] = 1.1397468137245244;
  params.xD_17[1] = 1.8883934547350631;
  params.xD_17[2] = 1.4038856681660068;
  params.xD_17[3] = 0.17437730638329096;
  params.xD_17[4] = -1.6408365219077408;
  params.xD_17[5] = -0.04450702153554875;
  params.xD_18[0] = 1.7117453902485025;
  params.xD_18[1] = 1.1504727980139053;
  params.xD_18[2] = -0.05962309578364744;
  params.xD_18[3] = -0.1788825540764547;
  params.xD_18[4] = -1.1280569263625857;
  params.xD_18[5] = -1.2911464767927057;
  params.xD_19[0] = -1.7055053231225696;
  params.xD_19[1] = 1.56957275034837;
  params.xD_19[2] = 0.5607064675962357;
  params.xD_19[3] = -1.4266707301147146;
  params.xD_19[4] = -0.3434923211351708;
  params.xD_19[5] = -1.8035643024085055;
  params.xD_20[0] = -1.1625066019105454;
  params.xD_20[1] = 0.9228324965161532;
  params.xD_20[2] = 0.6044910817663975;
  params.xD_20[3] = -0.0840868104920891;
  params.xD_20[4] = -0.900877978017443;
  params.xD_20[5] = 0.608892500264739;
  params.xD_21[0] = 1.8257980452695217;
  params.xD_21[1] = -0.25791777529922877;
  params.xD_21[2] = -1.7194699796493191;
  params.xD_21[3] = -1.7690740487081298;
  params.xD_21[4] = -1.6685159248097703;
  params.xD_21[5] = 1.8388287490128845;
  params.P[0] = 1.540760836186494;
  params.P[1] = 1.8374624326697224;
  params.P[2] = 1.1700335442371346;
  params.P[3] = 1.2603450727289152;
  params.P[4] = 1.6919775118728428;
  params.P[5] = 1.8955703281419836;
  params.A[0] = -0.6372460621593619;
  params.A[1] = -1.741307208038867;
  params.A[2] = 1.456478677642575;
  params.A[3] = -0.8365102166820959;
  params.A[4] = 0.9643296255982503;
  params.A[5] = -1.367865381194024;
  params.A[6] = 0.7798537405635035;
  params.A[7] = 1.3656784761245926;
  params.A[8] = 0.9086083149868371;
  params.x_0[0] = -0.5635699005460344;
  params.x_0[1] = 0.9067590059607915;
  params.x_0[2] = -1.4421315032701587;
  params.x_0[3] = -0.7447235390671119;
  params.x_0[4] = -0.32166897326822186;
  params.x_0[5] = 1.5088481557772684;
  params.B[0] = -1.385039165715428;
  params.B[1] = 1.5204991609972622;
  params.B[2] = 1.1958572768832156;
  params.B[3] = 1.8864971883119228;
  params.B[4] = -0.5291880667861584;
  params.B[5] = -1.1802409243688836;
}
