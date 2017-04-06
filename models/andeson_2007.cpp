// details:
// from anderson et al 2007 - Vancomycin pharmacokinetics in preterm neonates and 
// the prediction of adult clearance.

[PARAM] @annotated
CL  : 0.345 : Clearance (L/hr)
V   : 1.75  : Volume (L) 
wt  : 2.9   : Weight (kg)
pma : 34.8  : post-menstral age (wk)
scr : 0.9   : serum creatinine (mg/dL)
RDV : 0     : observed dv value (mg/L)
CID : 0     : Base ID
Fventilation : 
Finotrope :

[CMT] @annotated
CENT : Central compartment (mg)

[PKMODEL]
ncmt=1, trans=11

[MAIN]
D_CENT = 1; 
double NORM_WT = 70;
double NORM_PMA = 34.8;
double CLi = 3.83*pow(wt/NORM_WT,0.75)*(pow(pma, 3.68)/(pow(pma, 3.68) + pow(33.3, 3.68)))*(516*pow(e, (0.00823*((PMA-40)/52-40)))/scr)/6)*Fventilation;
double Vi = 39.4*(wt/NORM_WT)*Finotrope;

[OMEGA] @annotated
  ECL : 0.04 : Eta on CL
  EV  : 0.01 : Eta on V
  
  [SIGMA] @annotated
  PROP : 0.04 : Proportional error (%CV)
  ADD  : 1.14  : Additive (SD)
  
  [TABLE]
double CP = CENT/Vi;
double DV = CP*(1+PROP);

[CAPTURE] @annotated
  CP  : predicted plasma concentration (mg/L)
  DV  : plasma concentration (mg/L)
  CLi : Individual Clearance (L/hr)
  Vi  : Individual Volume (L)
  wt  : Weight (kg)
  pma : post-menstral age (wk)
  scr : serum creatinine (mg/dL)
  RDV : observed dv value (mg/L)
  CID : Base ID
  Fventilation :
  Finotrope :3