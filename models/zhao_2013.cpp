[PARAM] @annotated
CL  : 0.0571  : Clearance (L/hr)
V   : 0.791   : Volume (L) 
WT  : 1.1416  : Weight (kg)
BWT : 1.1010  : Birth Weight (kg)
SCR : 0.475   : serum creatinine (mg/dL)
PNA : 17      : postnatal age (days)

[CMT] @annotated
CENT : Central compartment (mg)

[PKMODEL]
ncmt=1, trans=11

[MAIN]
D_CENT = 1; 
double NORM_WT = 1.1416;
double NORM_BWT = 1.101;
double NORM_PNA = 17;
double NORM_SCR = 0.475;
double eWTCL = 0.599;
double eBWTCL = 0.513;
double eWTV = 0.898;
double eSCRCL = 0.525;
double sfPNACL = 0.282;
double Rf = 1/pow(SCR/NORM_SCR, eSCRCL);
double Fmat = pow(BWT/NORM_BWT, eBWTCL)*(1 + sfPNACL*(PNA/NORM_PNA));
double CLi = CL*pow(WT/NORM_WT, eWTCL)*Fmat*Rf*exp(ECL);
double Vi = V*pow(WT/NORM_WT, eWTV)*exp(EV);
  
[OMEGA] @annotated
ECL : 0.032 : Eta on CL
EV  : 0.161 : Eta on V

[SIGMA] @annotated
PROP : 0.041 : Proportional error (variance)
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
PNA : post-menstral age (wk)
SCR : serum creatinine (mg/dL)
