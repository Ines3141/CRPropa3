#ifndef CRPROPA_MAGNETICBOTTLE_H
#define CRPROPA_MAGNETICBOTTLE_H

#include "crpropa/magneticField/MagneticField.h"


#include <string>
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <sstream>

#include "crpropa/Vector3.h"
#include "crpropa/Referenced.h"
#include "crpropa/Units.h"

namespace crpropa {

/**

@class MagneticBottle
@brief Magnetic bottle field model

See e.g. Oslo University
*/

class MagneticBottle: public MagneticField {
private:
	double B_0; // Magnetic field strength
	double D_0; // Distance between the two Dipols
	Vector3d M_0; // Magnetic moment

public:
/** Constructor
 @param B_0	Magnetic field strength
 @param D_0	Distance between the two Dipols
 @param M_0	Magnetic moment
*/
 MagneticBottle(double B_0, double D_0, Vector3d M_0);

 Vector3d getField(const Vector3d& pos) const;

 void setB0(double B);
 void setD0(double D);
 void setM0(Vector3d M);

 double getB0() const;
 double getD0() const;
 Vector3d getM0() const;
};

} // end namespace crpropa

#endif // CRPROPA_MAGNETICBOTTLE_H
