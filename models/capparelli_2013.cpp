$PARAM TVCL= 0.248, TVVc= 0.636, SCR=0.7, AGE=2190, BW=22

$SET end=120, delta=0.1 

$CMT CENT 

$MAIN
D_CENT = 1;

double CL = TVCL*pow(BW,0.75)*pow(0.48/SCR,0.361)*pow(log(AGE)/7.8,0.995);
double Vc = TVVc*BW;


$ODE
  
dxdt_CENT = - (CL/Vc)*CENT; 



$OMEGA @name IIV
0

$SIGMA
0

$TABLE
double CP = CENT/Vc;

$CAPTURE
CP CL Vc BW AGE SCR