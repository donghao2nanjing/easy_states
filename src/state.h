#ifndef STATE_H 
#define STATE_H 

#include "types.h"

#define LEVEL_STATE 0 
#define LEVEL_ALARM 1 
#define LEVEL_FAULT 2 
#define LEVEL_CRITICAL 3 

#define UNDER_THRESHOLD_VALID 0
#define OVER_THRESHOLD_VALID 1 

#define PERIOD_CHECK 0 
#define COUNT_CHECK 1  // TODO

typedef union state_status{
    rt_uint8_t byte ; 
    struct status_bit
    {
        rt_uint8_t valid : 1 ;  // if the state is triggered valid.
        rt_uint8_t _valid : 1 ; 
        rt_uint8_t masked : 1 ; 
        rt_uint8_t check_unmasked_only : 1 ;  // the state is checked only when unmasked.
        rt_uint8_t recoverable : 1 ; // if the state is recoverable.
        rt_uint8_t type : 1 ; // 0: under threshold to trigger; 1: over threshold to trigger.
        rt_uint8_t check_by: 1 ; // 0: trigger by periodical check; 1: trigger by count
        rt_uint8_t reserved : 1 ;
    }bits;
} state_status;

typedef struct state
{
    rt_uint16_t number ;  
    rt_uint8_t level ; 
    state_status status ;

    rt_int32_t _cnt ;
    rt_int32_t _cnt_max ; 

    rt_int32_t _step_valid;  // step when greater than high threshold 
    rt_int32_t _step_recover ;  // step when less than lower threshold

    float valid_threshold; 
    float recover_threshold ;
}state;

void state_check_bool(state* s, bool_t exceeded);
void state_reset(state* s);
void state_array_reset(state** s_array, rt_uint16_t n);
void state_check_value(state*s, float value);

rt_uint8_t get_state_number(state*s); 
rt_uint8_t get_state_masked(state*s); 
void set_state_masked(state*s, bool_t masked); 
rt_uint8_t get_state_level(state*s);
rt_err_t set_state_level(state*s, rt_uint8_t level);
rt_uint8_t get_state_recoverable(state*s);
void set_state_recoverable(state*s, rt_uint8_t recoverable);

float get_state_high_threshold(state*s);
float get_state_low_threshold(state*s);

#endif 