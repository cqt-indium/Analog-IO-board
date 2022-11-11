#include "init_chips.hpp"

#include "utilities.hpp"
#include "SPISlave.h"
#include "SPIMaster.h"

static void prepare_fast_spi_transfer24(){
    SPI1.begin();
    SPI1.beginTransaction(SPISettings(MAX_DAC_FCLK, MSBFIRST, SPI_MODE1));
    set_fastio_pin(26);  // MOSI1
    set_fastio_pin(27);  // SCK1
    pinMode(39, OUTPUT); // new MISO as output
    SPI1.setCS(0);
    set_fastio_pin(0);
    // new board 
    SPI1.setMISO(1);
    set_fastio_pin(1);

    IMXRT_LPSPI_t* spi_regs = &IMXRT_LPSPI3_S;
    uint16_t div = 720000000 / MAX_DAC_FCLK_PRAC;
    // spi_regs -> CCR = LPSPI_CCR_SCKDIV(div-2) | LPSPI_CCR_DBT(20) | LPSPI_CCR_PCSSCK(1)  | LPSPI_CCR_SCKPCS(1);
    spi_regs -> CCR = LPSPI_CCR_SCKDIV(div-2) | LPSPI_CCR_DBT(125) | LPSPI_CCR_PCSSCK(185)  | LPSPI_CCR_SCKPCS(0);
    
    uint32_t tcr = spi_regs -> TCR;
    spi_regs -> TCR = (tcr & 0xfffff000) | LPSPI_TCR_FRAMESZ(47) | LPSPI_TCR_RXMSK | LPSPI_TCR_WIDTH(1);
    spi_regs->CFGR1 |= LPSPI_CFGR1_PINCFG(1);
}


static void init_DAC1()
{
    pinMode(LDAC1, OUTPUT);
    digitalWrite(LDAC1, LOW);
    pinMode(DAC_CLR1, OUTPUT);
    digitalWrite(DAC_CLR1, HIGH); 
}

static void init_DAC2()
{
    pinMode(LDAC2, OUTPUT);
    digitalWrite(LDAC2, LOW);
    pinMode(DAC_CLR2, OUTPUT);
    digitalWrite(DAC_CLR2, HIGH); 
}


static void init_ADC()
{
}

void init_chips()
{
    // This will set a higher IPG root clock
    CCM_CBCDR = (CCM_CBCDR & ~CCM_CBCDR_IPG_PODF_MASK) | CCM_CBCDR_IPG_PODF(1);
    // increase CPU clock speed to 800MHz 
    // set_arm_clock_cpp(720000000);
    
    init_DAC1();
    init_DAC2();

    delay(20); // wait for chips start-up 
    
    // init_ADC();
    
    prepare_fast_spi_transfer24();

    // calibration of dac starts from here 

    
    delay(200);
}


