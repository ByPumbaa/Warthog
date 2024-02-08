/** @file cmdline.h
 *  @brief The header file for the command line option parser
 *  generated by GNU Gengetopt version 2.23
 *  http://www.gnu.org/software/gengetopt.
 *  DO NOT modify this file, since it can be overwritten
 *  @author GNU Gengetopt */

#ifndef CMDLINE_H
#define CMDLINE_H

/* If we use autoconf.  */
#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <stdio.h> /* for FILE */

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#ifndef CMDLINE_PARSER_PACKAGE
/** @brief the program name (used for printing errors) */
#define CMDLINE_PARSER_PACKAGE "wart-node"
#endif

#ifndef CMDLINE_PARSER_PACKAGE_NAME
/** @brief the complete program name (used for help and version) */
#define CMDLINE_PARSER_PACKAGE_NAME "wart-node"
#endif

#ifndef CMDLINE_PARSER_VERSION
/** @brief the program version */
#define CMDLINE_PARSER_VERSION VERSION
#endif

/** @brief Where the command line options are stored */
struct gengetopt_args_info
{
  const char *help_help; /**< @brief Print help and exit help description.  */
  const char *detailed_help_help; /**< @brief Print help, including all details and hidden options, and exit help description.  */
  const char *version_help; /**< @brief Print version and exit help description.  */
  char * bind_arg;	/**< @brief Socket to listen on, defaults to \"0.0.0.0:9186\" for main net and \"0.0.0.0:9286\" for test net.  */
  char * bind_orig;	/**< @brief Socket to listen on, defaults to \"0.0.0.0:9186\" for main net and \"0.0.0.0:9286\" for test net original value given at command line.  */
  const char *bind_help; /**< @brief Socket to listen on, defaults to \"0.0.0.0:9186\" for main net and \"0.0.0.0:9286\" for test net help description.  */
  char * connect_arg;	/**< @brief Specify peer list.  */
  char * connect_orig;	/**< @brief Specify peer list original value given at command line.  */
  const char *connect_help; /**< @brief Specify peer list help description.  */
  const char *isolated_help; /**< @brief Do not allow peers (for testing purposes, do not use in production) help description.  */
  const char *testnet_help; /**< @brief Enable testnet help description.  */
  char * chain_db_arg;	/**< @brief specify chain data file.  */
  char * chain_db_orig;	/**< @brief specify chain data file original value given at command line.  */
  const char *chain_db_help; /**< @brief specify chain data file help description.  */
  char * peers_db_arg;	/**< @brief specify data file.  */
  char * peers_db_orig;	/**< @brief specify data file original value given at command line.  */
  const char *peers_db_help; /**< @brief specify data file help description.  */
  const char *debug_help; /**< @brief Enable debug messages help description.  */
  char * rpc_arg;	/**< @brief JSON RPC endpoint socket, defaults to \"127.0.0.1:3000\" for main net and \"127.0.0.1:3100\" for test net.  */
  char * rpc_orig;	/**< @brief JSON RPC endpoint socket, defaults to \"127.0.0.1:3000\" for main net and \"127.0.0.1:3100\" for test net original value given at command line.  */
  const char *rpc_help; /**< @brief JSON RPC endpoint socket, defaults to \"127.0.0.1:3000\" for main net and \"127.0.0.1:3100\" for test net help description.  */
  char * publicrpc_arg;	/**< @brief Public JSON RPC endpoint socket, disabled by default.  */
  char * publicrpc_orig;	/**< @brief Public JSON RPC endpoint socket, disabled by default original value given at command line.  */
  const char *publicrpc_help; /**< @brief Public JSON RPC endpoint socket, disabled by default help description.  */
  const char *enable_public_help; /**< @brief Shorthand for --publicrpc=0.0.0.0:3001 help description.  */
  char * config_arg;	/**< @brief Configuration file, default is \"config.toml\", in testnet \"testnet_chain.db3\".  */
  char * config_orig;	/**< @brief Configuration file, default is \"config.toml\", in testnet \"testnet_chain.db3\" original value given at command line.  */
  const char *config_help; /**< @brief Configuration file, default is \"config.toml\", in testnet \"testnet_chain.db3\" help description.  */
  const char *test_help; /**< @brief test the configuration file (check for correct syntax) help description.  */
  const char *dump_config_help; /**< @brief dump the current configuration to stdout help description.  */
  
  unsigned int help_given ;	/**< @brief Whether help was given.  */
  unsigned int detailed_help_given ;	/**< @brief Whether detailed-help was given.  */
  unsigned int version_given ;	/**< @brief Whether version was given.  */
  unsigned int bind_given ;	/**< @brief Whether bind was given.  */
  unsigned int connect_given ;	/**< @brief Whether connect was given.  */
  unsigned int isolated_given ;	/**< @brief Whether isolated was given.  */
  unsigned int testnet_given ;	/**< @brief Whether testnet was given.  */
  unsigned int chain_db_given ;	/**< @brief Whether chain-db was given.  */
  unsigned int peers_db_given ;	/**< @brief Whether peers-db was given.  */
  unsigned int debug_given ;	/**< @brief Whether debug was given.  */
  unsigned int rpc_given ;	/**< @brief Whether rpc was given.  */
  unsigned int publicrpc_given ;	/**< @brief Whether publicrpc was given.  */
  unsigned int enable_public_given ;	/**< @brief Whether enable-public was given.  */
  unsigned int config_given ;	/**< @brief Whether config was given.  */
  unsigned int test_given ;	/**< @brief Whether test was given.  */
  unsigned int dump_config_given ;	/**< @brief Whether dump-config was given.  */

} ;

