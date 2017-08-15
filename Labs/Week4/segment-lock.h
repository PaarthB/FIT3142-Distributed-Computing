/*
 * Miscellanous includes.
 * (c) 2004, SCSSE, Monash Uni, Carlo Kopp
 */

#define SHMSZ  128
#define SEGMENTID  2222

typedef struct
	seg_data {
		int		mylock;		/* Server exit command from client */
		int		present;	/* Server exit command from client */
		int		exit;		/* Server exit command from client */
		int		rpm;		/* Revolutions per Minute 0 - 7000 */
		int		crankangle;	/* crankshaft angle 0 - 360 deg */
		int		throttle;	/* throttle setting 0 - 100 % */
		int		fuelflow;	/* fuelflow setting 0 - 100 % */
		int		temp;		/* engine temperature 0 - 100 % */
		int		fanspeed;	/* cooling fan speed 0 - 100 % */
		int		oilpres;	/* lubricant pressure 0 - 100 % */
	} SEG_DATA;

#define CLIENT_1  0x01
#define CLIENT_2  0x02
#define CLIENT_3  0x04
#define CLIENT_4  0x08
