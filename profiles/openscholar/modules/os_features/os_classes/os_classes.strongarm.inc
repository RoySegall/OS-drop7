<?php
// $Id$

/**
 * @file
 * os_classes.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function os_classes_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  /* Edit this to true to make a default strongarm disabled initially */


  $strongarm->disabled = FALSE;
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_anonymous_class';
  $strongarm->value = 0;
  $export['comment_anonymous_class'] = $strongarm;

  $strongarm = new stdClass();
  /* Edit this to true to make a default strongarm disabled initially */


  $strongarm->disabled = FALSE;
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_anonymous_class_material';
  $strongarm->value = 0;
  $export['comment_anonymous_class_material'] = $strongarm;

  $strongarm = new stdClass();
  /* Edit this to true to make a default strongarm disabled initially */


  $strongarm->disabled = FALSE;
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_class';
  $strongarm->value = '0';
  $export['comment_class'] = $strongarm;

  $strongarm = new stdClass();
  /* Edit this to true to make a default strongarm disabled initially */


  $strongarm->disabled = FALSE;
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_class_material';
  $strongarm->value = '0';
  $export['comment_class_material'] = $strongarm;

  $strongarm = new stdClass();
  /* Edit this to true to make a default strongarm disabled initially */


  $strongarm->disabled = FALSE;
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_default_mode_class';
  $strongarm->value = 1;
  $export['comment_default_mode_class'] = $strongarm;

  $strongarm = new stdClass();
  /* Edit this to true to make a default strongarm disabled initially */


  $strongarm->disabled = FALSE;
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_default_mode_class_material';
  $strongarm->value = 1;
  $export['comment_default_mode_class_material'] = $strongarm;

  $strongarm = new stdClass();
  /* Edit this to true to make a default strongarm disabled initially */


  $strongarm->disabled = FALSE;
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_default_per_page_class';
  $strongarm->value = '50';
  $export['comment_default_per_page_class'] = $strongarm;

  $strongarm = new stdClass();
  /* Edit this to true to make a default strongarm disabled initially */


  $strongarm->disabled = FALSE;
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_default_per_page_class_material';
  $strongarm->value = '50';
  $export['comment_default_per_page_class_material'] = $strongarm;

  $strongarm = new stdClass();
  /* Edit this to true to make a default strongarm disabled initially */


  $strongarm->disabled = FALSE;
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_form_location_class';
  $strongarm->value = 1;
  $export['comment_form_location_class'] = $strongarm;

  $strongarm = new stdClass();
  /* Edit this to true to make a default strongarm disabled initially */


  $strongarm->disabled = FALSE;
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_form_location_class_material';
  $strongarm->value = 1;
  $export['comment_form_location_class_material'] = $strongarm;

  $strongarm = new stdClass();
  /* Edit this to true to make a default strongarm disabled initially */


  $strongarm->disabled = FALSE;
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_preview_class';
  $strongarm->value = '1';
  $export['comment_preview_class'] = $strongarm;

  $strongarm = new stdClass();
  /* Edit this to true to make a default strongarm disabled initially */


  $strongarm->disabled = FALSE;
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_preview_class_material';
  $strongarm->value = '1';
  $export['comment_preview_class_material'] = $strongarm;

  $strongarm = new stdClass();
  /* Edit this to true to make a default strongarm disabled initially */


  $strongarm->disabled = FALSE;
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_subject_field_class';
  $strongarm->value = 1;
  $export['comment_subject_field_class'] = $strongarm;

  $strongarm = new stdClass();
  /* Edit this to true to make a default strongarm disabled initially */


  $strongarm->disabled = FALSE;
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_subject_field_class_material';
  $strongarm->value = 1;
  $export['comment_subject_field_class_material'] = $strongarm;

  $strongarm = new stdClass();
  /* Edit this to true to make a default strongarm disabled initially */


  $strongarm->disabled = FALSE;
  $strongarm->api_version = 1;
  $strongarm->name = 'menu_options_class';
  $strongarm->value = array(
    0 => 'main-menu',
  );
  $export['menu_options_class'] = $strongarm;

  $strongarm = new stdClass();
  /* Edit this to true to make a default strongarm disabled initially */


  $strongarm->disabled = FALSE;
  $strongarm->api_version = 1;
  $strongarm->name = 'menu_options_class_material';
  $strongarm->value = array(
    0 => 'main-menu',
  );
  $export['menu_options_class_material'] = $strongarm;

  $strongarm = new stdClass();
  /* Edit this to true to make a default strongarm disabled initially */


  $strongarm->disabled = FALSE;
  $strongarm->api_version = 1;
  $strongarm->name = 'menu_parent_class';
  $strongarm->value = 'main-menu:0';
  $export['menu_parent_class'] = $strongarm;

  $strongarm = new stdClass();
  /* Edit this to true to make a default strongarm disabled initially */


  $strongarm->disabled = FALSE;
  $strongarm->api_version = 1;
  $strongarm->name = 'menu_parent_class_material';
  $strongarm->value = 'main-menu:0';
  $export['menu_parent_class_material'] = $strongarm;

  $strongarm = new stdClass();
  /* Edit this to true to make a default strongarm disabled initially */


  $strongarm->disabled = FALSE;
  $strongarm->api_version = 1;
  $strongarm->name = 'node_options_class';
  $strongarm->value = array(
    0 => 'status',
  );
  $export['node_options_class'] = $strongarm;

  $strongarm = new stdClass();
  /* Edit this to true to make a default strongarm disabled initially */


  $strongarm->disabled = FALSE;
  $strongarm->api_version = 1;
  $strongarm->name = 'node_options_class_material';
  $strongarm->value = array(
    0 => 'status',
  );
  $export['node_options_class_material'] = $strongarm;

  $strongarm = new stdClass();
  /* Edit this to true to make a default strongarm disabled initially */


  $strongarm->disabled = FALSE;
  $strongarm->api_version = 1;
  $strongarm->name = 'node_preview_class';
  $strongarm->value = '0';
  $export['node_preview_class'] = $strongarm;

  $strongarm = new stdClass();
  /* Edit this to true to make a default strongarm disabled initially */


  $strongarm->disabled = FALSE;
  $strongarm->api_version = 1;
  $strongarm->name = 'node_preview_class_material';
  $strongarm->value = '0';
  $export['node_preview_class_material'] = $strongarm;

  $strongarm = new stdClass();
  /* Edit this to true to make a default strongarm disabled initially */


  $strongarm->disabled = FALSE;
  $strongarm->api_version = 1;
  $strongarm->name = 'node_submitted_class';
  $strongarm->value = 0;
  $export['node_submitted_class'] = $strongarm;

  $strongarm = new stdClass();
  /* Edit this to true to make a default strongarm disabled initially */


  $strongarm->disabled = FALSE;
  $strongarm->api_version = 1;
  $strongarm->name = 'node_submitted_class_material';
  $strongarm->value = 0;
  $export['node_submitted_class_material'] = $strongarm;

  $strongarm = new stdClass();
  /* Edit this to true to make a default strongarm disabled initially */


  $strongarm->disabled = FALSE;
  $strongarm->api_version = 1;
  $strongarm->name = 'pathauto_node_class_pattern';
  $strongarm->value = 'classes/[node:title]';
  $export['pathauto_node_class_pattern'] = $strongarm;

  $strongarm = new stdClass();
  /* Edit this to true to make a default strongarm disabled initially */


  $strongarm->disabled = FALSE;
  $strongarm->api_version = 1;
  $strongarm->name = 'pathauto_node_class_material_pattern';
  $strongarm->value = 'classes/[node:field_class]/materials/[node:title]';
  $export['pathauto_node_class_material_pattern'] = $strongarm;

  return $export;
}

