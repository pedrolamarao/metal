.att_syntax

//! extern "C" std::uint32_t volatile _interrupted

.extern interrupted

//! x86 interrupt service routine

.global __interrupt_service_routine
.type   __interrupt_service_routine, STT_FUNC
__interrupt_service_routine:
    incl interrupted
	iret
