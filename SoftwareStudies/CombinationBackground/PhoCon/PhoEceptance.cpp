
#include "TRandom3.h"
#include "TMath.h"

#include <iostream>

double kuno( double Pmu,
                                                    double x,
                                                    double y,
                                                    double cthetaE,
                                                    double cthetaG,
                                                    double cthetaGE)    // differential BR as in Kuno's paper
{
    double EMMU = 105.6583715;		// muon mass in MeV
    double EMASS = 0.51099906;		// electron mass in MeV
    double eps = EMASS/EMMU;
    double r = eps*eps;
    double beta = sqrt(1.0-4.0*r/(x*x));
    double d = 1.0-beta*cthetaGE;

    // double pi = 3.14159265358979323846;
    // double twopi = 2*pi;
    // double elm_coupling = 1.43996e-12;
    // double hbarc = 4.13566e-12/twopi * 299.792458;
    // double fine_structure_const = elm_coupling/hbarc;

    double F0 = 8.0/d*(y*y*(3.0-2.0*y)+6.0*x*y*(1.0-y)+2.0*x*x*(3.0-4.0*y)-4.0*x*x*x) + 8.0*(-x*y*(3.0-y-y*y)-x*x*(3.0-y-4.0*y*y)+2.0*x*x*x*(1.0+2.0*y)) + 2.0*d*(x*x*y*(6.0-5.0*y-2.0*y*y)-2.0*x*x*x*y*(4.0+3.0*y)) + 2.0*d*d*x*x*x*y*y*(2.0+y);
    double F1 = 32.0/(d*d)*(-y*(3.0-2.0*y)/x-(3.0-4.0*y)+2.0*x) + 8.0/d*(y*(6.0-5.0*y)-2.0*x*(4.0+y)+6.0*x*x) + 8.0*(x*(4.0-3.0*y+y*y)-3.0*x*x*(1.0+y)) + 6.0*d*x*x*y*(2.0+y);
    double F2 = 32.0/(d*d)*((4.0-3.0*y)/x-3.0) + 48.0*y/d;
    double F = F0 + r*F1 + r*r*F2;

    double G0 = 8.0/d*(x*y*(1.0-2.0*y)+2.0*x*x*(1.0-3.0*y)-4.0*x*x*x) + 4.0*(-x*x*(2.0-3.0*y-4.0*y*y)+2.0*x*x*x*(2.0+3.0*y)) - 4.0*d*x*x*x*y*(2.0+y);
    double G1 = 32.0/(d*d)*(-1.0+2.0*y+2.0*x) + 8.0/d*(-x*y+6.0*x*x) - 12.0*x*x*(2.0+y);
    double G2 = -96.0/(d*d);
    double G = G0 + r*G1 + r*r*G2;

    double H0 = 8.0/d*(y*y*(1.0-2.0*y)+x*y*(1.0-4.0*y)-2.0*x*x*y) + 4.0*(2.0*x*y*y*(1.0+y)-x*x*y*(1.0-4.0*y)+2.0*x*x*x*y) + 2.0*d*(x*x*y*y*(1.0-2.0*y)-4.0*x*x*x*y*y) + 2.0*d*d*x*x*x*y*y*y;
    double H1 = 32.0/(d*d)*(-y*(1.0-2.0*y)/x+2.0*y) + 8.0/d*(y*(2.0-5.0*y)-x*y) + 4.0*x*y*(2.0*y-3.0*x) + 6.0*d*x*x*y*y;
    double H2 = -96.0*y/(d*d*x) + 48.0*y/d;
    double H = H0 + r*H1 + r*r*H2;

    double kunoBR;
    kunoBR = F + beta*Pmu*cthetaE*G + Pmu*cthetaG*H;
    kunoBR = 0.0072973525693/(64.0*M_PI*M_PI*M_PI)*beta/y*kunoBR;


    /////////////////Addiations Andrew
    // double kunoBR1 = F + beta*Pmu*cthetaE*G + Pmu*cthetaG*H;
    //double test = CLHEP::RandFlat::shoot();
    //G4cout << " test " << test<<G4endl;

    // if( test < kunoBR){
    //   G4cout << "  " <<G4endl;
    //   G4cout << " test " << test<<G4endl;
    //   G4cout << " E gamma " << y*EMMU*0.5<<G4endl;
    //   G4cout << " E electron " << x*EMMU*0.5<<G4endl;
    //   G4cout << " Second part " << kunoBR1<<G4endl;
    //   G4cout << " Final part " << kunoBR<<G4endl;
    // }
    // if( test > kunoBR){
    //   G4cout << "  " <<G4endl;
    //   G4cout << " Failed " <<G4endl;
    //   G4cout << " test " << test<<G4endl;
    //   G4cout << " E gamma " << y*EMMU*0.5<<G4endl;
    //   G4cout << " E electron " << x*EMMU*0.5<<G4endl;
    //   G4cout << " Second part " << kunoBR1<<G4endl;
    //   G4cout << " Final part " << kunoBR<<G4endl;
    // }
    return kunoBR;
}