/** @brief The additional parameters to pass to parser functions */
struct cmdline_parser_params
{
  int override; /**< @brief whether to override possibly already present options (default 0) */
  int initialize; /**< @brief whether to initialize the option structure gengetopt_args_info (default 1) */
  int check_required; /**< @brief whether to check that all required options were provided (default 1) */
  int check_ambiguity; /**< @brief whether to check for options already specified in the option structure gengetopt_args_info (default 0) */
  int print_errors; /**< @brief whether getopt_long should print an error message for a bad option (default 1) */
} ;

/** @brief the purpose string of the program */
extern const char *gengetopt_args_info_purpose;
/** @brief the usage string of the program */
extern const char *gengetopt_args_info_usage;
/** @brief the description string of the program */
extern const char *gengetopt_args_info_description;
/** @brief all the lines making the help output */
extern const char *gengetopt_args_info_help[];
/** @brief all the lines making the detailed help output (including hidden options and details) */
extern const char *gengetopt_args_info_detailed_help[];

/**
 * The command line parser
 * @param argc the number of command line options
 * @param argv the command line options
 * @param args_info the structure where option information will be stored
 * @return 0 if everything went fine, NON 0 if an error took place
 */
int cmdline_parser (int argc, char **argv,
  struct gengetopt_args_info *args_info);

/**
 * The command line parser (version with additional parameters - deprecated)
 * @param argc the number of command line options
 * @param argv the command line options
 * @param args_info the structure where option information will be stored
 * @param override whether to override possibly already present options
 * @param initialize whether to initialize the option structure my_args_info
 * @param check_required whether to check that all required options were provided
 * @return 0 if everything went fine, NON 0 if an error took place
 * @deprecated use cmdline_parser_ext() instead
 */
int cmdline_parser2 (int argc, char **argv,
  struct gengetopt_args_info *args_info,
  int override, int initialize, int check_required);

/**
 * The command line parser (version with additional parameters)
 * @param argc the number of command line options
 * @param argv the command line options
 * @param args_info the structure where option information will be stored
 * @param params additional parameters for the parser
 * @return 0 if everything went fine, NON 0 if an error took place
 */
int cmdline_parser_ext (int argc, char **argv,
  struct gengetopt_args_info *args_info,
  struct cmdline_parser_params *params);

/**
 * Save the contents of the option struct into an already open FILE stream.
 * @param outfile the stream where to dump options
 * @param args_info the option struct to dump
 * @return 0 if everything went fine, NON 0 if an error took place
 */
int cmdline_parser_dump(FILE *outfile,
  struct gengetopt_args_info *args_info);

/**
 * Save the contents of the option struct into a (text) file.
 * This file can be read by the config file parser (if generated by gengetopt)
 * @param filename the file where to save
 * @param args_info the option struct to save
 * @return 0 if everything went fine, NON 0 if an error took place
 */
int cmdline_parser_file_save(const char *filename,
  struct gengetopt_args_info *args_info);

/**
 * Print the help
 */
void cmdline_parser_print_help(void);
/**
 * Print the detailed help (including hidden options and details)
 */
void cmdline_parser_print_detailed_help(void);
/**
 * Print the version
 */
void cmdline_parser_print_version(void);

/**
 * Initializes all the fields a cmdline_parser_params structure 
 * to their default values
 * @param params the structure to initialize
 */
void cmdline_parser_params_init(struct cmdline_parser_params *params);

/**
 * Allocates dynamically a cmdline_parser_params structure and initializes
 * all its fields to their default values
 * @return the created and initialized cmdline_parser_params structure
 */
struct cmdline_parser_params *cmdline_parser_params_create(void);

/**
 * Initializes the passed gengetopt_args_info structure's fields
 * (also set default values for options that have a default)
 * @param args_info the structure to initialize
 */
void cmdline_parser_init (struct gengetopt_args_info *args_info);
/**
 * Deallocates the string fields of the gengetopt_args_info structure
 * (but does not deallocate the structure itself)
 * @param args_info the structure to deallocate
 */
void cmdline_parser_free (struct gengetopt_args_info *args_info);

/**
 * Checks that all the required options were specified
 * @param args_info the structure to check
 * @param prog_name the name of the program that will be used to print
 *   possible errors
 * @return
 */
int cmdline_parser_required (struct gengetopt_args_info *args_info,
  const char *prog_name);


#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /* CMDLINE_H */
