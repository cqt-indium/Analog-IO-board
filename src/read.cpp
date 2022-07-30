
#include "read.hpp"

/**
 * @brief Fast spi transfer16, cf. SPI.h implementation
 *
 * @param data: 16-bit data word to transfer  
 * @return uint16_t ADC chip readback 
 */
uint16_t transfer16(uint16_t data)
{
    static IMXRT_LPSPI_t* spim_regs = &IMXRT_LPSPI4_S;
    spim_regs->TDR           = data;
    while ((spim_regs -> RSR & LPSPI_RSR_RXEMPTY)) ;
    return spim_regs->RDR;
}


uint16_t read_ain0()
{
    return ain0; 
}
uint16_t read_ain1()
{
    return ain1; 
}
uint16_t read_bin0()
{
    return bin0; 
}
uint16_t read_bin1()
{
    return bin1; 
}


#if 0
uint16_t read()
{
    ADC_TRANSFER_NOP;
    return read_high_throughput();
}

uint16_t read_high_throughput()
{
    ASSERT_ADC;
    uint16_t ret = transfer16(ADC_NOP);
    DEASSERT_ADC;
    return ret;
}

pair read_pair()
{
    ADC_TRANSFER_NOP;
    return read_pair_high_throughput();
}

pair read_pair_high_throughput()
{
    pair ret = {};
    ASSERT_ADC;
    prepare_slave_read();
    ret.a = transfer16(ADC_NOP);
    ret.b = slave_read();
    DEASSERT_ADC;
    return ret;
}

quad read_quad()
{
    ADC_TRANSFER_NOP;
    ADC_TRANSFER_NOP;
    return read_quad_high_throughput();
}

quad read_quad_high_throughput()
{
    quad ret = {};
    ASSERT_ADC;
    prepare_slave_read();
    ret.a0 = transfer16(ADC_NOP);
    ret.b0 = slave_read();
    DEASSERT_ADC;
    ASSERT_ADC;
    prepare_slave_read();
    ret.a1 = transfer16(ADC_NOP);
    ret.b1 = slave_read();
    DEASSERT_ADC;
    return ret;
}
#endif
