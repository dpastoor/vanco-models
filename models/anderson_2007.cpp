// details:
// from anderson et al 2007 - Vancomycin pharmacokinetics in preterm neonates and 
// the prediction of adult clearance.
[PARAM] @annotated
CL    : 3.83 : Clearance (L/hr)
V     : 39.4 : Volume (L) 
WT    : 2.9  : Weight (kg)
PMA   : 34.8 : post-menstral age (wk)
SCR   : 0.9  : serum creatinine (mg/dL)
VENT  : 0    : Ventillation status
IONT  : 0    : ionotrope status
Kage  : 0.00789 : scaling constant of age on renal function
Fvent : 1.03 : Scaling factor applied for use of positive pressure artificial ventilation
Fiont : 1.19 : Scaling factor applied for use of inotropes (use of dopamine)
OCC   : 1     : Occasion
  
[CMT] @annotated
CENT : Central compartment (mg)

[PKMODEL]
ncmt=1, trans=11

[MAIN]
D_CENT = 1; 
double NORM_WT = 70;
double NORM_PMA = 34.8;
double Fpma = pow(PMA, 3.68)/(pow(PMA, 3.68) + pow(33.3, 3.68));
// publication serum creatinine in umol/L however standardizing to mg/dL so 
// extra division by 88.42
double CPR = 516*exp(Kage*((PMA-40)/(52-40)))/88.42;
double CLcr = CPR/SCR; // units of L/hr/70kg
double Rf = CLcr/6; // Renal function is the ratio of predicted CLCR to standard CLCR of 6 L/hr/70kg
double CLi = CL*Rf*pow(WT/NORM_WT,0.75)*Fpma*(Fvent*exp(VENT))*exp(ECL + IOVCL);
double Vi = V*(WT/NORM_WT)*(Fiont*exp(IONT))*exp(EV);

[OMEGA] @annotated @block @correlation @name IIV
ECL : 0.044       : Eta on CL
EV  : 0.896 0.039 : Eta on V

[OMEGA] @annotated @name IOV
IOVCL : 0.0149 : Eta on IOV for CL  
  
[SIGMA] @annotated
PROP : 0.053 : Proportional error (%CV)
ADD  : 2.25  : Additive 
  
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
VENT   : Ventillation status
IONT   : ionotrope status
Kage   : scaling constant of age on renal function
CPR    : creatinine production rate age related fraction
CLcr   : creatinine clearance (L/hr/70kg) 
Rf     : scaling constant of age on renal function
Fvent  : Scaling factor applied for use of positive pressure artificial ventilation
Fiont  : Scaling factor applied for use of inotropes (use of dopamine)
OCC    : Occasion