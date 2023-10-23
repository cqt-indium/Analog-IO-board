#include "read.hpp"
#include "servo/controllers/iir_controller.hpp"
#include "servo/reference.hpp"
#include "write.hpp"

static ReferencePath refs[8] = {ReferencePath(), ReferencePath(), ReferencePath(), ReferencePath(), ReferencePath(), ReferencePath(), ReferencePath(), ReferencePath()};

static PIController
    servo_odt{[]() { return (double)read_ain0(); },
             [](double x) { write(4, x); },
             {-1 / 8.},
             {0., -1 / 2.},
             -0.002,
             0.,     // min output DAC number
             1500.,  // max output DAC number
             &refs[0],
             &refs[4],
             };

// overwrite the weak symbols 
extern pController
    pc0 = &servo_odt;