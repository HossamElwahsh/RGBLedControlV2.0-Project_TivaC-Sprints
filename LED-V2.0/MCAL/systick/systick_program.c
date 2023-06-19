/**
 * @file    :   led_program.c
 * @author  :   Hossam Elwahsh - https://github.com/HossamElwahsh
 * @brief   :   Program File contains all SYSTICK functions' implementation
 * @version :   0.1
 * @date    :   2023-06-17
 *
 * @copyright Copyright (c) 2023
 */

#include "systick_interface.h"
#include "systick_private.h"
#include "bit_math.h"

static boolean gl_systick_initialized = FALSE;
static en_systick_clk_src_t gl_en_systick_clk_src;

/**
 * @brief                       : Initializes SYSTICK driver
 *
 * @param ptr_st_systick_cfg        : Pointer to Systick Configuration
 *
 * @return  ST_OK              :   In case of Successful Operation
 *          ST_INVALID_ARGS    :   In case of Failed Operation (Invalid Arguments Given)
 *          ST_INVALID_CONFIG  :   In case of Failed Operation (Invalid Systick Config Given)
 */
en_systick_error_t systick_init(st_systick_cfg_t * ptr_st_systick_cfg)
{
    en_systick_error_t en_systick_error_retval = ST_OK;

    // args/cfg check
    if(NULL_PTR == ptr_st_systick_cfg)
    {
        en_systick_error_retval = ST_INVALID_ARGS;
    }
    else
    {
        // cfg check
        if(
                (ptr_st_systick_cfg->bool_systick_int_enabled > TRUE) ||
                (ptr_st_systick_cfg->en_systick_clk_src >= CLK_SRC_TOTAL)
                )
        {
            en_systick_error_retval = ST_INVALID_CONFIG;
        }
        else
        {
            // enable/disable interrupts
            // set clock source
            WRITE_BIT(STCTRL, STCTRL_INT_ENABLE, ptr_st_systick_cfg->bool_systick_int_enabled);
            WRITE_BIT(STCTRL, STCTRL_CLK_SRC, ptr_st_systick_cfg->en_systick_clk_src);

            // update globals
            gl_en_systick_clk_src = ptr_st_systick_cfg->en_systick_clk_src;
            gl_systick_initialized = TRUE;
        }
    }

    return en_systick_error_retval;
}

/**
 * @brief                      : Initiates a sync blocking delay
 *
 * @param uint32_ms_delay      : Desired delay in ms
 *
 * @return  ST_OK              :   In case of Successful Operation
 *          ST_INVALID_ARGS    :   In case of Failed Operation (Invalid Arguments Given)
 *          ST_INVALID_CONFIG  :   In case of Failed Operation (Invalid Systick Config Given)
 */
en_systick_error_t systick_ms_delay(uint32_t_ uint32_ms_delay)
{
    en_systick_error_t en_systick_error_retval = ST_OK;

        if(FALSE == gl_systick_initialized)
        {
            en_systick_error_retval = ST_INVALID_CONFIG;
        }
        else
        {
            // a. calculate number of clock cycles for desired delay
            float fl_ms_per_cycle = 0.0f;
            uint32_t_ fl_no_of_cycles_req = 0;
            if(CLK_SRC_PIOSC == gl_en_systick_clk_src)
            {
                fl_ms_per_cycle = 1000.0f/((float)((PIOSC_MHZ/4.0f) * 1000000)); // PIOSC / 4
                fl_no_of_cycles_req = ((float)uint32_ms_delay/fl_ms_per_cycle)+1;
            }
            else if(CLK_SRC_SYS_CLK == gl_en_systick_clk_src)
            {
                fl_ms_per_cycle = 1000.0f/((float)(SYS_CLOCK_MHZ * 1000000.0f));
                fl_no_of_cycles_req = ((float)uint32_ms_delay/fl_ms_per_cycle)+1;
            }

            // args check
            if(
                    (fl_no_of_cycles_req > STLOAD_MAX_VALUE) ||
                    (fl_no_of_cycles_req < STLOAD_MIN_VALUE)
                    )
            {
                en_systick_error_retval = ST_INVALID_ARGS;
            }

            // 1. Program the value in the STRELOAD Register
            /* todo Software should not rely on the value of a reserved bit. To provide
               todo compatibility with future products, the value of a reserved bit should be
               todo preserved across a read-modify-write operation. */
            STRELOAD = fl_no_of_cycles_req;

            // 2. Clear STCURRENT register by writing any value (preferably a zero)
            STCURRENT = ZERO;

            // 3. Configure the STCTRL register for the required operation
            SET_BIT(STCTRL, STCTRL_ENABLE); // start timer
            while (GET_BIT(STCTRL, STCTRL_COUNT) == 0);
            CLR_BIT(STCTRL, STCTRL_ENABLE); // stop timer
        }

    return en_systick_error_retval;
}