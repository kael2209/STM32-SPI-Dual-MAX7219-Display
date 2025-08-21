#include "stm32f10x.h"         
#include "spi.h"

void spi_init(uint8_t spi)
{
	if (spi==1)
	{
		// CLock to SPI1 and GPIOA
		RCC->APB2ENR|= RCC_APB2ENR_SPI1EN | RCC_APB2ENR_IOPAEN;
		// Config pins
		GPIOA->CRL&=~(0xF<<16)&~(0xF<<20)&~(0xF<<24)&~(0xF<<28);
		GPIOA->CRL|=(1<<16);		// Output for CSS
		GPIOA->ODR|=(1<<4);			// High
		GPIOA->CRL|=(11<<20)|(11<<28);	// AFPP for PA5,PA7
		//GPIOA->CRL|=(8<<24);						// Input for MISO
		// Set up SPI
		SPI1->CR1|=(1<<2);		// Master mode
		SPI1->CR1|=(2<<3);		// fclk/16;
		SPI1->CR1&=~(3<<0);		// CPHA =0 CPOL =0;
		SPI1->CR1|=(1<<9);		// Quan lu chan CSS bang phan mem
		SPI1->CR1|=(1<<8);		
	}
	else if (spi==2)
	{
		// CLock to SPI2 and GPIOB
		RCC->APB1ENR|= RCC_APB1ENR_SPI2EN;
		RCC->APB2ENR|= RCC_APB2ENR_IOPBEN;
		// Config pins
		GPIOB->CRH&=~(0xF<<16)&~(0xF<<20)&~(0xF<<24)&~(0xF<<28);
		GPIOB->CRH|=(1<<16);	// Output for CSS
		GPIOB->ODR|=(1<<12);			// High
		GPIOB->CRH|=(11<<20)|(11<<28);	// AFPP for PB13,PB15
		//GPIOB->CRH|=(8<<24);						// Input for MISO
		// Set up SPI
		SPI2->CR1|=(1<<2);		// Master mode
		SPI2->CR1|=(2<<3);		// fclk/16;
		SPI2->CR1&=~(3<<0);		// CPHA =0 CPOL =0;
		SPI2->CR1|=(1<<9);		// Quan lu chan CSS bang phan mem
		SPI2->CR1|=(1<<8);		
	}
}
void spi_enabled(uint8_t spi)
{
	if (spi==1)
	{
		SPI1->CR1|=(1<<6);
	}
	else if (spi==2)
	{
		SPI2->CR1|=(1<<6);
	}
}
void spi_start(uint8_t spi)
{
	if (spi==1)
	{
		spi_init(spi);
		spi_enabled(spi);
	}
	else if (spi==2)
	{
		spi_init(spi);
		spi_enabled(spi);
	}
	
}
/****************************************************************/
void nss_enabled(uint8_t spi)
{
	if (spi==1)
	{
		GPIOA->ODR&=~(1<<4);
	}
	else if (spi==2)
	{
		GPIOB->ODR&=~(1<<12);
	}
}
void nss_disabled(uint8_t spi)
{
	if (spi==1)
	{
		GPIOA->ODR|=(1<<4);
	}
	else if (spi==2)
	{
		GPIOB->ODR|=(1<<12);
	}
}
/****************************************************************/
void spi_write(uint8_t spi,uint8_t data)
{
	if (spi==1)
	{
		nss_enabled(spi);
		while(!(SPI1->SR&(1<<1)));
		SPI1->DR = data;
		while (SPI1->SR & SPI_SR_BSY);
		(void)SPI1->DR;
		nss_disabled(spi);
	}
	else if (spi==2)
	{
		nss_enabled(spi);
		while(!(SPI2->SR&(1<<1)));
		SPI2->DR = data;
		while (SPI2->SR & SPI_SR_BSY);
		(void)SPI2->DR;
		nss_disabled(spi);
	}
}
void spi_send_muplty(uint8_t spi,uint8_t *data, int size)
{
	nss_enabled(spi);
	if (spi==1)
	{
		for (int i = 0; i < size; i++)
		{
			// Ch? TXE (Transmit Buffer Empty)
			while (!(SPI1->SR & SPI_SR_TXE));
			// G?i d? li?u
			SPI1->DR = data[i];
			// Ch? RXNE (Receive Buffer Not Empty)
			while (!(SPI1->SR & SPI_SR_RXNE));
			// Ð?c d? li?u nh?n du?c (d? xóa c? RXNE)
			(void)SPI1->DR;
		}
	}
	else if (spi==2)
	{
		for (int i = 0; i < size; i++)
		{
			// Ch? TXE (Transmit Buffer Empty)
			while (!(SPI2->SR & SPI_SR_TXE));
			// G?i d? li?u
			SPI2->DR = data[i];
			// Ch? RXNE (Receive Buffer Not Empty)
			while (!(SPI2->SR & SPI_SR_RXNE));
			// Ð?c d? li?u nh?n du?c (d? xóa c? RXNE)
			(void)SPI2->DR;
		}
	}

	nss_disabled(spi);
}

void spi_writereg8(uint8_t spi,uint8_t reg, uint8_t data)
{
	uint8_t tx_buffer[2];
	tx_buffer[0] = reg;
	tx_buffer[1] = data;
	spi_send_muplty(spi,tx_buffer,2);
}




















