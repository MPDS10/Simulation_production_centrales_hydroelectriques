#include "dot.h"

#include <string.h>

// Templates
#define DOT_HEADER "digraph {\n"
#define DOT_NODE_STYLE_TEMPLATE "  node [shape=Mrecord, style=filled, "\
                                "fillcolor=%s, fontname=courier];\n"
#define DOT_FOOTER "}\n"

// Timeline templates
#define DOT_TIMELINE_START_TEMPLATE "  \"timeline\" "\
  "[label=\"{ Timeline | num-future-timesteps: %u | future-durations: ["
#define DOT_TIMELINE_END_TEMLATE "] }\"];\n"

// Link templates
#define DOT_LINK_TEMPLATE "  \"link_%s\" [label=\"{ Link %s }\"];\n"

// Plant templates
#define DOT_PLANT_START_TEMPLATE "  \"plant_%s\" "\
  "[label=\"{ Plant %s | min-powers: ["
#define DOT_PLANT_MIDDLE_TEMPLATE "] | max-powers: ["
#define DOT_PLANT_END_TEMPLATE "] }\"];\n"

// Zone templates
#define DOT_ZONE_START_TEMPLATE "  \"zone_%s\" "\
  "[label=\"{ Zone %s | expected-demands: ["
#define DOT_ZONE_END_TEMLATE "] }\"];\n"

// Arcs templates
#define DOT_ARC_LINK_ZONE_TEMPLATE "  \"link_%s\" -> \"zone_%s\";\n"
#define DOT_ARC_ZONE_LINK_TEMPLATE "  \"zone_%s\" -> \"link_%s\";\n"
#define DOT_ARC_PLANT_ZONE_TEMPLATE "  \"plant_%s\" -> \"zone_%s\";\n"

// Help functions
// --------------

/**
 * Creates a protected identifier from a non protected identifier
 *
 * More precisely, replace the special characters '<' and '>' respectively by
 * "&lt;" and "&gt;".
 *
 * Note: The function assumes that the size of the protected_id string is
 * sufficient to receive the protected string.
 *
 * @param protected_id  The resulting protected identifier
 * @param id            The non protected identifier
 */
void write_protected_id(char* protected_id, const char* id) {
  const char* s;
  char* t;
  for (s = id, t = protected_id; *s != '\0'; ++s) {
    if (*s == '<') {
      strncpy(t, "&lt;", 4);
      t += 4;
    } else if (*s == '>') {
      strncpy(t, "&gt;", 4);
      t += 4;
    } else {
      *t = *s;
      ++t;
    }
  }
  *t = '\0';
}

/**
 * Writes a DOT string representing a timeline
 *
 * @param timeline  The timeline to print
 */
void dot_print_timeline(const struct Timeline* timeline) {
  printf(DOT_NODE_STYLE_TEMPLATE, "bisque");
  printf(DOT_TIMELINE_START_TEMPLATE, timeline->num_future_timesteps);
  for (int t = 0; t < timeline->num_future_timesteps; ++t) {
    if (t > 0)
      printf(", ");
    printf("%d", timeline->future_durations[t]);
  }
  printf(DOT_TIMELINE_END_TEMLATE);
}

/**
 * Writes a DOT string representing a link
 *
 * @param link  The link to print
 */
void dot_print_link(const struct Link* link) {
  printf(DOT_NODE_STYLE_TEMPLATE, "orange");
  char protected_id[4 * ID_MAX_LENGTH + 1];
  write_protected_id(protected_id, link->id);
  printf(DOT_LINK_TEMPLATE, link->id, protected_id);
}

/**
 * Writes a DOT string representing a plant
 *
 * @param plant  The plant to print
 */
void dot_print_plant(const struct Plant* plant) {
  printf(DOT_NODE_STYLE_TEMPLATE, "palegreen");
  const char* id = plant->id;
  const struct Timeline* timeline = plant->timeline;
  printf(DOT_PLANT_START_TEMPLATE, id, id);
  for (int t = 0; t < timeline->num_future_timesteps; ++t) {
    if (t > 0)
      printf(", ");
    printf("%g", plant->min_powers[t]);
  }
  printf(DOT_PLANT_MIDDLE_TEMPLATE);
  for (int t = 0; t < timeline->num_future_timesteps; ++t) {
    if (t > 0)
      printf(", ");
    printf("%g", plant->max_powers[t]);
  }
  printf(DOT_PLANT_END_TEMPLATE);
}

/**
 * Writes a DOT string representing a zone
 *
 * @param zone  The zone to print
 */
void dot_print_zone(const struct Zone* zone) {
  printf(DOT_NODE_STYLE_TEMPLATE, "salmon");
  const char* id = zone->id;
  const struct Timeline* timeline = zone->timeline;
  printf(DOT_ZONE_START_TEMPLATE, id, id);
  for (int t = 0; t < timeline->num_future_timesteps; ++t) {
    if (t > 0)
      printf(", ");
    printf("%g", zone->expected_demands[t]);
  }
  printf(DOT_ZONE_END_TEMLATE);
}

/**
 * Writes a DOT string representing the relations between a link and its source
 * and target zones
 *
 * @param link  The link
 */
void dot_print_arcs_link_zones(const struct Link* link) {
  printf(DOT_ARC_ZONE_LINK_TEMPLATE, link->source->id, link->id);
  printf(DOT_ARC_LINK_ZONE_TEMPLATE, link->id, link->target->id);
}

/**
 * Writes a DOT string representing the relations between a plant and its zone
 *
 * @param plant  The plant
 */
void dot_print_arc_plant_zone(const struct Plant* plant) {
  puts("  edge [arrowhead=odiamond]");
  printf(DOT_ARC_PLANT_ZONE_TEMPLATE, plant->id, plant->zone->id);
}

// Implementation
// --------------

void dot_print_scenario(const struct Scenario* scenario) {
  printf(DOT_HEADER);
  dot_print_timeline(&scenario->timeline);
  for (int l = 0; l < scenario->num_links; ++l)
    dot_print_link(scenario->links + l);
  for (int p = 0; p < scenario->num_plants; ++p)
    dot_print_plant(scenario->plants + p);
  for (int z = 0; z < scenario->num_zones; ++z)
    dot_print_zone(scenario->zones + z);
  for (int l = 0; l < scenario->num_links; ++l)
    dot_print_arcs_link_zones(scenario->links + l);
  for (int p = 0; p < scenario->num_plants; ++p)
    dot_print_arc_plant_zone(scenario->plants + p);
  printf(DOT_FOOTER);
}
