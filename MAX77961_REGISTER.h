/*
 * MAX77961_REGISTER.h
 *
 *  Created on: 5 Jul 2021
 *      Author: Sam
 */

#ifndef MAX77961_REGISTER_H_
#define MAX77961_REGISTER_H_


/****************************************************************************
 *                    MAX77960/MAX77961 Register Map                        *
 ****************************************************************************/

/* CID */
#define	CID					0x00
#define REVISION			5
#define REVISION_MASK		0x07 << REVISION
#define VERSION				0
#define VERSION_MASK		0x1F << VERSION

/* SWREST */
#define	SWRST				0x01
#define SW_RST				0
#define SOFTWARE_RESET		0xA5

/* TOP_INT */
#define	TOP_INT				0x02
#define TSHDN_I				2
#define TSHDN_I_MASK		0x01 << TSHDN_I
#define SYSOVLO_I 			1
#define SYSOVLO_I_MASK		0x01 << SYSOVLO_I
#define SYSUVLO_I			0
#define SYSUVLO_I_MASK		0x01 << SYSUVLO_I

/* TOP_INT_MASK */
#define	TOP_INT_MASK		0x03
#define TSHDN_M				2
#define TSHDN_M_MASK		0x01 << TSHDN_M
#define SYSOVLO_M			1
#define SYSOVLO_M_MASK		0x01 << SYSOVLO_M
#define SYSUVLO_M			0
#define SYSUVLO_M_MASK		0x01 << SYSUVLO_M

/* TOP_INT_OK */
#define	TOP_INT_OK			0x04
#define TSHDN_OK			2
#define TSHDN_OK_MASK		0x01 << TSHDN_OK
#define SYSOVLO_OK			1
#define SYSOVLO_OK_MASK		0x01 << SYSOVLO_OK
#define SYSUVLO_OK			0
#define SYSUVLO_OK_MASK		0x01 << SYSUVLO_OK

/* CHG_INT */
#define	CHG_INT				0x10
#define	AICL_I              7
#define	AICL_I_MASK         0x01 << AICL_I
#define	CHGIN_I             6
#define	CHGIN_I_MASK        0x01 << CHGIN_I
#define	B2SOVRC_I           5
#define	B2SOVRC_I_MASK      0x01 << B2SOVRC_I
#define	CHG_I               4
#define	CHG_I_MASK          0x01 << CHG_I
#define	BAT_I               3
#define	BAT_I_MASK          0x01 << BAT_I
#define	CHGINILIM_I         2
#define	CHGINILIM_I_MASK    0x01 << CHGINILIM_I
#define	DISQBAT_I           1
#define	DISQBAT_I_MASK      0x01 << DISQBAT_I
#define	OTG_PLIM_I          0
#define	OTG_PLIM_I_MASK     0x01 << OTG_PLIM_I

/* CHG_INT_MASK */
#define	CHG_INT_MASK		0x11
#define	AICL_M              7
#define	AICL_M_MASK         0x01 << AICL_M
#define	CHGIN_M             6
#define	CHGIN_M_MASK        0x01 << CHGIN_M
#define	B2SOVRC_M           5
#define	B2SOVRC_M_MASK      0x01 << B2SOVRC_M
#define	CHG_M               4
#define	CHG_M_MASK          0x01 << CHG_M
#define	BAT_M               3
#define	BAT_M_MASK          0x01 << BAT_M
#define	CHGINILIM_M         2
#define	CHGINILIM_M_MASK    0x01 << CHGINILIM_M
#define	DISQBAT_M           1
#define	DISQBAT_M_MASK      0x01 << DISQBAT_M
#define	OTG_PLIM_M          0
#define	OTG_PLIM_M_MASK     0x01 << OTG_PLIM_M

/* CHG_INT_OK */
#define	CHG_INT_OK			0x12
#define	AICL_OK             7
#define	AICL_OK_MASK        0x01 << AICL_OK
#define	CHGIN_OK            6
#define	CHGIN_OK_MASK       0x01 << CHGIN_OK
#define	B2SOVRC_OK          5
#define	B2SOVRC_OK_MASK     0x01 << B2SOVRC_OK
#define	CHG_OK              4
#define	CHG_OK_MASK         0x01 << CHG_OK
#define	BAT_OK              3
#define	BAT_OK_MASK         0x01 << BAT_OK
#define	CHGINILIM_OK        2
#define	CHGINILIM_OK_MASK   0x01 << CHGINILIM_OK
#define	DISQBAT_OK          1
#define	DISQBAT_OK_MASK     0x01 << DISQBAT_OK
#define	OTG_PLIM_OK         0
#define	OTG_PLIM_OK_MASK    0x01 << OTG_PLIM_OK

/* Charger details 00 */
#define CHG_DTLS_00    		0x13
#define CHGIN_DTLS			5
#define CHGIN_DTLS_MASK		0x03 << CHGIN_DTLS
#define OTG_DTLS			3
#define OTG_DTLS_MASK		0x03 << OTG_DTLS
#define QB_DTLS				0
#define QB_DTLS_MASK		0x01 << QB_DTLS

