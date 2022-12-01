/*-----------------------------------------------------------------------------
 *  "gcc-plugin.h" must be the FIRST file to be included 
 *-----------------------------------------------------------------------------*/
#include "gcc-plugin.h"
#include "config.h"
#include <stdio.h>
#include "system.h"
#include "coretypes.h"
#include "tm.h"
#include "tm_p.h"
#include "diagnostic.h"
#include "tree-flow.h"
#include "tree-pass.h"
#include "toplev.h"
#include "gimple.h"

/*-----------------------------------------------------------------------------
 *  Each plugin MUST define this global int to assert compatibility with GPL; 
 *  else the compiler throws a fatal error 
 *-----------------------------------------------------------------------------*/
int plugin_is_GPL_compatible;  

/*function declarations*/
static unsigned int gimple_analysis (void);
static void analyze_gimple_statement (gimple);
static void identify_operator (gimple);
static void call_arguments (gimple);

/*-----------------------------------------------------------------------------
 *  Structure of the pass we want to insert, identical to a regular ipa pass
 *-----------------------------------------------------------------------------*/
struct gimple_opt_pass pass_plugin = {
{
        GIMPLE_PASS,
        "gimple_analysis",            /*  name */
        NULL,                         /*  gate */
        gimple_analysis,              /*  execute */
        NULL,                         /*  sub */
        NULL,                         /*  next */
        0,                            /*  static pass number */
        TV_INTEGRATION,               /*  tv_id */
        0,                            /*  properties required */
        0,                            /*  properties provided */
        0,                            /*  properties destroyed */
        0,                            /*  todo_flags start */
        0                             /*  todo_flags end */
        }
};


/*-----------------------------------------------------------------------------
 *  This structure provides the information about inserting the pass in the
 *  pass manager. 
 *-----------------------------------------------------------------------------*/
struct register_pass_info pass_info = {
  &(pass_plugin.pass),                  /* Address of new pass, here, the 'struct
                                        opt_pass' field of 'gimple_opt_pass'
                                        defined above */
        "cfg",                          /* Name of the reference pass for hooking up
                                        the new pass.   ??? */
        0,                              /* Insert the pass at the specified instance
                                        number of the reference pass. Do it for
                                        every instance if it is 0. */
        PASS_POS_INSERT_AFTER           /* how to insert the new pass: before,
                                        after, or replace. Here we are inserting
                                        a pass names 'plug' after the pass named
                                        'pta' */
};

/*-----------------------------------------------------------------------------
 *  plugin_init is the first function to be called after the plugin is loaded
 *-----------------------------------------------------------------------------*/
  int
plugin_init(struct plugin_name_args *plugin_info,
    struct plugin_gcc_version *version)
{

        /*-----------------------------------------------------------------------------
        * Plugins are activiated using this callback 
        *-----------------------------------------------------------------------------*/
        register_callback (
        plugin_info->base_name,     /* char *name: Plugin name, could be any
                                     name. plugin_info->base_name gives this
                                     filename */
        PLUGIN_PASS_MANAGER_SETUP,  /* int event: The event code. Here, setting
                                     up a new pass */
        NULL,                       /* The function that handles event */
        &pass_info);                /* plugin specific data */

        return 0;
}

/* Execute function */
static unsigned int gimple_analysis (void)
{
        basic_block bb;
        gimple_stmt_iterator gsi;

        /* Iterating over each basic block of a function */
        FOR_EACH_BB_FN (bb, cfun)
        {
                /*Iterating over each gimple statement in a basic block*/
                for (gsi = gsi_start_bb(bb); !gsi_end_p(gsi); gsi_next (&gsi))
                analyze_gimple_statement(gsi_stmt(gsi));
        }

        return 0;
}

static void analyze_gimple_statement (gimple stmt)
{
        if (!dump_file)
                return;

        if (gimple_code (stmt) == GIMPLE_COND)
        {
                fprintf(dump_file, "\nConditional statment : ");
                print_gimple_stmt (dump_file, stmt, 0, 0);
        }

        if (gimple_code (stmt) == GIMPLE_CALL)
        {
                fprintf(dump_file, "\nCall statment : ");
                print_gimple_stmt (dump_file, stmt, 0, 0);

                call_arguments (stmt);
        }

        if (gimple_code (stmt) == GIMPLE_ASSIGN)
        {       
                fprintf(dump_file, "\nAssignment statment : ");
                print_gimple_stmt (dump_file, stmt, 0, 0);

                identify_operator (stmt);
        }
}

static void identify_operator (gimple stmt)
{
        /* Get the code of expression computed on RHS */
        enum tree_code code = gimple_assign_rhs_code (stmt);

        /* Determine the class of the expression on RHS */
        switch (get_gimple_rhs_class (code))
        {
                /* Expression containing unary operator */
                case GIMPLE_UNARY_RHS:
                        fprintf (dump_file, "Unary operator\n");
                break;
                
                /* Expression containing binary operator */
                case GIMPLE_BINARY_RHS:
                        fprintf (dump_file, "Binary operator\n");
                break;

                case GIMPLE_SINGLE_RHS:
                        fprintf (dump_file, "No operator\n");
        }
}

static void call_arguments (gimple stmt)
{
        /* Iterate over all the arguments in the call statement.
        API gimple_call_num_args gives the number of arguments passed to 
        the call statement */
        int i;
        fprintf (dump_file, "Call arguments : ");
        for (i = 0; i < gimple_call_num_args (stmt); i++)
        {
                /* API gimple_call_arg would return the argument at position i */
                tree arg = gimple_call_arg (stmt, i);
                fprintf (dump_file, "  %s", get_name (arg));
        }
}
