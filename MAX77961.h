/*
 * MAX77961.h
 *
 *  Created on: 5 Jul 2021
 *      Author: Sam
 */

#ifndef MAX77961_H_
#define MAX77961_H_

#include "stdint.h"

/*
 * Charger configuration 1
 */
typedef enum {
	MAX77961_PQNE_DISABLE 		= 0x00U,
	MAX77961_PQNE_ENABLE 		= 0x80U
} MAX77961_PQNE_t;

typedef enum {
	MAX77961_LPM_NORMAL			= 0x00U,
	MAX77961_LPM_LOW_POWER		= 0x40U
} MAX77961_LPM__t;

typedef enum {
	MAX77961_CHG_RSTRT_100MV	= 0x00U,
	MAX77961_CHG_RSTRT_150MV	= 0x10U,
	MAX77961_CHG_RSTRT_200MV	= 0x20U,
	MAX77961_CHG_RSTRT_DISABLE	= 0x30U
} MAX77961_CHG_RSTRT_t;

typedef enum {
	MAX77961_STAT_DISABLE		= 0x00U,
	MAX77961_STAT_ENABLE		= 0x08U
} MAX77961_STAT_t;

typedef enum {
	MAX77961_FCHGTIME_DISABLE	= 0x00U,
	MAX77961_FCHGTIME_3HRS,
	MAX77961_FCHGTIME_4HRS,
	MAX77961_FCHGTIME_5HRS,
	MAX77961_FCHGTIME_6HRS,
	MAX77961_FCHGTIME_7HRS,
	MAX77961_FCHGTIME_8HRS,
	MAX77961_FCHGTIME_10HRS
} MAX77961_FCHGTIME_t;

/*
 * Charger configuration 3
 */
typedef enum {
	MAX77961_SYS_TRACK_ENABLE	= 0x00U,
	MAX77961_SYS_TRACK_DISABLE	= 0x80U
} MAX77961_SYS_TRACK_t;

typedef enum {
	MAX77961_B2SOVRC_DTC_6MS	= 0x00U,
	MAX77961_B2SOVRC_DTC_100MS	= 0x40U
} MAX77961_B2SOVRC_DTC_t;

typedef enum {
	MAX77961_TO_TIME_30SEC		= 0x00U,
	MAX77961_TO_TIME_10MIN		= 0x08U,
	MAX77961_TO_TIME_20MIN		= 0x10U,
	MAX77961_TO_TIME_30MIN		= 0x18U,
	MAX77961_TO_TIME_40MIN		= 0x20U,
	MAX77961_TO_TIME_50MIN		= 0x28U,
	MAX77961_TO_TIME_60MIN		= 0x30U,
	MAX77961_TO_TIME_70MIN		= 0x38U
} MAX77961_TO_TIME_t;

typedef enum {
	MAX77961_TO_ITH_100MA		= 0x00U,
	MAX77961_TO_ITH_200MA,
	MAX77961_TO_ITH_300MA,
	MAX77961_TO_ITH_400MA,
	MAX77961_TO_ITH_500MA,
	MAX77961_TO_ITH_600MA
} MAX77961_TO_ITH_t;


typedef enum {
	MAX77961_OK			= 0x00U,
	MAX77961_ERROR,
	MAX77961_COM_FAIL,
	MAX77961_UNLOCK_FAIL
} MAX77961_Status_t;





typedef struct {
	uint32_t input_current_limit;
	uint32_t fast_charge_current;
	uint32_t top_off_timer;
	uint32_t top_off_current;
	uint32_t termination_voltage;

	char message[10];

} MAX77961_t;



MAX77961_Status_t max77961_init(MAX77961_t *this);
MAX77961_Status_t max77961_charger_protection_unlock();
MAX77961_Status_t max77961_charger_protection_lock();
MAX77961_Status_t max77961_software_reset();

void max77961_sys_track(MAX77961_SYS_TRACK_t state);

MAX77961_Status_t max77961_set_input_current_limit(uint32_t icurr_limit);
MAX77961_Status_t max77961_set_fast_charge_current(uint32_t fcharge_current);
void max77961_set_top_off_current(uint32_t toff_current);
void max77961_set_termination_voltage(uint32_t term_voltage);

uint8_t max77961_get_number_of_cell();

void max77961_error_handle();
void mtest();
#endif /* MAX77961_H_ */
