// details:
// from allegaert et al 2007 - renal drug clearance in preterm neonates: relation to prenatal growth
// 
[PARAM] @annotated
CL    : 1.58     : Clearance (L/hr)
V     : 39.3     : Volume (L) 
WT    : 70       : Weight (kg)
PMA   : 34.8     : post-menstral age (wk)
SCR   : 0.9      : serum creatinine (mg/dL)
KAGE  : 0.00789  : scaling constant of age on renal function
SLPCL : 0.456    : slope of clearance changes with PMA
FSGA  : 0.834    : fractional difference small for gestational age
SGA   : 0        : small for gestational age
FNCOX : 0.795    : fractional difference ncox
NCOX  : 0        : NCOX use
OCC   : 1        : Occasion
  
[CMT] @annotated
CENT : Central compartment (mg)

[PKMODEL]
ncmt=1, trans=11

[MAIN]
D_CENT = 1; 
double NORM_WT = 70;
double FPMA = exp(SLPCL*(PMA - 30));
// publication serum creatinine in umol/L however standardizing to mg/dL so 
// extra division by 88.42
double CPR = 516*exp(KAGE*((PMA-30)/(52-40)))/88.42;
double CLCR = CPR/SCR; // units of L/hr/70kg
double RF = CLCR/6; // Renal function is the ratio of predicted CLCR to standard CLCR of 6 L/hr/70kg
double CLi = CL*RF*pow(WT/NORM_WT,0.75)*FPMA*FNCOX*exp(NCOX)*FSGA*exp(SGA)*exp(ECL + IOVCL);
double Vi = V*(WT/NORM_WT)*exp(EV);

[OMEGA] @annotated @block @correlation @name IIV
ECL   : 0.0338       : Eta on CL
EV    : 0.98   0.042 : Eta on V

[OMEGA] @annotated @name IOV
IOVCL : 0.00225      : Eta on IOV for CL  
  
[SIGMA] @annotated
PROP  : 0.078       : Proportional error (%CV)
ADD   : 1.74        : Additive 
  
[TABLE]
double CP = CENT/Vi;
double DV = CP*(1+PROP) + ADD;

[CAPTURE] @annotated
CP     : predicted plasma concentration (mg/L)
DV     : plasma concentration (mg/L)
CLi    : Individual Clearance (L/hr)
Vi     : Individual Volume (L)
WT     : Weight (kg)
PMA    : post-menstral age (wk)
SCR    : serum creatinine (mg/dL)
CPR    : creatinine production rate age related fraction
CLCR   : creatinine clearance (L/hr/70kg) 
RF     : scaling constant of age on renal function
OCC    : Occasion
KAGE   : scaling constant of age on renal function
SLPCL  : slope of clearance changes with PMA
FSGA   : fractional difference small for gestational age
SGA    : small for gestational age
FNCOX  : fractional difference ncox
NCOX   : NCOX use
OCC    : Occasion