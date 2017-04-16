// details:
// from lo et al 2010 - Population pharmacokinetics of vancomycin in premature Malaysian neonates:
// identification of predictors for dosing determination.

[PARAM] @annotated
CL  : 0.345 : Clearance (L/hr)
V   : 1.75  : Volume (L) 
wt  : 2.9   : Weight (kg)
pma : 34.8  : post-menstral age (wk)
scr : 0.9   : serum creatinine (mg/dL)
SGA : 0    : small-for-gestational-age
spiro : 0   : spironolactone (L/kg)


[CMT] @annotated
CENT : Central compartment (mg)

[PKMODEL]
ncmt=1, trans=11

[MAIN]
D_CENT = 1; 
double NORM_WT = 70;
double NORM_PMA = 30;
double CLi = 1.0 * pow((wt/NORM_WT), 0.75) * pow((pma/NORM_PMA), 3.16) * (0.83*SGA + 1.03*(1-SGA))
double Vi = 0.572 * (1-0.344*spiro) * wt

[OMEGA] @annotated
  ECL : 20.5 : Eta on CL
  EV  : 12.6 : Eta on V
  BOV: 16.7 : BOV of C
  
  [SIGMA] @annotated
  PROP : 22.9 : Proportional error (%CV)
  ADD  : 1.51  : Additive (SD)
  
  [TABLE]
double CP = CENT/Vi;
double DV = CP*(1+PROP)+ADD;

[CAPTURE] @annotated
  CP  : predicted plasma concentration (mg/L)
  DV  : plasma concentration (mg/L)
  CLi : Individual Clearance (L/hr)
  Vi  : Individual Volume (L)
  wt  : Weight (kg)
  pma : post-menstral age (wk)
  scr : serum creatinine (mg/dL)
  SGA : small-for-gestational-age
  spiro : spironolactone (L/kg)
