#ifndef faust_autodiffverifier_h
#define faust_autodiffverifier_h

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif

#include "dspFactoryOwner.h"
#include "faust/gui/MapUI.h"
#include "faust/dsp/dsp-combiner.h"
#include "faust/audio/dummy-audio.h"

class autodiffVerifier : private dspFactoryOwner
{
public:
    autodiffVerifier(std::string inputDSPPath,
                     std::string differentiableDSPPath,
                     float epsilon = 1e-3f);
    
    ~autodiffVerifier();
    
    void initialise();
    
    void verify();

private:
    const int kNumIterations{100};
    const float kEpsilon;
    
    /**
     * Create a cascade of parallel `dsp` instances.
     *
     * @param dsp A DSP algorithm to duplicate as part of the cascade.
     * @param numInstances The number (>= 1) of dsp instances to create.
     * @return If numInstances == 1, a clone of the supplied dsp instance.
     * Otherwise a dsp_paralellizer instance containing cascaded `dsp`
     * instances, e.g.:
     *
     * ```
     * new dsp_paralellizer(
     *     dsp->clone(),
     *     new dsp_paralellizer(
     *         dsp->clone(), dsp->clone()
     *     )
     * )
     * ```
     */
    dsp *createDSPCascade(dsp *dsp, int numInstances);
    
    int fNumParams;
    std::string fInputDSPPath, fDifferentiableDSPPath;
    dsp *fDSP;
    std::unique_ptr<MapUI> fUI;
    std::unique_ptr<dummyaudio> fAudio;
};


#endif //faust_autodiffverifier_h