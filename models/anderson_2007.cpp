// details:
// from anderson et al 2007 - Vancomycin pharmacokinetics in preterm neonates and 
// the prediction of adult clearance.
[PARAM] @annotated
CL        : 3.83    : Clearance (L/h)
V         : 39.4    : Volume (L) 
WT        : 2.9     : Weight (kg)
PMA       : 34.8    : post-menstral age (wk)
EMATCL50  : 33.3    : PMA (wk) at 50% of mature clearance
HILLCL    : 3.68    : Hill parameter for sigmoid Emax maturation
SCR       : 0.9     : serum creatinine (mg/dL)
VENT      : 0       : Ventilation status (0=no ventilation 1=ventilation)
INOT      : 0       : Inotrope status (0=no inotrope 1=inotrope)
Kage      : 0.00789 : scaling constant of age on renal function
Fvent     : 1.03    : Scaling factor applied for use of positive pressure artificial ventilation
Finot     : 1.19    : Scaling factor applied for use of inotropes (use of dopamine)
OCC       : 1       : Occasion
  
[CMT] @annotated
CENT : Central compartment (mg)

[PKMODEL]
ncmt=1, trans=11

[MAIN]

D_CENT = 1; 
double STD_WT = 70; //  Standard weight kg (not "normal" weight)
double STD_CLCR = 6;  // Standard creatinine clearance L/h/70kg
double STD_CPR = 516; // Creatinine production rate (umol/h/70kg)
double STD_AGE = 40;  // Standard age (y)
double TERM_PMA = 40; // PMA at full term (wk)
double NORM_WT = 70;
double Fpma = 1/(1+pow(PMA/EMATCL50,-HILLCL)); // more efficient calculation of sigmoid emax
// publication creatinine production rate in umol/h however standardizing to dg/h (mg/dL=dg/L) so 
// extra division by 88.42
double CPR = STD_CPR/88.42*exp(Kage*((PMA-TERM_PMA)/52-STD_AGE)); // PMA converted to post-natal age (y)
double CLcr = CPR/SCR; // units of L/h/70kg
double Rf = CLcr/STD_CLCR; // Renal function is the ratio of predicted CLCR to standard CLCR of 6 L/hr/70kg
  
double CLi = CL*Rf*pow(WT/STD_WT,0.75)*Fpma*pow(Fvent,VENT)*exp(ECL + IOVCL);
double Vi = V*(WT/STD_WT)*pow(Fiont, INOT)*exp(EV);

[OMEGA] @annotated @block @correlation @name IIV
ECL : 0.044       : Eta on CL
EV  : 0.896 0.039 : Eta on V

[OMEGA] @annotated @name IOV
IOVCL : 0.0149 : Eta on IOV for CL  
  
[SIGMA] @annotated
PROP : 0.053 : Proportional error (variance)
ADD  : 2.25  : Additive ((mg/L)^2)
  
[TABLE]
double CP = CENT/Vi;
double DV = CP*(1+PROP) + ADD;

[CAPTURE] @annotated
CP     : predicted plasma concentration (mg/L)
DV     : plasma concentration (mg/L)
CLi    : Individual Clearance (L/hr)
Vi     : Individual Volume (L)
WT     : Weight (kg)
PMA    : post-menstrual age (wk)
SCR    : serum creatinine (mg/dL)
VENT   : ventilation status
IONT   : ionotrope status
Kage   : scaling constant of PMA on predicted creatinine production rate
CPR    : creatinine production rate age related fraction
CLcr   : creatinine clearance (L/h/70kg) 
Rf     : scaling constant of age on renal function
Fvent  : Scaling factor applied for use of positive pressure artificial ventilation
Finot  : Scaling factor applied for use of inotropes (use of dopamine)
OCC    : Occasion