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

/*-----------------------------------------------------------------------------
 *  Each plugin MUST define this global int to assert compatibility with GPL; 
 *  else the compiler throws a fatal error 
 *-----------------------------------------------------------------------------*/
int plugin_is_GPL_compatible;  

/*function declarations*/
static unsigned int inter_gimple_manipulation (void);
static void gather_local_variables (void);
static void gather_global_variables (void);

/*-----------------------------------------------------------------------------
 *  Structure of the pass we want to insert, identical to a regular ipa pass
 *-----------------------------------------------------------------------------*/
struct simple_ipa_opt_pass pass_plugin = {
  {
    SIMPLE_IPA_PASS,
    "dump-vars",                          /*  name */
    NULL,                                 /*  gate */
    inter_gimple_manipulation,            /*  execute */
    NULL,                                 /*  sub */
    NULL,                                 /*  next */
    0,                                    /*  static pass number */
    TV_INTEGRATION,                        /*  tv_id */
    0,                                    /*  properties required */
    0,                                    /*  properties provided */
    0,                                    /*  properties destroyed */
    0,                                    /*  todo_flags start */
    0                                     /*  todo_flags end */
  }
};


/*-----------------------------------------------------------------------------
 *  This structure provides the information about inserting the pass in the
 *  pass manager. 
 *-----------------------------------------------------------------------------*/
struct register_pass_info pass_info = {
  &(pass_plugin.pass),            /* Address of new pass, here, the 'struct
                                     opt_pass' field of 'gimple_opt_pass'
                                     defined above */
  "pta",                          /* Name of the reference pass for hooking up
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
static unsigned int inter_gimple_manipulation (void)
{
	basic_block bb;
	gimple_stmt_iterator gsi;
	struct cgraph_node *node;
        
	/* function call to print the global variables*/
	gather_global_variables (); 

	/* Iterating over each basic block of a function */        
	for (node = cgraph_nodes; node; node = node->next)
	{
		/* Nodes without a body, and clone nodes are not interesting. */
	        if (!gimple_has_body_p (node->decl) || node->clone_of)
			continue;

		push_cfun (DECL_STRUCT_FUNCTION (node->decl));

		fprintf (dump_file,"\n\n------ Function : %s ------\n",cgraph_node_name(node));
		/* function call to print the local variables of a function*/
		gather_local_variables ();
  
                pop_cfun ();
 	}
	return 0;
}

/* Print local variables */
static void gather_local_variables () 
{
	unsigned int u;
	tree list = cfun->local_decls;

	fprintf(dump_file,"\nLocal variables :\n");                                      
	FOR_EACH_LOCAL_DECL (cfun, u, list)                                                                    
	{       
		if (!DECL_ARTIFICIAL (list) && dump_file)                               
	  	      fprintf(dump_file, "%s\n", get_name (list));
		list = TREE_CHAIN (list);                                               
	}                                                          
}

/* Print global variables */
static void gather_global_variables ()
{
	struct varpool_node *node;
       
	fprintf(dump_file,"\nGlobal variables :\n");
	for (node = varpool_nodes; node; node = node->next)
	{
    	    tree var = node->decl;
            if (!DECL_ARTIFICIAL(var))
		    fprintf(dump_file, "%s\n", get_name (var));
  	}
}
