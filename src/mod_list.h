/*
 * This file list all available modules.
 */

#ifndef MOD_LIST_H_
#define MOD_LIST_H_

//*****************Frame format****************************
// addresse / register / size / data[512]

//*****************Module list****************************
enum {
    MASTER,
    TACTIL,
    LED,
    PHOTORESISTOR,
    SCREEN,
    MIC,
    SYNTHE,
    IMU
};
//*****************Module address list****************************
enum {
    MASTER_ADDR = 1,
    TACTIL_ADDR,
    LED_ADDR,
    PHOTORESISTOR_ADDR,
    SCREEN_ADDR,
    MIC_ADDR,
    SYNTHE_ADDR,
    IMU_ADDR,
}addr_register_t;;

//*****************Module registers****************************

typedef enum {
    MASTER_REGISTER
}master_register_t;

typedef enum {
    PHOTORESISTOR_LEVEL // request with no data, ask for a reply
}photoresistor_register_t;

typedef enum {
    LIGHT_LEVEL // request with no data, ask for a reply
}tactil_register_t;

typedef enum {
    LED_REGISTER
}led_register_t;

typedef enum {
    SCREEN_REGISTER
}screen_register_t;

typedef enum {
    MIC_LEVEL // request with no data, ask for a reply
}mic_register_t;

typedef enum {
    SYNTHE_VOL
}synthe_register_t;

typedef enum {
    IMU_REGISTER
}imu_register_t;


#endif /* MOD_LIST_H_ */
