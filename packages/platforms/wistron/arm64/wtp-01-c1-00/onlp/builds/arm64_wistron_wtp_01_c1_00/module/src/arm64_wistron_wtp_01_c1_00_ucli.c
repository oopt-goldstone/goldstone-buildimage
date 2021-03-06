/**************************************************************************//**
 *
 *
 *
 *****************************************************************************/
#include <arm64_wistron_wtp_01_c1_00/arm64_wistron_wtp_01_c1_00_config.h>

#if ARM64_WISTRON_WTP_01_C1_00_CONFIG_INCLUDE_UCLI == 1

#include <uCli/ucli.h>
#include <uCli/ucli_argparse.h>
#include <uCli/ucli_handler_macros.h>

static ucli_status_t
arm64_wistron_wtp_01_c1_00_ucli_ucli__config__(ucli_context_t* uc)
{
    UCLI_HANDLER_MACRO_MODULE_CONFIG(arm64_wistron_wtp_01_c1_00)
}

/* <auto.ucli.handlers.start> */
/* <auto.ucli.handlers.end> */

static ucli_module_t
arm64_wistron_wtp_01_c1_00_ucli_module__ =
    {
        "arm64_wistron_wtp_01_c1_00_ucli",
        NULL,
        arm64_wistron_wtp_01_c1_00_ucli_ucli_handlers__,
        NULL,
        NULL,
    };

ucli_node_t*
arm64_wistron_wtp_01_c1_00_ucli_node_create(void)
{
    ucli_node_t* n;
    ucli_module_init(&arm64_wistron_wtp_01_c1_00_ucli_module__);
    n = ucli_node_create("arm64_wistron_wtp_01_c1_00", NULL, &arm64_wistron_wtp_01_c1_00_ucli_module__);
    ucli_node_subnode_add(n, ucli_module_log_node_create("arm64_wistron_wtp_01_c1_00"));
    return n;
}

#else
void*
arm64_wistron_wtp_01_c1_00_ucli_node_create(void)
{
    return NULL;
}
#endif

