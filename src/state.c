#include "state.h"

void state_check_bool(state* s, bool_t exceeded){
    // Do nothing if the state is set to check only when unmasked.
    if( s->status.bits.check_unmasked_only && s->status.bits.masked){
        return;
    }

    if(exceeded){
        s->_cnt += s->_step_valid ;
        if(s->_cnt >= s->_cnt_max){
            s->_cnt = s->_cnt_max;
            s->status.bits._valid = 1 ; 
            // s->status.valid = s->status._valid && (!s->status.masked);
            s->status.bits.valid = (!s->status.bits.masked);
        }
    }else if(s->status.bits.recoverable){
        s->_cnt -= s->_step_recover ;
        if(s->_cnt <= 0){
            s->_cnt = 0 ; 
            s->status.bits._valid = 0 ; 
            // s->status.valid = s->status._valid && (!s->status.masked);
            s->status.bits.valid = 0 ; 
        }
    }else{
        // Nothing to do 
    }
}

void state_reset(state* s){
    s->status.bits.valid = 0 ; 
    s->status.bits._valid = 0 ; 
    s->_cnt = 0 ; 
}

void state_array_reset(state** s_array, rt_uint16_t n){
    rt_uint16_t i = 0; 
    for(i = 0; i ++; i < n){
        if(*s_array != RT_NULL ){
            state_reset(*s_array);
        }else{
            break;
        }
    }
}

void state_check_value(state*s, float value){
    if(s->status.bits.check_unmasked_only && s->status.bits.masked){
        return;
    }

    if(s->status.bits.type == UNDER_THRESHOLD_VALID){
        if(value < s->valid_threshold){
            s->_cnt += s->_step_valid ;
        }else if(value > s->recover_threshold && s->status.bits.recoverable){
            s->_cnt -= s->_step_recover;
        }else{
            // DO NOTHING
        }
    }else{
        if(value > s->valid_threshold){
            s->_cnt += s->_step_valid ; 
        }else if(value < s->recover_threshold && s->status.bits.recoverable){
            s->_cnt -= s->_step_recover;
        }else{
            // DO NOTHING
        }
    }

    if(s->_cnt >= s->_cnt_max){
        s->_cnt = s->_cnt_max; 
        s->status.bits._valid = 1 ; 
        // s->status.valid = s->status._valid && (!s->status.masked);
        s->status.bits.valid = (!s->status.bits.masked);
    }else if( s->_cnt <= 0){
        s->_cnt = 0 ; 
        s->status.bits._valid = 0 ; 
        // s->status.valid = s->status._valid && (!s->status.masked);
        s->status.bits.valid = 0 ; 
    }else{
        // DO NOTHING
    }
}


rt_uint8_t get_state_number(state* s){
    return s->number;
}

rt_uint8_t get_state_masked(state* s){
    return s->status.bits.masked;
}

void set_state_masked(state* s, bool_t masked){
    s->status.bits.masked = (masked > 0);
}

rt_uint8_t get_state_level(state* s){
    return s->level;
}

rt_err_t set_state_level(state* s, rt_uint8_t level){
    if(level <= LEVEL_CRITICAL){
        s->level = level; 
        return RT_EOK;
    }else{
        return - RT_ERROR;
    }
}

rt_uint8_t get_state_recoverable(state*s){
    return s->status.bits.recoverable;
}

void set_state_recoverable(state*s, rt_uint8_t recoverable){
    s->status.bits.recoverable = (recoverable > 0) ; 
}

float get_state_valid_threshold(state*s){
    return s->valid_threshold;
}

float get_state_recover_threshold(state*s){
    return s->recover_threshold; 
}
