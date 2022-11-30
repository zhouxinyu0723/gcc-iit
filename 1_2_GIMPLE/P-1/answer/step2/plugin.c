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
static unsigned int intra_dump_vars (void);
static void gather_local_variables (void);
static void gather_global_variables (void);

/*-----------------------------------------------------------------------------
 *  Structure of the pass we want to insert, identical to a regular ipa pass
 *-----------------------------------------------------------------------------*/
class my_gimple_opt_pass : public simple_ipa_opt_pass // CHANGE 1
{

public:
    pass_data my_pass_data;
    my_gimple_opt_pass(const pass_data& data, gcc::context *ctxt)
        : simple_ipa_opt_pass(data, ctxt)
    {
      my_pass_data = data;
    }

    virtual my_gimple_opt_pass* clone() override
    {
        // We do not clone ourselves
        
        return new my_gimple_opt_pass(this->my_pass_data, g);
    }

    virtual unsigned int execute(function *)
    {
        //std::cout << "EXECUTE\n";
        intra_dump_vars ();
        return 1;
    }

};

pass_data my_pass_data={
    SIMPLE_IPA_PASS,                                      
    "dump-vars",           	        /*  name */
    OPTGROUP_NONE, 
    TV_INTEGRATION,                	/*  tv_id */    
    0,                            	/*  properties required */    
    0,                            	/*  properties provided */    
    0,                            	/*  properties destroyed */   
    0,                            	/*  todo_flags start */       
    0                             	/*  todo_flags end */         
};
my_gimple_opt_pass pass_plugin(my_pass_data, g);

/*-----------------------------------------------------------------------------
 *  This structure provides the information about inserting the pass in the
 *  pass manager. 
 *-----------------------------------------------------------------------------*/
struct register_pass_info pass_info = {
  &(pass_plugin),            /* Address of new pass, here, the 'struct
                                     opt_pass' field of 'gimple_opt_pass'
                                     defined above */
  "pta",                          /* Name of the reference pass for hooking up
                                     the new pass.   ??? */    // CHANGE 2
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
static unsigned int intra_dump_vars (void)
{
	basic_block bb;
	gimple_stmt_iterator gsi;

	if (!dump_file)
		return 1;

	/* function call to print the local variables of a function*/     // CHANGE 3
  cgraph_node* node = symtab->first_defined_function ();
                /* Iterate over all the nodes in the cgraph */
  for (; node; node = symtab->next_defined_function(node))
  {
      /* Nodes without a body, and clone nodes are not interesting. */
          if (!gimple_has_body_p (node->decl) || node->clone_of)
                  continue;

          push_cfun (DECL_STRUCT_FUNCTION (node->decl));

          /* function call to print the local variables of a function*/
          gather_local_variables ();

          pop_cfun ();
  }

	/* function call to print the global variables*/
	gather_global_variables (); 

	return 0;
}

/* Function to print local variables */
static void gather_local_variables () 
{
	tree list;
	unsigned int u;

	fprintf(dump_file,"Local variables :\n");
	FOR_EACH_LOCAL_DECL (cfun, u, list)
	{
  		if (!DECL_ARTIFICIAL (list))
			fprintf(dump_file, "%s\n", get_name (list));
		list = TREE_CHAIN (list);
	}
}

/* Function to print global variables */
static void gather_global_variables ()
{
  // symbol_table symtab_ = *symtab;
	varpool_node *node = symtab->first_variable ();
	
	if (!dump_file)
		return;

	fprintf(dump_file,"Global variables :\n");
	for (; node; node = symtab->next_defined_variable (node))
	{
		tree var = node->decl;
		if (!DECL_ARTIFICIAL(var))
			fprintf(dump_file, "%s\n", get_name (var));
	}
}

