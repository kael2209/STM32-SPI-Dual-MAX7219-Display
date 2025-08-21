#include <stdint.h>

void spi_init(uint8_t spi);
void spi_enabled(uint8_t spi);
void spi_start(uint8_t spi);

void nss_enabled(uint8_t spi);
void nss_disabled(uint8_t spi);


void spi_write(uint8_t spi,uint8_t data);
void spi_send_muplty(uint8_t spi,uint8_t *data, int size);
void spi_writereg8(uint8_t spi,uint8_t reg, uint8_t data);



