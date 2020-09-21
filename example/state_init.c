#include "state.h" 

/* decalaration of states */ 
state ov1 ;
state ov2 ;
state ov3 ;
state uv1 ;
state uv2 ;

void state_init(void){
    /* generated code for state initialization */
	/* over voltage state monitor */
	ov1.number = 1;
	ov1.level = LEVEL_STATE;
	ov1.valid_threshold = 5;
	ov1.recover_threshold = 4;
	ov1.status.bits.valid = 0;
	ov1.status.bits.masked = 0;
	ov1.status.bits.check_by = PERIOD_CHECK;
	ov1.status.bits.recoverable = 1;
	ov1.status.bits.check_unmasked_only = 0;
	ov1.status.bits.type = OVER_THRESHOLD_VALID;
	ov1._cnt_max = 10.0;
	ov1._step_valid = 2.0;
	ov1._step_recover = 1.0;

	/* over voltage state monitor */
	ov2.number = 2;
	ov2.level = LEVEL_STATE;
	ov2.valid_threshold = 5;
	ov2.recover_threshold = 4;
	ov2.status.bits.valid = 0;
	ov2.status.bits.masked = 1;
	ov2.status.bits.check_by = PERIOD_CHECK;
	ov2.status.bits.recoverable = 1;
	ov2.status.bits.check_unmasked_only = 0;
	ov2.status.bits.type = OVER_THRESHOLD_VALID;
	ov2._cnt_max = 10.0;
	ov2._step_valid = 2.0;
	ov2._step_recover = 1.0;

	/* over voltage state monitor */
	ov3.number = 3;
	ov3.level = LEVEL_STATE;
	ov3.valid_threshold = 5;
	ov3.recover_threshold = 4;
	ov3.status.bits.valid = 0;
	ov3.status.bits.masked = 0;
	ov3.status.bits.check_by = PERIOD_CHECK;
	ov3.status.bits.recoverable = 0;
	ov3.status.bits.check_unmasked_only = 0;
	ov3.status.bits.type = OVER_THRESHOLD_VALID;
	ov3._cnt_max = 10.0;
	ov3._step_valid = 2.0;
	ov3._step_recover = 1.0;

	/* under voltage state monitor */
	uv1.number = 4;
	uv1.level = LEVEL_ALARM;
	uv1.valid_threshold = -5;
	uv1.recover_threshold = -4;
	uv1.status.bits.valid = 0;
	uv1.status.bits.masked = 0;
	uv1.status.bits.check_by = COUNT_CHECK;
	uv1.status.bits.recoverable = 1;
	uv1.status.bits.check_unmasked_only = 0;
	uv1.status.bits.type = UNDER_THRESHOLD_VALID;
	uv1._cnt_max = 6.0;
	uv1._step_valid = 3.0;
	uv1._step_recover = 2.0;

	/* under voltage state monitor */
	uv2.number = 5;
	uv2.level = LEVEL_ALARM;
	uv2.valid_threshold = -5;
	uv2.recover_threshold = -4;
	uv2.status.bits.valid = 0;
	uv2.status.bits.masked = 1;
	uv2.status.bits.check_by = COUNT_CHECK;
	uv2.status.bits.recoverable = 1;
	uv2.status.bits.check_unmasked_only = 1;
	uv2.status.bits.type = UNDER_THRESHOLD_VALID;
	uv2._cnt_max = 6.0;
	uv2._step_valid = 3.0;
	uv2._step_recover = 2.0;

}