/*
 * MAX77961.c
 *
 *  Created on: 5 Jul 2021
 *      Author: Sam
 */

#include "MAX77961_REGISTER.h"
#include "MAX77961.h"
#include "string.h"

/*
 *	These function should be implement by user to match the hardware they use.
 */
__attribute__((weak)) MAX77961_Status_t max77961_reg_read(uint8_t address, uint8_t *pdata, uint8_t size)
{
	return MAX77961_ERROR;
}

__attribute__((weak)) MAX77961_Status_t max77961_reg_write(uint8_t address, uint8_t *pdata, uint8_t size)
{
	return MAX77961_ERROR;
}

// Define
#define MAX77961_ADDRESS 	0xD2
#define ILIM_STEP			50		/* 50mA */
#define ILIM_MIN			100
#define ILIM_MAX			6300
#define ISET_STEP1			50		/* 50mA */
#define ISET_MIN			100
#define ISET_MAX			6000
#define ISET_STEP2			100		/* 100mA */
#define ISET_MIDDLE			500
#define ITO_STEP			100		/* 100mA */
#define ITO_MIN				100
#define ITO_MAX				600
#define VSET_STEP			20		/* 20mV */
#define VSET_MIN			8000
#define VSET_MAX			9260

MAX77961_t *g_max77961 = NULL;

// Static function prototype
static MAX77961_Status_t reg_write(uint8_t reg, uint8_t data);
static MAX77961_Status_t reg_read(uint8_t reg, uint8_t *pdata);
static MAX77961_Status_t reg_update(uint8_t reg, uint8_t data, uint8_t mask);
static MAX77961_Status_t reg_read_bitfield(uint8_t reg, uint8_t *pdata, uint8_t bitfield, uint8_t mask);

// Quick test
uint8_t g_data = 1;
void mtest()
{

	g_data = max77961_get_number_of_cell();
}

/*
 *
 */
void max77961_sys_track(MAX77961_SYS_TRACK_t state) {
	reg_update(CHG_CNFG_03, state << SYS_TRACK_DIS, SYS_TRACK_DIS_MASK);
	reg_update(CHG_CNFG_09, 0x07 << MINVSYS, MINVSYS_MASK);
}

/*
 *
 */
MAX77961_Status_t max77961_init(MAX77961_t *this) {
	if (this != NULL) {
		g_max77961 = this;
		return MAX77961_OK;
	}
	else {
		return MAX77961_ERROR;
	}
}

/*
 *	Unlock charger protection.
 */
MAX77961_Status_t max77961_charger_protection_unlock()
{
	const uint8_t MAX_TRY = 10;
	uint8_t ntry = 0;
	uint8_t reg_data = 0;
	uint8_t chgprot_state = 0;

	while (1) {
		reg_write(CHG_CNFG_06, CHGPROT_UNLOCK << CHGPROT);
		reg_read(CHG_CNFG_06, &reg_data);
		chgprot_state = (reg_data & CHGPROT_MASK) >> CHGPROT;
		if (chgprot_state == CHGPROT_UNLOCK)
			return MAX77961_OK;
		else if (++ntry > MAX_TRY)
			return MAX77961_ERROR;
	}
}

/*
 *	Lock charger's registers.
 */
MAX77961_Status_t max77961_charger_protection_lock()
{
	const uint8_t MAX_TRY = 10;
	uint8_t ntry = 0;
	uint8_t reg_data = 0;
	uint8_t chgprot_state = 0;

	while (1) {
		reg_write(CHG_CNFG_06, CHGPROT_LOCK << CHGPROT);
		reg_read(CHG_CNFG_06, &reg_data);
		chgprot_state = (reg_data & CHGPROT_MASK) >> CHGPROT;
		if (chgprot_state == CHGPROT_LOCK)
			return MAX77961_OK;
		else if (++ntry > MAX_TRY)
			return MAX77961_ERROR;
	}
}

/*
 *	Perform software reset to type O registers.
 */
MAX77961_Status_t max77961_software_reset()
{
	if (reg_write(SWRST, SOFTWARE_RESET << SW_RST) != MAX77961_OK)
		return MAX77961_ERROR;
	return MAX77961_OK;
}

/*
 *	This function set the input current limit (mA).
 */
