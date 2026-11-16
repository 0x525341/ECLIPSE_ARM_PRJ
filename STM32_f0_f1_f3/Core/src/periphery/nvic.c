#include "nvic.h"

void nvic_enable_irq(IRQn_Type irq)
{
	NVIC_EnableIRQ(irq);
}

void nvic_disable_irq(IRQn_Type irq)
{
	NVIC_DisableIRQ(irq);
}

void nvic_clear_pending_irq(IRQn_Type irq)
{
	NVIC_ClearPendingIRQ(irq);
}

void nvic_disable_irqs(void)
{
	__disable_irq();
}

void nvic_enable_irqs(void)
{
	__enable_irq();
}

void nvic_set_priority_grouping(uint32_t group)
{
	NVIC_SetPriorityGrouping(group);
}

void nvic_set_priority(IRQn_Type irq, uint32_t priority)
{
	  NVIC_SetPriority(irq, NVIC_EncodePriority(NVIC_GetPriorityGrouping(),priority, 0));
}
