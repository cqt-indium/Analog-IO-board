#include "read.hpp"
#include "servo/controllers/pi_controller_windup.hpp"
#include "servo/controllers/iir_controller.hpp"
#include "servo/reference.hpp"
#include "write.hpp"

static ReferencePath refs[8] = {ReferencePath(), ReferencePath(), ReferencePath(), ReferencePath(), ReferencePath(), ReferencePath(), ReferencePath(), ReferencePath()};


static VanillaPIController
    servo_odt{[]() { return (double)read_ain0(); },
             [](double x) { write(4, x); },
             -0.002, -0.0005, 
             0.,     // min output DAC number
             1500.,  // max output DAC number
             &refs[0],
             &refs[4],
             };

static ConstantController 
    odt_aom_vco_mod{
        []() { return 0.; }, 
        [](double x) {write(5, x);}, 
        {}, 
        {}, 
        -1., 
        17445., 19065.,
        &refs[1],
        &refs[5],  
    };
// overwrite the weak symbols 
extern pController
    pc0 = &servo_odt, 
    pc1 = &odt_aom_vco_mod;