
#include "analog_io.h"
#include "controllers/iir_controller.hpp"
#include "reference.hpp"

static ReferencePath refs[] = {ReferencePath(), ReferencePath(), ReferencePath(), ReferencePath(),ReferencePath(), ReferencePath(), ReferencePath(), ReferencePath()};

PIController
    controller0{[]() { return (double)read_ain0(); },
                [](double x) { write(4, x); },
                {-1 / 3.},
                {0., -1 / 2.},
                -0.015,
                0.,     // min output DAC number
                1100.,  // max output DAC number
                &refs[0],&refs[4]},
    controller1{[]() { return (double)read_ain1(); },
                [](double x) { write(5, x); },
                {-1 / 3.},
                {0., -1 / 2.},
                -0.015,
                0.,
                1100.,
                &refs[1],&refs[5]},
    controller2{[]() { return (double)read_bin0(); },
                [](double x) { write(6, x); },
                {-1 / 4.},
                {0., -1 / 2.},
                -0.003,
                0.,
                1100.,
                &refs[2],&refs[6]},
    controller3{[]() { return (double)read_bin1(); },
                [](double x) { write(7, x); },
                {-1 / 3.},
                {0., -1 / 2.},
                -0.015,
                0.,
                1100.,
                &refs[3],&refs[7]};

typedef Controller* const pController;

extern __attribute__((weak)) pController
    pc0 = &controller0,
    pc1 = &controller1,
    pc2 = &controller2,
    pc3 = &controller3;
