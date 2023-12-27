#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <types.h>

#include <log.h>

#include <common.h>

#include <sys-clk.h>
#include <reg-ncat.h>

#include <mmu.h>

#include <sys-gpio.h>
#include <sys-spi.h>
#include <sys-uart.h>
#include <sys-dram.h>
#include <sys-sdcard.h>

sunxi_serial_t uart_dbg = {
        .base = SUNXI_UART3_BASE,
        .id = 3,
        .gpio_tx = {GPIO_PIN(GPIO_PORTB, 6), GPIO_PERIPH_MUX7},
        .gpio_rx = {GPIO_PIN(GPIO_PORTB, 7), GPIO_PERIPH_MUX7},
};

sunxi_spi_t sunxi_spi0 = {
        .base = SUNXI_SPI0_BASE,
        .id = 0,
        .clk_rate = 75 * 1000 * 1000,
        .gpio_cs = {GPIO_PIN(GPIO_PORTC, 1), GPIO_PERIPH_MUX4},
        .gpio_sck = {GPIO_PIN(GPIO_PORTC, 0), GPIO_PERIPH_MUX4},
        .gpio_mosi = {GPIO_PIN(GPIO_PORTC, 2), GPIO_PERIPH_MUX4},
        .gpio_miso = {GPIO_PIN(GPIO_PORTC, 3), GPIO_PERIPH_MUX4},
        .gpio_wp = {GPIO_PIN(GPIO_PORTC, 4), GPIO_PERIPH_MUX4},
        .gpio_hold = {GPIO_PIN(GPIO_PORTC, 5), GPIO_PERIPH_MUX4},
};

sdhci_t sdhci0 = {
        .name = "sdhci0",
        .reg = (sdhci_reg_t *) SUNXI_SMHC0_BASE,
        .voltage = MMC_VDD_27_36,
        .width = MMC_BUS_WIDTH_4,
        .clock = MMC_CLK_50M,
        .removable = 0,
        .isspi = FALSE,
        .gpio_clk = {GPIO_PIN(GPIO_PORTF, 2), GPIO_PERIPH_MUX2},
        .gpio_cmd = {GPIO_PIN(GPIO_PORTF, 3), GPIO_PERIPH_MUX2},
        .gpio_d0 = {GPIO_PIN(GPIO_PORTF, 1), GPIO_PERIPH_MUX2},
        .gpio_d1 = {GPIO_PIN(GPIO_PORTF, 0), GPIO_PERIPH_MUX2},
        .gpio_d2 = {GPIO_PIN(GPIO_PORTF, 5), GPIO_PERIPH_MUX2},
        .gpio_d3 = {GPIO_PIN(GPIO_PORTF, 4), GPIO_PERIPH_MUX2},
};

dram_para_t dram_para = {
        .dram_clk = 792,
        .dram_type = 3,
        .dram_zq = 0x7b7bfb,
        .dram_odt_en = 0x00,
        .dram_para1 = 0x000010d2,
        .dram_para2 = 0,
        .dram_mr0 = 0x1c70,
        .dram_mr1 = 0x42,
        .dram_mr2 = 0x18,
        .dram_mr3 = 0,
        .dram_tpr0 = 0x004a2195,
        .dram_tpr1 = 0x02423190,
        .dram_tpr2 = 0x0008b061,
        .dram_tpr3 = 0xb4787896,// unused
        .dram_tpr4 = 0,
        .dram_tpr5 = 0x48484848,
        .dram_tpr6 = 0x00000048,
        .dram_tpr7 = 0x1620121e,// unused
        .dram_tpr8 = 0,
        .dram_tpr9 = 0,// clock?
        .dram_tpr10 = 0,
        .dram_tpr11 = 0x00340000,
        .dram_tpr12 = 0x00000046,
        .dram_tpr13 = 0x34000100,
};

void clean_syterkit_data(void) {
    /* Disable MMU, data cache, instruction cache, interrupts */
    arm32_mmu_disable();
    printk(LOG_LEVEL_INFO, "disable mmu ok...\n");
    arm32_dcache_disable();
    printk(LOG_LEVEL_INFO, "disable dcache ok...\n");
    arm32_icache_disable();
    printk(LOG_LEVEL_INFO, "disable icache ok...\n");
    arm32_interrupt_disable();
    printk(LOG_LEVEL_INFO, "free interrupt ok...\n");
}