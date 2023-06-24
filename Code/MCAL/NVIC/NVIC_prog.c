#include "NVIC_private.h"
#include "NVIC_interface.h"

#include "../../STD_LIBRARIES/STD_TYPES.h"
#include "../../STD_LIBRARIES/bit_math.h"



nvic_enu_return_state_t nvic_EnablePeripheral(nvic_enu_interupt_index_t copy_enu_interupt_index) {
    nvic_enu_return_state_t return_value = NVIC_NOT_OK;
    
    if (copy_enu_interupt_index <= 31) {
        SET_BIT(HWREG32((NVIC_BASE_ADDRESS + NVIC_EN0)), copy_enu_interupt_index);
    } else if (copy_enu_interupt_index <= 63) {
        SET_BIT(HWREG32((NVIC_BASE_ADDRESS + NVIC_EN1)), copy_enu_interupt_index);
    } else if (copy_enu_interupt_index <= 95) {
        SET_BIT(HWREG32((NVIC_BASE_ADDRESS + NVIC_EN2)), copy_enu_interupt_index);
    } else if (copy_enu_interupt_index <= 127) {
        SET_BIT(HWREG32((NVIC_BASE_ADDRESS + NVIC_EN3)), copy_enu_interupt_index);
    } else if (copy_enu_interupt_index < NVIC_MAX_INVALID_INT) {
        SET_BIT(HWREG32((NVIC_BASE_ADDRESS + NVIC_EN4)), copy_enu_interupt_index);
    } else {
        // Handle the case when the interrupt index is invalid or out of range
    }
    
    return return_value;
}


/**
 * Disables the specified peripheral interrupt in the NVIC.
 *
 * @param copy_enu_interupt_index The interrupt index to be disabled.
 * @return Return state indicating the success or failure of the operation.
 */
nvic_enu_return_state_t nvic_DisablePeripheral(nvic_enu_interupt_index_t copy_enu_interupt_index)
{
	nvic_enu_return_state_t return_value = NVIC_NOT_OK;

	if (copy_enu_interupt_index <= 31)
	{
		SET_BIT(HWREG32((NVIC_BASE_ADDRESS + NVIC_DIS0)), copy_enu_interupt_index);
	}
	else if (copy_enu_interupt_index <= 63)
	{
		SET_BIT(HWREG32((NVIC_BASE_ADDRESS + NVIC_DIS1)), copy_enu_interupt_index);
	}
	else if (copy_enu_interupt_index <= 95)
	{
		SET_BIT(HWREG32((NVIC_BASE_ADDRESS + NVIC_DIS2)), copy_enu_interupt_index);
	}
	else if (copy_enu_interupt_index <= 127)
	{
		SET_BIT(HWREG32((NVIC_BASE_ADDRESS + NVIC_DIS3)), copy_enu_interupt_index);
	}
	else if (copy_enu_interupt_index < NVIC_MAX_INVALID_INT)
	{
		SET_BIT(HWREG32((NVIC_BASE_ADDRESS + NVIC_DIS4)), copy_enu_interupt_index);
	}
	else
	{
		// Invalid interrupt index
	}

	return return_value;
}
