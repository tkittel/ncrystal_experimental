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

#include "NCrystal/NCTypes.hh"

namespace NC = NCrystal;

NC::DataSourceName::DataSourceName()
  : m_str( [](){ static auto s_def = makeSO<std::string>(); return s_def; }() )
{
}

std::ostream& NC::operator<<( std::ostream& os, const OrientDir& od )
{
  if ( od.crystal.has_value<CrystalAxis>() ) {
    auto& v = od.crystal.get<CrystalAxis>();
    os << "@crys:" << fmt(v[0]) << ',' << fmt(v[1]) << ',' << fmt(v[2]);
  } else if ( od.crystal.has_value<HKLPoint>() ) {
    auto& v = od.crystal.get<HKLPoint>();
    os << "@crys_hkl:" << fmt(v[0]) << ',' << fmt(v[1]) << ',' << fmt(v[2]);
  } else {
    os << "@crys:<MISSING>";
  }
  os << "@lab:" << fmt(od.lab[0])<< ',' << fmt(od.lab[1])<< ',' << fmt(od.lab[2]);
  return os;
}

std::ostream& NC::operator<< (std::ostream& os, const DensityState& ds)
{
  if ( ds.type == DensityState::Type::SCALEFACTOR ) {
    os << fmt(ds.value)<<"x";
  } else if ( ds.type == DensityState::Type::DENSITY ) {
    os << fmt(ds.value)<<"gcm3";
  } else {
    nc_assert( ds.type == DensityState::Type::NUMBERDENSITY );
    os << fmt(ds.value)<<"perAa3";
  }
  return os;
}
