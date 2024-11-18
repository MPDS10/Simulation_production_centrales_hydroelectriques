#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <jansson.h>

#include "component/link.h"
#include "component/zone.h"
#include "dot.h"
#include "plan.h"
#include "scenario.h"
#include "timeline.h"
#include "unit.h"

// Usage
// -----

#define USAGE "NAME\n\
    simprod - simulate the energy production and transport through a network\n\
\n\
SYNOPSIS\n\
    simprod [target] [arguments] \n\
\n\
DESCRIPTION\n\
    Without argument, shows this help.\n\
\n\
    If the target is 'plan', the program displays information about a plan on\n\
    stdout. If no argument is provided, a plan on an empty scenario is used.\n\
    Otherwise, a valid JSON filepath can be provided, containing the plan to\n\
    be loaded.\n\
\n\
    If the target is 'scenario', the program displays information about a\n\
    scenario on stdout. If no argument is provided, an empty scenario is\n\
    used. Otherwise, a valid JSON filepath can be provided, containing the\n\
    scenario to be loaded. The option -t|--to can also be used to specify the\n\
    output format. Currently, only two formats are allowed: 'json' (the\n\
    default) and 'dot' (the Graphviz format).\n\
\n"

// Types
// -----

// The output format to use
enum OutputFormat {
  // The output format is JSON
  JSON_OUTPUT_FORMAT,
  // The output format is DOT
  DOT_OUTPUT_FORMAT,
};

// Errors
// ------

/**
 * Reports an error about an unrecognized target
 *
 * @param target  The provided target
 */
void report_error_non_recognized_target(const char* target) {
  fprintf(stderr, "Unrecognized target: %s\n", target);
  fprintf(stderr, USAGE);
}

/**
 * Reports an error about having passed too many arguments
 */
void report_error_too_many_arguments(const char* target) {
  fprintf(stderr, "Too many arguments for target '%s'\n", target);
  fprintf(stderr, USAGE);
}

/**
 * Reports an error about loading a JSON value from a file
 *
 * @param error  The error found by Jansson
 */
void report_error_loading_json_from_file(json_error_t error) {
  fprintf(stderr, "Problem while loading JSON file: %s\n", error.text);
}

// Help functions
// --------------

bool uses_option_t(int argc, char** argv, int i) {
  return argc >= i + 1 &&
         (strcmp(argv[i], "-t") == 0 || strcmp(argv[i], "--to") == 0);
}

enum OutputFormat get_output_format(int argc, char** argv) {
  if (argc <= 2)
    return JSON_OUTPUT_FORMAT;
  if (uses_option_t(argc, argv, argc - 2))
    return strcmp(argv[argc - 1], "dot") == 0 ?
      DOT_OUTPUT_FORMAT : JSON_OUTPUT_FORMAT;
}

const char* get_input_filename(int argc, char** argv) {
  if (uses_option_t(argc, argv, 2))
    return argc <= 4 ? NULL : argv[4];
  else
    return argv[2];
}

// Targets
// -------

/**
 * Indicates if the given target is supported
 *
 * @param target  The invoked target
 * @return        true if and only if the target is supported
 */
bool is_target_supported(const char* target) {
  return strcmp(target, "scenario") == 0 ||
         strcmp(target, "plan") == 0;
}

/**
 * Processes the 'plan' target
 */
void process_plan_target(int argc, char* argv[]) {
  if (argc >= 4) {
    report_error_too_many_arguments("plan");
    exit(1);
  }

  json_t* json_output;
  struct Plan plan;
  if (argc == 2) {
    struct Timeline timeline;
    timeline_initialize(&timeline, 0, NULL);
    plan_initialize(&plan, &timeline);
    timeline_free(&timeline);
    json_output = plan_to_json(&plan);
  } else {
    const char* input_filename = argv[2];
    json_error_t error;
    json_t* json_input = json_load_file(input_filename, 0, &error);
    if (!json_input) {
      report_error_loading_json_from_file(error);
      exit(1);
    }
    plan_from_json(&plan, json_input);
    json_decref(json_input);
    json_output = plan_to_json(&plan);
  }
  json_dumpf(json_output, stdout, JSON_INDENT(2));
  printf("\n");
  json_decref(json_output);
  plan_free(&plan);
}

/**
 * Processes the 'scenario' target
 *
 * @param argc  The number of application arguments
 * @param argv  The application arguments
 */
void process_scenario_target(int argc, char* argv[]) {
  if (argc >= 6) {
    report_error_too_many_arguments("scenario");
    exit(1);
  }

  struct Scenario scenario;
  const char* input_filename = get_input_filename(argc, argv);
  if (input_filename == NULL) {
    struct Timeline timeline;
    timeline_initialize(&timeline, 0, NULL);
    scenario_initialize(&scenario, &timeline);
    timeline_free(&timeline);
  } else {
    const char* input_filename = argv[2];
    json_error_t error;
    json_t* json_input = json_load_file(input_filename, 0, &error);
    if (!json_input) {
      report_error_loading_json_from_file(error);
      exit(1);
    }
    scenario_from_json(&scenario, json_input);
    json_decref(json_input);
  }

  enum OutputFormat of = get_output_format(argc, argv);
  if (of == JSON_OUTPUT_FORMAT) {
    json_t* json_output = scenario_to_json(&scenario);
    json_dumpf(json_output, stdout, JSON_INDENT(2));
    printf("\n");
    json_decref(json_output);
  } else {
    dot_print_scenario(&scenario);
  }
  scenario_free(&scenario);
}

// Main
// ----

int main(int argc, char* argv[]) {
  if (argc == 1) {
    printf(USAGE);
    exit(0);
  } else if (!is_target_supported(argv[1])) {
    report_error_non_recognized_target(argv[1]);
    exit(1);
  }

  if (strcmp(argv[1], "plan") == 0)
    process_plan_target(argc, argv);
  else if (strcmp(argv[1], "scenario") == 0)
    process_scenario_target(argc, argv);
  return 0;
}
