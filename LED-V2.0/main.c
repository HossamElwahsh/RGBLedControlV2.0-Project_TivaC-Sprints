/**
 ** @file      main.c
 ** @brief     
 ** @author    
 ** @date      June 16, 2023
 ** @version   0.1
 */

/*- INCLUDES
----------------------------------------------*/
#include "app.h"

int main(void)
{
    en_app_error_t en_app_error = APP_OK;

    // initialize app
    en_app_error = app_init();

    if(APP_OK == en_app_error)
    {
        app_start();
    }
    else
    {
        // Do Nothing
        while(1)
        {
            // Do Nothing
        }
    }


	return 0;
}