void ScaleBR()
{
      double Pmu = -1.0;	// Muon polarisation, -1 for mu^+
      //if (GetParentName() == "mu-")Pmu = +1.0;

      double x;			// Electron momentum
      double y;			// Gamma momentum
      double cthetaE;
      double cthetaG;
      double cthetaGE;
      double u, umax;

      // double EMMU = 105.6583715;		// muon mass in MeV
      // double EMASS = 0.51099906;		// electron mass in MeV
   double EMMU = 105.6583715;		// muon mass in MeV
    double EMASS = 0.51099906;
      double eps = EMASS/EMMU;

      double Gmin = 20;					// cut on photon energy in MeV
      double ycut_cut = 2.0*Gmin/EMMU;
      double ycut_10 = 2.0*10.0/EMMU;           // cut on photon energy at 10 MeV (for which the BR is known)

      int nint = 1e6;                           // number of interations for MC integration

      double som0 = 0;
      double q_sqr = 0.0;

      double som0sum_10 = 0.0;
      double som0sqrsum_10 = 0.0;
      double som0sum_10_3 = 0.0;
      //double dsom0_10_3 = 0.0;
      //double dsom0MC_10 = 0.0;
      //double dsom0V_10 = 0.0;

      double som0sum_cut = 0.0;
      double som0sqrsum_cut = 0.0;
      double som0sum_cut_3 = 0.0;
      //double dsom0_cut_3 = 0.0;
      //double dsom0MC_cut = 0.0;
      //double dsom0V_cut = 0.0;


      long Nvol_10 = 0;
      long Nvol_cut = 0;
      long Nvol = 0;

      double BRscale = 0.0;
      double y_min = 0.0;

      if(ycut_cut<=ycut_10)
      {
        umax = -1.0*log(ycut_cut);
        y_min = ycut_cut;
      }
      else
      {
        umax = -1.0*log(ycut_10);
        y_min = ycut_10;
      }

  TRandom3 generator;

    // Sum of BR's
    for(int i = 0; i<nint; i++)
	{
// 	  do{
	    do
	    {
	      do{
            x=generator.Rndm();
            u=umax*generator.Rndm();
            y=exp(-u/1.0);
			Nvol++;
          }while(x<2.0*eps || y<y_min || x>1.0+eps*eps || y>1.0-eps*eps);

            auto unitE = mu3e::util::rand_u3d();
            auto unitG = mu3e::util::rand_u3d();

            cthetaE = unitE.z;
            cthetaG = unitG.z;
            cthetaGE = dot(unitE, unitG);

	    q_sqr = 1 + eps*eps - x - y + x*y/2.0*(1.0 - TMath::Sqrt(1.0 - 4.0*eps*eps/(x*x))*cthetaGE);
          q_sqr  = q_sqr/((1.0-eps)*(1.0-eps));
	    }while(q_sqr < 0.0 || q_sqr > 1.0 );
        som0 = kuno(Pmu, x, y, cthetaE, cthetaG, cthetaGE);
// 	  }while(CLHEP::RandFlat::shoot()*1.0/y > som0);

      if(som0 < 0.0)
	  {
        som0 = 0.0;
	  }

	  if(y>=ycut_cut)
	  {
        som0sum_cut = som0sum_cut + som0;
        som0sqrsum_cut = som0sqrsum_cut + som0*som0;
	    Nvol_cut++;
	  }

	  if(y>=ycut_10)
	  {
        som0sum_10 = som0sum_10 + som0;
        som0sqrsum_10 = som0sqrsum_10 + som0*som0;
	    Nvol_10++;
	  }

	}

    // MC integral of the BR's for both cuts
	som0sum_cut_3 = 64.0*som0sum_cut/Nvol;
	som0sum_10_3 = 64.0*som0sum_10/Nvol;

//	dsom0MC_cut = som0sqrsum_cut - som0sum_cut*som0sum_cut/Nvol_cut;
//	dsom0MC_10 = som0sqrsum_10 - som0sum_10*som0sum_10/Nvol_10;
 //   dsom0V_cut = (double)(Nvol - Nvol_cut)/(Nvol*Nvol_cut)*som0sum_cut*som0sum_cut;
 //   dsom0V_10 = (double)(Nvol - Nvol_10)/(Nvol*Nvol_10)*som0sum_10*som0sum_10;
//	dsom0_cut_3 = 64.0/Nvol*sqrt(dsom0MC_cut + dsom0V_cut*dsom0V_cut);
//	dsom0_10_3 = 64.0/Nvol*sqrt(dsom0MC_10 + dsom0V_10*dsom0V_10);

    // Get scaling factor with respect to 10MeV cut
	BRscale = som0sum_cut_3/som0sum_10_3;
    //dBRScale = sqrt(dsom0_cut_3/som0sum_cut_3*dsom0_cut_3/som0sum_cut_3 + dsom0_10_3/som0sum_10_3*dsom0_10_3/som0sum_10_3)*som0sum_cut_3/som0sum_10_3;
	std::cout<<"BR "<<BRscale<<std::endl;
}
