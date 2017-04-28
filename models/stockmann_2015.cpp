$PARAM CL = 0.345, VC = 1.75, wt=2.9, pma=34.8, scr=0.9 

$CMT CENT

$PKMODEL ncmt=1, trans=11

$MAIN
double NORM_WT = 2.9;
double NORM_PMA = 34.8;
double CLi = CL*pow(wt/NORM_WT,0.75)*(1/(1 + pow((pma/NORM_PMA),-4.53)))*pow(1/scr, 0.267)*exp(ETA(1));
double Vi = VC*(wt/NORM_WT)*exp(ETA(2));

$OMEGA
0.04
0.15

$TABLE
double DV = CENT/pred_V;

$CAPTURE CLi Vi wt pma scr DV