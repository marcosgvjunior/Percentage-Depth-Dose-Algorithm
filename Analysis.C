//Institute of Physics - Federal University of Rio de Janeiro
//Interdisciplinary Academic Master's Degree in Applied Physics
//Student: Marcos Vieira
//February, 2019

#define Analysis_cxx
#include "Analysis.h"
#include  <TH2.h>
#include  <TStyle.h>
#include  <TCanvas.h>
#include  <string>
#include  <sstream>

#define CONV_FACTOR_POS 10000000
#define CONV_FACTOR_EN 1000000

Double_t spherecenter( Double_t ym, Double_t radiusm );

void Analysis::Loop()
{
  if ( fChain  ==  0 ) return;

  Int_t index1, index2, index3;
  index1 = index2 = index3 = 0;

  Double_t depth1, depth2, depth3;
  depth1 = depth2 = depth3 = 0.0;

  Double_t radius1 = 0.5;
  Double_t radius2 = 0.25;
  Double_t radius3 = 0.1;

  Double_t maximumdepth = 50;

  Double_t dosedepth1[51] = {0};
  Double_t dosedepth2[101] = {0};
  Double_t dosedepth3[251] = {0};

  Double_t vol1, vol2, vol3;
  Double_t PI   = 3.141592653589793238463;

  vol1 = ( 4/3 )*PI*radius1*radius1*radius1;
  vol2 = ( 4/3 )*PI*radius2*radius2*radius2;
  vol3 = ( 4/3 )*PI*radius3*radius3*radius3;

  Double_t mass1, mass2, mass3;
  Double_t rhowater = 0.001; // kg/cm3

  mass1 = vol1*rhowater;
  mass2 = vol2*rhowater;
  mass3 = vol3*rhowater;

  Int_t evttot = 0;
  Double_t coordx = 0;
  Double_t coordy = 0;
  Double_t coordz = 0;

  Long64_t  lastEventNumber  =  -1;
  Long64_t nentries  =  fChain ->  GetEntriesFast();
  Long64_t nbytes  =  0, nb  =  0;

  for ( Long64_t jentry = 0; jentry < nentries;jentry++  )
  {
    Long64_t ientry  =  LoadTree( jentry );
    if ( ientry  <  0 ) break;
    nb  =  fChain ->  GetEntry( jentry );   nbytes  +=  nb;
    //if ( jentry > 3000 ) break;
    //if ( evt == 4999999 ) break;
    Long64_t lastB_OfThisEvent  =  jentry;

    if ( evt  >  lastEventNumber )
    {
      evttot += 1;
      lastEventNumber  =  evt;

      for( Int_t i = 0; i < 10000; i++  )
      {
        fChain ->  GetEntry( jentry + i );

        if ( ( coordx - x == 0 ) && ( coordy - y == 0 ) && ( coordz - z == 0 ) ){break;}

        if ( evt  ==  lastEventNumber )
        {
          coordx = x;
          coordy = y;
          coordz = z;

          if( ( abs( x/CONV_FACTOR_POS ) < ( radius1 ) ) && ( abs( z/CONV_FACTOR_POS ) < ( radius1 ) ) && ( de > 0 ) )
          {
            depth1 = spherecenter( y/CONV_FACTOR_POS, radius1 );

            if ( (  pow( x/CONV_FACTOR_POS, 2 )  +  pow( ( ( y/CONV_FACTOR_POS )-depth1 ), 2 )  +  pow( z/CONV_FACTOR_POS, 2 ) )   <=  pow( radius1, 2 )  )
            {
              index1  =  ( depth1 + radius1 )/( 2*radius1 );
              dosedepth1[index1]  =  dosedepth1[index1]  +  ( ( de/CONV_FACTOR_EN )*( 1.60218e-13 )/mass1 );

              depth2 = spherecenter( y/CONV_FACTOR_POS, radius2 );

              if ( (  pow( x/CONV_FACTOR_POS, 2 )  +  pow( ( ( y/CONV_FACTOR_POS )-depth2 ), 2 )  +  pow( z/CONV_FACTOR_POS, 2 ) )   <=  pow( radius2, 2 )  )
              {
                index2  =  ( depth2 + radius2 )/( 2*radius2 );
                dosedepth2[index2]  =  dosedepth2[index2]  +  ( ( de/CONV_FACTOR_EN )*( 1.60218e-13 )/mass2 );

                depth3 = spherecenter( y/CONV_FACTOR_POS, radius3 );

                if ( (  pow( x/CONV_FACTOR_POS, 2 )  +  pow( ( ( y/CONV_FACTOR_POS )-depth3 ), 2 )  +  pow( z/CONV_FACTOR_POS, 2 ) )   <=  pow( radius3, 2 )  )
                {
                  index3  =  ( depth3 + radius3 )/( 2*radius3 );
                  dosedepth3[index3]  =  dosedepth3[index3]  +  ( ( de/CONV_FACTOR_EN )*( 1.60218e-13 )/mass3 );
                }
                else {continue;}
              }
              else {continue;}
            }
            else {continue;}
          }
          else {continue;}
        }
        else
        {
          if( evt < lastEventNumber ) { lastEventNumber = evt - 1; }
          lastB_OfThisEvent  =  jentry + i - 1;
          fChain ->  GetEntry( jentry + i - 1 );
          break;
        }
      }

      jentry  =  lastB_OfThisEvent;

      if( evt%500000 == 0 ){cout  <<  " evt " <<  evt  <<  " evttot "  <<  evttot  <<  endl;}
    }
    else {continue;}
  }

  cout  <<  " evt " <<  evt  <<  " evttot "  <<  evttot  <<  endl;

  std::ofstream dsp0;
  Int_t ind0 = 0;
  dsp0.open ( "values_pdd_r_05.dat", std::ofstream::out );

  for( Double_t p = radius1; p  <= maximumdepth; p = p + ( 2*radius1 ) )
  {
    ind0  =  ( p + radius1 )/( 2*radius1 );
    dsp0  <<  p  <<  "  "  <<  dosedepth1[ind0]  <<  "\n";
  }
  dsp0.close();

  std::ofstream dsp1;
  Int_t ind1 = 0;
  dsp1.open ( "values_pdd_r_025.dat", std::ofstream::out );

  for( Double_t pq = radius2; pq  <= maximumdepth; pq = pq + ( 2*radius2 ) )
  {
    ind1  =  ( pq + radius2 )/( 2*radius2 );
    dsp1  <<  pq  <<  " "  <<  dosedepth2[ind1]  <<  "\n";
  }
  dsp1.close();

  std::ofstream dsp2;
  Int_t ind2 = 0;
  dsp2.open ( "values_pdd_r_01.dat", std::ofstream::out );

  for( Double_t pw = radius3; pw  <= maximumdepth; pw = pw + ( 2*radius3 ) )
  {
    ind2  =  ( pw + radius3 )/( 2*radius3 );
    dsp2  <<  pw  <<  " "  <<  dosedepth3[ind2]  <<  "\n";
  }
  dsp2.close();
}

Double_t spherecenter( Double_t ym, Double_t radiusm )
{
  Double_t ratio  = 0.0;
  Double_t center = 0.0;

  ratio   = ym/( 2*radiusm );
  center  =  ceil( ratio )*radiusm  +  floor( ratio )*radiusm;

  return center;
}
