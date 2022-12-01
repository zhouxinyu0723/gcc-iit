/*-----------------------------------------------------------------------------
 *  "gcc-plugin.h" must be the FIRST file to be included
 *-----------------------------------------------------------------------------*/
#include "gcc-plugin.h"
#include "context.h"
#include "config.h"
#include <stdio.h>
#include "system.h"
#include "coretypes.h"
#include "tm.h"
#include "tm_p.h"
#include "diagnostic.h"
//#include "tree-flow.h"
#include "tree-pass.h"
#include "tree.h"
#include "gimple.h"
#include "gimple-iterator.h"
#include "cgraph.h"
#include "toplev.h"
#include "optinfo.h"
#include "dumpfile.h"
#include "pass_manager.h"

/*-----------------------------------------------------------------------------
 *  Each plugin MUST define this global int to assert compatibility with GPL;
 *  else the compiler throws a fatal error
 *-----------------------------------------------------------------------------*/
int plugin_is_GPL_compatible;

/*function declarations*/
static unsigned int gimple_analysis(void);

/*-----------------------------------------------------------------------------
 *  Structure of the pass we want to insert, identical to a regular ipa pass
 *-----------------------------------------------------------------------------*/
class my_gimple_opt_pass : public gimple_opt_pass
{

public:
        pass_data my_pass_data;
        my_gimple_opt_pass(const pass_data &data, gcc::context *ctxt)
            : gimple_opt_pass(data, ctxt)
        {
                my_pass_data = data;
        }

        virtual my_gimple_opt_pass *clone() override
        {
                // We do not clone ourselves. But no clone will produce an error
                return new my_gimple_opt_pass(this->my_pass_data, g);
        }

        virtual unsigned int execute(function *)
        {
                // std::cout << "EXECUTE\n";
                gimple_analysis();
                return 0;
        }
};

pass_data my_pass_data = {
    GIMPLE_PASS,                   // good
    "gimple_analysis", /*  name */ // good
    OPTGROUP_NONE,
    TV_INTEGRATION, /*  tv_id */   // good
    0, /*  properties required */  // good
    0, /*  properties provided */  // good
    0, /*  properties destroyed */ // good
    0, /*  todo_flags start */     // good
    0 /*  todo_flags end */        // good
};
my_gimple_opt_pass pass_plugin(my_pass_data, g);

/*-----------------------------------------------------------------------------
 *  This structure provides the information about inserting the pass in the
 *  pass manager.
 *-----------------------------------------------------------------------------*/
struct register_pass_info pass_info = {
    &pass_plugin,  /* Address of new pass, here, the 'struct
                          opt_pass' field of 'gimple_opt_pass'
                          defined above */
    "cfg",                /* Name of the reference pass for hooking up
                          the new pass.   ??? */
    0,                    /* Insert the pass at the specified instance
                          number of the reference pass. Do it for
                          every instance if it is 0. */
    PASS_POS_INSERT_AFTER /* how to insert the new pass: before,
                          after, or replace. Here we are inserting
                          a pass names 'plug' after the pass named
                          'pta' */
};

/*-----------------------------------------------------------------------------
 *  plugin_init is the first function to be called after the plugin is loaded
 *-----------------------------------------------------------------------------*/
int plugin_init(struct plugin_name_args *plugin_info,
                struct plugin_gcc_version *version)
{

        /*-----------------------------------------------------------------------------
         * Plugins are activiated using this callback
         *-----------------------------------------------------------------------------*/
        register_callback(
            plugin_info->base_name,    /* char *name: Plugin name, could be any
                                        name. plugin_info->base_name gives this
                                        filename */
            PLUGIN_PASS_MANAGER_SETUP, /* int event: The event code. Here, setting
                                        up a new pass */
            NULL,                      /* The function that handles event */
            &pass_info);               /* plugin specific data */

        return 0;
}

/* Execute function */
static unsigned int gimple_analysis(void)
{
        basic_block bb;
        gimple_stmt_iterator gsi;

        if (!dump_file)
                return 1;
        fprintf(dump_file, "Gimple Code :\n");

        /* Iterating over each basic block of a function */
        FOR_EACH_BB_FN(bb, cfun)
        {
                fprintf(dump_file, "bb %d\n", bb->index);
                /*Iterating over each gimple statement in a basic block*/
                for (gsi = gsi_start_bb(bb); !gsi_end_p(gsi); gsi_next(&gsi))
                {
                        /* Now you can access GIMPLE statements in each basic block.
                           Write your code here. */
                        /* ------- question 1 -------*/
                        fprintf(dump_file, "%s     ", gimple_code_name [gimple_code (gsi_stmt (gsi))]);
                        /* ----- question 1 end------*/
                        /* ------- question 2 -------*/
                        if (gimple_code (gsi_stmt (gsi)) == GIMPLE_ASSIGN){
                                 const char* RHS_CLASS_NAME[5] = {"GIMPLE_INVALID_RHS",	
                                "GIMPLE_TERNARY_RHS",	/* The expression is a ternary operation.  */
                                "GIMPLE_BINARY_RHS",	/* The expression is a binary operation.  */
                                "GIMPLE_UNARY_RHS",	/* The expression is a unary operation.  */
                                "GIMPLE_SINGLE_RHS"};	/* The expression is a single object (an SSA */
                                fprintf(dump_file, "%s     ", RHS_CLASS_NAME[gimple_assign_rhs_class  (gsi_stmt (gsi))]);
                        }
                        /* ----- question 2 end------*/
                        /* ------- question 3 -------*/ 
                        if (gimple_code (gsi_stmt (gsi)) == GIMPLE_CALL){
                                unsigned int num = gimple_call_num_args(gsi_stmt (gsi));
                                for (unsigned int i=0;i<num;i++){
                                        fprintf(dump_file, " %s     ", get_name(gimple_call_arg(gsi_stmt (gsi), i)));
                                }
                        }
                        /* ----- question 3 end------*/
                        fprintf(dump_file, "\n");
                        
                }
        }

        return 0;
}
