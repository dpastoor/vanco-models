// details:
// from lo et al 2010 - Population pharmacokinetics of vancomycin in premature Malaysian neonates:
// identification of predictors for dosing determination.

[PARAM] @annotated
CL    : 1     : Clearance (L/hr)
V     : 36.6 : Volume (L) 
WT    : 2.9   : Weight (kg)
PMA   : 34.8  : post-menstral age (wk)
SCR   : 0.9   : serum creatinine (mg/dL)
SGA   : 0     : small-for-gestational-age
SPIRO : 0     : spironolactone (L/kg)
OCC   : 1     : Occasion


[CMT] @annotated
CENT : Central compartment (mg)

[PKMODEL]
ncmt=1, trans=11

[MAIN]
D_CENT = 1; 
double NORM_WT = 70;
double NORM_PMA = 30;
double CLi = CL * pow((WT/NORM_WT), 0.75) * pow((PMA/NORM_PMA), 3.16) * (0.83*SGA + 1.03*(1-SGA))*exp(ECL+IOVCL);
double Vi = V * (1-0.344*SPIRO) * WT/NORM_WT * exp(EV);

[OMEGA] @annotated @name IIV
ECL : 0.042 : Eta on CL
EV  : 0.0159 : Eta on V

[OMEGA] @annotated @name IOV
IOVCL : 0.0256 : IOV on CL

  
[SIGMA] @annotated
PROP : 0.0524 : Proportional error (%CV)
ADD  : 2.28  : Additive (SD)
  
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
  SGA : small-for-gestational-age
  SPIRO : spironolactone (L/kg)