/* Charger details 01 */
#define CHG_DTLS_01    		0x14
#define TREG				7
#define TREG_MASK			0x01 << TREG
#define BAT_DTLS			4
#define BAT_DTLS_MASK		0x07 << BAT_DTLS
#define CHG_DTLS			0
#define CHG_DTLS_MASK		0x0F << CHG_DTLS

/* Charger details 02 */
#define CHG_DTLS_02    		0x15
#define	THM_DTLS			4
#define THM_DTLS_MASK		0x07 << THM_DTLS
#define APP_MODE_DTLS 		3
#define APP_MODE_DTLS_MASK 	0x01 << APP_MODE_DTLS
#define FSW_DTLS			1
#define FSW_DTLS_MASK		0x03 << FSW_DTLS
#define NUM_CELL_DTLS 		0
#define NUM_CELL_DTLS_MASK 	0x01 << NUM_CELL_DTLS
#define NUM_CELL_2			0x00
#define NUM_CELL_3			0x01

/* Charger configuration 00 */
#define	CHG_CNFG_00			0x16
#define COMM_MODE			7
#define COMM_MODE_MASK		1 << COMM_MODE
#define DISIBS				6
#define DISIBS_MASK			1 << DISIBS
#define STBY_EN				5
#define STBY_EN_MASK		1 << STBY_EN
#define WDTEN				4
#define WDTEN_MASK			1 << WDTEN
#define MODE				0
#define MODE_MASK			0x0F << MODE

/* Charger configuration 01 */
#define	CHG_CNFG_01			0x17
#define PQNE				7
#define PQNE_MASK			0x01 << PQNE
#define LPM					6
#define LPM_MASK			0x01 << LPM
#define CHG_RSTRT			4
#define CHG_RSTRT_MASK		0x03 << CHG_RSTRT
#define STAT_EN 			3
#define STAT_EN_MASK		0x01 << STAT_EN
#define FCHGTIME			0
#define FCHGTIME_MASK		0x07 << FCHGTIME

/* Charger configuration 02 */
#define	CHG_CNFG_02			0x18
#define CHGCC				0
#define CHGCC_MASK			0x3F << CHGCC

/* Charger configuration 03 */
#define	CHG_CNFG_03			0x19
#define SYS_TRACK_DIS		7
#define SYS_TRACK_DIS_MASK 	0x01 << SYS_TRACK_DIS
#define B2SOVRC_DTC			6
#define B2SOVRC_DTC_MASK    0x01 << B2SOVRC_DTC
#define TO_TIME				3
#define TO_TIME_MASK   		0x07 << TO_TIME
#define TO_ITH				0
#define TO_ITH_MASK			0x07 << TO_ITH

/* Charger configuration 04 */
#define	CHG_CNFG_04			0x1A
#define CHG_CV_PRM			0
#define CHG_CV_PRM_MASK		0x3F << CHGCC

/* Charger configuration 05 */
#define	CHG_CNFG_05			0x1B
#define ITRICKLE			4
#define ITRICKLE_MASK		0x03 << ITRICKLE
#define B2SOVRC				0
#define B2SOVRC_MASK		0x0F << B2SOVRC

/* Charger configuration 06 */
#define	CHG_CNFG_06			0x1C
#define CHGPROT				2
#define CHGPROT_MASK		0x03 << CHGPROT
#define CHGPROT_LOCK		0x00
#define CHGPROT_UNLOCK		0x03
#define WDTCLR				0
#define WDTCLR_MASK			0x03 << WDTCLR
#define WDTCLR_CLEAR		0x03				// Writing 0x03 to WDTCLR clears the
												// watchdog timer when it is enabled

/* Charger configuration 07 */
#define	CHG_CNFG_07			0x1D
#define JEITA_EN			7
#define JEITA_EN_MASK		0x01 << JEITA_EN
#define REGTEMP				3
#define REGTEMP_MASK		0x0F << REGTEMP
#define VCHGCV_COOL 		2
#define VCHGCV_COOL_MASK	0x01 << VCHGCV_COOL
#define ICHGCC_COOL			1
#define ICHGCC_COOL_MASK	0x01 << ICHGCC_COOL
#define FSHIP_MODE 			0
#define FSHIP_MODE_MASK		0x01 << FSHIP_MODE

/* Charger configuration 08 */
#define	CHG_CNFG_08			0x1E
#define CHGIN_ILIM			0
#define CHGIN_ILIM_MASK		0x7F << CHGIN_ILIM

/* Charger configuration 09 */
#define	CHG_CNFG_09			0x1F
#define INLIM_CLK			6
#define INLIM_CLK_MASK		0x03 << INLIM_CLK
#define OTG_ILIM			3
#define OTG_ILIM_MASK		0x07 << OTG_ILIM
#define MINVSYS				0
#define MINVSYS_MASK		0x07 << MINVSYS

/* Charger configuration 10 */
#define	CHG_CNFG_10			0x20
#define VCHGIN_REG			1
#define VCHGIN_REG_MASK		0x1F << VCHGIN_REG
#define DISKIP				0
#define DISKIP_MASK			0x01 << DISKIP


#endif /* MAX77961_REGISTER_H_ */
