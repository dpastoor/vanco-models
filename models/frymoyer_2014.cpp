// details:
// from frymoyer et al 2014 - Assocation between Vancomycin Trough Concentration and 
// Area under the Concentration-Time Curve in Neonates

[PARAM] @annotated
CL  : 0.345 : Clearance (L/hr)
V   : 1.75  : Volume (L) 
WT  : 2.9   : Weight (kg)
PMA : 34.8  : post-menstral age (wk)
SCR : 0.9   : serum creatinine (mg/dL)

[CMT] @annotated
CENT : Central compartment (mg)

[PKMODEL]
ncmt=1, trans=11

[MAIN]
D_CENT = 1; 
double NORM_WT = 2.9;
double NORM_PMA = 34.8;
double CLi = CL*pow(WT/NORM_WT,0.75)*(1/(1 + pow((PMA/NORM_PMA),-4.53)))*pow(1/SCR, 0.267)*exp(ECL);
double Vi = V*(WT/NORM_WT)*exp(EV);
  
[OMEGA] @annotated
ECL : 0.04 : Eta on CL
EV  : 0.01 : Eta on V

[SIGMA] @annotated
PROP : 0.04 : Proportional error (variance)
ADD  : 1.14  : Additive (SD)

[TABLE]
double CP = CENT/Vi;
double DV = CP*(1+PROP) + ADD;

[CAPTURE] @annotated
CP  : predicted plasma concentration (mg/L)
DV  : plasma concentration (mg/L)
CLi : Individual Clearance (L/hr)
Vi  : Individual Volume (L)
WT  : Weight (kg)
PMA : post-menstral age (wk)
SCR : serum creatinine (mg/dL)
