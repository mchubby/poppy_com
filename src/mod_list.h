/*
 * This file list all available modules.
 */

#ifndef MOD_LIST_H_
#define MOD_LIST_H_

//*****************Frame format****************************
// address / register / size / data[512]
// byte    / byte     / byte / byte[]

// minimum msg is :
// address / register / 0

//*****************Module list****************************
enum {
    MASTER,
    TACTIL,
    LED,
    PHOTORESISTOR,
    SCREEN,
    MIC,
    SYNTHE,
    IMU,
    VIBRATOR,
    SERVO
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
    VIBRATOR_ADDR,
    SERVO_ADDR
}addr_register_t;
//*****************Module registers****************************

typedef enum {
    MASTER_GET_MIC_LEVEL, // uint16_t level
    MASTER_GET_TACTIL_LEVEL, // uint16_t level
    MASTER_GET_IMU_LEVEL // {float yow, float pitch, float roll, int16_t accelx, int16_t accely, int16_t accelz} (float = 4 bytes)
}master_register_t;

typedef enum {
    PHOTORESISTOR_LEVEL // request with no data, ask for a reply
}photoresistor_register_t;

typedef enum {
    TOUCH_LEVEL // request with no data, ask for a reply
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
    SYNTHE_VOL,
    PLAY_TEST1, // no data, just play the melody
    PLAY_TEST2, // no data, just play the melody
}synthe_register_t;

typedef enum {
    IMU_LEVEL // request with no data, ask for a reply
}imu_register_t;

typedef enum {
    VIBRATOR_SPEED
}vibrator_register_t;

typedef enum {
    SERVO_LEFT_POSITION,
    SERVO_RIGHT_POSITION
}servo_register_t;


#endif /* MOD_LIST_H_ */
