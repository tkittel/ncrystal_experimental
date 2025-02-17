////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//  This file is part of NCrystal (see https://mctools.github.io/ncrystal/)   //
//                                                                            //
//  Copyright 2015-2022 NCrystal developers                                   //
//                                                                            //
//  Licensed under the Apache License, Version 2.0 (the "License");           //
//  you may not use this file except in compliance with the License.          //
//  You may obtain a copy of the License at                                   //
//                                                                            //
//      http://www.apache.org/licenses/LICENSE-2.0                            //
//                                                                            //
//  Unless required by applicable law or agreed to in writing, software       //
//  distributed under the License is distributed on an "AS IS" BASIS,         //
//  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.  //
//  See the License for the specific language governing permissions and       //
//  limitations under the License.                                            //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

#include "NCrystal/internal/NCKinUtils.hh"
#include "NCrystal/internal/NCMath.hh"
namespace NC = NCrystal;

NC::PairDD NC::getAlphaLimits( double ekin_div_kT, double beta )
{
  nc_assert(ekin_div_kT >= 0.0);
  nc_assert(!ncisnan(beta));
  double kk = ekin_div_kT + beta;
  if ( !(kk >= 0.0) ) {
    //kinematically forbidden
    return std::make_pair(1.0,-1.0);
  }
  double a = kk + ekin_div_kT;
  double b = std::sqrt( ekin_div_kT * kk );
  b += b;
  return std::make_pair( ncmax(0.0,a - b), a + b );
}

NC::PairDD NC::convertAlphaBetaToDeltaEMu(double alpha, double beta, NeutronEnergy ekin, double kT )
{
#ifndef NDEBUG
  auto alim = getAlphaLimits(ekin.dbl()/kT,beta);
  nc_assert(valueInInterval(alim.first,alim.second,alpha));
#endif
  nc_assert( ekin.dbl() >= 0.0 );
  nc_assert( kT > 0.0 );
  nc_assert( alpha >= 0.0 );
  nc_assert( beta*kT >= -ekin.dbl() );
  const double delta_e = beta * kT;
  const double ekinfinal = ekin.dbl() + delta_e;
  const double denom = 2.0*std::sqrt(ekin.dbl() * ekinfinal);
  if ( !denom )
    NCRYSTAL_THROW(CalcError,"convertAlphaBetaToDeltaEMu invalid for beta=-E/kT (calling code should revert to flat alpha/mu distribution near that limit)");
  double mu =  ( ekin.dbl() + ekinfinal - alpha*kT ) / denom;
  nc_assert(ncabs(mu)<1.001);
  mu = ncclamp(mu,-1.0, 1.0);
  return std::make_pair( delta_e, mu );
}
