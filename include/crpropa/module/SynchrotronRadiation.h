#ifndef CRPROPA_SYNCHROTRONRADIATION_H
#define CRPROPA_SYNCHROTRONRADIATION_H

#include "crpropa/Module.h"
#include "crpropa/magneticField/MagneticField.h"

namespace crpropa {
/**
 * \addtogroup EnergyLosses
 * @{
 */

/**
 @class SynchrotronRadiation
 @brief Synchrotron radiation of charged particles in magnetic fields.

 This module simulates the continuous energy loss of charged particles in magnetic fields, c.f. Jackson.
 The magnetic field is specified either by a MagneticField or by a RMS field strength value.
 The module limits the next step size to ensure a fractional energy loss dE/E < limit (default = 0.1).
 Optionally, synchrotron photons above a threshold (default E > 10^7 eV) are created as secondary particles.
 Note that the large number of secondary photons per propagation can cause memory problems.
 To mitigate this, use thinning. However, this still does not solve the problem completely.
 For this reason, a break-condition stops tracking secondary photons and reweights the current ones. 
 */
class SynchrotronRadiation: public Module {
private:
	ref_ptr<MagneticField> field; ///< MagneticField instance
	double Brms; ///< Brms value in case no MagneticField is specified
	double limit; ///< fraction of energy loss length to limit the next step
	double thinning; ///< thinning parameter for weighted-sampling (maximum 1, minimum 0)
	bool havePhotons; ///< flag for production of secondary photons
	int maximumSamples; ///< maximum number of samples of synchrotron photons (break condition; defaults to 100; 0 or <0 means no sampling)
	double secondaryThreshold; ///< threshold energy for secondary photons
	std::vector<double> tabx; ///< tabulated fraction E_photon/E_critical from 10^-6 to 10^2 in 801 log-spaced steps
	std::vector<double> tabCDF; ///< tabulated CDF of synchrotron spectrum


public:
	/** Constructor
	 @param field			magnetic field object
	 @param havePhotons		if true, add secondary photons as candidates
	 @param thinning		weighted sampling of secondaries (0: all particles are tracked; 1: maximum thinning)
	 @param nSamples		number of synchrotron photons to be sampled and added as candidates
	 @param limit			step size limit as fraction of mean free path
	 */
	SynchrotronRadiation(ref_ptr<MagneticField> field, bool havePhotons = false, double thinning = 0, int nSamples = 0, double limit = 0.1);
	/** Constructor
	 @param field			RMS of the magnetic field (if magnetic-field object not provided)
	 @param havePhotons		if true, add secondary photons as candidates
	 @param thinning		weighted sampling of secondaries (0: all particles are tracked; 1: maximum thinning)
	 @param nSamples		number of synchrotron photons to be sampled and added as candidates
	 @param limit			step size limit as fraction of mean free path
	 */
	SynchrotronRadiation(double Brms = 0, bool havePhotons = false, double thinning = 0, int nSamples = 0, double limit = 0.1);
	
	void setField(ref_ptr<MagneticField> field);
	void setBrms(double Brms);	
	void setHavePhotons(bool havePhotons);
	void setThinning(double thinning);
	void setLimit(double limit);
	/** Set the maximum number of synchrotron photons that will be allowed to be added as candidates. 
	 This choice depends on the problem at hand. It must be such that all relevant physics is captured with the sample. Weights are added accordingly and the column 'weight' must be added to output.
	 @param nmax	maximum number of synchrotron photons to be sampled
	 */
	void setMaximumSamples(int nmax);
	/** Synchrotron photons above the secondary energy threshold are added as candidates.
	 This may lead to a quick increase in memory.
	 @param threshold	energy threshold above which photons will be added [in Joules]
	 */
	void setSecondaryThreshold(double threshold);	
	ref_ptr<MagneticField> getField();

	double getBrms();
	bool getHavePhotons();
	double getThinning();
	double getLimit();
	int getMaximumSamples();
	double getSecondaryThreshold() const;

	void initSpectrum();
	void process(Candidate *candidate) const;
	std::string getDescription() const;
};
/** @}*/

} // namespace crpropa

#endif // CRPROPA_SYNCHROTRONRADIATION_H
