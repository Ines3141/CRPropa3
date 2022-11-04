#include "crpropa/magneticField/MagneticBottle.h"
#include <math.h>

namespace crpropa {

	// was macht namespace crpropa???

	MagneticBottle::MagneticBottle(double B_0, double D, double M) {
		setB0(B_0);
		setD(D); // Distance between the Dipols 
		setM(M); // Magnetic dipol 
	}

	Vector3d MagneticBottle::getField(const Vector3d& pos) const {
		// Der Klasse MagneticBottle wird die Funktion getField zugeordnet
		// Als Parameter wird die Klasse Vector3d übergeben
		// Pos ist wahscheinlich die Position des Observers

		double pi = 3.14156; // Welche libary muss benutzt werden????
		double m_u = 1.26 * 10 ** (-6); // Magnetische Feldkonstante 
		double factor = m_u / (4 * pi);

		//Uni Oslo arbeitet mit kartesischen Koordinaten 
		double x = pos.getX();
		double y = pos.getY();
		double z = pos.getZ();

		Vector3d BA1(0., 0., D.);
		Vector3d BA2;
		Vector3d BB1(0., 0., -D.);
		Vector3d BB2;
		Vector3d B;

		//Erstellt 5 Instanzen der Klasse Vector3d
		// Wenn keine Parameter angegeben werden sind, sollte ein Vector3d (0.,0.,0.) erzeugt werden
		// BA erstellt den Dipol an der Stelle (0,0,D)

		double r_A = (x**2 + y**2 + (z - D)**2)**0.5;			// Betrag von Position Observer und BA
		BA1.x += 3 * x * (z - D) / r_A**5;						// Zuordnung der x-Koordinate 
		BA1.y += 3 * y * (z - D) / r_A**5;						// Zuordnung der y-Koordinate
		BA1.z += 3 * (z - D)**2  / r_A**5;						// Zuordnung der z-Koordinate


		BA2.x += -M / r_A**3;
		BA2.y += -M / r_A**3;
		BA2.z += -M / r_A**3;

		// Muss es BA.x += sein????? Ich glaube nicht

		//Dipol B
		double r_B = (x * *2 + y * *2 + (z + D) * *2) * *0.5;

		BB1.x += 3 * x * M * (z - D) / r_B * *5;
		BB1.y += 3 * y * M * (z - D) / r_B * *5;
		BB1.z += 3 * M * (z - D) * *2 / r_B * *5;

		BB2.x += -M / r_A * *3;
		BB2.y += -M / r_A * *3;
		BB2.z += -M / r_A * *3;

		// add all B-Fields together
		B.x = factor * (BA1.x + BA2.x + BB1.x + BB2.x);
		B.y = factor * (BA1.y + BA2.y + BB1.y + BB2.y);
		B.z = factor * (BA1.z + BA2.z + BB1.z + BB2.z);

		// overall scaling
		B *= B_0;


		return B;
	}

	void MagneticBottle::setB0(double B) {
		B_0 = B;
		return;
	}

	void MagneticBottle::setD0(double D) {
		D_0 = D;
		return;
	}

	void MagneticBottle::setM0(double M) {
		M_0 = M;
		return;
	}

	double MagneticBottle::getB0() const {
		return B_0;
	}

	double MagneticBottle::getD0() const {
		return D_0;
	}

	double MagneticBottle::getM0() const {
		return M_0;
	}



} //end namespace crpropa
