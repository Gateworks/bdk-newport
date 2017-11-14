#include <bdk.h>

/* Platform: RBD8030
 * QSGMII-VSC7421-02 Switch and RGX-VSC8531 Phy has RESET_L connected to GPIO37 of CN8030
 * Assert the RESET_L pin to High by gpio func will boot the VSC7421 switch and RGX Phy in BDK level.
 * This code part also captured in app/init/app.c also and 
 * disabled for enabling the reset_l if not in boot code.
 */

int bdk_if_sw_vitesse_setup(bdk_node_t node)
{
    //8030RBD: VSC7421 Switch RESET De-Assert: GPIO37
    //int bdk_gpio_initialize(bdk_node_t node, int gpio, int is_output, int output_value)
    bdk_gpio_initialize(node, 37, 1, 0);
    //100ms Assert
    bdk_wait_usec(100000);
    bdk_gpio_initialize(node, 37, 1, 1);
    //wait for min 15ms
    bdk_wait_usec(20);

    return 0;
}