MAX77961_Status_t max77961_set_input_current_limit(uint32_t icurr_limit)
{
	uint8_t data = 0;

	if (icurr_limit < ILIM_MIN || icurr_limit > ILIM_MAX)
		return MAX77961_ERROR;
	data = icurr_limit / ILIM_STEP + 1;
	if (reg_write(CHG_CNFG_08, data) != MAX77961_OK)
		return MAX77961_ERROR;
	return MAX77961_OK;
}

/*
 *	Set fast charge current (mA)
 */
MAX77961_Status_t max77961_set_fast_charge_current(uint32_t fcharge_current)
{
	uint8_t data = 0;

	if (fcharge_current < ISET_MIN || fcharge_current > ISET_MAX)
		return MAX77961_ERROR;

	if (fcharge_current <= ISET_MIDDLE)
		data = fcharge_current / ISET_STEP1 - 2;
	else
		data = fcharge_current / ISET_STEP2 + 3;

	if (reg_write(CHG_CNFG_02, data << CHGCC) != MAX77961_OK)
		return MAX77961_ERROR;
	return MAX77961_OK;
}

/*
 *	This function is for setting the top off current (mA).
 */
void max77961_set_top_off_current(uint32_t toff_current)
{
	uint8_t data = 0;

	if (toff_current < ITO_MIN || toff_current > ITO_MAX)
		return;

	data = toff_current / ITO_STEP - 1;
	reg_update(CHG_CNFG_03, data, TO_ITH_MASK);
}

/*
 *	This function is for setting the charger termination voltage (mV)
 */
void max77961_set_termination_voltage(uint32_t term_voltage)
{
	uint8_t vset = 0;

	// 2 Cell battery
	if (term_voltage < VSET_MIN || term_voltage > VSET_MAX)
		return;

	vset = term_voltage / VSET_STEP - 400;
	reg_write(CHG_CNFG_04, vset << CHG_CV_PRM);
}

/*
 * 	This function return the number of cell that the device is configured
 * 	through on-board resistor. It is read only and cannot be charge through
 * 	software.
 */
uint8_t max77961_get_number_of_cell()
{
	uint8_t numcell;

	reg_read_bitfield(CHG_DTLS_02, &numcell, NUM_CELL_DTLS, NUM_CELL_DTLS_MASK);
	switch (numcell) {
	case NUM_CELL_2:
		return 2;
	case NUM_CELL_3:
		return 3;
	default:
		return 0;
	}
}

/*
 *	Static Functions
 */
static MAX77961_Status_t reg_write(uint8_t reg, uint8_t data)
{
	uint8_t buffer_size = 2;
	uint8_t buffer[buffer_size];

	buffer[0] = reg;
	buffer[1] = data;

	if (max77961_reg_write(MAX77961_ADDRESS, buffer, buffer_size) != MAX77961_OK)
		return MAX77961_ERROR;
	return MAX77961_OK;
}

static MAX77961_Status_t reg_read(uint8_t reg, uint8_t *pdata)
{
	if (max77961_reg_write(MAX77961_ADDRESS, &reg, 1) != MAX77961_OK)
		return MAX77961_ERROR;
	if (max77961_reg_read(MAX77961_ADDRESS, pdata, 1) != MAX77961_OK)
		return MAX77961_ERROR;

	return MAX77961_OK;
}

static MAX77961_Status_t reg_update(uint8_t reg, uint8_t data, uint8_t mask)
{
	uint8_t old_data = 0;
	uint8_t new_data = 0;

	if (reg_read(reg, &old_data) != MAX77961_OK)
		return MAX77961_ERROR;

	new_data = (data & mask) | (old_data & (~mask));

	if (reg_write(reg, new_data) != MAX77961_OK)
		return MAX77961_ERROR;

	return MAX77961_OK;
}

static MAX77961_Status_t reg_read_bitfield(uint8_t reg, uint8_t *pdata, uint8_t bitfield, uint8_t mask)
{
	uint8_t reg_data = 0;
	if (reg_read(reg, &reg_data) != MAX77961_OK)
		return MAX77961_ERROR;
	*pdata = (reg_data & mask) >> bitfield;
	return MAX77961_OK;
}

__attribute__((weak)) void max77961_error_handle()
{
	while (1)
		;
}
